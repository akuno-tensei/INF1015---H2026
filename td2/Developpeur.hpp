/*
	Fichier : Developpeur.hpp
	Auteurs : Diego Alejandro Monsalve Rivas (2343317), Paul Tankeu Pajouo (2373265)
	Date : 11 février 2026
	Crée le 23 janvier 2026
*/

#pragma once
#include <iostream>
#include <string>
#include <utility>
#include "ListeJeux.hpp"
#include "Jeu.hpp"
#include <span>

class Developpeur {
	//TODO: En faire une classe qui suit les principes OO.
	//TODO: La destruction d'un Developpeur doit s'assurer que la désallocation de ListeJeux est faite.
	//TODO: Les méthodes à faire...

	public:
		Developpeur();
		Developpeur(const std::string& nom);
		~Developpeur();

		const std::string obtenirNom() const;

		int compterNombreJeux(const ListeJeux& listeJeux) const;

		void afficherTitresJeuxDeveloppeur() const;

		void ajouterJeuAListeJeux(Jeu* jeu);
		void mettreAJourListeJeux(const ListeJeux& listeJeux);

	private:
		std::pair<std::string, ListeJeux> paireNomJeux_;
};
