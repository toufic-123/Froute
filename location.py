import googlemaps
import geocoder
import random
from pprint import pprint
API_KEY = "AIzaSyDqrIC47PIDREpzX_f-wdtY6ISPtqDPhA0"
map_client = googlemaps.Client(API_KEY)


def get_my_location():
    g = geocoder.ip('me')
    location = (g.latlng[0], g.latlng[1])
    return location

def get_surrounding_locations(location, search_string,distance):
    response = map_client.places_nearby(
        location=location,
        keyword=search_string,
        name='place',
        radius=distance
    )
    return response

def get_random_location(business_list):
    rand = random.randint(0, len(business_list))
    return business_list[rand]

def main():

    location = get_my_location()
    search_string = 'restaurant'
    distance = 1000
    business_list = []

    response = get_surrounding_locations(location, search_string, distance)

    business_list.extend(response.get('results'))


    #pprint(business_list)
    pprint(get_random_location(business_list))


main()