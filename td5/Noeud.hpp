/*
		Nom du fichier : Noeud.hpp
		Crée le 19 mars 2026
		Modifié le 1 avril 2026
		Auteurs : Paul Tankeu Pajouo (2373265), Diego Alejandro Monsalve Rivas (2343317)

		Description : Ce fichier contient la définition de la classe Noeud, 
					  qui représente un élément d'une liste doublement liée.  
					  Chaque noeud contient une donnée de type T, 
					  ainsi que des pointeurs vers le noeud suivant et le noeud précédent dans la liste.
*/


#pragma once
#include <gsl/pointers>

template<typename T> class ListeLiee;
template<typename T> class Iterateur;

template<typename T>
class Noeud
{
public:
	Noeud() = default;

	Noeud(const T& donnee) :
		suivant_(nullptr),
		precedent_(nullptr)
	{
		donnee_ = make_unique<T>(donnee);
	}

	bool operator==(const Noeud& noeud) { return *donnee_ == *(noeud.donnee_); }

private:
	unique_ptr<Noeud<T>> suivant_ = nullptr;
	Noeud<T>* precedent_ = nullptr;
	unique_ptr<T> donnee_ = nullptr;

	// inline static constexpr unique_ptr<T> FIN = nullptr;

	friend class ListeLiee<T>;
	friend class Iterateur<T>;
};
