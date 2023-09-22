# Structuri de date şi algoritmi - Tema 2

Student: Andronache Madalina-Georgiana
Grupa: 312CC

Urmatorul fisier contine informatii despre rezolvarea problemei propusa in 
tema 2 de la SDA. Punctajul obtinut la testarea locala este de 100 de puncte,
dintre care 20 pentru Valgrind.

Cea mai mare provocare intalnita a fost rezolvarea corecta si cat mai eficienta
a problemei propuse intr-un timp cat mai scurt. Aceasta tema a fost rezolvata
pe parcursul a 17 zile: in total am lucrat la aceasta tema 25 h, dintre care 
2 h fiind necesare pentru scrierea fisierului README, iar restul pentru codare 
si testarea problemei. In viitor, imi doresc rezolvarea mai rapida a 
cerintelor.

Cuprins:
1. Cerinta 1 - Statistici
2. Cerinta 2 - Compresia fisierelor
3. Cerinta 3 - Decompresia fisierelor
4. Fisierul principal - main.c

Pentru rezolvarea intregii probleme am creat urmatoarele fisiere: main.c, c1.c,
c2.c, c3.c si structs.h. Pentru o intelegere mai buna a urmatoarelor functii 
prezentate, este importat de mentionat ca am definit in fisierul structs.h 
urmatoarele structuri: Pixel - avand campurile unsigned char red, green si 
blue, Node - reprezentand structura unui nod din arborele cuaternal si 
avand campurile Pixel data - in care se memoreaza valorile RGB, unsigned
char type - memorand 0, daca nodul este intern sau 1 daca nodul este terminal 
si cei 4 fii ai nodului in campurile area[i], cu i de la 0 la 3. 
Deoarece pentru cerintele 2 si 3 am folosit o coada, am implementat si doua 
structuri pentru acest tip de date: Node_q - memorand datele nodului din coada
si Queue - avand campurile first si last ale cozii.

# 1. Cerinta 1 - Statistici

Pentru rezolvarea acestei cerinte am implementat urmatoarele functii:
* Node *newNode(void) - creaza un nou nod al arborelui si aloca memorie pentru
acesta.
* Pixel **read(int *size, FILE *fin) - citeste datele din fisierul fin, 
reprezentand fisierul corespunzator imaginii PPM, returnand prin intermediul 
parametrului size dimensiunea imaginii si avand ca rezultat matricea de tip
Pixel corespunzatoare imaginii PPM.
* int evaluate(Pixel **image, int x, int y, int size, int factor, int 
*red_value, int *green_value, int *blue_value) - aceasta functie este folosita 
pentru a verifica daca scorul similitatii blocului care porneste din 
coordonatele x si y si are dimensiunea size este mai mica sau egala decat 
factorul furnizat. Daca aceasta conditie este indeplinita, atunci functia va 
returna 1, iar prin intermediul parametrilor red_value, green_value si
blue_value, valorile RGB corespunzatoare blocului. In caz contrar, functia
va returna 0.
* void complete(Node **node, Pixel **image, int x, int y, int size, 
int factor) - aceasta functie este folosita pentru a construi arborele 
cuaternal conform enuntului folosind matricea de tip Pixel data ca parametru.
Pornind din radacina se verifica cu ajutorul functiei evaluate, daca blocul 
corespunde unui nod terminal, in acest caz, salvand in campul data al nodului 
valorile RGB ale blocului, altfel, actualizam dimensiunea blocului si apelam 
recursiv functia pentru cei 4 fii ai nodului in care ne aflam la momentul 
curent.
* int min_level(Node *node) - aceasta functie este folosita pentru a calcula 
recursiv primul nivel, pornind de la radacina in jos, pe care se gaseste un
nod terminal.
* int levels(Node *node) - functia indeplineste primul subpunct al cerintei 1, 
returnand numarul de niveluri al arborelui. 
* int blocks(Node *node) - functia indeplineste al doilea subpunct al cerintei 
1, returnand numarul de blocuri din imagine care au scorul similitatii mai mic
sau egal cu factorul furnizat. Acest lucru este determinat prin calcularea 
numarului de noduri terminale ale arborelui cuaternal.
* int max_dimension(int dimension, int levels) - aceasta functie este folosita
pentru a rezolva ultimul subpunct al cerintei 1. Are ca parametrii dimensiunea
initiala a imaginii si nivelul pe care se gaseste primul nod terminal al 
arborelui si returneaza dimensiunea blocului reprezentat de acest nod 
terminal. 

# 2. Cerinta 2 - Compresia fisierelor

Pentru rezolvarea acestei cerinte am implementat urmatoarele functii:
* Queue *initQ(void) - initializeaza coada q, pe care o returneaza ca rezultat 
al functiei.
* void enqueue(Queue **q, Node *data) - introduce elementul de tip nod al 
arborelui cuaternal in coada q.
* Node *dequeue(Queue **q) - scoate elementul de tip nod al arborelui 
cuaternal din varful cozii, coada fiind o structura de tip FIFO (first in
first out) si returneaza acel nod ca rezultat al functiei.
* void bfs(Node *root, FILE *fout) - aceasta functie rezolva cerinta 2 a 
problemei, scriind in fisierul binar fout, parcurgerea pe nivel a arborelui
pornind din radacina si respectand enuntul problemei: pentru fiecare nod
se scrie in fisier 0 sau 1 respectand tipul nodului. Daca nodul este terminal,
se scriu in fisierul binar valorile RGB memorate in campul data al nodului.

# 3. Cerinta 3 - Decompresia fisierelor

Pentru rezolvarea acestei cerinte am implementat urmatoarele functii:
* Node *read_bfs(FILE *fin) - citind din fisierul binar fin, construim
arborele cuaternal corespunzator parcurgerii pe nivel a arborelui. Ne
folosim de o coada, in care initial adaugam radacina. Cat timp coada mai 
are elemente, scoate elementul din varful cozii si citim urmatoarele date:
tipul nodului (0 sau 1), daca nodul este terminal, citim si valorile RGB 
memorate in campul data al nodului, altfel initializam cei 4 fii ai nodului
si ii adaugam in coada.
* void fillImage(Node *node, int x, int y, int size, Pixel **image) -
construim matricea de pixeli recursiv corespunzatoare arborelui, pornind
de la coordonatele x si y si de dimensiune size. 
* void createPPM(FILE *fout, Pixel **image, int dimension) - aceasta functie
rezolva cerinta 3 a problemei, scriind in fisierul binar datele corespunzatoare
fisierului PPM. 

# 4. Fisierul principal - main.c

Acest program pune la un loc implementarea totala a problemei: in functia 
main se citeste ca argument in linia de comanda "-c1", "-c2" sau "-d". 
In functie de ce a fost introdus, se va rezolva cerinta 1, 2 sau 3.
* void resolve_C1(int factor, FILE *fin, FILE *fout) - aceasta functie
rezolva cerinta 1.
* void resolve_C2(int factor, FILE *fin, FILE *fout) - aceasta functie
rezolva cerinta 2.
* void resolve_D(FILE *fin, FILE *fout) - aceasta functie rezolva cerinta 3.
La finalul acestui program ne asiguram ca inchidem fisierele de intrare si 
iesire. 
