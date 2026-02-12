/* 
	Fichier : main.cpp
	Auteurs : Diego Alejandro Monsalve Rivas (2343317), Paul Tankeu Pajouo (2373265)
	Date : 11 février 2026
	Crée le 28 janvier 2026
*/


#include "Jeu.hpp"
#include "ListeDeveloppeurs.hpp"
#include <iostream>
#include <fstream>
#include <span>
#include "cppitertools/range.hpp"
#include "bibliotheque_cours.hpp"
#include "verification_allocation.hpp"
#include "debogage_memoire.hpp"  // Ajout des numéros de ligne des "new" dans le rapport de fuites.  Doit être après les include du système, qui peuvent utiliser des "placement new" (non supporté par notre ajout de numéros de lignes).

using namespace std;
using namespace iter;

#pragma region "Fonctions de base pour vous aider"
typedef uint8_t UInt8;
typedef uint16_t UInt16;
UInt8 lireUint8(istream& fichier)
{
	UInt8 valeur = 0;
	fichier.read((char*)&valeur, sizeof(valeur));
	return valeur;
}
UInt16 lireUint16(istream& fichier)
{
	UInt16 valeur = 0;
	fichier.read((char*)&valeur, sizeof(valeur));
	return valeur;
}
string lireString(istream& fichier)
{
	string texte;
	texte.resize(lireUint16(fichier));
	fichier.read((char*)&texte[0], streamsize(sizeof(texte[0])) * texte.length());
	return texte;
}
#pragma endregion

// Fonction qui cherche un designer par son nom dans une ListeJeux.  Devrait utiliser span.
Designer* chercherDesignerParNom(const ListeJeux& listeJeux, const string& nomDesigner) {
	for (Jeu* jeu : span(listeJeux.elements, listeJeux.nElements)) {
		for (Designer* designer : span(jeu->designers.elements, jeu->designers.nElements)) {
			if (designer->nom == nomDesigner) {
				return designer;
			}
		}
	}
	return nullptr;
}


Designer* lireDesigner(istream& fichier)
{
	Designer* designer = new Designer;
	designer->nom = lireString(fichier);
	designer->anneeNaissance = lireUint16(fichier);
	designer->pays = lireString(fichier);
	designer->listeJeuxParticipes.capacite = 0;
	designer->listeJeuxParticipes.nElements = 0;
	designer->listeJeuxParticipes.elements = nullptr;

	return designer; // Retourner le pointeur vers le designer crée.
}

// Fonction qui change la taille du tableau de jeux de ListeJeux.
void redimensionnerListeJeux(ListeJeux& listeJeux) {
	const unsigned nouvelleCapacite = listeJeux.capacite != 0 ? listeJeux.capacite * 2 : 2 ;

	listeJeux.capacite = nouvelleCapacite;

	Jeu** nouveauTableau = new Jeu* [nouvelleCapacite];

	for (unsigned i = 0; i < listeJeux.nElements; ++i) {
		nouveauTableau[i] = listeJeux.elements[i];
	}

	delete[] listeJeux.elements;
	listeJeux.elements = nouveauTableau;
}

// Fonction pour ajouter un Jeu à ListeJeux.
void ajouterJeuAListeJeux(ListeJeux& listeJeux, Jeu* jeu) {
	if (listeJeux.nElements == listeJeux.capacite) {
		redimensionnerListeJeux(listeJeux);
	}
	listeJeux.elements[listeJeux.nElements] = jeu;
	listeJeux.nElements++;
}

// Fonction qui change la taille du tableau de Designers d'un jeu.
void redimensionnerListeDesigners(ListeDesigners& listeDesigners) {
	const unsigned nouvelleCapacite = listeDesigners.capacite != 0 ? listeDesigners.capacite * 2 : 2;

	listeDesigners.capacite = nouvelleCapacite;

	Designer** nouveauTableau = new Designer* [nouvelleCapacite];

	for (unsigned i = 0; i < listeDesigners.nElements; ++i) {
		nouveauTableau[i] = listeDesigners.elements[i];
	}

	delete[] listeDesigners.elements;

	listeDesigners.elements = nouveauTableau;
}

// Fonction pour ajouter un Designer à ListeDesigners d'un Jeu.
void ajouterDesignerAListeDesigners(Jeu* jeu, Designer* designer) {
	if (jeu->designers.nElements == jeu->designers.capacite) {
		redimensionnerListeDesigners(jeu->designers);
	}
	jeu->designers.elements[jeu->designers.nElements] = designer;
	jeu->designers.nElements++;
}

