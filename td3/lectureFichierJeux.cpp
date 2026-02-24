// Fonctions pour lire le fichier binaire.
#include "lectureFichierJeux.hpp"
#include <fstream>
#include <cstdint>
#include "cppitertools/range.hpp"
#include "Liste.hpp"
#include "Jeu.hpp"



using namespace std;

using ListeJeux = Liste<Jeu>;
using ListeConcepteurs = Liste<Concepteur>;

using UInt8  = uint8_t;
using UInt16 = uint16_t;

#pragma region "Fonctions de lecture de base"
//TODO: Remplacer lireUint8 et lireUint16 par une seule fonction générique qui permet les deux, mais permettre uniquement des types qui sont is_trivially_copyable_v (un trait de type).
template <typename T>
T lireType(istream& fichier) {
	T valeur = 0;
	fichier.read(reinterpret_cast<char*>(&valeur), sizeof(valeur));
	return valeur;
}


//UInt8 lireUint8(istream& fichier)
//{
//	UInt8 valeur = 0;
//	fichier.read(reinterpret_cast<char*>(&valeur), sizeof(valeur));
//	return valeur;
//}
//
//UInt16 lireUint16(istream& fichier)
//{
//	UInt16 valeur = 0;
//	fichier.read(reinterpret_cast<char*>(&valeur), sizeof(valeur));
//	return valeur;
//}

string lireString(istream& fichier)
{
	string texte;
	texte.resize(lireType<uint16_t>(fichier));
	fichier.read(reinterpret_cast<char*>(&texte[0]), streamsize(sizeof(texte[0])) * texte.length());
	return texte;
}
#pragma endregion

shared_ptr<Concepteur> chercherConcepteur(ListeJeux& listeJeux, const string& nom)
{
	//TODO: Compléter la fonction (équivalent de trouverDesigner du TD2).
	auto critere = [&nom](std::shared_ptr<Concepteur> concepteur) { return concepteur->getNom() == nom; };

	for (unsigned i = 0; i < listeJeux.size(); ++i) {
		auto& listeConcepteurs = listeJeux[i]->accederListeConcepteurs();

		auto concepteur = listeConcepteurs.trouverElement(critere);

		if (concepteur != nullptr) {
			return concepteur;
		}
	}
	return nullptr;
}

shared_ptr<Concepteur> lireConcepteur(ListeJeux& lj, istream& f) {
	string nom              = lireString(f);
	unsigned anneeNaissance = lireType<uint16_t>(f);
	string pays             = lireString(f);

	//TODO: Compléter la fonction (équivalent de lireDesigner du TD2).
	std::shared_ptr<Concepteur> concepteur = chercherConcepteur(lj, nom);
	if (concepteur != nullptr) {
		return concepteur;
	}

	concepteur = std::make_shared<Concepteur>(nom, anneeNaissance, pays);

	cout << "C: " << nom << endl;  //TODO: Enlever cet affichage temporaire servant à voir que le code fourni lit bien les jeux.
	return concepteur;
}

shared_ptr<Jeu> lireJeu(istream& f, ListeJeux& lj)
{	
	//string titre = lireType<string>(f);
	string titre          = lireString(f);
	unsigned anneeSortie  = lireType<uint16_t>(f);
	string developpeur    = lireString(f);
	unsigned nConcepteurs = lireType<uint8_t>(f);

	std::shared_ptr<Jeu> jeu = std::make_shared<Jeu>(titre, anneeSortie, developpeur);

	ListeConcepteurs& listeConcepteurs = jeu->accederListeConcepteurs();

	//TODO: Compléter la fonction (équivalent de lireJeu du TD2).
	for (unsigned int i = 0; i < nConcepteurs; i++) {
		std::shared_ptr<Concepteur> concepteur = lireConcepteur(lj, f);
		listeConcepteurs.ajouterElement(concepteur);
	}



	cout << "J: " << titre << endl;  //TODO: Enlever cet affichage temporaire servant à voir que le code fourni lit bien les jeux.
	return jeu;
}

ListeJeux creerListeJeux(const string& nomFichier) {
	ifstream f(nomFichier, ios::binary);
	f.exceptions(ios::failbit);
	int nElements = lireType<uint16_t>(f);

	//TODO: Compléter la fonction.
	ListeJeux listeJeux;

	for ([[maybe_unused]] int i : iter::range(nElements)) {
		shared_ptr<Jeu> jeu = lireJeu(f, listeJeux);
		listeJeux.ajouterElement(jeu);
	}

	return listeJeux;
}
