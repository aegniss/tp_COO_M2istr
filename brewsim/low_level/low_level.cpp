#include <cpr/cpr.h>

#include <fstream>
#include <iostream>
#include <memory>
#include <nlohmann/json.hpp>

using namespace std;
using json = nlohmann::json;

const int id_dep = 1;
const int id_mach_1 = 1;
const int id_mach_2 = 2;
const int id_ing_1 = 4;
const int id_ing_2 = 8;
const int id_prix_1 = 4;
const int id_prix_2 = 11;
const int id_qi_1 = 3;
const int id_qi_2 = 10;
const int id_action = 7;
const int id_recette = 2;
const int id_usine = 3;

class Departement  //
{
 public:
  int _numero;
  int _prix_m2;

  Departement(int numero, int prix_m2) : _numero(numero), _prix_m2(prix_m2) {}
  Departement(json data) : _numero(data["numero"]), _prix_m2(data["prix_m2"]) {}
  Departement(int id) {
    string url = "http://localhost:8000/Departement/" + to_string(id);
    printf("%s\n", url.c_str());
    cpr::Response r = cpr::Get(cpr::Url{url});
    json data = json::parse(r.text);
    set(data["numero"], data["prix_m2"]);
  }
  void set(int n, int p) {
    _numero = n;
    _prix_m2 = p;
  }
  void affichage() {
    cout << "Numero de departement:" << _numero << ",\t";
    cout << "Prix du metre carre : " << _prix_m2 << endl;
  }
  friend class Prix;
  friend class Usine;
};

class Machine  //
{
 public:
  std::string _nom;
  int _prix;

 public:
  Machine(string nom, int prix) : _nom(nom), _prix(prix) {}
  Machine(json data) : _nom(data["nom"]), _prix(data["prix"]) {}
  Machine(int id) {
    string url = "http://localhost:8000/Machine/" + to_string(id);
    cpr::Response r = cpr::Get(cpr::Url{url});
    json data = json::parse(r.text);
    set(data["machine"], data["prix"]);
  }
  void set(string n, int p) {
    _nom = n;
    _prix = p;
  }
  void affichage() {
    cout << "Nom de la machine: " << _nom << ",\t";
    cout << "Prix:" << _prix << endl;
  }
  friend class Action;
  friend class Usine;
};

class Ingredient  //
{
 public:
  std::string _nom;

  Ingredient(string nom) : _nom(nom) {}
  Ingredient(int id) {
    string url = "http://localhost:8000/Ingredient/" + to_string(id);
    cpr::Response r = cpr::Get(cpr::Url{url});
    json data = json::parse(r.text);
    set(data["ingredient"]);
  }
  void set(string n) { _nom = n; }
  void affichage() { cout << "Ingredient: " << _nom << endl; }

  friend class Prix;
  friend class QuantiteIngredient;
  friend class Action;
  friend class Recette;
  friend class Usine;
};

class Prix  //
{
 public:
  std::unique_ptr<Ingredient> _ingredient;
  std::unique_ptr<Departement> _departement;
  int _prix;
  Prix(unique_ptr<Ingredient> ingredient, unique_ptr<Departement> departement,
       int prix)
      : _ingredient(move(ingredient)),
        _departement(move(departement)),
        _prix(prix) {}
  Prix(int id) {
    string url = "http://localhost:8000/Prix/" + to_string(id);
    cpr::Response r = cpr::Get(cpr::Url{url});
    json data = json::parse(r.text);
    set(data[" prix "], data[" ingredient "]);
  }

  void set(const int p, const int i) {
    unique_ptr<Ingredient> ingredient;

    if (i == id_prix_1)
      ingredient = make_unique<Ingredient>(id_ing_1);
    else if (i == id_prix_2)
      ingredient = make_unique<Ingredient>(id_ing_2);

    unique_ptr<Departement> departement = make_unique<Departement>(id_dep);

    _ingredient = move(ingredient);
    _departement = move(departement);
    _prix = p;
  }
  void affichage() {
    cout << "Ingredient: " << _ingredient->_nom << ",\t";
    cout << "Departement: " << _departement->_numero << ",\t";
    cout << "Prix: " << _prix << endl;
  }
};

class QuantiteIngredient {
 public:
  std::unique_ptr<Ingredient> _ingredient;
  int _quantite;

