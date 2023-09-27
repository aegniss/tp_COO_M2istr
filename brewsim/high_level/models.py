from django.db import models

# Create your models here.
class Departement (models.Model):
    numero=models.IntegerField()
    prix_m2=models.IntegerField()
    def __str__(self):
        return self.Departement

class Ingredient (models.Model):
    nom=models.CharField(max_length=100)
        def __str__(self):
            return self.nom

class Prix (models.Model):
    ingredient =models.ForeignKey(
        Ingredient,
        on_delete=models.PROTECT,
        # blank=True, null=True,
        # related_name="+",
        )
    def __str__(self):
        return self.ingredient

    departement =models.ForeignKey(
        Departement,
        on_delete=models.PROTECT,
        # blank=True, null=True,
        # related_name="+",
        )
    def __str__(self):
        return self.departement

    prix=models.IntegerField()

    def __str__(self):
        return self.prix

class QuantiteIngredient (models.Model):
    ingredient =models.ForeignKey(
        Ingredient,
        on_delete=models.PROTECT,
        blank=True, null=True,
        # related_name="+",
        )
    def __str__(self):
        return self.ingredient

    quantite =models.IntegerField()
        def __str__(self):
            return self.quantite


class Machine(models.Model):
    nom=models.CharField(max_length=100)
        def __str__(self):
            return self.nom

    prix=models.IntegerField()
        def __str__(self):
            return self.prix



class Action(models.Model):
    machine =models.ForeignKey(
        Machine,
        on_delete=models.PROTECT,
        # blank=True, null=True,
        # related_name="+",
        )
            def __str__(self):
                return self.machine

    commande=models.CharField(max_length=100)
            def __str__(self):
                return self.commande

    duree=models.IntegerField()
            def __str__(self):
                return self.duree

    ingredients = models.ManyToManyField(QuantiteIngredient)
                def __str__(self):
                    return self.ingredients

    action=models.ForeignKey(
        "self",
        on_delete=models.PROTECT,
         blank=True, null=True,
         related_name="+",
        )

        def __str__(self):
            return self.action

class Recette (models.Model):
    nom=models.CharField(max_length=100)
                def __str__(self):
                    return self.nom

    action =models.ForeignKey(
        Action,
        on_delete=models.PROTECT,
        # blank=True, null=True,
        # related_name="+",
        )
                def __str__(self):
                    return self.action




class Usine (models.Model):
    departement =models.ForeignKey(
        Departement,
        on_delete=models.PROTECT,
        # blank=True, null=True,
        # related_name="+",
        )
            def __str__(self):
                    return self.departement

    taille=models.IntegerField()
                    def __str__(self):
                        return self.taille

    machines=models.ManyToManyField(Machine)
                def __str__(self):
                    return self.machines

    recettes=models.ManyToManyField(Recette)
                def __str__(self):
                    return self.recettes

    stocks=models.ManyToManyField(QuantiteIngredient)
                def __str__(self):
                    return self.stocks
