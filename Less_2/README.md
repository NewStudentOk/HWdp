# Домашнее задание к занятию «Структурные шаблоны: Proxy, Decorator, Adapter»

### Цель задания

Выполнив это задание, вы научитесь применять паттерны «Декоратор» и «Заместитель» в программах.

### Задание 1

В программу рендеринга HTML из лекции (раздел про паттерн «Декоратор») добавьте новые классы для декорирования текста.
```
class Paragraph: ...

auto text_block = new Paragraph(new Text());
text_block->render("Hello world");

>>> <p>Hello world</p>
```

```
class Reversed: ...

auto text_block = new Reversed(new Text());
text_block->render("Hello world");

>>> dlrow olleH
```

```
class Link: ...

auto text_block = new Link(new Text());
text_block->render("netology.ru", "Hello world");

>>> <a href=netology.ru>Hello world</a>
```

Обратите внимание

1. Сигнатура метода `Link::render()` не совпадает с сигнатурой оригинального метода.
2. Для разворота строки используйте функцию `std::reverse` [cppreference](https://en.cppreference.com/w/cpp/algorithm/reverse).

------

### Задание 2

В дополнение к классам-заместителям `VeryHeavyDatabase`, реализованным на лекции, реализуйте класс
```
class OneShotDB : VeryHeavyDatabase {
  explicit OneShotDB (VeryHeavyDatabase* real_object, size_t shots=1) : ...
}
```
Он должен возвращать данные по ключу из реального объекта то количество раз, которое указано в конструкторе.
Исчерпав лимит получения данных, метод `GetData` всегда возвращает строку error.
Пример использования:
```
auto real_db = VeryHeavyDatabase();
auto limit_db = OneShotDB(std::addressof(real_db), 2);
std::cout << limit_db.GetData("key") << std::endl;
std::cout << limit_db.GetData("key") << std::endl;
std::cout << limit_db.GetData("key") << std::endl;

Output:
>>> value
>>> value
>>> error
```

