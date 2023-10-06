#include <iostream>
#include <cpr/cpr.h>
#include<nlohmann/json.hpp>
using namespace std;

using json = nlohmann::json;

class Departement//
{
  public :
    int numero_;
    int prix_m2_;

  Departement(int numero, int prix_m2)
  {
    numero_=numero;
    prix_m2_=prix_m2;
  }

  Departement(int id)
  {
    auto Response = cpr::Get(cpr::Url("http://localhost:8000/Departement/"+ to_string (id)));
    auto j= json::parse(Response.text);
    numero_ =j["numero"];
    prix_m2_  =j["prix_m2"];
    std::cout << "numero :" << numero_ << std::endl;
    std::cout << "prix_m2 :" << prix_m2_ << std::endl;
  }

  Departement(json data)
   {
     //data = json::parse(txt); //create unitiialized json object
     //std::cout << data << std::endl;

     auto numero =data["numero"];
     auto prix_m2  =data["prix_m2"];


     // uses at to access fields from json object
     std::cout << "numero :" << numero << std::endl;
     std::cout << "prix_m2 :" << prix_m2 << std::endl;


   }

  void Affichage(void)
  {
    cout << "le departement " << numero_ <<'\n';

    cout << "prix m2 =" << prix_m2_ << '\n';
  }
};


class Ingredient//
{
  public :
    std::string nom_;


  Ingredient(int id)
  {
    auto Response = cpr::Get(cpr::Url("http://localhost:8000/Departement/"+ to_string (id)));
    auto j= json::parse(Response.text);
    nom_ =j["nom"];
    std::cout << "nom :" << nom_ << std::endl;
  }

  void Affichage(void)
  {
    cout << "ingredient :"<< nom_ <<'\n';
  }
};

class Prix//
{
  public :

    std::unique_ptr<Ingredient>  ingredient_;
    std::unique_ptr<Departement> departement_;
    int prix_;


  Prix(int id)
  {
    auto Response = cpr::Get(cpr::Url("http://localhost:8000/Departement/"+ to_string (id)));
    auto j= json::parse(Response.text);
    ingredient_ = std::make_unique <Ingredient> (j["ingredient"]);
    departement_ =std::make_unique <Departement> (j["departement"]);
    prix_ =j["prix"];

  }

  void Affichage(void)
  {
    std::cout << "ingredient :" << ingredient_ << std::endl;
    std::cout << "departement :" << departement_ << std::endl;
    std::cout << "prix :" << prix_ << std::endl;
  }
};

class Usine
{
  public :

    std::unique_ptr<Departement> departement_;
    int taille_;
    std::vector<std::unique_ptr<Machine>> machines_;
    std::vector<std::unique_ptr<Recette>> recettes_;
    std::vector<std::unique_ptr<QuantiteIngredient>> stocks_;

  Usine(int id)
{


    auto Response = cpr::Get(cpr::Url("http://localhost:8000/Departement/"+ to_string (id)));
    auto j= json::parse(Response.text);
    departement_ =std::make_unique <Departement> (j["departement"]);
    taille_ =j["taille"];

    for (const auto &vec1: machines_) {
      std::make_unique <j["machines"]> (vec1);
    }

    for (const auto &vec2: recettes_) {
      std::make_unique <j["recettes"]> (vec2);
    }

    for (const auto &vec3: stocks_) {
      std::make_unique <j["stocks"]> (vec3);
    }
//    machines_ =std::make_unique <Machine> (j["machines"]);
    //recettes_ =std::make_unique <Recette> (j["recette"]);
    //recettes_ =std::make_unique <QuantiteIngredient> (j["stocks"]);

}

  void Affichage(void)
  {
    std::cout << "departement :" << departement_ << std::endl;
    std::cout << "taille :" << taille_ << std::endl;
    std::cout << "machines :" << machines_ << std::endl;
    std::cout << "recettes :" << recettes_ << std::endl;
    std::cout << "stocks :" << stocks_ << std::endl;
  }
};

//std::make_unique ingredient

class Action//
{
  public :

