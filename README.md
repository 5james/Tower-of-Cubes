//ENG Brief README

This project is about creating the highest possible tower of cubes. Here are some rules about cubes and how the tower should look like:

- Each Cube's faces are varicoloured (This means that number of colours avaible are minimum 6)
- Each Cube has specified weight
- If you want to put cube A on top of cube B -> cube B must be heavier or the same weight as cube A AND colour of top of cube B must be the same as colout of bottom of cube A

The idea to solve this problem will be in documentation.

//PL Dok³adny README

1. Dane studenta: Jakub Guzek
Semestr: 15Z

2. Specyfikacja problemu:
Danych jest N kolorowych szeœcianów, z których ka¿dy ma inn¹ wagê. Szeœciany s¹ niejednokolorowe (ka¿da œciana ma inny kolor). Zadanie polega na zbudowaniu za pomoc¹ szeœcianów mo¿liwie najwy¿sz¹ wie¿ê spe³niaj¹c¹ warunki:

Nie mo¿na po³o¿yæ ciê¿szego szeœcianu na l¿ejszym
Dolna œciana szeœcianu musi mieæ taki sam kolor jak górna innego, który jest poni¿ej

Dane wejœciowe – zestawy kolekcji szeœcianów (ka¿dy szeœcian ma podane na wejœciu kolory œcianek)

Wynik – liczba szeœcianów najwy¿szej wie¿y, oraz ich konfiguracja œcianek.

3. Aktywacja programu:
Program nie ma argumentów / parametrów wejœciowych (argc, argv)

Po w³¹czeniu programu zgodnie z poleceniem:
wczytuje plik i wykonuje algorytmy
generacja losowych grafow oraz wykonanie wszysystkich algorytmow
Dane wejœciowe: N szeœcianów(int), M kolorów(int), W maxymalna waga(int)
generacja wielu grafow oraz ich wykonanie + porownanie w tabelce
	Dane wejœciowe: wybór algorytmu 1 lub 2 lub 3

4. Struktory danych:
a) Node
Ca³y program ma rozwi¹zywaæ problem wie¿y szeœcianów. Ka¿dy szeœcian rozszepia siê na 6 NODE.
Node wiêc reprezentuje œcianê. Ka¿dy ma swój kolor, przeciwn¹ œcianê oraz id (numer szeœcianu). Z szeœcianem jest przypisywana równie¿ waga.
Ka¿dy Node (ju¿ niezale¿nie od szeœcianów) ma swoich s¹siadów po kolorach oraz najbli¿szych po rozpiêciu szeœcianu.
b) SimpleNodesTree
U¿yty w GraphBFSTree. Jest to wêze³ w drzewie. Posiada informacje o id szeœcianu; kolorze, który jest na dnie. Posiada te¿ informacje bezpoœrednio zwi¹zane z drzewem - rodzic oraz vector dzieci.
c)std::pair
wielokrotnie wykorzystywana struktura po to, aby m.in. przechowywaæ jednoczeœnie kolor i id, Node* i coœ jeszcze

5. Algorytmy:

 a. BFS Tree
Jest to moja inwencja. BFS Mia³aby ona dzia³aæ na takiej zasadzie, ¿e budujê drzewo (w atrybucie ma ID szeœcianu):
0. Tworzê roota, który jest najciê¿szym ze wszystkich danych szeœcianów
1. Dodajê do liœci wszystkie mo¿liwe s¹siedztwa (szeœciany), mo¿liwe - z listy s¹siadów wierzcho³ków nale¿¹cych do szeœcianu wybieram tylko tych, które siê nie powtórzy³y w drodze do roota - np. jeœli id roota to 2 oraz mam liœæ szeœcianu o id 3 i w jego s¹siadach jest 2 to nie mogê go ju¿ dodaæ. Nie trzeba dodawaæ, ¿e musi siê zgadzaæ pod wzglêdem koloru oraz, ¿e musi byæ l¿ejszy.
2. Powtarzamy pkt 1 a¿ do wyczerpania. Najd³u¿sza droga od szeœcianu koñcowego (liœcia) do roota to nasza wie¿a.
Niestety z moich kalkulacji algorytm ten ma du¿o za du¿¹ z³o¿onoœæ obliczeniow¹ przy ma³ej iloœci kolorów. Na przyk³ad jeœli mamy 100 takich samych szeœcianów, to root bêdzie mia³ 100 dzieci -> 100 dzieci bêdzie mia³o 99 itd. Co nie wró¿y nic dobrego. Za to przy du¿ej iloœci kolorów w porównaniu do szeœcianów dajê dok³adny wynik w miarê szybko.
Algorytm jest rozpoczynany z nodów, które s¹ najciê¿sze. Wad¹ takiego rozwi¹zania jest to, ¿e przy ma³ej ich liczbie oraz przy ogromnej liczbie kolorów mo¿e siê okazaæ, ¿e zwróci nienajlepszy wynik. Korzyœæ takiego rozwi¹zania to oczywiœcie cenny czas. Myœlê, ¿e ruszanie z najciê¿szych nodów jest optymalne dla tego rozwi¹zania.
 b. DFS (Depth First Search)
