/*
			Nom du fichier : Iterateur.hpp
			Crée le 19 mars 2026
			Modifié le 1 avril 2026
			Auteurs : Paul Tankeu Pajouo (2373265), Diego Alejandro Monsalve Rivas (2343317)

			Description : Ce fichier contient la définition de la classe Iterateur, 
						  qui est utilisée pour parcourir les éléments d'une ListeLiee.  
							L'itérateur permet d'avancer et de reculer dans la liste, 
							ainsi que de comparer des itérateurs et de déréférencer pour accéder aux éléments.
*/

#pragma once
#include "noeud.hpp"
#include "gsl/gsl_assert"
template<typename T>
class Iterateur
{
	friend class ListeLiee<T>;

	public:

		Iterateur() = default;

		Iterateur(Noeud<T>* noeud) : position_(noeud) {}

		~Iterateur() = default;

		void avancer() {
			if (position_) {
				position_ = position_->suivant_.get();
			}
		}
	
		void reculer() {
			if (position_) {
				position_ = position_->precedent_;
			}
		}

		bool operator==(const Iterateur<T>& it) const = default;

		Iterateur<T>& operator++() {
			avancer();
			return *this;
		}

		T& operator*() const { return *(position_->donnee_); }

	private:
		Noeud<T>* position_ = nullptr;
};

