/*
	Fichier : ListeDeveloppeurs.cpp
	Auteurs : Diego Alejandro Monsalve Rivas (2343317), Paul Tankeu Pajouo (2373265)
	Date : 11 février 2026
	Crée le 5 février 2026
*/

#pragma once

#include "ListeDeveloppeurs.hpp"

ListeDeveloppeurs::ListeDeveloppeurs() {
	nElements_ = 0;
	capacite_ = 0;
	elements_ = nullptr;
}

ListeDeveloppeurs::~ListeDeveloppeurs() {
	nElements_ = 0;
	capacite_ = 0;
	delete[] elements_;
}

void ListeDeveloppeurs::afficher() const {
	for (Developpeur* developpeur : std::span(this->elements_, this->nElements_)) {
		std::cout << "\n\033[34m------------------------------------------\033[0m\n" << std::endl;
		developpeur->afficherTitresJeuxDeveloppeur();
		std::cout << "\n\033[34m------------------------------------------\033[0m\n" << std::endl;
	}
}

void ListeDeveloppeurs::redimensionnerListeDeveloppeurs() {

	const unsigned nouvelleCapacite = this->capacite_ != 0 ? this->capacite_ * 2 : 2;

	Developpeur** nouveauTableau = new Developpeur* [nouvelleCapacite];

	for (unsigned i = 0; i < this->nElements_; ++i) {
		nouveauTableau[i] = this->elements_[i];
	}

	delete[] this->elements_;

	this->capacite_ = nouvelleCapacite;
	this->elements_ = nouveauTableau;
}

bool siDeveloppeurPresent(Developpeur** listeDeveloppeurs, unsigned nElements, Developpeur& developpeurAChercher) {
	for (const Developpeur* developpeur : std::span(listeDeveloppeurs, nElements)) {
		if (developpeur->obtenirNom() == developpeurAChercher.obtenirNom()) {
			return true;
		}
	}
	return false;
}

void ListeDeveloppeurs::ajouterDeveloppeur(Developpeur& developpeur) {
	if (siDeveloppeurPresent(this->elements_, this->nElements_, developpeur) == false) {
		if (this->nElements_ == this->capacite_) {
			this->redimensionnerListeDeveloppeurs();
		}
		this->elements_[this->nElements_] = &developpeur;
		this->nElements_++;
	}
}

void ListeDeveloppeurs::retirerDeveloppeur(Developpeur& developpeur) {

	Developpeur** nouveauTableau = new Developpeur* [this->capacite_];

	unsigned j = 0;

	for (unsigned i = 0; i < this->nElements_; ++i) {
		if (this->elements_[i] != &developpeur) {
			nouveauTableau[j] = this->elements_[i];
			++j;
		}
	}

	delete[] this->elements_;

	this->nElements_--;
	this->elements_ = nouveauTableau;
}