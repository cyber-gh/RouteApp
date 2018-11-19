from django import forms
from .models import Route


class RouteForm(forms.ModelForm):
    class Meta:
        model = Route
        fields = ("begin_point", "end_point", "duration")
