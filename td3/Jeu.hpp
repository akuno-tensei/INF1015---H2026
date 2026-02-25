/*
	Fichier : Jeu.hpp
	Auteur : Paul Tankeu Pajouo (2373265), Diego Alejandro Monsalve Rivas (2343317)
	Crée le : 2026-02-10
	Modifié le : 2026-02-24

	Description: Ce fichier contient la déclaration de la classe Jeu, qui représente un jeu vidéo, avec ses attributs et méthodes.
*/


#pragma once
#include <string>
#include "Concepteur.hpp"
#include "Liste.hpp"

using ListeConcepteurs = Liste<Concepteur>;

class Jeu {
public:
	// Constructeur par défaut 
	Jeu();

	// Constructeur paramétré.
	Jeu(std::string titre, unsigned anneeSortie, std::string developpeur);

	// Constructeur de copie
	Jeu(const Jeu& autre);

	// surchage de l'opérateur = 
	Jeu& operator=(const Jeu& autre);

	const std::string& getTitre() const;

	void setTitre(std::string titre);

	unsigned getAnneeSortie() const;

	void setAnneeSortie(unsigned annee);

	const std::string& getDeveloppeur() const;

	void setDeveloppeur(std::string developpeur);


	// Accéder à la liste de concepteurs.
	ListeConcepteurs& accederListeConcepteurs();

	// Méthode pour changer un concepteur de la liste en connaissant son indice
	void changerConcepteur(unsigned indice, std::shared_ptr<Concepteur> autreConcepteur);

	// Trouver un concepteur selon un critère donné par une lambda, en utilisant la méthode de Liste.
	std::shared_ptr<Concepteur> trouverConcepteur(const std::function<bool(std::shared_ptr<Concepteur>)>& critere) const;

private:
	std::string titre_;
	unsigned anneeSortie_;
	std::string developpeur_;

	// Attribut de la liste des concepteurs du jeu
	ListeConcepteurs listeConcepteurs_;
};