from geopy.geocoders import Nominatim
import json
geolocator = Nominatim(user_agent="Test applicatiion")
query = dict()
#query["country"] = "Romania"
query["tourism"] = "attraction"
location = geolocator.geocode(query, language='en')
if location != None:
    print (json.dumps(location.raw, indent=4))
    print (location.address)
else:
    print ("No location!" , location)