"""
URL configuration for brewsim project.

The `urlpatterns` list routes URLs to views. For more information please see:
    https://docs.djangoproject.com/en/4.2/topics/http/urls/
Examples:
Function views
    1. Add an import:  from my_app import views
    2. Add a URL to urlpatterns:  path('', views.home, name='home')
Class-based views
    1. Add an import:  from other_app.views import Home
    2. Add a URL to urlpatterns:  path('', Home.as_view(), name='home')
Including another URLconf
    1. Import the include() function: from django.urls import include, path
    2. Add a URL to urlpatterns:  path('blog/', include('blog.urls'))
"""
from django.contrib import admin
from django.urls import path
from high_level import views

urlpatterns = [
    path("admin/", admin.site.urls),
    path(
        "Departement/<int:pk>",
        views.DepartementDetailView.as_view(),
        name="Departement",
    ),
    path(
        "Recette/<int:pk>",
        views.RecetteDetailView.as_view(),
        name="Recette",
    ),
    path(
        "Ingredient/<int:pk>",
        views.IngredientDetailView.as_view(),
        name="Ingredient",
    ),
    path(
        "Machine/<int:pk>",
        views.MachineDetailView.as_view(),
        name="Machine",
    ),
    path(
        "QuantiteIngredient/<int:pk>",
        views.QuantiteIngredientDetailView.as_view(),
        name="QuantiteIngredient",
    ),
    path(
        "Usine/<int:pk>",
        views.UsineDetailView.as_view(),
        name="Usine",
    ),
    path(
        "Action/<int:pk>",
        views.ActionDetailView.as_view(),
        name="Action",
    ),
    path(
        "Prix/<int:pk>",
        views.PrixDetailView.as_view(),
        name="Prix",
    ),

    path(
        "Departement/api/<int:pk>",
        views.DepartementDetailView.as_view(),
        name="Departement",
    ),
    path(
        "Recette/api/<int:pk>",
        views.RecetteDetailView.as_view(),
        name="Recette",
    ),
    path(
        "Ingredient/api/<int:pk>",
        views.IngredientDetailView.as_view(),
        name="Ingredient",
    ),
    path(
        "Machine/api/<int:pk>",
        views.MachineDetailView.as_view(),
        name="Machine",
    ),
    path(
        "QuantiteIngredient/api/<int:pk>",
        views.QuantiteIngredientDetailView.as_view(),
        name="QuantiteIngredient",
    ),
    path(
        "Usine/api/<int:pk>",
        views.UsineDetailView.as_view(),
        name="Usine",
    ),
    path(
        "Action/api/<int:pk>",
        views.ActionDetailView.as_view(),
        name="Action",
    ),
    path(
        "Prix/api/<int:pk>",
        views.PrixDetailView.as_view(),
        name="Prix",
    ),
]
