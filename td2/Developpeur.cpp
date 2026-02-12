/*
	Fichier : Developpeur.cpp
	Auteurs : Diego Alejandro Monsalve Rivas (2343317), Paul Tankeu Pajouo (2373265)
	Date : 11 février 2026
	Crée le 5 février 2026
*/


#include "Developpeur.hpp"



Developpeur::Developpeur() {
	paireNomJeux_.first = "Inconnu";

	paireNomJeux_.second.capacite = 0;
	paireNomJeux_.second.nElements = 0;
	paireNomJeux_.second.elements = nullptr;
}

Developpeur::Developpeur(const std::string& nom) {
	paireNomJeux_.first = nom;

	paireNomJeux_.second.capacite = 0;
	paireNomJeux_.second.nElements = 0;
	paireNomJeux_.second.elements = nullptr;
}

Developpeur::~Developpeur() {
	paireNomJeux_.second.nElements = 0;
	paireNomJeux_.second.capacite = 0;
	delete[] paireNomJeux_.second.elements;
}


const std::string Developpeur::obtenirNom() const {
	return this->paireNomJeux_.first;
}

void Developpeur::afficherTitresJeuxDeveloppeur() const {
	std::cout << "Nom du développeur : " << this->obtenirNom() << std::endl << std::endl;
	std::cout << "  ---------- Liste des Jeux ----------" << std::endl;
	unsigned i = 0;
	for (Jeu* jeu : std::span(paireNomJeux_.second.elements, paireNomJeux_.second.nElements)) {
		std::cout << "Jeu " << ++i << " : " << jeu->titre << std::endl;
	}
}

int Developpeur::compterNombreJeux(const ListeJeux& listeJeux) const {
	unsigned n = 0;

	for (Jeu* jeu : std::span(listeJeux.elements, listeJeux.nElements)) {
		if (jeu->developpeur == this->obtenirNom()) {
			++n;
		}
	}

	return n;
}

bool siJeuDejaDansListeJeux(const ListeJeux& listeJeux, Jeu* jeuATrouver) {
	for (Jeu* jeu : std::span(listeJeux.elements, listeJeux.nElements)) {
		if (jeu == jeuATrouver) {
			return true;
		}
	}
	return false;
}

void Developpeur::ajouterJeuAListeJeux(Jeu* jeu) {
	unsigned nElements = paireNomJeux_.second.nElements;

	if (siJeuDejaDansListeJeux(this->paireNomJeux_.second, jeu) ==  false) {
		this->paireNomJeux_.second.elements[nElements] = jeu;
		this->paireNomJeux_.second.nElements++;
	}
		
}

void redimensionnerListeJeux(ListeJeux& listeJeux, unsigned capacite) {

		listeJeux.capacite = capacite;

		Jeu** nouveauTableau = new Jeu* [capacite];

		for (unsigned i = 0; i < listeJeux.nElements; ++i) {
			nouveauTableau[i] = listeJeux.elements[i];
		}

		delete[] listeJeux.elements;
		listeJeux.elements = nouveauTableau;
}

void Developpeur::mettreAJourListeJeux(const ListeJeux& listeJeux) {
	this->paireNomJeux_.second.capacite = compterNombreJeux(listeJeux);

	redimensionnerListeJeux(this->paireNomJeux_.second, this->paireNomJeux_.second.capacite);

	if (this->paireNomJeux_.second.capacite > this->paireNomJeux_.second.nElements) {

		for (Jeu* jeu : std::span(listeJeux.elements, listeJeux.nElements)) {
			if (jeu->developpeur == this->obtenirNom()) {
				ajouterJeuAListeJeux(jeu);
			}
		}
	}
}