Nie wystarczy tutaj zwyk³y Depth First Search. Bêdzie trzeba wprowadziæ trochê zmian. Jak w zwyk³ym Depth First Search tworzymy STOS. Stos ten jednak nie bêdzie dotyczy³ wierzcho³ków, jakie przeszliœmy, lecz id szeœcianów, przez które przeszliœmy. Chodzimy po wierzcho³kach i nie mo¿emy wejœæ w wierzcho³ek, który nale¿y do szeœcianu, który jest na stosie-1. Napisa³em na stosie-1, gdy¿ mo¿emy chodziæ po wierzcho³kach szeœcianu, który jest na szczycie stosu. Jest to logiczne, gdy¿ mo¿emy wtedy wyjœæ ze wszystkich wierzcho³ków (kolorów-œcian) tego szeœcianu. Na bie¿¹co zapisujemy sobie maksymalny rozmiar stosu, jaki by³ oraz do tej liczby listê wskaŸników do wierzcho³ków, której dotyczy ten maksymalny rozmiar. W ten sposób po skoñczeniu dzia³ania algorytmu mamy gotowe rozwi¹zanie – najwy¿sz¹ wie¿ê szeœcianów. Oprócz wskaŸników zapamiêtuje siê, która œciana jest zwrócona ku do³owi. 
Algorytm jest rozpoczynany z nodów, które s¹ najciê¿sze. Wad¹ takiego rozwi¹zania jest to, ¿e przy ma³ej ich liczbie oraz przy ogromnej liczbie kolorów mo¿e siê okazaæ, ¿e zwróci nienajlepszy wynik. Korzyœæ takiego rozwi¹zania to oczywiœcie cenny czas. Myœlê, ¿e ruszanie z najciê¿szych nodów jest optymalne dla tego rozwi¹zania.

 c. Random walking
Jest to przyk³ad b³¹dzenia losowego. Chodzimy po wierzcho³kach i zapisujemy sobie id wszystkich przejrzanych szeœcianów, tak aby nie móc przejœæ do przejrzanego ju¿ szeœcianu. Dodatkowo zapamiêtujemy kolory. Pierwszy node, do którego wchodzimy z danego id szeœcianu zawiera po¿¹dany kolor. Wybór wierzcho³ka-s¹siada, do którego przechodzimy jest kompletnie losowy. Lista s¹siadów jest na nowo aktualizowana i zapisywana, czyli usuwane s¹ wierzcho³ki, które nale¿¹ do szeœcianów, które zosta³y przejrzane. Zapisywana jest do tymczasowej listy lub vectora. Robi siê to, aby siê upewniæ, ¿e jest jakiœ s¹siad, do którego mo¿na przejœæ. Jeœli takowego nie ma to koñczy siê algorytm. Dzia³anie tego algorytmu przewa¿nie nie da siê przewidzieæ. Tak wiêc wynik tego algorytmu mo¿e wypaœæ od bardzo s³abego do bardzo dobrego, a nawet najlepszego rozwi¹zania.

6. Pliki Ÿród³owe + wygenerowane dane:
data.txt - wygenerowane dane potrzebne do 1szej opcji wywolania programu
declarations.h - ogólne deklaracje dla ca³ej aplikacji
Generator.h, Generator.cpp - nag³ówek i implementacja generatora danych. Zapisuje to na data.txt
Graph.h, Graph.cpp - Podstawowy graf, generacja, wypis wierzcho³ków bez implementacji solve()
GraphBFSTree.h, GraphBFSTree.cpp - Implementacja algorytmu BFS
GraphDFS.h, GraphDFS.cpp - Implementacja algorytmu DFS
GraphRandomWalking.h, GraphRandomWalking.cpp - Implementacja algorytmu random walking
main.cpp - g³ówny plik
Node.h, Node.cpp - Struktura danych - NODE
Table.h, Table,cpp - klasa do porównywania wyników Singleton
