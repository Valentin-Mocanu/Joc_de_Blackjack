#include <iostream>
#include <cstdlib> // Pentru rand() si srand()
#include <chrono> // Pentru masurarea timpului
#include <thread> // Pentru sleep (pauza)

using namespace std::this_thread;
using namespace std::chrono;

class Player {
private:
	int money = 100; // Banii jucatorului in momentul inceperii jocului
	int player_card; // Cartea aleasa random jucatorului
	int cards_on_table; // Reprezinta suma cartilor alese pana in acel moment, de pe masa
	int player_bet; // Pariul jucatorului (daca pierde, bani = bani - pariaza; daca castiga, bani = bani + pariaza)
	char initial_player_input; // Ofera optiunea jucatorului daca vrea sa porneasca jocul sau nu

public:
	void start_game() { // Inceputul jocului
		std::cout << "#==================================#";
		std::cout << "\n Bine ati venit la jocul Blackjack!";
		std::cout << "\n#==================================#";
		sleep_for(seconds(1)); // Aceasta comanda face o mica pauza de 2 secunde pentru a crea atmosfera unui joc si de a nu grabi lucrurile
		std::cout << "\n\nSuma dumneavoastra de bani: " << money << "$";
		sleep_for(seconds(1));
		std::cout << "\n\tDoriti sa incepeti jocul? (scrieti 'D' pentru DA sau orice alt caracter pentru NU): ";
		std::cin >> initial_player_input;
		sleep_for(seconds(1));

		if (initial_player_input == 'd' || initial_player_input == 'D') {
			place_bet();
		}

		else {
			std::cout << "\n\tAti iesit din joc!";
			std::cout << "\n#==================================#";
			return;
		}
	}

	void place_bet() { // Pariul dat de catre jucator
		bool bet_status = false; // Util pentru while

		if (money == 0) {
			std::cout << "\nNu mai aveti bani sa jucati! Din acest motiv nu mai puteti continua jocul!\n";
			sleep_for(seconds(1));
			std::cout << "\n\tAti iesit din joc!";
			std::cout << "\n#==================================#";
			return;
		}

		while (bet_status == false) {
			std::cout << "\nCat vreti sa pariati? Introduceti suma: ";
			std::cin >> player_bet;

			if (player_bet <= money && player_bet > 0) {
				bet_status = true;
				run_game();
			}

			else {
				std::cout << "\nSuma nevalida! Reluam pariul...";
			}
		}
	}

	void handle_win(int player_card_prediction1, int cards_on_table_prediction1) { // Este apelat atunci cand jucatorul castiga in momentul in care se opreste din a mai trage o carte
		sleep_for(seconds(2));
		std::cout << "\n\n---> ATI CASTIGAT! <---";
		sleep_for(seconds(1));
		std::cout << "\n\t+" << player_bet << "$ in contul dumneavoastra!";
		money = money + player_bet;
		sleep_for(seconds(1));
		std::cout << "\nDaca alegeati sa continuati jocul, cartea aleasa era " << player_card_prediction1 << ", iar suma de pe masa devenea " << cards_on_table_prediction1;
		sleep_for(seconds(1));
		std::cout << "\n\nReluam jocul...\n\n";
		sleep_for(seconds(2));
	}

	void handle_loss(int player_card_prediction1, int cards_on_table_prediction1) { // Este apelat atunci cand jucatorul pierde in momentul in care se opreste din a mai trage o carte
		sleep_for(seconds(2));
		std::cout << "\n\n---> GAME OVER! <---";
		sleep_for(seconds(1));
		std::cout << "\n\tAti pierdut -" << player_bet << "$";
		sleep_for(seconds(1));
		std::cout << "\nDaca alegeati sa continuati jocul, cartea aleasa era " << player_card_prediction1 << ", iar suma de pe masa devenea " << cards_on_table_prediction1;
		money = money - player_bet;
		sleep_for(seconds(1));
		std::cout << "\n\nReluam jocul...\n\n";
		sleep_for(seconds(2));
	}

