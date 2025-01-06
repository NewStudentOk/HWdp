# Домашнее задание к занятию «Порождающие шаблоны»

Выполнив это задание, вы научитесь использовать шаблон Builder для практических задач.

### Цель задания

1. Научиться использовать шаблон Builder для построения простых SQL-запросов.

### Задание 1

Реализуйте класс `SqlSelectQueryBuilder`, который можно использовать для построения
простых SELECT-запросов.

Пример использования класса:
```
#inclide "sql_query_builder.h"

int main {
    SqlSelectQueryBuilder query_builder;
    query_builder.AddColumn("name").AddColumn("phone");
    query_builder.AddFrom("students");
    query_builder.AddWhere("id", "42").AddWhere("name", "John");
    
    static_assert(query_builder.BuildQuery(), 
                    "SELECT name, phone FROM students WHERE id=42 AND name=John;");
}
```
#### Обратите внимание на следующие моменты
1. Методы построения запроса `AddColumn, AddFrom, AddWhere` могут вызывать в любом порядке. При этом запрос должен всегда строиться корректно.
2. Если метод `AddColumn` не был вызван, запрос должен начинаться с `SELECT * ...`.
3. Для простоты строки в запросе могут быть не выделены кавычками, как в примере.
4. Вызовы `AddFrom` должны перезаписывать название таблицы в классе.
5. Не забудьте `;` в конце каждого запроса.

------

### Задание 2
Расширьте класс из предыдущего задания методом 
```
SqlSelectQueryBuilder& AddWhere(const std::map<std::string, std::string>& kv) noexcept;
```
С помощью которого можно будет добавить в запрос сразу несколько условий.

Расширьте класс из предыдущего задания методом 
```
SqlSelectQueryBuilder& AddColumns(const std::vector<std::string>& columns) noexcept;
```
С помощью этого метода можно добавить в запрос сразу несколько полей, по которым он будет строиться вместо одного, как в базовом варианте.

---

### Задание 3 (необязательное)
Реализуйте потомок класса `SqlSelectQueryBuilder`, который сможет добавлять в условие `FROM` запроса дополнительные операторы «больше» и «меньше».
Пример кода с таким классом:
```
AdvancedSqlSelectQueryBuilder query_builder;
query_builder.AddColumns({"name", "phone"});
query_builder.AddFrom("students");
query_builder.<SomeMethod>(...); // Добавляем условие id > 42
static_assert(query_builder.BuildQuery(), 
                "SELECT name, phone FROM students WHERE id>42;");
```