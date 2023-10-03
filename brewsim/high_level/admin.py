# mysite/admin.py
from django.contrib import admin
from high_level import models

# Register your models here.


admin.site.register(models.Usine)
admin.site.register(models.Departement)
admin.site.register(models.Recette)
admin.site.register(models.Action)
admin.site.register(models.Machine)
admin.site.register(models.Ingredient)
admin.site.register(models.Prix)
admin.site.register(models.QuantiteIngredient)
