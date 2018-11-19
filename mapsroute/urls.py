from django.urls import path
from . import views

urlpatterns = [
    path('', views.input_form, name="input_form"),
    path("display_map", views.display_map, name="display_map")

]