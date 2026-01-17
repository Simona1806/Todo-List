#include <gtest/gtest.h>
#include "../Task.h"
//controllo che i getters funzionino correttamente
TEST(TaskTest, ValoreIniziale) {
    Task t(1, "Spesa", Time(10,0), Time(11,0));
    EXPECT_EQ(t.getId(), 1);
    EXPECT_EQ(t.getDescription(), "Spesa");
    EXPECT_FALSE(t.getStatus());
}
TEST(TaskTest, ValoreIniziale2) {
    Task t(2, "Palestra", Time(11,0), Time(12,0),false,true);
    EXPECT_EQ(t.getId(), 2);
    EXPECT_EQ(t.getDescription(), "Palestra");
    EXPECT_FALSE(t.getStatus());
    EXPECT_EQ(t.isImportant(), true);
}
TEST(TaskTest, ValoreIniziale3) {
    Task t(3, "Visita", Time(11,0), Time(12,0),true,true);
    EXPECT_EQ(t.getId(), 3);
    EXPECT_EQ(t.getDescription(), "Visita");
    EXPECT_TRUE(t.getStatus());
    EXPECT_EQ(t.isImportant(), true);
}
//controllo che lo stato del task venga cambiato correttamente
TEST(TaskTest, ToggleStatus) {
    Task t(1, "Spesa", Time(10,0), Time(11,0));
    t.toggleStatus();
    EXPECT_TRUE(t.getStatus());
    t.toggleStatus();
    EXPECT_FALSE(t.getStatus());
}
//controllo che l'importanza del task sia "letta" correttamente
TEST(TaskTest, Importante) {
    Task t(4, "Importante", Time(8,0), Time(9,0), false, true);
    EXPECT_TRUE(t.isImportant());
}
TEST(TaskTest, Importante2) {
    Task t(1, "Spesa", Time(10,0), Time(11,0));
    EXPECT_FALSE(t.isImportant());
}
//controllo che i Time dei task vengano comparati correttamente per assicurarmi un ordinamento giusto
TEST(TaskTest, ComparaOre) {
    Task t1(5, "A", Time(10,0), Time(11,0));
    Task t2(6, "B", Time(10,30), Time(11,30));
    EXPECT_TRUE(t1 < t2);
}
TEST(TaskTest, ComparaOre2) {
    Task t1(7, "A", Time(9,0), Time(10,0));
    Task t2(8, "B", Time(10,0), Time(11,0));
    EXPECT_TRUE(t1 < t2);
}
//controllo come vengono stampate le informazioni dei task
TEST(TaskTest, ToStringFormat) {
    Task t(5, "Corsa", Time(7,0), Time(8,0));
    EXPECT_NE(t.toString().find("07:00"), std::string::npos);
    EXPECT_NE(t.toString().find("Corsa"), std::string::npos);
}
//controllo che lo stato del task sia "letto" correttamente
TEST(TaskTest, doneTrue) {
    Task t(6, "Done", Time(10,0), Time(11,0), true);
    EXPECT_TRUE(t.getStatus());
}
//controllo la validità del task
TEST(TaskTest, Id) {
    Task t(999, "Id", Time(1,1), Time(2,2));
    EXPECT_EQ(t.getId(), 999);
}
TEST(TaskTest, Descrizione) {
    std::string d = "Task Molto Lungo Per Testare Stringhe";
    Task t(7, d, Time(1,1), Time(2,2));
    EXPECT_EQ(t.getDescription(), d);
}
TEST(TaskTest, SalvaTempo) {
    Time s(14,0), e(15,0);
    Task t(8, "T", s, e);
    EXPECT_EQ(t.getStartTime().formatTime(), "14:00");
    EXPECT_EQ(t.getEndTime().formatTime(), "15:00");
}