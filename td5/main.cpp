/*
		Nom du fichier : main.cpp
		Crée le 19 mars 2026 
		Modifié le 1 avril 2026
		Auteurs : Paul Tankeu Pajouo (2373265), Diego Alejandro Monsalve Rivas (2343317)

		Description : Ce fichier contient le code de test pour la classe ListeLiee et son itérateur.  
						Il lit les données des héros et vilains à partir de fichiers binaires, les stocke dans des listes liées, 
						et effectue diverses opérations pour tester la fonctionnalité de la liste liée et de l'itérateur.
*/

#include "Personnage.hpp"
#include "Heros.hpp"
#include "Vilain.hpp"
#include "VilainHeros.hpp"
#include "ListeLiee.hpp"
#include <fstream>
#include <vector>
#include <functional>
#include "cppitertools/range.hpp"
#include "bibliotheque_cours.hpp"
#include <span>

using namespace std;
using namespace iter;

using UInt8  = uint8_t;
using UInt16 = uint16_t;

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

template <typename T>
vector<T> lireFichier(istream& fichier)
{
	vector<T> elements;
	for ([[maybe_unused]] int i : range(lireUint16(fichier)))
		elements.push_back(T(fichier));
	return elements;
}

ifstream ouvrirLectureFichierBinaire(const string& nomFichier)
{
	ifstream fichier(nomFichier, ios::binary);
	fichier.exceptions(ios::failbit);
	return fichier;
}

// Permet d'avoir une référence non-const à un objet temporaire.
template <typename T> T& temporaireModifiable(T&& objet) { return objet; }

template <typename T>
vector<T> lireFichier(const string& nomFichier)
{
	return lireFichier<T>(temporaireModifiable(
		ouvrirLectureFichierBinaire(nomFichier)));
}

template <typename T>
Iterateur<T> trouverParNom(ListeLiee<T>& liste, const string& nom)
{
	Iterateur<T> fin = liste.end();
	for (Iterateur<T> pos = liste.begin(); pos != fin; pos.avancer()) {
		if ((*pos).getNom() == nom)
			return pos;
	}
	return fin;
}

int main()
{
	#pragma region "Bibliothèque du cours"
	// Permet sous Windows les "ANSI escape code" pour changer de couleur
	// https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac
	// les supportent normalement par défaut.
	bibliotheque_cours::activerCouleursAnsi();
	#pragma endregion
	
	// Trait de separation
	static const string trait =
		"═════════════════════════════════════════════════════════════════════════";

	static const string separateurSections = "\033[95m" + trait + "\033[0m\n";
	static const string separateurElements = "\033[33m" + trait + "\033[0m\n";

	//{ Solutionnaire du TD4:
	vector<Heros> heros = lireFichier<Heros>("heros.bin");
	vector<Vilain> vilains = lireFichier<Vilain>("vilains.bin");
	vector<unique_ptr<Personnage>> peronnages;  // Doit être des pointeurs pour le polymorphisme, l'énoncé ne force pas les unique_ptr.

	

	//TODO: Transférez les héros du vecteur heros dans une ListeLiee.
	ListeLiee<Heros> listeHeros;
	for (auto& h : heros) {
		listeHeros.push_back(h);
	}

	//TODO: Créez un itérateur sur la liste liée à la position du héros Alucard
	// Servez-vous de la fonction trouverParNom définie plus haut
	auto it = trouverParNom(listeHeros, "Alucard");
	(*it).afficher(cout);
	cout << separateurSections;

	//TODO: Servez-vous de l'itérateur créé précédemment pour trouver l'héroine Aya Brea,
	// en sachant qu'elle se trouve plus loin dans la liste.
	while (it != listeHeros.end() && (*it).getNom() != "Aya Brea") {
		it.avancer();
	}
	(*it).afficher(cout);
	cout << separateurSections;

	//TODO: Ajouter un hero bidon à la liste avant Aya Brea en vous servant de l'itérateur.
	Heros hero1("Monkey D. Luffy", "OnePiece", "Marshall D. Teach");

	listeHeros.insert(it, hero1);

	//TODO: Assurez-vous que la taille de la liste est correcte après l'ajout.
	cout << "Taille de la liste après l'ajout : " << listeHeros.size() << "\n";

	//TODO: Reculez votre itérateur jusqu'au héros Mario et effacez-le en utilisant l'itérateur, puis affichez le héros suivant dans la liste (devrait êter "Naked Snake/John").
	while(it != listeHeros.begin() && (*it).getNom() != "Mario") {
		it.reculer();
	}

	if (it != listeHeros.end() && (*it).getNom() == "Mario") {
		it = listeHeros.erase(it);
		cout << "Heros après Mario : " << (*it).getNom() << std::endl;
	}

	cout << "Taille de la liste après le retrait : " << listeHeros.size() << std::endl;

	//TODO: Assurez-vous que la taille de la liste est correcte après le retrait.

	//TODO: Effacez le premier élément de la liste.
	listeHeros.erase(listeHeros.begin());

	//TODO: Affichez votre liste de héros en utilisant un itérateur. La liste débute
	// avec le héros Randi et n'a pas Mario.
	// Servez-vous des methodes begin et end de la liste...
	cout << separateurSections << std::endl;
	for (auto iter = listeHeros.begin(); iter != listeHeros.end(); iter.avancer()) {
		(*iter).afficher(cout);
		cout << separateurElements << std::endl;
	}

	//TODO: Refaite le même affichage mais en utilisant une simple boucle "for" sur intervalle.
	cout << separateurSections << std::endl;
	for (Heros& hero : listeHeros) {
		hero.afficher(cout);
		cout << separateurElements << std::endl;
	}
	
	//TODO: Utilisez un conteneur pour avoir les héros en ordre alphabétique (voir point 2 de l'énoncé).
	cout << separateurSections << "Heros par ordre alphabetique:" << endl;
	std::vector<reference_wrapper<Heros>> herosTries;
	for (auto& h : listeHeros) {
		herosTries.push_back(h);
	}

	auto comparerParNom = [](const Heros& a, const Heros& b) { return a.getNom() < b.getNom(); };
	std::sort(herosTries.begin(), herosTries.end(), comparerParNom);

	for (const auto& h : herosTries) {
		cout << h.get().getNom() << endl;
	}
	//TODO: Assurez-vous de n'avoir aucune ligne non couverte dans les classes pour la liste liée.  Il peut y avoir des lignes non couvertes dans les personnages...
}
