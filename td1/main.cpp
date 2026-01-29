/*
Fichier : main.cpp
Auteurs : Diego Alejandro Monsalve Rivas (2343317), Paul Tankeu Pajouo (2373265)

Description : 
	- exercice1 : Affiche avec des "*" un triangle isocele de hauteur fournie par l'utilisateur
	- exercice2 : Affiche le code Cesar d'une phrase fournie par l'ulisateur (cle de decalage aussi fournie par lui)
	- exercice3 : Lit un fichier contenant des pairs (produits et valeurs) et affiche le maximum et le minimum des valeurs
	- exercice4 : Pour un modele de salle de cinema donnee (sous forme de tableau), affiche toutes les possibilites de dispositions sur une meme rangee
	              en fonction du nombre de places voulus par l'utlisateur
	- exercice5 : Lit un fichier d'etudiant contenant des pairs (matricule, departement) et affiche le nomnbre d'etudiants par departement
                  en fonction de la plage de recherche (plage de matricules) fournie par l'utlisateur
*/


#include <iostream>

#include <string>

#include <fstream>


//================================================ Exercice1 ==========================================

/* Affiche un triangle d'etoiles isocele de hauteur "n" */
void exercice1() {
	int n;
	std::cout << "Entrer la hauteur du triange : "; 
	std::cin >> n;

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

/* D�cale un caractere C de "key" positions dans l'alphabet */
char decalerCaractere(char C, int key) {
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

/* Chiffre une phrase en d�calant chaque caractere de "key" positions */
std::string chifferPhrase(const std::string& phrase, int key) {
	std::string result = "";
	for (int i = 0; i < phrase.length(); i++) {
		result += decalerCaractere(phrase[i], key);
	}

	return result;
}

/* Demande une phrase et une cle de chiffrement a l'utilisateur et affiche la phrase cryptee */
void exercice2() {
	std::string phrase; int key;
	
	std::cin.ignore();
	std::cout << "Veuillez entrer une phrase : "; 
	std::getline(std::cin, phrase);

	while (true) {

		std::cout << "Veuillez enter la cle de chiffrement (entre 1 et 17) : "; 
		std::cin >> key;

		if (key > 0 && key < 18) {
			break;
		}
		else {
			std::cout << "La cle de chiffrement entree n'est pas valide !" << std::endl;
		}
	}

	std::cout << "Voici la phrase encryptee : " << chifferPhrase(phrase, key) << std::endl;
}

//=====================================================================================================


//================================================ Exercice3 ==========================================

/* Trouve le minimum d'un tableau de double */
double trouverMinimum(double tab[], int dim) {
	double min = tab[0];
	for (int i = 1; i < dim; i++) {
		if (tab[i] < min) {
			min = tab[i];
		}
	}

	return min;
}

/* Trouve le maximum d'un tableau de double */
double trouverMaximum(double tab[], int dim) {
	double max = tab[0];
	for (int i = 1; i < dim; i++) {
		if (tab[i] > max) {
			max = tab[i];
		}
	}

	return max;
}

/* Lit un fichier contenant des produits et leurs prix,
stocke les prix dans un tableau, puis affiche le maximum et le minimum des prix */
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

	std::cout << "Maximum des prix du tableau : " << trouverMaximum(tab, taille) << std::endl;
	std::cout << "Minimum des prix du tableau : " << trouverMinimum(tab, taille) << std::endl;

}

//=====================================================================================================


//================================================ Exercice4 ==========================================

/* Verifie si un nombre de places est disponible dans une rangee a partir d'une colonne donnee */
bool trouverPlacesLibres(int tab[20][10], int rangee, int colonne, int places) {

	for (int i = colonne; i < colonne + places; i++) {
		if (tab[rangee][i] == 1) {
			return false;
		}
	}

	return true;
}

/* Affiche toutes les places disponibles dans un cinema */
void exercice4(int cinema[20][10]) {

	int n;
	std::cout << "Le nombre de places souhaitees : "; 
	std::cin >> n;

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 10; j++) {
			if (j == 9) {
				std::cout << cinema[i][j] << std::endl; 
			}
			else {
				std::cout << cinema[i][j];
			}
		}
	}

	for (int i = 0; i < 20; i++) {
		for (int j = 0; j < 10 - n + 1; j++) {
			if (trouverPlacesLibres(cinema, i, j, n)) {
				std::cout << "rangee " << i + 1 << " sieges de " << j + 1 << " a " << j + n << std::endl;
			}
		}
	}
}