	void run_game() { // Jocul propriu zis
		sleep_for(seconds(1));
		cards_on_table = std::rand() % 11 + 1; // Genereaza o carte (un numar) intre 1 si 11, care este stocata in suma_masa. Urmatoarele generari ale viitoarelor carti se vor face in carte_jucator
		std::cout << "------------------------------";
		std::cout << "\nA picat cartea cu numarul " << cards_on_table;
		std::cout << "\n------------------------------";
		char player_choice; // Necesar pentru ca jucatorul sa aleaga daca mai continua sau nu
		std::cout << "\n\tCe faceti? Alegeti o carte sau va opriti? (tastati 'A' pentru a continua / 'V' pentru a va opri): ";
		std::cin >> player_choice;

		if (player_choice == 'v' || player_choice == 'V') {
			int player_card_prediction1 = (std::rand() % 11 + 1); // Folosit pentru a vedea predictia urmatoarei carti alese atunci cand jucatorul se opreste
			int cards_on_table_prediction1 = cards_on_table + player_card_prediction1; // Folosit pentru a vedea predictia sumei cartilor alese de catre jucator pana in acel moment, de pe masa, atunci cand jucatorul se opreste

			if (cards_on_table_prediction1 > 21) {
				handle_win(player_card_prediction1, cards_on_table_prediction1);
				player_choice = 'v';
				start_game();
			}

			else {
				handle_loss(player_card_prediction1, cards_on_table_prediction1);
				player_choice = 'v';
				start_game();
			}
		}

		while (player_choice == 'a' || player_choice == 'A') {
			sleep_for(seconds(1));
			player_card = std::rand() % 11 + 1; // Genereaza o alta carte
			std::cout << "------------------------------";
			std::cout << "\nA picat cartea cu numarul " << player_card;
			cards_on_table = cards_on_table + player_card; // Face suma intre cartea/cartile vechi si cea noua
			std::cout << "\nSuma de pe masa este de " << cards_on_table;
			std::cout << "\n------------------------------";

			if (cards_on_table > 21) {
				sleep_for(seconds(1));
				std::cout << "\n\n---> GAME OVER! <---";
				sleep_for(seconds(1));
				std::cout << "\n\tAti pierdut -" << player_bet << "$";
				money = money - player_bet;
				sleep_for(seconds(1));
				std::cout << "\n\nReluam jocul...\n\n";
				sleep_for(seconds(2));
				player_choice = 'v';
				start_game();
			}

			else if (cards_on_table == 21) {
				sleep_for(seconds(1));
				std::cout << "\n\n---> ATI CASTIGAT <---";
				std::cout << "\nSuma de pe masa este fix 21! Felicitari!";
				sleep_for(seconds(1));
				std::cout << "\n\t+" << player_bet << "$ in contul dumneavoastra!";
				money = money + player_bet;
				sleep_for(seconds(1));
				std::cout << "\n\nReluam jocul...\n\n";
				sleep_for(seconds(2));
				player_choice = 'v';
				start_game();
			}

			else {
				std::cout << "\n\tCe faceti? Alegeti o carte sau va opriti? (tastati 'A' pentru a continua / 'V' pentru a va opri): ";
				std::cin >> player_choice;

				if (player_choice == 'v' || player_choice == 'V') {
					int player_card_prediction2 = (std::rand() % 11 + 1); // Are acelasi rol ca player_card_prediction1
					int cards_on_table_prediction2 = cards_on_table + player_card_prediction2; // Are acelasi rol ca cards_on_table_prediction1

					if (cards_on_table_prediction2 > 21) {
						handle_win(player_card_prediction2, cards_on_table_prediction2);
						player_choice = 'v';
						start_game();
					}

					else {
						handle_loss(player_card_prediction2, cards_on_table_prediction2);
						player_choice = 'v';
						start_game();
					}
				}
			}
		}
	}
};

int main() {
	srand(time(0)); // Initializeaza generatorul de numere aleatoare cu timpul curent, ca rezultatele sa fie diferite la fiecare rulare
	Player player;
	player.start_game();
}