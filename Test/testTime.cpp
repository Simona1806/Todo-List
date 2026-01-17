#include <gtest/gtest.h>
#include "../Time.h"
// Controllo che il formato sia giusto
TEST(TimeTest, DefaultConstructor) {
    EXPECT_EQ(Time().formatTime(), "00:00");
}
TEST(TimeTest, TempoValido) {
    EXPECT_EQ(Time(13, 45).formatTime(), "13:45");
}
//controllo che anche se viene inserita un'ora fuori dal range (0,24) l'ora impostata è 00
TEST(TimeTest, OraNonValida) {
    EXPECT_EQ(Time(25, 30).formatTime(), "00:30");
}
//controllo che anche se vengono inseriti i minuti fuori dal range (0,59) i minuti impostati sono 00
TEST(TimeTest, MinutiNonValidi) {
    EXPECT_EQ(Time(10, 61).formatTime(), "10:00");
}
//controllo il che anche se viene inserito un Time del tipo H:M, il time impostato è del tipo HH:MM
TEST(TimeTest, NoZero) {
    EXPECT_EQ(Time(5, 9).formatTime(), "05:09");
}
//controllo che le operazioni tra Time siano eseguite correttamente
TEST(TimeTest, OraeMinutiUguale) {
    EXPECT_TRUE(Time(10, 0) == Time(10, 0));
}
TEST(TimeTest, NonUguale) {
    EXPECT_FALSE(Time(10, 30) == Time(10, 31));
}
TEST(TimeTest, MinutiPiccoli) {
    EXPECT_TRUE(Time(10, 30) < Time(10, 31));
}
TEST(TimeTest, MinutiPiccoli2) {
    EXPECT_FALSE(Time(10, 32) < Time(10, 31));
}
TEST(TimeTest, OraPiccola) {
    EXPECT_TRUE(Time(10, 30) < Time(11, 30));
}
TEST(TimeTest, OraPiccola2) {
    EXPECT_FALSE(Time(12, 30) < Time(11, 30));
}
TEST(TimeTest, oraGrande) {
    EXPECT_TRUE(Time(15, 0) > Time(14, 59));
}
TEST(TimeTest, oraGrande2) {
    EXPECT_FALSE(Time(13, 0) > Time(14, 59));
}
TEST(TimeTest, minutiGrandi) {
    EXPECT_TRUE(Time(14, 59) > Time(14, 50));
}
TEST(TimeTest, minutiGrandi2) {
    EXPECT_FALSE(Time(14, 0) > Time(14, 59));
}
TEST(TimeTest, minoreUguale) {
    EXPECT_TRUE(Time(12, 0) <= Time(12, 0));
}
TEST(TimeTest, minoreUguale2) {
    EXPECT_FALSE(Time(12, 15) <= Time(12, 0));
}
//controllo che i getters funzionino correttamente
TEST(TimeTest, Getters) {
    Time t(20, 15);
    EXPECT_EQ(t.getHours(), 20);
    EXPECT_EQ(t.getMinutes(), 15);
}