int cinema[20][10] = {
							{0,0,1,1,1,0,1,1,1,1},
							{1,1,1,0,1,0,1,0,1,1},
							{0,0,0,1,1,0,0,1,1,1},
							{1,0,0,0,1,1,0,0,0,1},
							{1,0,1,0,1,1,0,1,0,0},
							{0,0,1,0,0,1,1,1,0,1},
							{1,1,1,0,0,1,1,1,0,0},
							{1,0,1,0,0,1,1,0,0,0},
							{1,0,1,0,1,1,1,1,1,0},
							{1,0,0,0,0,0,0,0,0,0},
							{1,1,1,1,0,0,0,1,1,0},
							{0,1,0,0,1,0,0,1,0,1},
							{0,0,0,0,0,1,0,0,1,1},
							{0,0,0,1,1,1,1,0,1,1},
							{0,1,1,0,0,1,1,0,0,0},
							{0,1,1,0,1,1,0,0,0,0},
							{0,1,1,1,0,0,0,1,0,1},
							{1,0,1,0,0,1,0,0,0,1},
							{1,0,0,0,0,0,0,0,1,1},
							{0,1,1,0,0,0,1,1,1,0}
};

//=====================================================================================================


//================================================ Exercice5 ==========================================

/* Structure repr�sentant un etudiant */
struct Etudiant {
	int matricule = 0;
	std::string departement;
};

/* Lit un fichier contenant des etudiants et leurs departements, et les stocke dans un tableau.
Retourne le nombre d'etudiants lus */
int recupererMatriculeDepartement(Etudiant tab[], std::string filename) {
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

/* D�nombre les etudiants dans chaque departement */
void compterEtudiants(Etudiant tab[], int stats[], int start, int end, int taille = 400) {

	for (int i = 0; i < taille; i++) {
		if (tab[i].matricule > end || tab[i].matricule < start) {
			continue;
		}
		else if (tab[i].departement == "ELE") {
			stats[0] += 1;
		}
		else if (tab[i].departement == "INF") {
			stats[1] += 1;
		}
		else if (tab[i].departement == "LOG") {
			stats[2] += 1;
		}
		else if (tab[i].departement == "GBM") {
			stats[3] += 1;
		}
		else {
			stats[4] += 1;
		}
	}
}

/* D�nombre les etudiants dans chaque departement selon une plage de matricules */
void exercice5(std::string filename = "etudiants.txt") {
	Etudiant* tab = new Etudiant[400];
	
	int taille = recupererMatriculeDepartement(tab, filename);

	int start, end;

	std::string correspondance[5] = { "Electrique" , "Informatique" , "Logiciel" , "Biomedical" , "Autre" };

	while (true) {
		int stats[5] = { 0, 0, 0, 0, 0 };

		std::cout << "Entrez la plage de matricule (0 0 pour terminer) : ";

		std::cin >> start; std::cin >> end;

		if (start == 0 && end == 0) {
			break;
		}

		compterEtudiants(tab, stats, start, end, taille);

		std::cout << "Dans cette plage, il y a ces nombres d'etudiants dans chaque domaine : " << std::endl;

		for (int i = 0; i < 5; i++) {
			std::cout << correspondance[i] << " : " << stats[i] << std::endl;
		}
	}
	delete[] tab;
}

//====================================================================================================

int main()
{
	// Test exercice1
	exercice1();

	// Test exercice2
	exercice2();
	

	// Test exercice3
	exercice3();

	// Test exercice4
	exercice4(cinema);

	// Test exercice5
	exercice5();

}
