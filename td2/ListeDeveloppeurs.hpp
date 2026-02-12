/*
	Fichier : ListeDeveloppeurs.hpp
	Auteurs : Diego Alejandro Monsalve Rivas (2343317), Paul Tankeu Pajouo (2373265)
	Date : 11 février 2026
	Crée le 23 janvier 2026
*/



#pragma once
#include "Developpeur.hpp"

class ListeDeveloppeurs
{
	//TODO: En faire une classe qui suit les principes OO.
	//TODO: On veut pouvoir ajouter et enlever un Developpeur* de la liste, avec réallocation dynamique tel que faite pour ListeJeux.
	//NOTE: Le code sera principalement copié de certaines fonctions écrites pour la partie 1, mais mises dans une classe.
	
	public:
		ListeDeveloppeurs();
		~ListeDeveloppeurs();

		void redimensionnerListeDeveloppeurs();

		void ajouterDeveloppeur(Developpeur& developpeur);

		void retirerDeveloppeur(Developpeur& developpeur);

		void afficher() const;

	private:
		unsigned nElements_;
		unsigned capacite_;
		Developpeur** elements_;
};
