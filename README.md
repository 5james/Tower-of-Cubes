//ENG Brief README

This project is about creating the highest possible tower of cubes. Here are some rules about cubes and how the tower should look like:

- Each Cube's faces are varicoloured (This means that number of colours avaible are minimum 6)
- Each Cube has specified weight
- If you want to put cube A on top of cube B -> cube B must be heavier or the same weight as cube A AND colour of top of cube B must be the same as colout of bottom of cube A

The idea to solve this problem will be in documentation.

//PL Dok�adny README

1. Dane studenta: Jakub Guzek
Semestr: 15Z

2. Specyfikacja problemu:
Danych jest N kolorowych sze�cian�w, z kt�rych ka�dy ma inn� wag�. Sze�ciany s� niejednokolorowe (ka�da �ciana ma inny kolor). Zadanie polega na zbudowaniu za pomoc� sze�cian�w mo�liwie najwy�sz� wie�� spe�niaj�c� warunki:

Nie mo�na po�o�y� ci�szego sze�cianu na l�ejszym
Dolna �ciana sze�cianu musi mie� taki sam kolor jak g�rna innego, kt�ry jest poni�ej

Dane wej�ciowe � zestawy kolekcji sze�cian�w (ka�dy sze�cian ma podane na wej�ciu kolory �cianek)

Wynik � liczba sze�cian�w najwy�szej wie�y, oraz ich konfiguracja �cianek.

3. Aktywacja programu:
Program nie ma argument�w / parametr�w wej�ciowych (argc, argv)

Po w��czeniu programu zgodnie z poleceniem:
wczytuje plik i wykonuje algorytmy
generacja losowych grafow oraz wykonanie wszysystkich algorytmow
Dane wej�ciowe: N sze�cian�w(int), M kolor�w(int), W maxymalna waga(int)
generacja wielu grafow oraz ich wykonanie + porownanie w tabelce
	Dane wej�ciowe: wyb�r algorytmu 1 lub 2 lub 3

4. Struktory danych:
a) Node
Ca�y program ma rozwi�zywa� problem wie�y sze�cian�w. Ka�dy sze�cian rozszepia si� na 6 NODE.
Node wi�c reprezentuje �cian�. Ka�dy ma sw�j kolor, przeciwn� �cian� oraz id (numer sze�cianu). Z sze�cianem jest przypisywana r�wnie� waga.
Ka�dy Node (ju� niezale�nie od sze�cian�w) ma swoich s�siad�w po kolorach oraz najbli�szych po rozpi�ciu sze�cianu.
b) SimpleNodesTree
U�yty w GraphBFSTree. Jest to w�ze� w drzewie. Posiada informacje o id sze�cianu; kolorze, kt�ry jest na dnie. Posiada te� informacje bezpo�rednio zwi�zane z drzewem - rodzic oraz vector dzieci.
c)std::pair
wielokrotnie wykorzystywana struktura po to, aby m.in. przechowywa� jednocze�nie kolor i id, Node* i co� jeszcze

5. Algorytmy:

 a. BFS Tree
Jest to moja inwencja. BFS Mia�aby ona dzia�a� na takiej zasadzie, �e buduj� drzewo (w atrybucie ma ID sze�cianu):
0. Tworz� roota, kt�ry jest najci�szym ze wszystkich danych sze�cian�w
1. Dodaj� do li�ci wszystkie mo�liwe s�siedztwa (sze�ciany), mo�liwe - z listy s�siad�w wierzcho�k�w nale��cych do sze�cianu wybieram tylko tych, kt�re si� nie powt�rzy�y w drodze do roota - np. je�li id roota to 2 oraz mam li�� sze�cianu o id 3 i w jego s�siadach jest 2 to nie mog� go ju� doda�. Nie trzeba dodawa�, �e musi si� zgadza� pod wzgl�dem koloru oraz, �e musi by� l�ejszy.
2. Powtarzamy pkt 1 a� do wyczerpania. Najd�u�sza droga od sze�cianu ko�cowego (li�cia) do roota to nasza wie�a.
Niestety z moich kalkulacji algorytm ten ma du�o za du�� z�o�ono�� obliczeniow� przy ma�ej ilo�ci kolor�w. Na przyk�ad je�li mamy 100 takich samych sze�cian�w, to root b�dzie mia� 100 dzieci -> 100 dzieci b�dzie mia�o 99 itd. Co nie wr�y nic dobrego. Za to przy du�ej ilo�ci kolor�w w por�wnaniu do sze�cian�w daj� dok�adny wynik w miar� szybko.
Algorytm jest rozpoczynany z nod�w, kt�re s� najci�sze. Wad� takiego rozwi�zania jest to, �e przy ma�ej ich liczbie oraz przy ogromnej liczbie kolor�w mo�e si� okaza�, �e zwr�ci nienajlepszy wynik. Korzy�� takiego rozwi�zania to oczywi�cie cenny czas. My�l�, �e ruszanie z najci�szych nod�w jest optymalne dla tego rozwi�zania.
 b. DFS (Depth First Search)