    std::unique_ptr<Machine> machine_;
    int commande_;
    int duree_;
    std::optional<std::unique_ptr<Action>> action_;
    std::vector<std::unique_ptr<Ingredient>> ingredients_;


  Action(int id)
  {
    auto Response = cpr::Get(cpr::Url("http://localhost:8000/Departement/"+ to_string (id)));
    auto j= json::parse(Response.text);
    machine_ =std::make_unique <Machine> (j["machine"]);
    duree_ =j["duree"];
    commande_ =j["commande"];

    for (const auto &vec4: ingredients_) {
      std::make_unique <j["ingredients"]> (vec4);
    }


    ii=0;
    if(j.find("action_") != j.end() )
    {
      action_ =std::make_unique <Action> (j["action"]);
      ii=1;
      //cout<<"l'attribut action present"<<endl;
    }
  }std::vector<

  void Affichage(void)
  {
    std::cout << "machine :" << machine_ << std::endl;
    std::cout << "duree :" << duree_ << std::endl;
    std::cout << "commande :" << commande_ << std::endl;
    std::cout << "ingredients :" << ingredients_ << std::endl;

    for (const auto &vec3: stocks_) {
      std::make_unique <j["stocks"]> (vec3);
    }

    if(ii==1)
    {
        std::cout << "action :" << action_ << std::endl;
    }
    else
    {
      cout<<"l'attribut action non present"<<endl;
    }

  }
};

class Recette//
{
  public :

    std::string nom_;
    std::unique_ptr<Action>  action_;

  Recette (int id)
  {
    auto Response = cpr::Get(cpr::Url("http://localhost:8000/Departement/"+ to_string (id)));
    auto j= json::parse(Response.text);
    nom_ =j["nom"];
    action_ = std::make_unique <Action> (j["action"]);

  }

  void Affichage(void)
  {
    std::cout << "nom :" << nom_ << std::endl;
    std::cout << "action :" << action_ << std::endl;
  }
};


class Machine//
{
  public :

    std::string nom_;
    int prix_;
    //std::action_;

  Action(int id) : prix_(id)/////////
  {
    auto Response = cpr::Get(cpr::Url("http://localhost:8000/Departement/"+ to_string (id)));
    auto j= json::parse(Response.text);
    nom_ =j["nom"];
    prix_ =j["prix"];

  }

  void Affichage(void)
  {
    std::cout << "nom :" << nom_ << std::endl;
    std::cout << "prix :" << prix_ << std::endl;
  }
};

class QuantiteIngredient
{
  public :
    std::unique_ptr<Ingredient>  ingredient_;
    int quantite_;


  Ingredient(int id)
  {
    auto Response = cpr::Get(cpr::Url("http://localhost:8000/Departement/"+ to_string (id)));
    auto j= json::parse(Response.text);
    ingredient_ = std::make_unique <Ingredient> (j["ingredient"]);
    quantite_ =j["quantite"];

  }

  void Affichage(void)
  {
    std::cout << "ingredient :" << ingredient_ << std::endl;
    cout << "quantite:"<< quantite_ <<'\n';
  }
};

int main(void)
{
Departement d1(31,2000);
Machine m1(M1, 1000);
Machine m2(M2, 1000);



/*
Departement d1(31,2000);
d1.Affichage();

cout<<"**************"<<endl;
auto R = cpr::Get( cpr::Url{"http://localhost:8000/Departement/1"});
//cout<<"contenu de la reponse :"<<R.text<<endl;

//std::string json_string = R"({"numero": 31, "prix_m2 ": 2000})";

    auto j= json::parse(R.text); //create unitiialized json object
    //std::cout << j << std::endl;

    auto numero =j["numero"];
    auto prix_m2  =j["prix_m2"];


    // uses at to access fields from json object
    std::cout << "numero :" << numero << std::endl;
    std::cout << "prix_m2 :" << prix_m2 << std::endl;

cout<<"*************"<<endl;
Departement d2(j);
cout<<"&&&&&&&&&&&&&&&&&&&&&&&&"<<endl;
Departement d3(1);
*/


}
