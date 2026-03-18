
/*
		Nom du fichier : VilainHeros.hpp
		Crée le 3 mars 2026
		Modifié le 18 mars 2026
		Auteurs : Paul Tankeu Pajouo (2373265), Diego Alejandro Monsalve Rivas (2343317)

		Description : Classe combine les caractéristiques de Heros et Vilain via un héritage multiple,
					  et ajoute une mission spéciale propre à ce type de personnage, avec des méthodes
					  pour afficher ses informations complètes.
*/

#pragma once

#include "Heros.hpp"
#include "Vilain.hpp"

class VilainHeros : public Heros, public Vilain {
	public:
		VilainHeros(const Heros& heros, const Vilain& vilain);
		~VilainHeros() override = default;
		void afficher(std::ostream& os) const override;

		void afficherMissionSpeciale(std::ostream& os) const;
		const std::string& obtenirMissionSpeciale() const { return missionSpeciale_; }

	private:
		std::string missionSpeciale_;
};