  QuantiteIngredient(unique_ptr<Ingredient> ingredient, int quantite)
      : _ingredient(std::move(ingredient)), _quantite(quantite) {}
  QuantiteIngredient(int id) {
    string url = "http://localhost:8000/QuantiteIngredient/" + to_string(id);
    cpr::Response r = cpr::Get(cpr::Url{url});
    json data = json::parse(r.text);
    set(data["ingredient "], data["quantite"]);
  }
  void set(string n, int q) {
    string nom_ingredient = n;
    unique_ptr<Ingredient> ingredient = make_unique<Ingredient>(nom_ingredient);
    _ingredient = move(ingredient);
    _quantite = q;
  }
  void affichage() {
    cout << "Ingredient: " << _ingredient->_nom << ",\t";
    cout << "Quantite: " << _quantite << endl;
  }
  friend class Action;
  friend class Recette;
  friend class Usine;
};

class Action  //
{
 public:
  std::unique_ptr<Machine> _machine;
  string _commande;
  int _duree;
  std::optional<std::unique_ptr<Action>> _action;
  std::vector<std::unique_ptr<QuantiteIngredient>> _ingredients;

  Action(unique_ptr<Machine> machine, string commande, int duree,
         vector<unique_ptr<QuantiteIngredient>> ingredients)
      : _machine(move(machine)),
        _commande(commande),
        _duree(duree),
        _ingredients(move(ingredients)) {}
  Action(int id) {
    string url = "http://localhost:8000/Action/" + to_string(id);
    cpr::Response r = cpr::Get(cpr::Url{url});
    json data = json::parse(r.text);
    set(data["Machine"], data["commande"], data["duree"], data["ingredients"]);
  }
  void set(string n, string c, int d, vector<string> i) {
    string nom_machine = n;
    vector<string> ingredients_ = i;

    unique_ptr<Machine> mach = make_unique<Machine>(nom_machine, 1000);
    vector<unique_ptr<QuantiteIngredient>> ingredientsss;
    for (const auto& j : ingredients_) {
      ingredientsss.push_back(make_unique<QuantiteIngredient>(
          move(make_unique<Ingredient>(j)), 100));
    }

    _machine = move(mach);
    _ingredients = move(ingredientsss);
    _commande = c;
    _duree = d;
  }
  void affichage() {
    cout << "Machine: " << _machine->_nom << ",\t";
    cout << "Commande: " << _commande << ",\t";
    cout << "Duree: " << _duree << ",\t";
    int i = 0;
    cout << "Ingredients: [";
    for (const auto& ing : _ingredients) {
      cout << ing->_ingredient->_nom;
      i += 1;
      if (i < _ingredients.size()) {
        cout << ", ";
      }
    }
    cout << "]" << endl;
  }
  friend class Recette;
  // friend class QuantiteIngredient;
};

class Recette  //
{
 public:
  std::string _nom;
  std::unique_ptr<Action> _action;

  Recette(string nom, unique_ptr<Action> action)
      : _nom(nom), _action(move(action)) {}
  Recette(int id) {
    string url = "http://localhost:8000/Recette/" + to_string(id);
    cpr::Response r = cpr::Get(cpr::Url{url});
    json data = json::parse(r.text);
    set(data["Recette"]);
  }

  void set(string n) {
    _nom = n;

    unique_ptr<Action> action;
    action = make_unique<Action>(id_action);
    _action = move(action);
  }

  void affichage() {
    cout << "Recette: " << _nom << ", \t";
    cout << "Action: " << _action->_commande << ", \t";
  }

  friend class Usine;
};

class Usine {
 public:
  std::unique_ptr<Departement> _departement;
  int _taille;
  std::vector<std::unique_ptr<Machine>> _machines;
  std::vector<std::unique_ptr<Recette>> _recettes;
  std::vector<std::unique_ptr<QuantiteIngredient>> _stocks;

  Usine(unique_ptr<Departement> departement, int taille,
        vector<unique_ptr<Machine>> machines,
        vector<unique_ptr<Recette>> recettes,
        vector<unique_ptr<QuantiteIngredient>> stocks)
      :

        _departement(move(departement)),
        _taille(taille),
        _machines(move(machines)),
        _recettes(move(recettes)),
        _stocks(move(stocks)) {}
  Usine(int id) {
    string url = "http://localhost:8000/Usine/" + to_string(id);
    cpr::Response r = cpr::Get(cpr::Url{url});
    json data = json::parse(r.text);
    set(data["departement"], data["taille"], data["machines"]);
  }

