from django.db import models
import os
from subprocess import call
# Create your models here.


class Route(models.Model):

    begin_point = models.CharField(max_length=100)
    end_point = models.CharField(max_length=100)
    begin_point_lat = models.CharField(max_length=30)
    begin_point_lng = models.CharField(max_length=30)
    end_point_lat = models.CharField(max_length=30)
    end_point_lng = models.CharField(max_length=30)
    duration = models.CharField(max_length=50)

    def save_in_file(self):
        with open("route_generator/user_input.txt", "w") as output:
            output.write(self.begin_point + "\n" + self.end_point + "\n" + self.duration)
        os.system("cd route_generator/ && python3 -u charge_station_api_parser.py && ./main && cd ..")
        self.save()

    def __str__(self):
        return self.begin_point + " " + self.end_point + " " + self.duration