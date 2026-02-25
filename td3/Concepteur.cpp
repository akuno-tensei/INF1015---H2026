/*
	Fichier : Concepteur.cpp
	Auteur : Paul Tankeu Pajouo (2373265), Diego Alejandro Monsalve Rivas (2343317)
	Crée le : 2026-02-24
	Modifié le : 2026-02-24

	Description: Ce fichier contient l'implémentation de la classe Concepteur, qui représente un concepteur de jeu vidéo, avec ses attributs et méthodes.
*/

#pragma once
#include "Concepteur.hpp"

Concepteur::Concepteur() {
	nom_ = "inconnu";
	anneeNaissance_ = 0;
	pays_ = "inconnu";
}

Concepteur::Concepteur(const std::string& nom, int anneNaissance, const std::string& pays) {
	nom_ = nom;
	anneeNaissance_ = anneNaissance;
	pays_ = pays;
}

const std::string& Concepteur::getNom() const { return nom_; }

void Concepteur::setNom(std::string nom) { nom_ = move(nom); }

int Concepteur::getAnneeNaissance() const { return anneeNaissance_; }

void Concepteur::setAnneeNaissance(int annee) { anneeNaissance_ = annee; }

const std::string& Concepteur::getPays() const { return pays_; }

void Concepteur::setPays(std::string pays) { pays_ = move(pays); }