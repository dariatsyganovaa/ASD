#include <gtest/gtest.h>
#include "../lib_itable/itable.h" 
#include "../lib_unsorted_table_on_arr/unsortedtable.h" 
#include "../lib_polynom/polynom.h"        

// 1. Тест создания таблицы
TEST(UnsortedTableTest, Can_Create_Table) {
    ASSERT_NO_THROW((UnsortedTableM<std::string, int>()));
}

TEST(UnsortedTableTest, New_Table_Is_Empty) {
    UnsortedTableM<std::string, int> table;
    EXPECT_TRUE(table.is_empty());
    EXPECT_EQ(table.size(), 0);
}

// 2. Тест вставки и поиска
TEST(UnsortedTableTest, Can_Insert_And_Find_Value) {
    UnsortedTableM<std::string, int> table;
    table.insert("key1", 100);

    int* val = table.find("key1");

    ASSERT_NE(val, nullptr); // Убеждаемся, что не нулевой адрес
    EXPECT_EQ(*val, 100);
    EXPECT_EQ(table.size(), 1);
}

// 3. Тест на ошибку при дублировании ключа
TEST(UnsortedTableTest, Throws_On_Duplicate_Insert) {
    UnsortedTableM<std::string, int> table;
    table.insert("key1", 10);

    // Ожидаем исключение, так как "key1" уже есть
    EXPECT_THROW(table.insert("key1", 20), std::runtime_error);
}

// 4. Тест поиска несуществующего ключа
TEST(UnsortedTableTest, Returns_Nullptr_If_Not_Found) {
    UnsortedTableM<std::string, int> table;
    table.insert("A", 1);

    EXPECT_EQ(table.find("B"), nullptr); // Должен вернуть нулевой адрес
}

// 5. Тест удаления (erase)
TEST(UnsortedTableTest, Can_Erase_Element) {
    UnsortedTableM<std::string, int> table;
    table.insert("A", 1);
    table.insert("B", 2);

    table.erase("A");

    EXPECT_EQ(table.size(), 1);
    EXPECT_EQ(table.find("A"), nullptr);
    EXPECT_NE(table.find("B"), nullptr); // Второй элемент должен остаться
}

TEST(UnsortedTableTest, Throws_On_Erase_Non_Existent_Key) {
    UnsortedTableM<std::string, int> table;
    EXPECT_THROW(table.erase("ghost"), std::runtime_error);
}

// 6. КОМПЛЕКСНЫЙ ТЕСТ С ПОЛИНОМАМИ (Главная цель лабы)
TEST(UnsortedTableTest, Working_With_Polynoms) {
    UnsortedTableM<std::string, Polynom> table;

    // Создаем два разных полинома
    Polynom p1;
    p1.addMonom(2.5, 211); // 2.5 * x^2 * y^1 * z^1

    Polynom p2;
    p2.addMonom(1.0, 100); // 1.0 * x^1

    // Вставляем их в таблицу под именами
    table.insert("First", p1);
    table.insert("Second", p2);

    // Ищем первый и проверяем данные
    Polynom* found = table.find("First");
    ASSERT_NE(found, nullptr);
    EXPECT_EQ(*found, p1); // Тут сработает operator== в Polynom

    // Проверяем, что в таблице действительно 2 элемента
    EXPECT_EQ(table.size(), 2);
}

// 7. Тест полиморфизма (работа через интерфейс ITable)
TEST(UnsortedTableTest, Works_Through_Interface_Pointer) {
    // Указатель на базовый класс (интерфейс)
    ITable<std::string, int>* tablePtr = new UnsortedTableM<std::string, int>();

    tablePtr->insert("test", 50);
    EXPECT_EQ(*tablePtr->find("test"), 50);

    delete tablePtr;
}