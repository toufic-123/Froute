from flask import Flask, request, jsonify, render_template
import googlemaps
import geocoder
import random
import re

app = Flask(__name__)

API_KEY = "YOUR_GOOGLE_MAPS_API_KEY"
map_client = googlemaps.Client(API_KEY)

def get_my_location():
    g = geocoder.ip('me')
    location = (g.latlng[0], g.latlng[1])
    return location

def get_surrounding_locations(location, search_string, distance):
    response = map_client.places_nearby(
        location=location,
        keyword=search_string,
        radius=distance
    )
    return response

def get_random_location(business_list):
    rand = random.randint(0, len(business_list)-1)
    return business_list[rand]

def get_directions(origin, destination):
    directions = map_client.directions(
        origin=origin,
        destination=f"place_id:{destination}",
        mode='walking'
    )
    return directions

def parse_json(json):
    parsed_steps = []
    leg = json[0].get('legs')[0]
    steps = leg.get('steps')
    for step in steps:
        pattern = re.compile(r'<.*?>')
        cleaned_text = re.sub(pattern, '', step.get('html_instructions'))
        parsed_steps.append(
            {
                "distance": step.get('distance'),
                "html_instructions": cleaned_text,
                "maneuver": step.get('maneuver')
            }
        )
    return parsed_steps

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/get-directions', methods=['POST'])
def get_directions_route():
    location = get_my_location()
    search_string = request.json.get('search_string', 'restaurant')
    distance = request.json.get('distance', 1000)

    response = get_surrounding_locations(location, search_string, distance)
    business_list = response.get('results', [])
    
    if not business_list:
        return jsonify({"error": "No businesses found"}), 404

    rand_location = get_random_location(business_list)
    directions = get_directions(location, rand_location.get('place_id'))
    parsed_steps = parse_json(directions)

    return jsonify({
        "parsed_json": parsed_steps,
        "location_name": rand_location.get('name')
    })

if __name__ == "__main__":
    app.run(debug=True)
