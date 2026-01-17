#include "TodoManager.h"
#include <iostream>
#include <fstream>
#include <stdexcept> // Necessario per le eccezioni
#include <algorithm> // Necessario per std::sort

TodoManager::TodoManager() {
    loadData();//va a pescare il contenuto del file dove sono stati salvati i task
}
//funzione che ordina i task in ordine crescente di orario
void TodoManager::sortTasks() {
    // std::sort userà automaticamente l'operator < sovracaricato
    std::sort(taskList.begin(), taskList.end());
}

void TodoManager::addEntry(const std::string& desc, const Time& start, const Time& end, bool important) {
    //Controllo che l'ora di inizio sia prima di quella finale
    if (start >= end) {
        throw std::invalid_argument("L'orario di inizio deve essere precedente all'orario di fine.");
    }

    // Controllo sovrapposizione
    if (Overlapping(start, end)) {
        throw std::runtime_error("Attenzione: questo orario si sovrappone a un'attivita' gia' esistente!");
    }
    //Se tutto è ok, aggiungo(incrementando id),ordino e salvo
    taskList.emplace_back(nextId, desc, start, end,false, important);
    nextId++;
    sortTasks();
    autoSave();
}
void TodoManager::removeEntry(int index) {
    // Controllo che il numero del task selezionato per essere calcellato sia corretto
    //se non è corretto, lancia una eccezione
    if (index <= 0) {
        throw std::out_of_range("Numero attivita' non valido!");
    }
    //altrimenti lo cancella
    for (auto it = taskList.begin(); it != taskList.end(); ++it) {
        if (it->getId() == index) {
            taskList.erase(it);
            autoSave();

            return;
        }
    }
    throw std::out_of_range("ID non trovato!");

}

void TodoManager::changeStatus(int index) {
    // Controllo indice con lancio di eccezione
    bool trovato = false;
    for (auto& t : taskList) {
        if (t.getId() == index) {
            t.toggleStatus();
            trovato = true;
            break;
        }
    }
    if (!trovato) {
        throw std::out_of_range("ID non trovato! Impossibile cambiare lo stato.");
    }

    autoSave();
}
//permette di visualizzare i task
void TodoManager::showList() const {
    if (taskList.empty()) {
        std::cout << "Nessunta attivita' presente." << std::endl;
        return;
    }

    std::cout << "\n===============================" << std::endl;
    std::cout << "       TASK IMPORTANTI           " << std::endl;
    std::cout << "\n-------------------------------" << std::endl;
    bool hasImp = false;
    for (const auto& t : taskList) {
        if (t.isImportant()) {
            std::cout << t.getId()<< ") " << t.toString() << std::endl;
            hasImp = true;
        }
    }
    if (!hasImp) std::cout << "  (Nessun task importante)" << std::endl;

    std::cout << "\n===============================" << std::endl;
    std::cout << "       TASK NORMALI              " << std::endl;
    std::cout << "\n-------------------------------" << std::endl;
    bool hasNorm = false;
    for (const auto& t : taskList) {
        if (!t.isImportant()) {
            std::cout << t.getId()<< ")" << t.toString() << std::endl;
            hasNorm = true;
        }
    }
    if (!hasNorm) std::cout << "  (Nessun task normale)" << std::endl;
    std::cout << "===============================\n" << std::endl;
}
//Scrive sul file
void TodoManager::autoSave() const {
    std::ofstream file(fileName);
    if (!file.is_open()) {
        throw std::runtime_error("Errore critico: Impossibile accedere al file per il salvataggio.");
    }
    for (const auto& t : taskList) {
        file << t.getId() << ";" << t.getDescription() << ";" << t.getStartTime() << ";" << t.getEndTime() << ";" << t.getStatus() << ";"<<t.isImportant()<<"\n";
    }
    file.close();
}
//Caricamento contenuto file
void TodoManager::loadData() {
    std::ifstream file(fileName);
    if (!file.is_open()) {
        nextId=1;
        return;
    };

    std::string idStr, desc, startStr, endStr, statusStr, impStr;
    int maxId = 0;

    while (std::getline(file, idStr, ';')) {
        if (!std::getline(file, desc, ';')) break;
        if (!std::getline(file, startStr, ';')) break;
        if (!std::getline(file, endStr, ';')) break;
        if (!std::getline(file, statusStr, ';')) break;
        if (!std::getline(file, impStr)) break;

        try {
            if (startStr.length() >= 5 && endStr.length() >= 5) {
                int currentId = std::stoi(idStr);

                int h1 = std::stoi(startStr.substr(0, 2));
                int m1 = std::stoi(startStr.substr(3, 2));
                int h2 = std::stoi(endStr.substr(0, 2));
                int m2 = std::stoi(endStr.substr(3, 2));

                bool isDone = (statusStr == "1");
                bool isImp = (impStr == "1");

                taskList.emplace_back(currentId, desc, Time(h1, m1), Time(h2, m2), isDone, isImp);
                if (currentId > maxId) maxId = currentId;

            }
        } catch (const std::exception& e) {
            // Se una riga è scritta male, la ignora e passa alla prossima
            continue;
        }
    }
    nextId = maxId + 1;
    file.close();
}

bool TodoManager::hasNoTasks() const { return taskList.empty(); }

bool TodoManager::Overlapping(const Time& newStart, const Time& newEnd) const {
    for (const auto& existingTask : taskList) {
        // Se il nuovo task inizia prima e finisce dopo un certo lasso di tempo gia assegnato
        // oppure il nuovo task finisce e inizia nello stesso momento di un task gia esistente...
        if (newStart < existingTask.getEndTime() && newEnd > existingTask.getStartTime()) {
            return true; // C'è una sovrapposizione!
        }
    }
    return false; // L'orario è libero
}
