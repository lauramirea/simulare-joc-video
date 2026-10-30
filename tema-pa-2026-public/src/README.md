# Tema-PA 2026

Completati aici documentatia proiectului:
Pasul 1:
    Pasul 1.1:
        Coada folosită la Pasul 1 pentru a citi și stoca jucătorii din fișierul .csv. Coada asigură principiul FIFO (First In,  First Out), păstrând ordinea exactă în care jucătorii au fost citiți, fiind apoi ușor de extras pentru a popula arborele de turneu.
    Pasul 1.2 Stiva folosită pentru citirea și stocarea misiunilor. O stivă a fost ideală aici deoarece extragerea misiunilor se face rapid, în timp O(1).
    Pasul 1.3 Am citit din fisier valorile celor 3 matrici și după le-am stocat în main prin mbool(matricea de parcurs) m2(matrice cost linii) și m3(matrice cost coloane)
Pasul 2:
    Pasul 2.1 Luptele dintre jucători sunt modelate perfect printr-un arbore binar. Prin parcurgerea în postordine (stânga, dreapta, rădăcină), se rezolvă meciurile de la baza piramidei până la marea finală
    Pasul 2.2 Max_heap folosit pentru a crea clasamentul post-turneu. Având o complexitate de extragere de $O(\log N)$, Max-Heap-ul a permis sortarea rapidă a câștigătorilor în funcție de energia rămasă
Pasul 3:Esențial la Pasul 3 pentru algoritmul A-star (A*). Priority queue-ul minim asigură extragerea mereu a nodului cu cel mai mic cost total f, eficientizând la maximum căutarea pe hartă în O(V \log V)

La finalul celor 3 pași am eliberat memoria fiecărei structuri și cea a matricilor.
Am creat cate un fișier pentru fiecare structură folosită, pe care le-am legat între ele(EX pasul 2.2 când a trebuit să pun jucătorii într-un maxheap și m-am folosit de arborele de concurs creat la pasul anterior)

