#include "TodoManager.h"
#include <iostream>
#include <fstream>
#include <stdexcept> // Necessario per le eccezioni

TodoManager::TodoManager() {
    loadData();//va a leggere il file dove sono stati salvati i task
}

void TodoManager::addEntry(const std::string& desc, const std::string& start, const std::string& end) {
    taskList.emplace_back(desc, start, end);//aggiunge il nuovo task
    autoSave();//salva il task sul file
}

void TodoManager::removeEntry(int index) {
    // Controllo che il numero del task selezionato per essere calcellato sia corretto
    //se non è corretto lancia una eccezione
    if (index < 0 || index >= taskList.size()) {
        throw std::out_of_range("Numero attivita' non valido! L'attivita' non esiste.");
    }
    //altrimenti lo cancella
    taskList.erase(taskList.begin() + index);
    autoSave();//e aggiorna il file
}

void TodoManager::changeStatus(int index) {
    // Controllo indice con lancio di eccezione
    if (index < 0 || index >= taskList.size()) {
        throw std::out_of_range("Numero attivita' non valido! Impossibile cambiare stato.");
    }
    taskList[index].toggleStatus();
    autoSave();
}
//permette di visualizzare i task
void TodoManager::showList() const {
    if (taskList.empty()) {
        std::cout << "\n>>> Nessuna attivita' presente." << std::endl;
        return;
    }
    std::cout << "\n--- LISTA ATTIVITA' ---" << std::endl;
    for (size_t i = 0; i < taskList.size(); i++) {
        std::cout << i + 1 << ". " << taskList[i].toString() << std::endl;
    }
}
//aggiorna il file
void TodoManager::autoSave() const {
    std::ofstream file(fileName);
    if (!file.is_open()) {
        throw std::runtime_error("Errore critico: Impossibile accedere al file per il salvataggio.");
    }
    for (const auto& t : taskList) {
        file << t.getDescription() << ";" << t.getStartTime() << ";"
             << t.getEndTime() << ";" << t.getStatus() << "\n";
    }
    file.close();
}
//carica i task sul file
void TodoManager::loadData() {
    std::ifstream file(fileName);
    if (!file.is_open()) return;

    std::string desc, start, end, statusStr;
    while (std::getline(file, desc, ';')) {
        std::getline(file, start, ';');
        std::getline(file, end, ';');
        std::getline(file, statusStr);
        if (!desc.empty()) {
            taskList.emplace_back(desc, start, end, (statusStr == "1"));
        }
    }
    file.close();
}

bool TodoManager::hasNoTasks() const { return taskList.empty(); }