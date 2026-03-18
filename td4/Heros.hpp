
/*
		Nom du fichier : Heros.hpp
		Crée le 3 mars 2026
		Modifié le 18 mars 2026
		Auteurs : Paul Tankeu Pajouo (2373265), Diego Alejandro Monsalve Rivas (2343317)

		Description : Classe représentant un heros, dérivée de Personnage, pouvant gérer une liste d'ennemis et d'alliés.
					  Cette classe étend Personnage en ajoutant la gestion d'une collection de noms
					  correspondant aux ennemis et alliés du héros, ainsi que des méthodes pour les
					  ajouter et les afficher.
*/

#pragma once
#include "Personnage.hpp"
#include <vector>
#include <span>

class Heros : virtual public Personnage {
	public:
		Heros(const std::string& nom, const std::string& parution);
		Heros(const Heros& autre);
		~Heros() override = default;

		// void redimensionnerListe(unsigned int nouvelleTaille);
		void ajouterPersonnage(const std::string& nom);
		void afficher(std::ostream& os) const override;

		const std::vector<std::string>& obtenirListe() const { return listeEnnemiAllies_; }
		void afficherListeEnnemiAllies(std::ostream& os) const;

	private:
		std::vector<std::string> listeEnnemiAllies_;
};