// Fonction qui enlève un jeu de ListeJeux.
void enleverJeuDeListeJeux(ListeJeux& listeJeux, Jeu* jeu) {
	Jeu** nouveauTableau = new Jeu* [listeJeux.capacite];

	unsigned index = 0;

	for (unsigned i = 0; i < listeJeux.nElements; ++i) {
		if (listeJeux.elements[i] != jeu) {
			nouveauTableau[index] = listeJeux.elements[i];
			index++;
		}
	}

	listeJeux.nElements--;
	delete[] listeJeux.elements;

	listeJeux.elements = nouveauTableau;
}


Jeu* lireJeu(istream& fichier, ListeJeux& listeJeux) {
	Jeu* jeu = new Jeu;
	jeu->titre = lireString(fichier);
	jeu->anneeSortie = lireUint16(fichier);
	jeu->developpeur = lireString(fichier);

	const unsigned capacite = lireUint8(fichier);

	jeu->designers.capacite = 0;
	jeu->designers.nElements = 0;
	jeu->designers.elements = nullptr;

	for ([[maybe_unused]] int i : iter::range(capacite)) {
		Designer* designer = lireDesigner(fichier);  
		
		
		Designer* siDesignerExistant = chercherDesignerParNom(listeJeux, designer->nom);

		if (siDesignerExistant != nullptr) {
			delete designer;

			// Mettre le designer dans la liste des designer du jeu.
			ajouterDesignerAListeDesigners(jeu, siDesignerExistant);

			// Ajouter le jeu à la liste des jeux auquel a participé le designer.
			ajouterJeuAListeJeux(siDesignerExistant->listeJeuxParticipes, jeu);
		}
		else {
			// Mettre le designer dans la liste des designer du jeu.
			ajouterDesignerAListeDesigners(jeu, designer);

			// Ajouter le jeu à la liste des jeux auquel a participé le designer.
			ajouterJeuAListeJeux(designer->listeJeuxParticipes, jeu);
		}

	}
	return jeu; //  Retourner le pointeur vers le nouveau jeu.
}

ListeJeux creerListeJeux(const string& nomFichier)
{
	ifstream fichier(nomFichier, ios::binary);
	fichier.exceptions(ios::failbit);
	int nElements = lireUint16(fichier);

	ListeJeux listeJeux = {};
	listeJeux.capacite = 0;
	listeJeux.nElements = 0;
	listeJeux.elements = nullptr;

	for ([[maybe_unused]] int n : iter::range(nElements))
	{
		Jeu* jeu = lireJeu(fichier, listeJeux); 
		
		// Ajouter le jeu à la ListeJeux.
		ajouterJeuAListeJeux(listeJeux, jeu);
	}

	return listeJeux; // Renvoyer la ListeJeux.
}

// Fonction pour détruire un jeu (libération de mémoire allouée).
void detruireJeu(Jeu* jeu, ListeJeux& listeJeux) {
	// Enlever le jeu de la liste des jeux auquel a participé les designers du jeu.

	unsigned taille = jeu->designers.nElements;

	for (Designer* designer : span(jeu->designers.elements, jeu->designers.nElements)) {
		enleverJeuDeListeJeux(designer->listeJeuxParticipes, jeu);
		if (designer->listeJeuxParticipes.nElements == 0) {
			delete[] designer->listeJeuxParticipes.elements;
			delete designer;
		}
	}
	enleverJeuDeListeJeux(listeJeux, jeu);

	for (unsigned i = 0; i < taille; ++i) {
		jeu->designers.elements[i] = nullptr;
	}

	jeu->designers.nElements = 0;
	jeu->designers.capacite = 0;

	delete[] jeu->designers.elements;
	delete jeu;
}


// Fonction pour détruire une ListeJeux et tous ses jeux.
void detruireListeJeux(ListeJeux& listeJeux) {

	const unsigned nElements = listeJeux.nElements;

	for (unsigned i = 0; i < nElements; i++) {
		detruireJeu(listeJeux.elements[0], listeJeux);
	}

	listeJeux.nElements = 0;
	listeJeux.capacite = 0;

	delete[] listeJeux.elements;
}

// Fonction pour afficher les infos d'un designer.
void afficherDesigner(const Designer* designer) {
	cout << "Nom: " << designer->nom << endl;
	cout << "Année de naissance: " << designer->anneeNaissance << endl;
	cout << "Pays: " << designer->pays << endl;
}

