# [UNIMIB][C++] Multiset
Il progetto richiede la progettazione e realizzazione di una classe che
implementa un MultiSet di elementi generici T. Un MultiSet è come un insieme
di dati che può contenere duplicati: es. S={1,4,6,4,9,4,7,10,12}.
Implementare il MultiSet in modo tale da minimizzare l’uso della memoria cioè
non dovete memorizzare i duplicati di un elemento. Facendo riferimento
all’esempio precedente, il '4' va memorizzato una sola volta sapendo però che
ci sono tre occorrenze di '4' in S.

## Implementazione
A parte i metodi essenziali per la classe (tra cui conoscere il numero totale di
elementi, aggiunta/rimozione elementi, conteggio occorrenze di un elemento,
ecc...), devono essere implementate le seguenti funzionalità:

1. la costruzione di un MultiSet anche a partire da una sequenza di dati
generici Q identificata da una coppia di iteratori generici. Questo
costruttore prende in input: l’iteratore di inizio sequenza, l’iteratore di
fine sequenza. Lasciate al compilatore la gestione della conversione di
dati tra Q e T.

2. Un iteratore di sola lettura (scegliere la categoria). L’iteratore deve
ritornare tutti gli elementi del MultiSet. Cioè, i duplicati vanno ritornati
in numero corretto. Nel caso d’esempio di S potrebbe essere una
sequenza di valori tipo: 1 4 4 4 6 9 7 10 12

3. Implementare l’operatore di confronto operator== tra due MultiSet
che ritorna true sse i due MultiSet (dello stesso tipo) contengono gli
stessi elementi con lo stesso numero di occorrenze dei duplicati.

4. Implementate un metodo contains che, dato un elemento di tipo T,
ritorna true se l'elemento esiste nel MultiSet.

5. Implementare la funzione globale operator<< per inviare su
std::ostream il contenuto del MultiSet nella forma:
{<X1, occorrenzeX1>, <X2, occorrenzeX2>,...,<XN, occorrenzeXN>}