  void set(int nu, int t, vector<string> nsm) {
    int num_departement = nu;
    vector<string> nom_machines = nsm;

    unique_ptr<Departement> depp;
    depp = make_unique<Departement>(num_departement, 2000);

    vector<unique_ptr<Machine>> machss;
    for (const auto& i : nom_machines) {
      machss.push_back(make_unique<Machine>(move(i), 1000));
    }
  }

  unique_ptr<Action> actionnt = make_unique<Action>(id_action);

  _departement = move(depp);
  _taille = t;
  _machines = move(machss);

  void affichage() {
    cout << "Departement: " << _departement->_numero << ", \t";
    cout << "Taille: " << _taille << ", \t";
    int i = 0;
    cout << "Machine: [";
    for (const auto& mach : _machines) {
      cout << mach->_nom;
      i += 1;
      if (i < _machines.size()) {
        cout << ", ";
      }
    }
    cout << "], \t";
  }
};

int main(void) {
  Departement dep_cons(31, 2000);
  dep_cons.affichage();

  json data_dep;
  data_dep["numero"] = 31;
  data_dep["prix_m2"] = 2000;

  Departement dep_cons_json(data_dep);
  dep_cons_json.affichage();

  Departement dep_cons_id(id_dep);
  dep_cons_id.affichage();

  Machine mach_cons("cuve", 1000);
  mach_cons.affichage();

  json data_mach;
  data_mach["nom"] = "cuve";
  data_mach["prix"] = 1000;

  Machine mach_cons_json(data_mach);
  mach_cons_json.affichage();

  Machine mach_cons_id(id_mach_1);
  mach_cons_id.affichage();

  Ingredient ing_cons("houblon");
  ing_cons.affichage();

  Ingredient ing_cons_id(id_ing_1);
  ing_cons_id.affichage();

  unique_ptr<Ingredient> houblon = make_unique<Ingredient>(id_ing_1);
  unique_ptr<Departement> departement = make_unique<Departement>(id_dep);
  Prix prix_cons(move(houblon), move(departement), 20);
  prix_cons.affichage();

  Prix prix_cons_id(id_prix_1);
  prix_cons_id.affichage();

  unique_ptr<Ingredient> orge = make_unique<Ingredient>(id_ing_2);
  QuantiteIngredient qi_cons(move(orge), 100);
  qi_cons.affichage();

  QuantiteIngredient qi_id(id_qi_2);
  qi_id.affichage();
  // Stockez les objets dans des variables
  unique_ptr<Machine> cuve = make_unique<Machine>(id_mach_1);
  vector<unique_ptr<QuantiteIngredient>> ingredientssss;
  ingredientssss.push_back(make_unique<QuantiteIngredient>(id_qi_1));
  ingredientssss.push_back(make_unique<QuantiteIngredient>(id_qi_2));
  // Créez un objet Action en utilisant les variables précédemment créées
  Action act_cons(move(cuve), "ebullition", 5, move(ingredientssss));
  act_cons.affichage();

  Action act_cons_id(id_action);
  act_cons_id.affichage();

  unique_ptr<Action> actionn = make_unique<Action>(id_action);

  Recette rec_cons("biere", move(actionn));
  rec_cons.affichage();

  Recette rec_cons_id(id_recette);
  rec_cons_id.affichage();

  unique_ptr<Departement> dep_ = make_unique<Departement>(id_dep);
  vector<unique_ptr<Machine>> machs;
  machs.push_back(make_unique<Machine>(id_mach_1));
  machs.push_back(make_unique<Machine>(id_mach_2));

  vector<unique_ptr<QuantiteIngredient>> iiingredients;
  iiingredients.push_back(make_unique<QuantiteIngredient>(id_qi_1));
  iiingredients.push_back(make_unique<QuantiteIngredient>(id_qi_2));
  printf("555");
  vector<unique_ptr<Recette>> recc;
  recc.push_back(make_unique<Recette>(id_recette));

  Usine usine_cons(move(dep_), 50, move(machs), move(recc),
                   move(iiingredients));
  usine_cons.affichage();

  Usine usine_cons_id(id_usine);
  usine_cons_id.affichage();

  return 0;
}
