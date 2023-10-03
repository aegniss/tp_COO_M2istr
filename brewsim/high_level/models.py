from django.db import models


# Create your models here.
class Departement(models.Model):
    numero = models.IntegerField()
    prix_m2 = models.IntegerField()

    def __str__(self):
        return f"{self.numero}"


class Ingredient(models.Model):
    nom = models.CharField(max_length=100)

    def __str__(self):
        return f" ingredient : {self.nom}"


class Prix(models.Model):
    ingredient = models.ForeignKey(
        Ingredient,
        on_delete=models.PROTECT,
        # blank=True, null=True,
        # related_name="+",
    )

    departement = models.ForeignKey(
        Departement,
        on_delete=models.PROTECT,
        # blank=True, null=True,
        # related_name="+",
    )

    prix = models.IntegerField()

    def __str__(self):
        return (
            f" prix {self.ingredient}"
            f" dans le {self.departement} = {self.prix} "
        )


class QuantiteIngredient(models.Model):
    ingredient = models.ForeignKey(
        Ingredient,
        on_delete=models.PROTECT,
        blank=True,
        null=True,
        # related_name="+",
    )

    def __str__(self):
        return f" quantite {self.ingredient} est : {self.quantite}"

    quantite = models.IntegerField()


class Machine(models.Model):
    nom = models.CharField(max_length=100)

    prix = models.IntegerField()

    def __str__(self):
        return f"machine {self.nom}"  # coute {self.prix}



class Action(models.Model):
    machine = models.ForeignKey(
        Machine,
        on_delete=models.PROTECT,
        # blank=True, null=True,
        # related_name="+",
    )

    commande = models.CharField(max_length=100)

    duree = models.IntegerField()

    ingredients = models.ManyToManyField(QuantiteIngredient)

    action = models.ForeignKey(
        "self",
        on_delete=models.PROTECT,
        blank=True,
        null=True,
        related_name="+",
    )

    def __str__(self):
        return f"Action machine {self.machine} avec commande {self.commande}"




class Recette(models.Model):
    nom = models.CharField(max_length=100)

    def __str__(self):
        return f" Recette : {self.nom}"

    action = models.ForeignKey(
        Action,
        on_delete=models.PROTECT,
        # blank=True, null=True,
        # related_name="+",
    )


class Usine(models.Model):
    departement = models.ForeignKey(
        Departement,
        on_delete=models.PROTECT,
        # blank=True, null=True,
        # related_name="+",
    )

    def __str__(self):
        return f"Usine du {self.departement}"

    taille = models.IntegerField()

    machines = models.ManyToManyField(Machine)

    recettes = models.ManyToManyField(Recette)

    stocks = models.ManyToManyField(QuantiteIngredient)
