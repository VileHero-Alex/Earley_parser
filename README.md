# Алгоритм Эрли

В данном проекте приведена реализация алгоритма Эрли, который умеет определять принадлежит ли слово контекстно-свободной грамматике.



# Взаимодействие с программой

После клонирования репозитория, запускаем в консоли следующую команду:

 `mkdir build && cd build && cmake .. && make`

После этого, есть два способа взаимодействия с проектом:
 
* Проверить корректность алгоритма: ввести свои тесты в файле tests.cpp (с уже известными ответами) в соответствующие ячейки файла и запустить следующую вышеупомянутую команду в консоли (предварительно прописав `cd .. && rm -r build`). После этого, напечатав в консоли `./tests`, появятся результаты проверки коррекности алгоритма.

* Узнать принадлежит ли слово грамматике: напечатав в консоли `./earley`, можно ввести свой запрос в следующем формате (каждый нетерминал должен быть заглавной буквой, каждый терминал - строчной буквой, каждое правило должно записываться в виде: A->$\alpha$ - пробелов вокруг стрелки быть не должно): 

```
<количество нетерминалов> <количество терминалов> <количество правил>
<список нетерминалов>
<список терминалов>
<список правил>
<стартовый нетерминал>
<количество запросов>
<запросы>
```
* Пример корректного ввода:

```
1 2 2
S
ab
S->
S->aSbS
S
2
aabb
ababaaabbb
``` 



# Earley Algorithm

This project provides an implementation of Earley's algorithm, which is able to determine whether a word belongs to a context free grammar.



# Interaction with the programme

After cloning the repository, run the following command in the console:

 `mkdir build && cd build && cmake ... && make`.

After that, there are two ways to interact with the project:
 
* Check the correctness of the algorithm: enter your tests in the tests.cpp file (with already known answers) into the corresponding cells of the file and run the following above-mentioned command in the console (having previously written `cd .. && rm -r build`). After that, type `./tests` in the console and the results of the algorithm's correctness check will appear.

* Find out if the word belongs to the grammar: by typing `./earley` in the console, you can enter your query in the following format (each non-terminal must be an uppercase letter, each terminal must be a lowercase letter, each rule must be written as: A->$\alpha$ - there should be no spaces around the arrow): 

```
<number of non-terminals> <number of terminals> <number of rules>
<list of non-terminals>
<list of terminals>
<list of rules>
<start non-terminal>
<number of queries>
<queries>
```
* Example of correct input:

```
1 2 2
S
ab
S->
S->aSbS
S
2
aabb
abababaaabbb
```