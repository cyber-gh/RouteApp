import json
import requests
import operator
import polyline
import urllib.parse
from geopy.geocoders import Nominatim

class Station(object):
    def __init__(self, nr, id, stype, title, address, latitutde, longitude):
        self.nr = nr
        self.id = id
        self.stype = stype
        self.title = title.replace(" ","_")
        self.address = address.replace(" ","_")
        self.latitude = latitutde
        self.longitude = longitude
        return super(Station, self).__init__()
    def __str__(self):
        return str(self.nr) + str(" ") + str(self.id) + str(" ") + str(self.stype) + str(" ") + str(self.title) + str(" ") + str(self.address) + str(" ") \
            + str(self.latitude) + str(" ") + str(self.longitude) 

response = requests.get("https://api.openchargemap.io/v2/poi/?countrycode=RO")
json_raw = response.content
json_parsed = json.loads(json_raw)
nr = 0
charge_station_list = list()
for el in json_parsed:
    id = el["ID"]
    title = el["AddressInfo"]["Title"]
    address = el["AddressInfo"]["AddressLine1"]
    latitude = el["AddressInfo"]["Latitude"]
    longitude = el["AddressInfo"]["Longitude"]
    nr += 1
    charge_station_list.append(Station(nr,id, "charge", title, address, latitude, longitude))

output = open("charge_stations.txt", "w")
#proxies_input = open("char")
#response = requests.get("http://router.project-osrm.org/route/v1/driving/") # add ?overview=false


for el in charge_station_list:
    output.write(str(el) + "\n")
# print(json_parsed)

tourism_stations = list()


with open('tourism.json', 'r') as f:
    temp = json.load(f)

#print(temp)
nr -= 1
for el in temp["results"]:
    id = el["id"]
    name = el["name"]
    address = el["formatted_address"]
    latitude = el["geometry"]["location"]["lat"]
    longitude = el["geometry"]["location"]["lng"]
    nr += 1
    tourism_stations.append(Station(nr,id,"attracion",name,address,latitude,longitude))
    
with open('tourism1.json', 'r') as f:
    temp = json.load(f)

#print(temp)
nr -= 1
for el in temp["results"]:
    id = el["id"]
    name = el["name"]
    address = el["formatted_address"]
    latitude = el["geometry"]["location"]["lat"]
    longitude = el["geometry"]["location"]["lng"]
    nr += 1
    tourism_stations.append(Station(nr,id,"attracion",name,address,latitude,longitude))
    

with open('tourism2.json', 'r') as f:
    temp = json.load(f)

#print(temp)

for el in temp["results"]:
    id = el["id"]
    name = el["name"]
    address = el["formatted_address"]
    latitude = el["geometry"]["location"]["lat"]
    longitude = el["geometry"]["location"]["lng"]
    nr += 1
    tourism_stations.append(Station(nr,id,"attracion",name,address,latitude,longitude))
    

with open('tourism3.json', 'r') as f:
    temp = json.load(f)

#print(temp)

for el in temp["results"]:
    id = el["id"]
    name = el["name"]
    address = el["formatted_address"]
    latitude = el["geometry"]["location"]["lat"]
    longitude = el["geometry"]["location"]["lng"]
    nr += 1
    tourism_stations.append(Station(nr,id,"attracion",name,address,latitude,longitude))
    


tourism_stations = list(set(tourism_stations))
joined_list = charge_station_list + tourism_stations
for i in range(len(joined_list)):
    for j in range(i,len(joined_list)):
        if (joined_list[i].nr > joined_list[j].nr):
            temp = joined_list[i]
            joined_list[i] = joined_list[j]
            joined_list[j] = temp

output = open("data1.txt", "w")
raw_coord = list()
raw_string_coord = ""
k = 0
for el in joined_list:
    raw_coord.append((el.latitude, el.longitude))
    if k < 20:
        raw_string_coord += str(el.latitude) + "," + str(el.longitude) + ";"
    output.write(str(el) + "\n")
    k += 1

raw_string_coord = raw_string_coord[:-1]
#polyline_encoded = polyline.encode(raw_coord, 5)

request_distance_matrix = "http://router.project-osrm.org/route/v1/driving/"
request_distance_matrix += raw_string_coord
request_distance_matrix += "?overview=false"
#print(request_distance_matrix)

with open("user_input.txt", "r") as input1:
    #temp_error_file = open("error.txt", "w")
    content_list_input = input1.readlines()
    content_list_input = [x.strip() for x in content_list_input] 
    #temp_error_file.write(str(content_list_input))
    begin_point = content_list_input[0]
    end_point = content_list_input[1]
    duration = float(content_list_input[2])
    geolocator = Nominatim(user_agent="HackItAll")
    address_begin_point, (latitude_begin, longitude_begin) = geolocator.geocode(begin_point)
    print(address_begin_point, latitude_begin, longitude_begin)
    address_end_point, (latitude_end, longitude_end) = geolocator.geocode(end_point)
    print(address_end_point, latitude_end, longitude_end)
    address_begin_point = address_begin_point.replace(" ","_")
    address_end_point = address_end_point.replace(" ","_")
    with open("user_parsed_input.txt", "w") as output:
        output.write(begin_point + "\n")
        output.write(str(latitude_begin) + " " + str(longitude_begin) + "\n")
        output.write(end_point + "\n")
        output.write(str(latitude_end) + " " + str(longitude_end) + "\n")
        output.write(str(duration))

exit

GOOGLE_API_KEY = "AIzaSyAGDcYNGISAiM_jwy_bWsgU1efQZwi1vRc"
# print((raw_coord))
request_distance_matrix = "https://maps.googleapis.com/maps/api/distancematrix/json?origins="
request_distance_matrix += raw_string_coord#urllib.parse.quote(polyline_encoded)
request_distance_matrix += "&destinations="
request_distance_matrix += raw_string_coord#urllib.parse.quote_plus(polyline_encoded)
request_distance_matrix += "&key="
request_distance_matrix += GOOGLE_API_KEY
#print(request_distance_matrix)
response = requests.get(request_distance_matrix)
json_raw = response.content
json_parsed = json.loads(json_raw)



#print(json_parsed)
#print(len(polyline_encoded))
#test = "kjwFjtsbMt%60EgnKcqLcaOzkGari%40naPxhVg%7CJjjb%40cqLcaOzkGari%40naPxhV"
#print(polyline.decode(test))
#print(polyline.decode((polyline_encoded)))
# https://maps.googleapis.com/maps/api/distancematrix/json?units=imperial&origins=40.6655101,-73.89188969999998&destinations=enc:_



