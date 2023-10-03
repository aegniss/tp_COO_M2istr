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
        return f" prix {self.ingredient}"
        f" dans le {self.departement} = {self.prix} "


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

    def costs(self, departement, Usine):
        cost_qi = (
            self.ingredient.prix_set.get(departement__numero=Usine.departement.numero).prix) * self.quantite
        return cost_qi


class Machine(models.Model):
    nom = models.CharField(max_length=100)

    prix = models.IntegerField()

    def __str__(self):
        return f"machine {self.nom}"  # coute {self.prix}

    def costs(self):
        cost_M = self.prix
        return cost_M


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
        return f"Action {self.machine} avec commande {self.commande}"


class Recette(models.Model):
    nom = models.CharField(max_length=100)

    def __str__(self):
        return f" Recette : {self.nom}"

    action = models.ForeignKey(
        Action,
        on_delete=models.PROTECT,
        # blank=True, null=True,
        # related_name="+",
    )  #


class Usine(models.Model):
    departement = models.ForeignKey(
        Departement,
        on_delete=models.PROTECT,
        # blank=True, null=True,
        # related_name="+",
    )  #

    def __str__(self):
        return f"Usine du {self.departement.numero}"

    taille = models.IntegerField()

    machines = models.ManyToManyField(Machine)

    recettes = models.ManyToManyField(Recette)

    stocks = models.ManyToManyField(QuantiteIngredient)

    def costs(self):
        self.machines.all()
        T = 0
        for m in self.machines.all():
            T += m.prix

        self.stocks.all()
        S = 0
        for si in self.stocks.all():
            S += si.costs(self.departement.numero, self)

        cost_U = (self.departement.prix_m2 * self.taille) + T + S
        return cost_U
