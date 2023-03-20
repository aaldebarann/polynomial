# Интерпретатор операций над полиномами
## Постановка задачи
Разработать программную систему для выполнения алгебраических операций над полиномами от трех переменных.
## Общие положения
* Полиномы хранятся в виде списка мономов.
* Моном - набор из степеней переменных и коэффициента.
* Полиномы хранятся во всех таблицах одновременно. Ключом является имя.
* Таблицы реализованы нескольких видов: линейная на массиве, линейная на списке, упорядоченная на массиве, дерево (АВЛ или красно-черное), две хэш-таблицы.
* Операции над отдельным полиномом: вычисление в точке, умножение на константу, производная, интеграл.
* Операции в выражениях из полиномов: сложение, вычитание,умножение на константу, умножение полиномов, деление полиномов*. Операции должны выполняться, используя постфиксную форму.
* Операции над таблицами: добавление полинома (во все сразу), удаление полинома (во всех сразу), поиск (только в активной таблице, выполняется в процессе вычисления выражений, составленных из имен полиномов).
* Активная (выбранная пользователем) таблица должна выводиться на экран в формате, как минимум, двух столбцов: 1) имя полинома, 2) строковое представление полинома.   

  (*) - операции не реализованы, но планируются в следующих версиях.
## Пример использования
Интерпретатор принимает выражения двух видов:
### 1. Задание полинома
Ввод:
```
p_1 = 2*x^2 + 3*x*y*z - 10*z
p_2 = p_1 + y - 1
```
В случае ошибки синтаксиса программа выводит сообщение об ошибке, иначе запоминает значение введенных полиномов.  
### 2. Вычисление выражений с полиномами  
Ввод:
```
p_2 - p_1
```
Вывод:
```
y - 1
```
## Структура проекта:
gtest - файлы google test  
include - .h файлы  
src - .cpp файлы  
test - файлы тестов  
samples - примеры использования
    
_monome.h, monome.cpp_ - класс монома  
_polynome.h, polynome.cpp_ - класс полинома  
_expression.h, expression.cpp_ - класс арифметического выражения  
_calculator.h, calculator.cpp_ - организует работу с пользователем  
## Разработчики
Иванченко Алексей (aaldebarann) - лидер команды, разработка парсинга и вычисления выражений с полиномами  
Свистунов Михаил (Newasw) - разработка GUI, таблиц  
Щербаков Павел (ko1o6ok) - разработка класса полином  
