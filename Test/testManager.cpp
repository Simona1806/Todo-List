#include <gtest/gtest.h>
#include "../TodoManager.h"
#include <fstream>

// Questa classe gestisce la pulizia dell'ambiente prima di OGNI test
class ManagerTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Svuota fisicamente il file sul disco prima di ogni test
        std::ofstream file("database_todo.txt", std::ios::trunc);
        file.close();
    }
};
//controllo che se il file è vuoto, venga rilevato dal metodo hanNoTask e che se, invece, non è vuoto vengo rilevato correttamente che non lo è
TEST_F(ManagerTest, FileVuoto) {
    TodoManager m;
    EXPECT_TRUE(m.hasNoTasks());
}
TEST_F(ManagerTest, ListaNonVuota) {
    TodoManager m;
    m.addEntry("T", Time(1,0), Time(2,0));
    EXPECT_FALSE(m.hasNoTasks());
}
//controllo che il task venga inserito correttamente
TEST_F(ManagerTest, AggiuntaTaskValido) {
    TodoManager m;
    EXPECT_NO_THROW(m.addEntry("Valido", Time(10,0), Time(11,0)));
}
//controllo che ora inizio < ora fine
TEST_F(ManagerTest, TimeNonValido) {
    TodoManager m;
    // Inizio (12) > Fine (11)
    EXPECT_THROW(m.addEntry("Errore", Time(12,0), Time(11,0)), std::invalid_argument);
}
//controllo che due task non siano sovrapposti
TEST_F(ManagerTest, Sovrapposizione) {
    TodoManager m;
    m.addEntry("T1", Time(14,0), Time(15,0));
    EXPECT_THROW(m.addEntry("T2", Time(14,0), Time(15,0)), std::runtime_error);
}

TEST_F(ManagerTest, Sovrapposizione2) {
    TodoManager m;
    EXPECT_THROW(m.addEntry("T2", Time(14,0), Time(14,0)),std::invalid_argument);
}

TEST_F(ManagerTest, SovrapposizioneParziale) {
    TodoManager m;
    m.addEntry("T1", Time(14,0), Time(15,0));
    EXPECT_THROW(m.addEntry("T2", Time(14,30), Time(15,30)), std::runtime_error);
}
//controllo che, anche se un task inizia alle 11, un altro task possa finire alle 11 e viceversa
TEST_F(ManagerTest, Sovraposizione3) {
    TodoManager m;
    m.addEntry("T1", Time(10,0), Time(11,0));
    EXPECT_NO_THROW(m.addEntry("T2", Time(11,0), Time(12,0)));
}
//controllo che l'indice del task del quale si vuole cambiare lo stato sia presente nella lista
TEST_F(ManagerTest, CambioStatus) {
    TodoManager m;
    EXPECT_THROW(m.changeStatus(9999), std::out_of_range);
}
//controllo che l'indice inserito del task da rimuovere sia presente nella lista /valido
TEST_F(ManagerTest, RimuovereTaskNonEsistente) {
    TodoManager m;
    EXPECT_THROW(m.removeEntry(9999), std::out_of_range);
}
TEST_F(ManagerTest, RimuovereTaskNonValido) {
    TodoManager m;
    EXPECT_THROW(m.removeEntry(-1), std::out_of_range);
}
//controllo che i task vengano inseriti correttamente sul file e letti e stampati altrettanto
TEST_F(ManagerTest, SalvataggioECaricamento) {
    TodoManager m1;
    m1.addEntry("Test", Time(10, 0), Time(11, 0), true);

    TodoManager m2;
    EXPECT_FALSE(m2.hasNoTasks());
    EXPECT_THROW(m2.addEntry("Duplicato", Time(10, 30), Time(11, 30)), std::runtime_error);
}
//controllo che l'id tei task sia gestito correttamente
TEST_F(ManagerTest, CoerenzaIDDopoEliminazione) {
    TodoManager m;
    m.addEntry("Task 1", Time(8, 0), Time(9, 0)); // Riceve ID 1
    m.addEntry("Task 2", Time(9, 0), Time(10, 0)); // Riceve ID 2

    m.removeEntry(1); // Elimino il primo

    m.addEntry("Task 3", Time(11, 0), Time(12, 0));
    // Il nuovo task non deve riutilizzare l'ID 1 o 2, ma deve essere 3
    EXPECT_NO_THROW(m.removeEntry(3));
}
//controllo che i task siano ordinati correttamente in base all'ora
TEST_F(ManagerTest, Ordinamento) {
    TodoManager m;
    m.addEntry("Task tardo", Time(20, 0), Time(21, 0));
    m.addEntry("Task presto", Time(7, 0), Time(8, 0));

    EXPECT_THROW(m.addEntry("Sovrapposizione Mattina", Time(7, 30), Time(8, 30)), std::runtime_error);
}