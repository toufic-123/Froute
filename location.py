import googlemaps
import geocoder
import random
import urllib.request
import json
from pprint import pprint

import time

import re



API_KEY = "AIzaSyDqrIC47PIDREpzX_f-wdtY6ISPtqDPhA0"
map_client = googlemaps.Client(API_KEY)
directions_endpoint = "https://maps.googleapis.com/maps/api/directions/json?"
geocode_endpoint = "https://maps.googleapis.com/maps/api/geocode/json?"


def get_my_location():
    g = geocoder.ip('me')
    location = (g.latlng[0], g.latlng[1])
    return location

def get_my_location_place_id(myLocation):
    # PROBABY NOT NEEDED
    gmap_location = map_client.reverse_geocode(
        latlng=myLocation
    )

    #print(gmap_location.get('place_id'))

def get_surrounding_locations(location, search_string,distance):
    response = map_client.places_nearby(
        location=location,
        keyword=search_string,
        name='place',
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
    print(json[0])
    leg = json[0].get('legs')[0]
    steps = leg.get('steps')
    for step in steps:

        # Define a regular expression pattern to match HTML tags
        pattern = re.compile(r'<.*?>')

        # Use the pattern to replace HTML tags with an empty string
        cleaned_text = re.sub(pattern, '', step.get('html_instructions'))
                      
        parsed_steps.append(
            {
                "distance":step.get('distance'),
                "html_instructions": cleaned_text,
                "maneuver":step.get('maneuver')
            }
        )

    return parsed_steps

def main():

    location = get_my_location()
    search_string = 'restaurant'
    distance = 1000
    business_list = []

    response = get_surrounding_locations(location, search_string, distance)

    business_list.extend(response.get('results'))


    rand_location = get_random_location(business_list)

    # get_my_location_place_id(location) <- shitty bad code
    directions = get_directions(location, rand_location.get('place_id'))

    parsed_steps = parse_json(directions)

    json_response = {
        "parsed_json": parsed_steps,
        "location_name": rand_location.get('name')
        }

    # pprint(json_response)

    return json_response

    # send json with steps and name of location

if __name__ == "__main__":
    main()