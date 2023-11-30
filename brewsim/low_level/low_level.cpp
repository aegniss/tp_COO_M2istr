#include <iostream>
#include <cpr/cpr.h>
#include<nlohmann/json.hpp>
#include <fstream>
using namespace std;


using json = nlohmann::json;

/*class Point{

  float abs;
  float ord;
  public :
  Point(float x, float y): abs{x}, ord{y} {}
    friend std::ostream& operator<<(std::ostream& out, const Point& p){
    return out << p.abs << " / " << p.ord;
  }

};
*/
int ii=0;




class Departement//
{
  public :
    int numero_;
    int prix_m2_;

  friend std::ostream& operator<<(std::ostream& out, const Departement& d){
  return out <<" numero " << d.numero_ << " prix m2 " << d.prix_m2_;}

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
  void Affichage(void)
  {
  /*  cout << "le departement " << numero_ <<'\n';

    cout << "prix m2 =" << prix_m2_ << '\n';
  */}
};


class Machine//
{
  public :

    std::string nom_;
    int prix_;
    //std::action_;

    friend std::ostream& operator<<(std::ostream& out, const Machine& m){
      return out <<" nom " << m.nom_ << " prix_ " << m.prix_;}

  Machine(int id)
  {
    auto Response = cpr::Get(cpr::Url("http://localhost:8000/Machine/"+ to_string (id)));
    auto j= json::parse(Response.text);
    nom_ =j["nom"];
    prix_ =j["prix"];

  }

  void Affichage(void)
  {
    //std::cout << "nom :" << nom_ << std::endl;
    //std::cout << "prix :" << prix_ << std::endl;
  }
};


class Ingredient//
{
  public :
    std::string nom_;

  friend std::ostream& operator<<(std::ostream& out, const Ingredient& i){
    return out <<" nom " << i.nom_ ;
  }

  Ingredient(int id)
  {
    auto Response = cpr::Get(cpr::Url("http://localhost:8000/Ingredient/"+ to_string (id)));
    auto j= json::parse(Response.text);
    nom_ =j["nom"];
    //std::cout << "nom :" << nom_ << std::endl;
  }

/*  void Affichage(void)
  {
    cout << "ingredient :"<< i.nom_ <<'\n';
  }*/

};

class Prix//
{
  public :

    std::unique_ptr<Ingredient>  ingredient_;
    std::unique_ptr<Departement> departement_;
    int prix_;

    friend std::ostream& operator<<(std::ostream& out, const Prix& p){
      return out <<" ingredient " << *p.ingredient_<< " departement " << *p.departement_<< " prix " << p.prix_;}


  Prix(int id)
  {
    auto Response = cpr::Get(cpr::Url("http://localhost:8000/Prix/"+ to_string (id)));
    auto j= json::parse(Response.text);
    ingredient_ = std::make_unique <Ingredient> (j["ingredient"]);
    departement_ =std::make_unique <Departement> (j["departement"]);
    prix_ =j["prix"];

  }

  void Affichage(void)
  {/*
    std::cout << "ingredient :" << ingredient_ << std::endl;
    std::cout << "departement :" << departement_ << std::endl;
    std::cout << "prix :" << prix_ << std::endl;    */
  }
};


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

  auto Response = cpr::Get(cpr::Url("http://localhost:8000/Action/"+ to_string (id)));
  auto j= json::parse(Response.text);
  //machine_ = std::make_unique<Machine>(j["machine"]["id"]);
  machine_ =std::make_unique <Machine> (j["machine"]);
  //machine_ = std::make_unique<Machine>(j["machine"]["id"].get<int>());

  duree_ =j["duree"];
  commande_ =j["commande"];

  //ingredients_.emplace_back(std::make_unique<Ingredient>(*vec4));

  for (const auto &vec4: ingredients_) {
    std::make_unique <j["ingredients"]> (vec4);
    std::make_unique<Departement::Ingredient>(j["ingredients"]);

  }

  if(j.find("action_") != j.end() )
  {
    action_ =std::make_unique <Action> (j["action"]);
    //cout<<"l'attribut action present"<<endl;
  }

}

friend std::ostream& operator<<(std::ostream& out, const Action& a)
{
  return out <<" commande " << *a.action_ << " duree " << a.duree;
}



void Affichage(void)
{
/*  std::cout << "machine :" << machine_ << std::endl;
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
*/
}

};




class Recette//
{
  public :

    std::string nom_;
    std::unique_ptr<Action>  action_;

    friend std::ostream& operator<<(std::ostream& out, const Recette& r){
      return out <<" nom " << r.nom_ << " Action " << r.action_;}


  Recette (int id)
  {
    auto Response = cpr::Get(cpr::Url("http://localhost:8000/Recette/"+ to_string (id)));
    auto j= json::parse(Response.text);
    nom_ =j["nom"];
    action_ = std::make_unique <Action> (j["action"]);

  }

  void Affichage(void)
  {
    std::cout << "nom :" << nom_ << std::endl;
    /*//std::cout << "action :" << action_ << std::endl;

    std::ostream& operator<<(std::ostream& out, const std::unique_ptr<Departement::Ingredient::Action>& actionPtr) {
    if (actionPtr) {
        out << *actionPtr;  // Assuming there is an operator<< for Action
    } else {
        out << "nullptr";
    }
    return out;
  }*/

  }
 };



class QuantiteIngredient
{
  public :
    std::unique_ptr<Ingredient>  ingredient_;
    int quantite_;

    friend std::ostream& operator<<(std::ostream& out, const QuantiteIngredient& qi){
      return out <<" nom " << qi->ingredient_ << " quantite " << qi.quantite_;}

  Ingredient(int id)
  {
    auto Response = cpr::Get(cpr::Url("http://localhost:8000/Departement/"+ to_string (id)));
    auto j= json::parse(Response.text);
    ingredient_ = std::make_unique <Ingredient> (j["ingredient"]);
    quantite_ =j["quantite"];
  }



  void Affichage(void)
  {
    //std::cout << "ingredient :" << ingredient_ << std::endl;
    //cout << "quantite:"<< quantite_ <<'\n';
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

    friend std::ostream& operator<<(std::ostream& out, const Usine& u){
      return out <<" Departement " << u.departement_ << " taille " << u.taille_<< " machines " << u.machines_<< " recettes " << u.recettes_<< " stocks " << u.stocks_s;}

  Usine(int id)
{

    auto Response = cpr::Get(cpr::Url("http://localhost:8000/Usine/"+ to_string (id)));
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
  {/*
    std::cout << "departement :" << departement_ << std::endl;
    std::cout << "taille :" << taille_ << std::endl;
    std::cout << "machines :" << machines_ << std::endl;
    std::cout << "recettes :" << recettes_ << std::endl;
    std::cout << "stocks :" << stocks_ << std::endl;     */
  }
};



int main(void)
{

//Machine m1(M1, 1000);
//Machine m2(M2, 1000);


auto response = cpr::Get(cpr::Url{"http://localhost:8000/Departement/api/1"});

if (response.status_code == 200) {
    std::cout << "Response: " << response.text << std::endl;
}
else {
    std::cerr << "Error: " << response.status_code << std::endl;
}

//Departement d1(1);

return 0;
}
