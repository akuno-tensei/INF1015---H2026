/*
	Fichier : main.cpp
	Auteur : Paul Tankeu Pajouo (2373265), Diego Alejandro Monsalve Rivas (2343317)
	Crée le : 2026-02-10
	Modifié le : 2026-02-24

	Description: Ce fichier contient le main du projet, qui teste les différentes fonctionnalités demandées, 
	notamment la lecture du fichier binaire, l'affichage des jeux et concepteurs, la recherche de concepteur selon un critère donné par une lambda, 
	l'ajout d'un jeu à la liste de jeux, 
	et la copie d'un jeu pour vérifier que la copie profonde de la liste de concepteurs est bien faite.
*/

#pragma once
#include <iostream>
#include <fstream>
#include "Liste.hpp"
#include "Concepteur.hpp"
#include "Jeu.hpp"
#include "lectureFichierJeux.hpp"
#include "bibliotheque_cours.hpp"
#include "verification_allocation.hpp"

using namespace std;

//TODO: Vos surcharges d'opérateur <<
ostream& operator<<(ostream& o, const ListeConcepteurs& listeConcepteurs) {
	for (unsigned i = 0; i < listeConcepteurs.size(); ++i) {
		o << "Concepteur " << i + 1 << " : " << listeConcepteurs[i]->getNom() << ", né en " << listeConcepteurs[i]->getAnneeNaissance() << " au " << listeConcepteurs[i]->getPays() << endl;
	}
	return o;
}

ostream& operator<<(ostream& o, const ListeJeux& listeJeux) {
	for (unsigned i = 0; i < listeJeux.size(); ++i) {
		ListeConcepteurs& listeConcepteurs = listeJeux[i]->accederListeConcepteurs();
		o << "Jeu " << i + 1 << " : " << listeJeux[i]->getTitre() << ", sorti en " << listeJeux[i]->getAnneeSortie() << " par " << listeJeux[i]->getDeveloppeur() << endl;
		o << "---------- Liste des concepteurs ----------" << endl;
		o << listeConcepteurs;
		o << endl;
	}
	return o;
}

ostream& operator<<(ostream& o, shared_ptr<Concepteur> concepteur) {
	return o << "Concepteur : " << concepteur->getNom() << ", né en " << concepteur->getAnneeNaissance() << " au " << concepteur->getPays() << endl;
}

ostream& operator<<(ostream& o, shared_ptr<Jeu> jeu) {
	ListeConcepteurs& listeConcepteurs = jeu->accederListeConcepteurs();
	o << "Jeu : " << jeu->getTitre() << ", sorti en " << jeu->getAnneeSortie() << " par " << jeu->getDeveloppeur() << endl;
	o << "---------- Liste des concepteurs ----------" << endl;
	o << listeConcepteurs;
	return o;
}

ostream& operator<<(ostream& o, Jeu jeu) {
	ListeConcepteurs& listeConcepteurs = jeu.accederListeConcepteurs();
	o << "Jeu : " << jeu.getTitre() << ", sorti en " << jeu.getAnneeSortie() << " par " << jeu.getDeveloppeur() << endl;
	o << "---------- Liste des concepteurs ----------" << endl;
	o << listeConcepteurs;
	return o;
}

int main([[maybe_unused]] int argc, [[maybe_unused]] char** argv)
{
	#pragma region "Bibliothèque du cours"
	// Permet sous Windows les "ANSI escape code" pour changer de couleur
	// https://en.wikipedia.org/wiki/ANSI_escape_code ; les consoles Linux/Mac
	// les supportent normalement par défaut.
	bibliotheque_cours::activerCouleursAnsi(); 
	#pragma endregion
	
	ListeJeux listeJeux = creerListeJeux("jeux.bin");
	static const string ligneSeparation = "\n\033[92m"
		"══════════════════════════════════════════════════════════════════════════"
		"\033[0m\n";

	//TODO: L'affichage de listeJeux et l'écriture dans le fichier devraient fonctionner.

	//TODO: Compléter le main avec les tests demandés.

	// Obtenir le jeu 3 et afficher son titre pour vérifier que la lecture du fichier a fonctionné.
	cout << ligneSeparation << endl;

	cout << "listeJeux[2] : " << listeJeux[2]->getTitre() << endl << endl;

	cout << ligneSeparation << endl;

	// Tester la fonction trouverConcepteur de lectureFichierJeux, qui cherche un concepteur dans la liste de jeux selon un nom donné.
	cout << ligneSeparation << endl;

	cout << "---------- Test de trouverConcepteur de lectureFichierJeux avec critère de nom 'Yoshinori Kitase' ----------" << endl;
	string nom = "Yoshinori Kitase";

	cout << chercherConcepteur(listeJeux, nom) << endl << endl;

	cout << ligneSeparation << endl;

	// Tester la méthode trouverConcepteur de Jeu, qui cherche un concepteur dans la liste de concepteurs du jeu selon un critère donné par une lambda.
	cout << ligneSeparation << endl;

	auto critere = [](std::shared_ptr<Concepteur> concepteur) { return concepteur->getNom() == "Yoshinori Kitase"; };

	cout << "Pour listeJeux[0] -> "  << listeJeux[0]->trouverConcepteur(critere) << endl;

	cout << "Pour listeJeux[1] -> " << listeJeux[1]->trouverConcepteur(critere) << endl;

	cout << ligneSeparation << endl;

	// Afficher la liste de jeux pour vérifier que l'affichage fonctionne avec la surcharge d'opérateur .
	cout << ligneSeparation << endl;

	cout << listeJeux << endl;

	cout << ligneSeparation << endl;
	
	// Tester la surcharge d'opérateur << pour un jeu individuel. 
	// Tester l'ajout d'un jeu déjà présent dans la liste, pour vérifier que la vérification d'existence dans la liste fonctionne.
	cout << ligneSeparation << endl;

	std::shared_ptr<Jeu> jeu = listeJeux[2];
	listeJeux.ajouterElement(jeu);

	cout << ligneSeparation << endl;

	// Tester la copie d'un jeu, pour vérifier que la copie profonde de la liste de concepteurs est bien faite.
	cout << ligneSeparation << endl;

	Jeu copieJeu = *(listeJeux[2]);

	copieJeu.changerConcepteur(0, listeJeux[0]->accederListeConcepteurs()[0]); // modification de la copie du jeu

	copieJeu.accederListeConcepteurs()[1] = listeJeux[0]->accederListeConcepteurs()[1]; // modification de la copie du jeu

	cout << "---------- Copie du jeu 3 avec modification de la copie ----------" << endl << endl;
	cout << copieJeu << endl;
	cout << "---------- Après modification de la copie du jeu 3 ----------" << endl << endl;
	cout << listeJeux[2] << endl;

	cout << ligneSeparation << endl;

	cout << ligneSeparation << endl;

	bool pareil = listeJeux[2]->accederListeConcepteurs()[0] == copieJeu.accederListeConcepteurs()[0];

	cout << "Adresses des premiers concepteurs égales  (1 : True, 0 : False) ??" << endl << "Réponse : " << pareil << endl;

	cout << ligneSeparation << endl;
	//TODO: S'assurer qu'aucune ligne de code est non couverte.
	//NOTE: Il n'est pas nécessaire de couvrir les getters/setters simples fournis; il faut tester si vous en ajoutez ou les modifiez.
	//NOTE: Pour Liste, qui est générique, on demande de couvrir uniquement pour Liste<Jeu>, pas pour tous les types.
}