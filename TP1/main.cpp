
#include <iostream>

#include <string>

#include <fstream>

#include <map>




//================================================ Exercice1 ==========================================

void exercice1(int n) {
	if (n == 1) {
		std::cout << '*' << std::endl;
	}
	else {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < 2 * n + 1; j++) {
				if (j == 2 * n) {
					std::cout << std::endl;
				}
				else if (i + j < n - 1) {
					std::cout << ' ';
				}
				else if (j - i > n - 1) {
					std::cout << ' ';
				}
				else {
					std::cout << '*';
				}
			}
		}
	}
}

//=====================================================================================================


//================================================ Exercice2 ==========================================

char shift(char C, int key) {
	char result;
	int asciiC = (int)C;

	if (asciiC == (int)' ') {
		asciiC = '&';
	}
	else if (asciiC > 96) {
		asciiC = ((asciiC - (int)'a') + key) % 26 + (int)'a';
	}
	else {
		asciiC = ((asciiC - (int)'A') + key) % 26 + (int)'A';
	}
	result = (char)asciiC;

	return result;
}

std::string exercice2(std::string& phrase, int key) {
	for (int i = 0; i < phrase.length(); i++) {
		phrase[i] = shift(phrase[i], key);
	}

	return phrase;

}

//=====================================================================================================


//================================================ Exercice3 ==========================================

double minimum(double tab[], int dim) {
	double min = tab[0];
	for (int i = 1; i < dim; i++) {
		if (tab[i] < min) {
			min = tab[i];
		}
	}

	return min;
}

double maximum(double tab[], int dim) {
	double max = tab[0];
	for (int i = 1; i < dim; i++) {
		if (tab[i] > max) {
			max = tab[i];
		}
	}

	return max;
}

void exercice3(std::string filename = "aliments.txt") {
	std::string produit = "None", prix;
	std::fstream file(filename);
	int taille = 0;
	double tab[100];

	while (true) {
		std::getline(file, produit, ' ');
		std::getline(file, prix);
		if (produit == "") {
			break;
		}
		tab[taille] = std::stod(prix);
		taille += 1;
	}
	file.close();

	std::cout << "Maximum des prix du tableau : " << maximum(tab, taille) << std::endl;
	std::cout << "Minimum des prix du tableau : " << minimum(tab, taille) << std::endl;

}

//=====================================================================================================


//================================================ Exercice4 ==========================================

bool found(int tab[20][10], int rangee, int colonne, int places) {
	for (int i = 0; i < 10; i++) {
		for (int j = colonne; j < colonne + places; j++) {
			if (tab[i][j] == 0) {
				return false;
			}
		}
	}
	return true;
}

void exercice4(int n, int cinema[20][10]) {
	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 10; j++) {
			if (found(cinema, i, j, n)) {
				std::cout << "rangee " << i + 1 << "sieges de " << j + 1 << " a " << j + n << std::endl;
			}
		}
	}
}

//=====================================================================================================


//================================================ Exercice5 ==========================================

struct Etudiant {
	int matricule;
	std::string departement;
};

int collecte(Etudiant tab[], std::string filename) {
	std::string mat, dep;
	std::fstream file(filename);

	int indice = 0;
	while (true) {
		std::getline(file, mat, ' ');
		std::getline(file, dep);

		if (mat == "") {
			break;
		}

		Etudiant etudiant = { std::stoi(mat), dep };
		tab[indice] = etudiant;
		indice++;
	}

	file.close();
	return indice;
}

std::map<std::string, int> denombrement(Etudiant tab[], int start, int end, int taille = 400) {
	std::map<std::string, int> result = { {"Electrique", 0}, {"Informatique", 0}, {"Logiciel", 0}, {"Biomedical", 0}, {"Autre", 0} };

	for (int i = 0; i < taille; i++) {
		if (tab[i].matricule > end or tab[i].matricule < start) {
			continue;
		}
		else if (tab[i].departement == "ELE") {
			result["Electrique"] += 1;
		}
		else if (tab[i].departement == "INF") {
			result["Informatique"] += 1;
		}
		else if (tab[i].departement == "LOG") {
			result["Logiciel"] += 1;
		}
		else if (tab[i].departement == "GBM") {
			result["Biomedical"] += 1;
		}
		else {
			result["Autre"] += 1;
		}
	}
	return result;
}

void exercice5(std::string filename = "etudiants.txt") {
	Etudiant tab[400];
	
	int taille = collecte(tab, filename);

	int start, end;

	std::cout << "Entrez la plage de matricule (0 0 pour terminer) : ";
	
	std::cin >> start; std::cin >> end;

	std::map<std::string, int> stats = denombrement(tab, start, end, taille);

	std::cout << "Dans cette plage, il y a ces nombres d'etudiants dans chaque domaine : " << std::endl;

	for (auto dep : stats) {
		std::cout << dep.first << " : " << dep.second << std::endl;
	}

}

//====================================================================================================

int main()
{
	// Test exercice1 avec des triangles de hauteurs : 1, 2, 3, 4, 5, 6
	exercice1(1);
	exercice1(2);
	exercice1(3);
	exercice1(4);
	exercice1(5);
	exercice1(6);

	// Test exercice2 avec : Chiffrement par decalage
	std::string phrase = "Chiffrement par decalage";
	std::cout << exercice2(phrase, 4) << std::endl;

	// Test exercice3
	exercice3();

	// Test exercice4
	// Pas de test possible pour cette exo

	// Test exercice5
	exercice5();

}
