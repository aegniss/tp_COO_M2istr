from json import dumps

from django.http import HttpResponse
from django.views.generic.detail import DetailView
#from rest_framework.views import APIView

from .models import (
    Action,
    Departement,
    Ingredient,
    Machine,
    Prix,
    QuantiteIngredient,
    Recette,
    Usine,
)


class DepartementDetailView(DetailView):
    model = Departement

    def render_to_response(self, context, **response_kwargs):
        return HttpResponse(dumps(self.object.json()))


class DepartementDetailAPIView(DetailView):
    model = Departement

    def render_to_response(self, context, **response_kwargs):
        return HttpResponse(dumps(self.object.json_extended()))


class IngredientDetailView(DetailView):
    model = Ingredient

    def render_to_response(self, context, **response_kwargs):
        return HttpResponse(dumps(self.object.json()))




class ActionDetailView(DetailView):
    model = Action

    def render_to_response(self, context, **response_kwargs):
        return HttpResponse(dumps(self.object.json()))



class PrixDetailView(DetailView):
    model = Prix

    def render_to_response(self, context, **response_kwargs):
        return HttpResponse(dumps(self.object.json()))




class MachineDetailView(DetailView):
    model = Machine

    def render_to_response(self, context, **response_kwargs):
        return HttpResponse(dumps(self.object.json()))



class RecetteDetailView(DetailView):
    model = Recette

    def render_to_response(self, context, **response_kwargs):
        return HttpResponse(dumps(self.object.json()))



class UsineDetailView(DetailView):
    model = Usine

    def render_to_response(self, context, **response_kwargs):
        return HttpResponse(dumps(self.object.json()))




class QuantiteIngredientDetailView(DetailView):
    model = QuantiteIngredient

    def render_to_response(self, context, **response_kwargs):
        return HttpResponse(dumps(self.object.json()))
