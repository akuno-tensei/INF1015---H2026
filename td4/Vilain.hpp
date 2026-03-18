
/*
		Nom du fichier : Vilain.hpp
		Crée le 3 mars 2026
		Modifié le 18 mars 2026
		Auteurs : Paul Tankeu Pajouo (2373265), Diego Alejandro Monsalve Rivas (2343317)

		Description : Classe représentant un vilain, dérivée de Personnage, possédant un objectif spécifique.
					  Cette classe  étend Personnage en ajoutant un attribut décrivant l'objectif du vilain,
					  ainsi que des méthodes pour l'afficher en plus des informations de base du personnage.
*/

#pragma once
#include "Personnage.hpp"

class Vilain : virtual public Personnage {
	public:
		Vilain(const std::string& nom, const std::string& parution, const std::string& objectif);
		Vilain(const Vilain& autreVilain);
		~Vilain() override = default;

		void afficher(std::ostream& os) const override;

		void afficherObjectif(std::ostream& os) const;
		const std::string& obtenirObjectif() const { return objectif_; }

	private:
		std::string objectif_;
};