from django.db import models


# Create your models here.
class Departement(models.Model):
    numero = models.IntegerField()
    prix_m2 = models.IntegerField()

    def __str__(self):
        return f"{self.numero}"

    def json(self):
        return {"numero": self.numero, "prix_m2": self.prix_m2}

    def json_extended(self):
        return {
            "numero": self.numero,
            "prix_m2 ": self.prix_m2,
            # "Usine": self.usine_set.get().json_extended(),
            # "prix": [
            #   p.json_extended()
            #  for p in self.prix_set.all()
            # # {
            # #  http://localhost:8000/Departement/api/1  "ingredient": self.ingredient_set.all(),
            # #    "prix": Ingredient.prix_set.all(),
            # # }
            #  ],
        }


class Ingredient(models.Model):
    nom = models.CharField(max_length=100)

    def __str__(self):
        return f" ingredient : {self.nom}"

    def json(self):
        return {"ingredient": self.nom}

    def json_extended(self):
        return {"ingredient": self.nom}


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
            f" ingredient : {self.ingredient} dep {self.departement} prix {self.prix} "
        )

    def json(self):
        return {
            " ingredient ": self.ingredient.id,
            # "dep": self.departement,
            " prix ": self.prix,
        }

    def json_extended(self):
        return {
            "ingredient ": self.ingredient.json_extended(),
            # "dep": self.departement.json_extended(),
            "prix": self.prix,
        }


class QuantiteIngredient(models.Model):
    ingredient = models.ForeignKey(
        Ingredient,
        on_delete=models.PROTECT,
        blank=True,
        null=True,
        # related_name="+",
    )

    quantite = models.IntegerField()

    def __str__(self):
        return f"quantite {self.ingredient} est : {self.quantite}"

    def json(self):
        return {
            "ingredient ": self.ingredient.nom,
            "quantite": self.quantite,
        }

    def json_extended(self):
        return {
            "ingredient ": self.ingredient.json_extended(),
            "quantite": self.quantite,
        }

    def costs(self, departement):
        cost_qi = (
            self.ingredient.prix_set.get(departement__numero=departement).prix
        ) * self.quantite
        return cost_qi


class Machine(models.Model):
    nom = models.CharField(max_length=100)

    prix = models.IntegerField()

    def __str__(self):
        return f"machine {self.nom}"  # coute {self.prix}

    def json(self):
        return {"machine": self.nom, "prix": self.prix}  # coute {self.prix}

    def json_extended(self):
        return {"machine": self.nom, "prix": self.prix}

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
        return f"Machine {self.machine} avec commande {self.commande}"

    def json(self):
        T = []
        for m in self.ingredients.all():
            T.append(m.ingredient.nom)

        return {
            "Machine": self.machine.nom,
            "commande": self.commande,
            "duree": self.duree,
            "ingredients": T,
        }

    def json_extended(self):
        T = []
        for m in self.ingredients.all():
            T.append(m.json_extended())

        return {
            "Machine": self.machine.json_extended(),
            "commande": self.commande,
            "duree": self.duree,
            "ingredients": T,
        }


class Recette(models.Model):
    nom = models.CharField(max_length=100)

    action = models.ForeignKey(
        Action,
        on_delete=models.PROTECT,
        # blank=True, null=True,serializable
        # related_name="+",
    )

    def __str__(self):
        return f" Recette : {self.nom} avec action_id {self.action.id}"

    def json(self):
        return {"Recette": self.nom, "action_id": self.action.id}

    def json_extended(self):
        return {"Recette": self.nom, "action_id": self.action.id}


class Usine(models.Model):
    departement = models.ForeignKey(
        Departement,
        on_delete=models.PROTECT,
        # blank=True, null=True,
        # related_name="+",
    )

    taille = models.IntegerField()

    machines = models.ManyToManyField(Machine)

    recettes = models.ManyToManyField(Recette)

    stocks = models.ManyToManyField(QuantiteIngredient)

    def __str__(self):
        return f"Usine du {self.departement.numero}"

    def json(self):
        T = []
        for m in self.machines.all():
            T.append(m.id)

        return {
            "departement": self.departement.numero,
            "taille": self.taille,
            "machines": T,
        }

    def json_extended(self):
        T = []
        for m in self.machines.all():
            T.append(m.json_extended())
        return {
            # "departement": self.departement.numero,
            "taille": self.taille,
            "machines": T,
        }

    def costs(self):
        self.machines.all()
        T = 0
        for m in self.machines.all():
            T += m.prix

        self.stocks.all()
        S = 0
        for si in self.stocks.all():
            S += si.costs(self.departement.numero)

        cost_U = (self.departement.prix_m2 * self.taille) + T + S
        print(cost_U)
        return cost_U
