#include <iostream>
#include <string>
#include <stdexcept>
#include "TodoManager.h"

int main() {
    TodoManager manager;
    int scelta = -1;

    while (scelta != 0) {
        manager.showList();
        std::cout << "\n----- TODO LIST MENU -----" << std::endl;
        std::cout << "1. Aggiungi Attivita'" << std::endl;
        std::cout << "2. Inverti Stato Attivita' (Da fare/Fatto)" << std::endl;
        std::cout << "3. Elimina Attivita'" << std::endl;
        std::cout << "0. Esci" << std::endl;
        std::cout << "==========================" << std::endl;
        std::cout << "Scelta: ";

        // Controllo che l'utente non inserisca una stringa
        if (!(std::cin >> scelta)) {
            std::cout << "\n>>> ERRORE: Devi inserire un numero! <<<\n" << std::endl;
            std::cin.clear();//serve per resettare lo stato di fallimento del cin
            std::cin.ignore(1000, '\n');// Pulisce il buffer
            scelta = -1;
            continue;
        }
        std::cin.ignore(1000, '\n');//serve per cancellare il '\n' dell'invio
        //la funzione getline legge tutto finchè non trova \n, se viene lasciato si fermerà li senza leggere la descrizione del task o altro

        switch (scelta) {
            case 1: {
                std::string d;
                int h1, m1, h2, m2;
                char impChar;

                std::cout << "Cosa hai in piano per oggi? ";
                std::getline(std::cin, d);//legge finche trova \n, non uso cin per questo

                std::cout << "Ora inizio (HH MM): ";
                if (!(std::cin >> h1 >> m1)) {
                    std::cout << "Errore input orario!" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    break;
                }

                std::cout << "Ora fine (HH MM): ";
                if (!(std::cin >> h2 >> m2)) {
                    std::cout << "Errore input orario!" << std::endl;
                    std::cin.clear();
                    std::cin.ignore(1000, '\n');
                    break;
                }

                std::cout << "E' importante? (s/n): ";
                std::cin >> impChar;
                std::cin.ignore(10000, '\n');
                bool isImp = (impChar == 's' || impChar == 'S');

                try {
                    manager.addEntry(d, Time(h1, m1), Time(h2, m2), isImp);
                    std::cout << ">> Task aggiunto correttamente!" << std::endl;
                } catch (const std::exception& e) {
                    std::cerr << "ERRORE: " << e.what() << std::endl;
                }
                break;
            }

            case 2: {
                if (manager.hasNoTasks()) {
                    std::cout << ">> Nessun task disponibile." << std::endl;
                } else {
                    int idx;
                    std::cout << "Del quale task vuoi modificare lo stato?: ";
                    if (std::cin >> idx) {
                        try {
                            manager.changeStatus(idx);
                            std::cout << ">> Stato aggiornato!" << std::endl;
                        } catch (const std::out_of_range& ex) {
                            std::cerr << "ERRORE: " << ex.what() << std::endl;
                        }
                    }
                }
                break;
            }

            case 3: {
                if (manager.hasNoTasks()) {
                    std::cout << ">> Nulla da eliminare." << std::endl;
                } else {
                    int idx;
                    std::cout << "Inserisci il numero del task da eliminare: ";
                    if (std::cin >> idx) {
                        try {
                            manager.removeEntry(idx);
                            std::cout << ">> Attivita' rimossa con successo!" << std::endl;
                        } catch (const std::out_of_range& ex) {
                            std::cerr << "ERRORE: " << ex.what() << std::endl;
                        }
                    }
                }
                break;
            }

            case 0:
                std::cout << "Uscita in corso..." << std::endl;
                break;

            default:
                std::cout << "Opzione non valida, riprova." << std::endl;
                break;
        }
    }

    std::cout << "Dati salvati automaticamente. A presto!" << std::endl;
    return 0;
}