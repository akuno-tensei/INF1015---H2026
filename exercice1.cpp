void afficher(char c, int x) {
	if (x > 0) {
		for (int i = 0; i < x; i++) {
			std::cout << c;
		}
	}
}

void afficherTriangle(int x) {
	if (x > 1) {
		for (int i = 0; i < x; i++) {
			afficher(' ', x - i - 1);
			afficher('*', i);
			std::cout << '*';
			afficher('*', i);
			afficher(' ', x - i - 1);
			std::cout << std::endl;
		}
	}
}

void afficherTriangleV2(int x) {
	if (x == 1) {
		std::cout << '*';
	}
	else {
		for (int i = 0; i < x; i++) {
			for (int j = 0; j < 2 * x + 1; j++) {
				if (j == 2 * x) {
					std::cout << std::endl;
				}
				else if (i + j < x - 1) {
					std::cout << ' ';
				}
				else if (j > i + x - 1) {
					std::cout << ' ';
				}
				else {
					std::cout << '*';
				}
			}
		}
	}
}

int main() {
	afficherTriangleV2(10);
}