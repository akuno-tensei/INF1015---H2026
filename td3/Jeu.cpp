/*
	Fichier : Jeu.cpp
	Auteur : Paul Tankeu Pajouo (2373265), Diego Alejandro Monsalve Rivas (2343317)
	Crée le : 2026-02-24
	Modifié le : 2026-02-24

	Description: Ce fichier contient l'implémentation de la classe Jeu, qui représente un jeu vidéo, avec ses attributs et méthodes.
 */

#pragma once
#include "Jeu.hpp"

Jeu::Jeu() {
	titre_ = "Inconnu";
	anneeSortie_ = 0;
	developpeur_ = "Inconnu";
}

Jeu::Jeu(std::string titre, unsigned anneeSortie, std::string developpeur) {
	titre_ = titre;
	anneeSortie_ = anneeSortie;
	developpeur_ = developpeur;
}

Jeu::Jeu(const Jeu& autre) {
	*this = autre;
}

Jeu&  Jeu::operator=(const Jeu& autre) {
	if (this != &autre) {
		titre_ = autre.titre_;
		anneeSortie_ = autre.anneeSortie_;
		developpeur_ = autre.developpeur_;
		listeConcepteurs_ = autre.listeConcepteurs_;  // La classe Liste doit faire une copie profonde de ses éléments.
	}
	return *this;
}

const std::string& Jeu::getTitre() const { return titre_; }

void Jeu::setTitre(std::string titre) { titre_ = move(titre); }

unsigned Jeu::getAnneeSortie() const { return anneeSortie_; }

void Jeu::setAnneeSortie(unsigned annee) { anneeSortie_ = annee; }

const std::string& Jeu::getDeveloppeur() const { return developpeur_; }

void Jeu::setDeveloppeur(std::string developpeur) { developpeur_ = move(developpeur); }

ListeConcepteurs& Jeu::accederListeConcepteurs() { return listeConcepteurs_; }

void Jeu::changerConcepteur(unsigned indice, std::shared_ptr<Concepteur> autreConcepteur) {
	listeConcepteurs_[indice] = autreConcepteur;
}

std::shared_ptr<Concepteur> Jeu::trouverConcepteur(const std::function<bool(std::shared_ptr<Concepteur>)>& critere) const {
	return listeConcepteurs_.trouverElement(critere);
}
