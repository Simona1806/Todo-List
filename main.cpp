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
        std::cin.ignore(1000, '\n');

        switch (scelta) {
            case 1: {
                std::string d, s, e;
                std::cout << "Cosa hai in piano per oggi? ";
                std::getline(std::cin, d);
                std::cout << "Ora inizio (HH:MM): ";
                std::getline(std::cin, s);
                std::cout << "Ora fine (HH:MM):   ";
                std::getline(std::cin, e);
                //Uso le eccezioni per assicurarmi che la scelta sia stata salvata correttamente
                try {
                    manager.addEntry(d, s, e);
                    std::cout << ">> Attivita' aggiunta e salvata!" << std::endl;
                } catch (const std::exception& ex) {
                    std::cerr << "ERRORE: " << ex.what() << std::endl;
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
                            manager.changeStatus(idx - 1);
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
                            manager.removeEntry(idx - 1);
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