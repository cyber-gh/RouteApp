from django.shortcuts import render, redirect
from .forms import RouteForm
from .models import Route
import json

# Create your views here.


def input_form(request):
    if request.method == "POST":
        form = RouteForm(request.POST, RouteForm)
        if form.is_valid():
            route = form.save()
            route.save_in_file()
            route.save()
            return redirect("display_map")
    else:
        form = RouteForm()
    return render(request, 'input_form.html', {'form': form})

def display_map(request):
    with open("route_generator/final_output.txt","r") as input:
        content = input.readlines()
        content = [x.strip() for x in content]
    content = "/".join(content)
    print(content)
    return render(request,"map_display.html", {"form": content})