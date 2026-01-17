
---

# ToDo List C++ – Registro Attività (A.A. 2025–2026)

Applicazione da terminale per la gestione di una ToDo List giornaliera, sviluppata in **C++17** con architettura modulare e orientata agli oggetti. Permette di organizzare le attività evitando sovrapposizioni orarie e garantendo la persistenza dei dati.

## Funzionalità principali

* **Gestione oraria delle attività**: aggiunta di task con orario di inizio e fine.
* **Controllo sovrapposizioni**: validazione automatica per impedire l'inserimento di attività in orari già occupati.
* **Modalità Importante**: possibilità di contrassegnare task prioritari per una visualizzazione filtrata.
* **Ordinamento automatico**: le attività sono sempre ordinate cronologicamente per orario di inizio.
* **Persistenza dei dati**: salvataggio e caricamento automatico su file `database_todo.txt`.
* **Validazione input**: gestione degli errori per orari non validi e input testuali errati.

## Struttura del progetto

```
Todo-List/
├── main.cpp             # Interfaccia utente e gestione menu
├── TodoManager.{h,cpp}  # Logica di gestione della lista e file I/O
├── Task.{h,cpp}         # Modello della singola attività
├── Time.{h,cpp}         # Gestione e confronto degli orari
├── CMakeLists.txt       # Configurazione Build System
├── README.md            # Documentazione
└── Test/                # Cartella dei Test Unitari
    ├── testTime.cpp     # Test per la classe Time
    ├── testTask.cpp     # Test per la classe Task
    └── testManager.cpp  # Test per la logica del TodoManager

```


## Compilazione ed esecuzione

1. Aprire la cartella `Todo-List` in CLion (o un altro IDE compatibile con CMake).
2. Assicurarsi di avere una toolchain C++ aggiornata (supporto C++17).
3. Compilare e lanciare il programma (`Todo-List`) oppure eseguire i test (`esegui_test`).
4. Per eseguire i test da terminale:
```bash
mkdir build && cd build
cmake ..
make
./esegui_test

```



## Menu dell'applicazione

Il programma offre un menu per la gestione:

1. **Aggiungi Attività**: inserimento di descrizione, orario e priorità (importante/normale).
2. **Inverti Stato Attivita'**: segna un task come "Fatto" o "Da fare" tramite ID.
3. **Elimina Attivita'**: rimuove un task specifico dall'elenco tramite il suo ID univoco.
4. **Esci**: chiude il programma salvando automaticamente le modifiche.

## Testing

Ho implementato una suite completa di test unitari utilizzando **Google Test** per verificare la robustezza del progetto. I test coprono la gestione degli orari, il corretto funzionamento degli ID e la prevenzione delle sovrapposizioni.

Google Test viene scaricato automaticamente tramite CMake (FetchContent) e integrato nel processo di build per garantire la massima portabilità del progetto.

## Autore

**Toma Florentina-Simona** – Matricola 7164752

Corso di Laurea in Ingegneria Informatica

Esame di Laboratorio di Programmazione (A.A. 2025–2026)

---