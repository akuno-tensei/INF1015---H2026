/*
	Fichier: Concepteur.hpp
	Auteur: Paul Tankeu Pajouo (2373265), Diego Alejandro Monsalve Rivas (2343317)
	Crée le: 2026-02-10
	Modifié le: 2026-02-24

	Description: Ce fichier contient la déclaration de la classe Concepteur, qui représente un concepteur de jeu vidéo, avec ses attributs et méthodes.
*/

#pragma once
#include <iostream>
#include <string>

class Concepteur {
public:
	// Constructeur par défaut
	Concepteur();

	//  Constructeur paramétré.
	Concepteur(const std::string& nom, int anneNaissance, const std::string& pays);

	const std::string& getNom() const;

	void setNom(std::string nom);

	int getAnneeNaissance() const;

	void setAnneeNaissance(int annee);

	const std::string& getPays() const;

	void setPays(std::string pays);

private:
	std::string nom_;
	int anneeNaissance_;
	std::string pays_;
};