// Fonction pour afficher les infos d'un jeu ainsi que ses designers.
void afficherJeu(const Jeu* jeu) {
	cout << "Titre: " << jeu->titre << endl;
	cout << "Année de sortie: " << jeu->anneeSortie << endl;
	cout << "Développeur: " << jeu->developpeur << endl;
	cout << "Designers:" << endl;
	for (Designer* designer : span(jeu->designers.elements, jeu->designers.nElements)) {
		afficherDesigner(designer);
		cout << endl;
	}
}


// Votre ligne de séparation doit être différent de celle utilisée dans le main.

// Fonction pour afficher tous les jeux de ListeJeux, séparés par un ligne.
void afficherListeJeux(const ListeJeux& listeJeux) {
	for (Jeu* jeu : span(listeJeux.elements, listeJeux.nElements)) {
		afficherJeu(jeu);
		cout << "\n\033[34m────────────────────────────────────────\033[0m\n" << endl;
	}
}


int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
#pragma region "Bibliothèque du cours"
	// Permet sous Windows les "ANSI escape code" pour changer de couleur
	// https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac
	// les supportent normalement par défaut.
	bibliotheque_cours::activerCouleursAnsi();
#pragma endregion

	int* fuite = new int;  // Pour vérifier que la détection de fuites fonctionne; un message devrait dire qu'il y a une fuite à cette ligne.


	/* ====================================================================== Partie 1 =================================================================== */

	ListeJeux listeJeux = creerListeJeux("jeux.bin"); // Appeler correctement votre fonction de création de la liste de jeux.

	static const string ligneSeparation = "\n\033[35m════════════════════════════════════════\033[0m\n";
	cout << ligneSeparation << endl;
	cout << "Premier jeu de la liste :" << endl;

	//Afficher le premier jeu de la liste (en utilisant la fonction).  Devrait être Chrono Trigger.
	afficherJeu(listeJeux.elements[0]);


	cout << ligneSeparation << endl;

	// Appel à votre fonction d'affichage de votre liste de jeux.
	afficherListeJeux(listeJeux);

	/* ====================================================================================================================================================== */

	/* ======================================================================= Partie 2 ===================================================================== */

	// Faire les appels à toutes vos fonctions/méthodes pour voir qu'elles fonctionnent et avoir 0% de lignes non exécutées dans le programme (aucune ligne rouge dans la couverture de code; c'est normal que les lignes de "new" et "delete" soient jaunes).  Vous avez aussi le droit d'effacer les lignes du programmes qui ne sont pas exécutée, si finalement vous pensez qu'elle ne sont pas utiles.
	ListeDeveloppeurs* listeDeveloppeurs = new ListeDeveloppeurs;

	Developpeur* square = new Developpeur{ "Square"s };
	square->mettreAJourListeJeux(listeJeux);

	Developpeur* nintendo = new Developpeur{"Nintendo"s};
	nintendo->mettreAJourListeJeux(listeJeux);

	Developpeur* konami = new Developpeur{ "Konami"s };
	konami->mettreAJourListeJeux(listeJeux);

	Developpeur* maxis = new Developpeur{ "Maxis"s };
	maxis->mettreAJourListeJeux(listeJeux);

	Developpeur* sega = new Developpeur{ "Sega"s };
	sega->mettreAJourListeJeux(listeJeux);

	listeDeveloppeurs->ajouterDeveloppeur(*square);
	listeDeveloppeurs->ajouterDeveloppeur(*nintendo);
	listeDeveloppeurs->ajouterDeveloppeur(*konami);
	listeDeveloppeurs->ajouterDeveloppeur(*maxis);
	listeDeveloppeurs->ajouterDeveloppeur(*square);
	listeDeveloppeurs->ajouterDeveloppeur(*sega);
	
	listeDeveloppeurs->afficher();

	// retrait de developpeurs
	listeDeveloppeurs->retirerDeveloppeur(*konami);
	listeDeveloppeurs->retirerDeveloppeur(*maxis);
	listeDeveloppeurs->retirerDeveloppeur(*square);
	listeDeveloppeurs->retirerDeveloppeur(*sega);

	cout << endl << endl << "      -------  Après retrait -------" << endl << endl;
	listeDeveloppeurs->afficher();

	/* ======================================================================================================================================================= */


	// Détruire tout avant de terminer le programme.  Devrait afficher "Aucune fuite detectee." a la sortie du programme; il affichera "Fuite detectee:" avec la liste des blocs, s'il manque des delete.
	delete square; delete nintendo; delete konami; delete maxis; delete sega;

	delete listeDeveloppeurs;

	detruireListeJeux(listeJeux);

	delete fuite;
}
