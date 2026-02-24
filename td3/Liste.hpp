#pragma once
#include <iostream>
#include <span>
#include <functional>

constexpr unsigned int CAPACITE_INITIALE = 2;

// Rentdre la liste générique.
template <typename T> 
class Liste {
public:
	// Constructeurs et surcharges d'opérateurs
	Liste() {
		capacite_ = 0;
		nElements_ = 0;
		elements_.reset();
	}

	// Surcharge de l'opérateur [] pour accéder à un élément de la liste.
	std::shared_ptr<T> operator[] (unsigned indice) const {
		return elements_[indice];
	}

	// Méthode pour ajouter un élément à la liste
	void ajouterElement(std::shared_ptr<T> element) {
		if (capacite_ == nElements_) {
			redimensionnerListe();
		}

		auto critere = [&element](std::shared_ptr<T> elem) { return elem == element; };
		std::shared_ptr<T> elementPresent = this->trouverElement(critere);

		if (elementPresent != nullptr) {
			std::cerr << "L'élément est déjà présent dans la liste." << std::endl;
			return;
		}
		else {
			elements_[nElements_] = element;
			nElements_++;
		}
	}

	// Pour size, on utilise le même nom que les accesseurs de la bibliothèque standard, qui permet d'utiliser certaines fonctions de la bibliotheque sur cette classe.
	unsigned size() const         { return nElements_; }
	unsigned obtenirCapacite() const  { return capacite_; }

	// Méthode pour changer la capacité de la liste
	void redimensionnerListe() {
		unsigned int nouvelleCapacite = capacite_ != 0 ? capacite_ * 2 : CAPACITE_INITIALE;

		auto nouveauTableau =  std::make_unique<std::shared_ptr<T>[]>(nouvelleCapacite);

		for (unsigned i = 0; i < nElements_; ++i) {
			nouveauTableau[i] = std::move(elements_[i]);
		}

		elements_.reset();

		capacite_ = nouvelleCapacite;
		elements_ = std::move(nouveauTableau);
	}

	// Méthode pour trouver un élément selon un critère (lambda).
	std::shared_ptr<T> trouverElement(const std::function<bool(std::shared_ptr<T>)>& critere) const {
		for (unsigned i = 0; i < nElements_; ++i) {
			if (critere(elements_[i])) {
				return elements_[i];
			}
		}
		return nullptr;
	}

private:
	unsigned nElements_;
	unsigned capacite_;

	// Attribut contenant les éléments de la liste.
	std::shared_ptr<std::shared_ptr<T>[]> elements_;
};