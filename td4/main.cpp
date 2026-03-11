#include <fstream>
#include "bibliotheque_cours.hpp"
#include "Personnage.hpp"
#include "Heros.hpp"
#include "Vilain.hpp"
#include "VilainHeros.hpp"

using namespace std;

using UInt8  = uint8_t;
using UInt16 = uint16_t;

// Trait de separation
static const string TRAIT = "═════════════════════════════════════════════════════════════════════════";

const Couleur COULEUR_INITIALE = Couleur::BLANC;

UInt8 lireUint8(istream& fichier)
{
	UInt8 valeur = 0;
	fichier.read(reinterpret_cast<char*>(&valeur), sizeof(valeur));
	return valeur;
}

UInt16 lireUint16(istream& fichier)
{
	UInt16 valeur = 0;
	fichier.read(reinterpret_cast<char*>(&valeur), sizeof(valeur));
	return valeur;
}

string lireString(istream& fichier)
{
	string texte;
	texte.resize(lireUint16(fichier));
	fichier.read(reinterpret_cast<char*>(&texte[0]), streamsize(sizeof(texte[0])) * texte.length());
	return texte;
}

template <class T>
concept Dereferencable = requires (T&& t) { *std::forward<T>(t); };

// Surcharge quand c'est un pointeur
template <Dereferencable T> 
decltype(auto) as_ref(T&& t)
{
	return *std::forward<T>(t);
}

// Surcharge moins contrainte (donc quand ce n'est pas un pointeur)
template <class T>
T&& as_ref(T&& t) {
	return std::forward<T>(t);
}

template <typename U>
shared_ptr<U> lirePerso(istream& fichier) {
	string nomPerso = lireString(fichier);
	string parution = lireString(fichier);
	string enemiOuObjectif = lireString(fichier);

	if constexpr (is_same_v<U, Heros>) {
		auto heros = make_shared<Heros>(nomPerso, parution);
		heros->ajouterPersonnage(enemiOuObjectif);

		unsigned int nbreAllies = lireUint8(fichier);
		for (unsigned int j = 0; j < nbreAllies; j++) {
			string allie = lireString(fichier);
			heros->ajouterPersonnage(allie);
		}
		return heros;
	}
	else if constexpr (is_same_v<U, Vilain>) {
		return make_shared<Vilain>(nomPerso, parution, enemiOuObjectif);
	}

	return nullptr;
}

template <typename T>
vector<shared_ptr<T>> creerVecteurPerso(istream& fichier) {
	unsigned int nbrePerso = lireUint16(fichier);
	vector<shared_ptr<T>> vecteurPerso;
	vecteurPerso.reserve(nbrePerso);

	for (unsigned int i = 0; i < nbrePerso; i++) {
		vecteurPerso.push_back(lirePerso<T>(fichier));
	}

	return vecteurPerso; 
}

template <typename P>
void afficherPerso(const shared_ptr<P>& personnage, ostream& os) {
	personnage->afficher(os);
}

template <typename P>
void afficherVecteurPerso(const vector<shared_ptr<P>>& personnages, ostream& os) {
	for (const shared_ptr<P>& personnage : span(personnages)) {
		afficherPerso(personnage, os);
		os << TRAIT << endl;
	}
}

template <typename P>
void afficherPersoColorie(shared_ptr<P>& personnage, ostream& os, Couleur couleur= COULEUR_INITIALE) {
	personnage->changerCouleur(couleur);
	personnage->afficher(os);
}

template <typename P>
void afficherVecteurPersoColorie(vector<shared_ptr<P>>& personnages, ostream& os, Couleur couleur = COULEUR_INITIALE) {
	for (shared_ptr<P>& perso : span(personnages)) {
		afficherPersoColorie<P>(perso, os, couleur);
		os << TRAIT << endl;
	}
}



int main()
{
	#pragma region "Bibliothèque du cours"
	// Permet sous Windows les "ANSI escape code" pour changer de couleur
	// https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac
	// les supportent normalement par défaut.
	bibliotheque_cours::activerCouleursAnsi();
	#pragma endregion
	
	
	// Ouverture des fichiers binaires
	ifstream fichierHeros("heros.bin", ios::binary);
	ifstream fichierVilains("vilains.bin", ios::binary);
	fichierHeros.exceptions(ios::failbit);
	fichierVilains.exceptions(ios::failbit);

	//TODO: Votre code pour le main commence ici
	vector<shared_ptr<Personnage>> personnages;

	vector<shared_ptr<Heros>> heros = creerVecteurPerso<Heros>(fichierHeros);

	vector<shared_ptr<Vilain>> vilains = creerVecteurPerso<Vilain>(fichierVilains);

	afficherVecteurPerso(heros, cout);
	
	afficherVecteurPerso(vilains, cout);

	afficherVecteurPersoColorie<Heros>(heros, cout, Couleur::BLEU);

	afficherVecteurPersoColorie<Vilain>(vilains, cout, Couleur::ROUGE);

	// shared_ptr<Personnage> perso = make_shared<Personnage>(*heros[0]);

	personnages.insert(personnages.end(), heros.begin(), heros.end()); 
	personnages.insert(personnages.end(), vilains.begin(), vilains.end());

	afficherVecteurPerso(personnages, cout);

	shared_ptr<VilainHeros> vilainHeros = make_shared<VilainHeros>(*heros.at(0), *vilains.at(2));

	afficherPersoColorie(vilainHeros, cout, Couleur::JAUNE);

	cout << TRAIT << endl;

	personnages.push_back(vilainHeros);

	personnages.at(personnages.size() - 1)->afficher(cout);
}