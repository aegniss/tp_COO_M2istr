from django.db import models

# Create your models here.
class Departement (models.Model):
    numero=models.IntegerField()
    prix_m2=models.IntegerField()

class Ingredient (models.Model):
    nom=models.CharField(max_length=100)

class Prix (models.Model):
    ingredient =models.ForeignKey(
        Ingredient,
        on_delete=models.PROTECT,
        # blank=True, null=True,
        # related_name="+",
        )

    departement =models.ForeignKey(
        Departement,
        on_delete=models.PROTECT,
        # blank=True, null=True,
        # related_name="+",
        )

    prix=models.IntegerField()


class QuantiteIngredient (models.Model):
    ingredient =models.ForeignKey(
        Ingredient,
        on_delete=models.PROTECT,
        # blank=True, null=True,
        # related_name="+",
        )

    quantite =models.IntegerField()

class Machine(models.Model):
    nom=models.CharField(max_length=100)
    prix=models.IntegerField()



class Action(models.Model):
    machine =models.ForeignKey(
        Machine,
        on_delete=models.PROTECT,
        # blank=True, null=True,
        # related_name="+",
        )

    commande=models.CharField(max_length=100)

    duree=models.IntegerField()

    ingredients = models.ManyToManyField(QuantiteIngredient)

    action=models.ForeignKey(
        "self",
        on_delete=models.PROTECT,
         blank=True, null=True,
         related_name="+",
        )



class Recette (models.Model):
    nom=models.CharField(max_length=100)
    action =models.ForeignKey(
        Action,
        on_delete=models.PROTECT,
        # blank=True, null=True,
        # related_name="+",
        )





class Usine (models.Model):
    departement =models.ForeignKey(
        Departement,
        on_delete=models.PROTECT,
        # blank=True, null=True,
        # related_name="+",
        )

    taille=models.IntegerField()

    machines=models.ManyToManyField(Machine)

    recettes=models.ManyToManyField(Recette)

    stocks=models.ManyToManyField(QuantiteIngredient)