Nie wystarczy tutaj zwyk�y Depth First Search. B�dzie trzeba wprowadzi� troch� zmian. Jak w zwyk�ym Depth First Search tworzymy STOS. Stos ten jednak nie b�dzie dotyczy� wierzcho�k�w, jakie przeszli�my, lecz id sze�cian�w, przez kt�re przeszli�my. Chodzimy po wierzcho�kach i nie mo�emy wej�� w wierzcho�ek, kt�ry nale�y do sze�cianu, kt�ry jest na stosie-1. Napisa�em na stosie-1, gdy� mo�emy chodzi� po wierzcho�kach sze�cianu, kt�ry jest na szczycie stosu. Jest to logiczne, gdy� mo�emy wtedy wyj�� ze wszystkich wierzcho�k�w (kolor�w-�cian) tego sze�cianu. Na bie��co zapisujemy sobie maksymalny rozmiar stosu, jaki by� oraz do tej liczby list� wska�nik�w do wierzcho�k�w, kt�rej dotyczy ten maksymalny rozmiar. W ten spos�b po sko�czeniu dzia�ania algorytmu mamy gotowe rozwi�zanie � najwy�sz� wie�� sze�cian�w. Opr�cz wska�nik�w zapami�tuje si�, kt�ra �ciana jest zwr�cona ku do�owi. 
Algorytm jest rozpoczynany z nod�w, kt�re s� najci�sze. Wad� takiego rozwi�zania jest to, �e przy ma�ej ich liczbie oraz przy ogromnej liczbie kolor�w mo�e si� okaza�, �e zwr�ci nienajlepszy wynik. Korzy�� takiego rozwi�zania to oczywi�cie cenny czas. My�l�, �e ruszanie z najci�szych nod�w jest optymalne dla tego rozwi�zania.

 c. Random walking
Jest to przyk�ad b��dzenia losowego. Chodzimy po wierzcho�kach i zapisujemy sobie id wszystkich przejrzanych sze�cian�w, tak aby nie m�c przej�� do przejrzanego ju� sze�cianu. Dodatkowo zapami�tujemy kolory. Pierwszy node, do kt�rego wchodzimy z danego id sze�cianu zawiera po��dany kolor. Wyb�r wierzcho�ka-s�siada, do kt�rego przechodzimy jest kompletnie losowy. Lista s�siad�w jest na nowo aktualizowana i zapisywana, czyli usuwane s� wierzcho�ki, kt�re nale�� do sze�cian�w, kt�re zosta�y przejrzane. Zapisywana jest do tymczasowej listy lub vectora. Robi si� to, aby si� upewni�, �e jest jaki� s�siad, do kt�rego mo�na przej��. Je�li takowego nie ma to ko�czy si� algorytm. Dzia�anie tego algorytmu przewa�nie nie da si� przewidzie�. Tak wi�c wynik tego algorytmu mo�e wypa�� od bardzo s�abego do bardzo dobrego, a nawet najlepszego rozwi�zania.

6. Pliki �r�d�owe + wygenerowane dane:
data.txt - wygenerowane dane potrzebne do 1szej opcji wywolania programu
declarations.h - og�lne deklaracje dla ca�ej aplikacji
Generator.h, Generator.cpp - nag��wek i implementacja generatora danych. Zapisuje to na data.txt
Graph.h, Graph.cpp - Podstawowy graf, generacja, wypis wierzcho�k�w bez implementacji solve()
GraphBFSTree.h, GraphBFSTree.cpp - Implementacja algorytmu BFS
GraphDFS.h, GraphDFS.cpp - Implementacja algorytmu DFS
GraphRandomWalking.h, GraphRandomWalking.cpp - Implementacja algorytmu random walking
main.cpp - g��wny plik
Node.h, Node.cpp - Struktura danych - NODE
Table.h, Table,cpp - klasa do por�wnywania wynik�w Singleton
