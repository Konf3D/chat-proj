1. Список участников:</br>

Артур (Konf3D)</br>

2. Идея решения:</br>

Все данные хранятся в оперативной памяти и не сохраняются в файловой системе - см. примечание в задании к проекту на skillfactory</br>

После запуска пользователь может войти в свою учетку, либо создать её. При возникших проблемах его оповещает приложение.</br>

После входа, пользователя может написать сообщение всем, либо конкретному пользователю, а также вывести сообщения на экран. При возникших проблемах его оповещает приложение.</br>

(Дополнительный функционал) Сообщения можно вывести на экран. Приватные сообщения нельзя просмотреть.


</br>

3. Пользовательские типы:</br>

class Message - это контейнер для хранения ифнормации о сообщении и отправителе.</br>

class PrivateMessage - тоже, что Message, но есть ифнормация о получателе и требует пароль пользователя.</br>

class User - данные об аккаунте. Имеет пуской конструктор, чтобы указать на отсутствие пользователя в базе данных</br>

class BD - это СУБД + БД для приложения. Хранит все данные о пользователях и сообщениях и выдает нужные данные по требованию.</br>

class chatGUI - отвечает за ввод и вывод данных для пользователя и взаимодействует с БД.</br>

4. Реализация всего проекта была выполнена в одиночку. Была попытка сработаться с напарником, но не вышло. 
