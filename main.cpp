#include <iostream>
#include <cassert>
#include "Multiset.h"

//Classe da usare nel multiset come tipo custom
class Persona{

private:
    std::string _nome;
    std::string _cognome;

public:

    //costruttore di default
    Persona() : _nome(""), _cognome("") {}

    //costruttore secondario
    explicit Persona(std::string n, std::string c) : _nome(n), _cognome(c){}

    //distruttore
    ~Persona() {};

    //copy constructor
    Persona(const Persona &other): _nome(other._nome), _cognome(other._cognome) {}

    //to string
    std::string to_string() const {
        return _nome + " " + _cognome;
    }

    //operatore assegnamento
    Persona& operator=(const Persona &other){
        if(this != &other) {
            Persona tmp(other);
            std::swap(this->_nome, tmp._nome);
            std::swap(this->_cognome, tmp._cognome);
        }
        return *this;
    }

    //operatore di confronto(uguaglianza)
    bool operator==(const Persona &other) const{
        if(this == &other)
            return true;

        if(this->_cognome == other._cognome && this->_nome == other._nome)
            return true;

        return false;
    }
};

//ridefinizione operatore di stream di output per oggetti di tipo 'Persona'
std::ostream& operator<<(std::ostream &os, const Persona &p){
    os << p.to_string();
    return os;
}



//_______________FUNTORI DI COMPARAZIONE________________

//funtore di comparazione per dati di tipo 'Persona'
struct equal_persona{
    bool operator()(const Persona &p1, const Persona &p2) const {
        return p1==p2;
    }
};

//funtore di comparazione per dati di tipo intero
struct equal_int{
    bool operator()(int a, int b) const {
        return a==b;
    }
};

//funtore di comparazione per dati di tipo string
struct equal_string{
    bool operator()(std::string a, std::string b) const {
        return a==b;
    }
};
//___________________________________________________


//Funzione che stampa tutti i valori del multiset tramite const_iterator
template<typename T, typename E>
void stampa_multiset(Multiset<T,E> &ms){
    typename Multiset<T,E>::const_iterator it_begin = ms.begin(), it_end = ms.end();
    std::cout << "{ ";
    while(it_begin != it_end){
        std::cout << *it_begin;
        if(++it_begin != it_end)
            std::cout << ", ";
    }
    std::cout << " }" << std::endl;
}

//typedef della classe Multiset su diversi tipi di variabili(interi, stringhe, custom)
typedef Multiset <int,equal_int> ms_interi;
typedef Multiset <std::string,equal_string> ms_stringhe;
typedef Multiset <Persona,equal_persona> ms_persone;


//_____TEST DELLE FUNZIONI SU MULTISET DI INTERI________
void test_metodi_multiset_interi() {

    //costruttore di default
    ms_interi ms_interi1;

    //test metodo 'aggiungi' su multiset di interi
    ms_interi1.aggiungi(6);
    ms_interi1.aggiungi(3);
    ms_interi1.aggiungi(4);
    ms_interi1.aggiungi(3);
    ms_interi1.aggiungi(3);
    ms_interi1.aggiungi(37);
    ms_interi1.aggiungi(8);
    ms_interi1.aggiungi(24);
    //ms_interi1 : {6, 3, 4, 3, 3, 37, 8, 24}

    //test metodo 'num_elementi' su multiset di interi
    assert(ms_interi1.num_elementi() == 8);

    //test metodo 'num_occorrenze' su multiset di interi
    assert(ms_interi1.num_occorrenze(37) == 1); //elemento con occorrenze = 1
    assert(ms_interi1.num_occorrenze(3) == 3); //elemento con occorrenze > 1

    //test metodo 'contains' su multiset di interi
    assert(ms_interi1.contains(999) == false); //elemento non presente nel multiset
    assert(ms_interi1.contains(24) == true); //elemento presente, occorrenze = 1
    assert(ms_interi1.contains(3) == true); //elemento presente, occorrenze > 1

    //test metodo 'rimuovi' su multiset di interi
    ms_interi1.rimuovi(3); //rimozione elemento, occorrenze > 1
    ms_interi1.rimuovi(4); //rimozione elemento, occorrenze = 1
    ms_interi1.rimuovi(1111); //rimozione elemento non esistente nel multiset
    ms_interi1.rimuovi(6); //rimozione elemento in testa
    ms_interi1.rimuovi(24); //rimozone elemento in coda
    //ms_interi1 : {3,3,37,8}

    //test metodo 'num_elementi' su multiset di interi(dopo rimozione elementi)
    assert(ms_interi1.num_elementi() == 4);

    //test metodo 'num_occorrenze' su multiset di interi(dopo rimozione elementi)
    assert(ms_interi1.num_occorrenze(3) == 2);
    assert(ms_interi1.num_occorrenze(24) == 0);

    //test metodo 'contains' su multiset di interi(dopo rimozione elementi)
    assert(ms_interi1.contains(24) == false);
    assert(ms_interi1.contains(3) == true);

    //test copy constructor su multiset di interi
    ms_interi ms_interi2(ms_interi1);

    //test operatore assegnamento su multiset di interi
    ms_interi ms_interi3 = ms_interi2;

    //test del costruttore secondario su multiset di interi(lista di valori presente in un array)
    int int_array[5] = {11, 22, 33, 22, 88};
    ms_interi ms_interi4(int_array, int_array + 5);

    //test del costruttore secondario su multiset di interi(lista di valori presente in un altro multiset)
    ms_interi ms_interi5(ms_interi4.begin(), ms_interi4.end());

    //test del costruttore secondario su multiset di char(lista di valori presente in un array), con cast
    char char_array[5] = {'a', 'b', 'c', 'a', 'd'};
    ms_interi ms_interi6(char_array, char_array + 5);

    //test metodo 'num_occorrenze' su multiset di interi creato da un array di char
    assert(ms_interi6.num_occorrenze(97) == 2);

    //test operatore di confronto(uguaglianza) su multiset di interi creato da un altro multiset di interi
    assert(ms_interi5 == ms_interi4);

    //test metodo 'num_elementi' su multiset di interi creato da un array di interi
    assert(ms_interi4.num_elementi() == 5);

    //test metodo 'num_occorrenze' su multiset di interi creato da un array di interi
    assert(ms_interi4.num_occorrenze(22) == 2);
    assert(ms_interi4.num_occorrenze(88) == 1);

    //test operatore di confronto(uguaglianza) su multiset di interi
    assert(ms_interi1 == ms_interi2);

    //test operatore di confronto(disuguaglianza) su multiset di interi
    assert(ms_interi1 != ms_interi4);

    //test stampa del multiset utilizzando gli iteratori
    std::cout << "Stampa multiset formato da interi: ";
    stampa_multiset(ms_interi1);

    //test stampa del multiset utilizzando l'operatore di stream di output
    std::cout << "Stampa multiset formato da interi(con operatore<<): " << ms_interi1;
    std::cout << std::endl;

    //test metodo 'svuota_multiset' su multiset di interi
    ms_interi1.svuota_multiset();
    assert(ms_interi1.num_elementi() == 0); //controllo che effettivamente il multiset sia stato svuotato
}
//----------------------------------------


//_____TEST DELLE FUNZIONI SU MULTISET DI STRINGHE________
void test_metodi_multiset_stringhe() {

    //costruttore di default
    ms_stringhe ms_stringhe1;

    //test metodo 'aggiungi' su multiset di stringhe
    ms_stringhe1.aggiungi("C");
    ms_stringhe1.aggiungi("C++");
    ms_stringhe1.aggiungi("Java");
    ms_stringhe1.aggiungi("Kotlin");
    ms_stringhe1.aggiungi("C++");
    ms_stringhe1.aggiungi("C++");
    ms_stringhe1.aggiungi("GoLang");
    //ms_stringhe1 : {"C", "C++", "Java", "Kotlin", "C++", "GoLang", "C++"}

    //test metodo 'num_elementi' su multiset di stringhe
    assert(ms_stringhe1.num_elementi() == 7);

    //test metodo 'num_occorrenze' su multiset di stringhe
    assert(ms_stringhe1.num_occorrenze("GoLang") == 1); //elemento con occorrenze = 1
    assert(ms_stringhe1.num_occorrenze("C++") == 3); //elemento con occorrenze > 1

    //test metodo 'contains' su multiset di stringhe
    assert(ms_stringhe1.contains("Python") == false); //elemento non presente nel multiset
    assert(ms_stringhe1.contains("Kotlin") == true); //elemento presente, occorrenze = 1
    assert(ms_stringhe1.contains("C++") == true); //elemento presente, occorrenze > 1

    //test metodo 'rimuovi' su multiset di stringhe
    ms_stringhe1.rimuovi("C++"); //rimozione elemento, occorrenze > 1
    ms_stringhe1.rimuovi("Kotlin"); //rimozione elemento, occorrenze = 1
    ms_stringhe1.rimuovi("JavaScript"); //rimozione elemento non esistente nel multiset
    ms_stringhe1.rimuovi("C"); //rimozione elemento in testa
    ms_stringhe1.rimuovi("GoLang"); //rimozone elemento in coda
    //ms_stringhe1 : {"Java", "C++", "C++"}

    //test metodo 'num_elementi' su multiset di stringhe(dopo rimozione elementi)
    assert(ms_stringhe1.num_elementi() == 3);

    //test metodo 'num_occorrenze' su multiset di stringhe(dopo rimozione elementi)
    assert(ms_stringhe1.num_occorrenze("C++") == 2);
    assert(ms_stringhe1.num_occorrenze("GoLang") == 0);

    //test metodo 'contains' su multiset di stringhe(dopo rimozione elementi)
    assert(ms_stringhe1.contains("GoLang") == false);
    assert(ms_stringhe1.contains("Java") == true);

    //test copy constructor su multiset di stringhe
    ms_stringhe ms_stringhe2(ms_stringhe1);

    //test operatore assegnamento su multiset di stringhe
    ms_stringhe ms_stringhe3 = ms_stringhe2;

    //test del costruttore secondario su multiset di stringhe
    std::string string_array[5] = {"Rust", "Perl", "Rust", "Prolog", "C#"};
    ms_stringhe ms_stringhe4(string_array, string_array + 5);

    //test del costruttore secondario su multiset di stringhe(lista di valori presente in un altro multiset)
    ms_stringhe ms_stringhe5(ms_stringhe4.begin(), ms_stringhe4.end());

    //test operatore di confronto(uguaglianza) su multiset di stringhe creato da un altro multiset di stringhe
    assert(ms_stringhe5 == ms_stringhe4);

    //test metodo 'num_elementi' su multiset di stringhe creato da un array di stringhe
    assert(ms_stringhe4.num_elementi() == 5);

    //test metodo 'num_occorrenze' su multiset di stringhe creato da un array di stringhe
    assert(ms_stringhe4.num_occorrenze("Rust") == 2);
    assert(ms_stringhe4.num_occorrenze("Prolog") == 1);

    //test operatore di confronto(uguaglianza) su multiset di stringhe
    assert(ms_stringhe1 == ms_stringhe2);

    //test operatore di confronto(disuguaglianza) su multiset di stringhe
    assert(ms_stringhe1 != ms_stringhe4);

    //test stampa del multiset utilizzando il const_iterator
    std::cout << "Stampa multiset formato da stringhe: ";
    stampa_multiset(ms_stringhe1);

    //test stampa del multiset utilizzando l'operatore di stream
    std::cout << "Stampa multiset formato da stringhe(con operatore<<): " << ms_stringhe1;
    std::cout << std::endl;

    //test metodo 'svuota_multiset' su multiset di stringhe
    ms_stringhe1.svuota_multiset();
    assert(ms_stringhe1.num_elementi() == 0); //controllo che effettivamente il multiset sia stato svuotato
}
//----------------------------------------


//_____TEST DELLE FUNZIONI SU MULTISET DI PERSONE________
void test_metodi_multiset_tipo_custom() {

    Persona p1( "luca", "gallo");
    Persona p2( "davide", "verdi");
    Persona p3("francesca", "grassi");
    Persona p4("maria", "vitale");
    Persona p5("angela", "milani");
    Persona p6("mario", "rossi");
    Persona p7("enrico ", "genovese");

    //costruttore di default
    ms_persone ms_persone1;

    //test metodo 'aggiungi' su multiset di tipi custom
    ms_persone1.aggiungi(p2);
    ms_persone1.aggiungi(p1);
    ms_persone1.aggiungi(p3);
    ms_persone1.aggiungi(p1);
    ms_persone1.aggiungi(p4);
    ms_persone1.aggiungi(p1);
    ms_persone1.aggiungi(p5);
    ms_persone1.aggiungi(p6);
    //ms_persone: {p2, p1, p3, p1, p4, p1, p5, p6}

    //test metodo 'num_elementi' su multiset di tipi custom
    assert(ms_persone1.num_elementi() == 8);

    //test metodo 'num_occorrenze' su multiset di tipi custom
    assert(ms_persone1.num_occorrenze(p4) == 1); //elemento con occorrenze = 1
    assert(ms_persone1.num_occorrenze(p1) == 3); //elemento con occorrenze > 1

    //test metodo 'contains' su multiset di tipi custom
    assert(ms_persone1.contains(p7) == false); //elemento non presente nel multiset
    assert(ms_persone1.contains(p5) == true); //elemento presente, occorrenze = 1
    assert(ms_persone1.contains(p1) == true); //elemento presente, occorrenze > 1

    //test metodo 'rimuovi' su multiset di tipi custom
    ms_persone1.rimuovi(p1); //rimozione elemento, occorrenze > 1
    ms_persone1.rimuovi(p5); //rimozione elemento, occorrenze = 1
    ms_persone1.rimuovi(p7); //rimozione elemento non esistente nel multiset
    ms_persone1.rimuovi(p2); //rimozione elemento in testa
    ms_persone1.rimuovi(p6); //rimozone elemento in coda
    //ms_persone: {p3, p1, p4, p1}

    //test metodo 'num_elementi' su multiset di tipi custom(dopo rimozione elementi)
    assert(ms_persone1.num_elementi() == 4);

    //test metodo 'num_occorrenze' su multiset di tipi custom(dopo rimozione elementi)
    assert(ms_persone1.num_occorrenze(p5) == 0);
    assert(ms_persone1.num_occorrenze(p1) == 2);

    //test metodo 'contains' su multiset di tipi custom(dopo rimozione elementi)
    assert(ms_persone1.contains(p5) == false);
    assert(ms_persone1.contains(p1) == true);

    //test copy constructor su multiset di tipi custom
    ms_persone ms_persone2(ms_persone1);

    //test operatore assegnamento su multiset di tipi custom
    ms_persone ms_persone3 = ms_persone2;

    //test del costruttore secondario su multiset di tipi custom
    Persona persone_array[5] = {p1, p2, p3, p1, p6};
    ms_persone ms_persone4(persone_array, persone_array + 5);

    //test del costruttore secondario su multiset di tipi custom(lista di valori presente in un altro multiset)
    ms_persone ms_persone5(ms_persone4.begin(), ms_persone4.end());

    //test operatore di confronto(uguaglianza) su multiset di tipi custom creato da un altro multiset di tipi custom
    assert(ms_persone5 == ms_persone4);

    //test metodo 'num_elementi' su multiset di tipi custom creato da un array di Persone
    assert(ms_persone4.num_elementi() == 5);

    //test metodo 'num_occorrenze' su multiset di tipi custom creato da un array di Persone
    assert(ms_persone4.num_occorrenze(p1) == 2);
    assert(ms_persone4.num_occorrenze(p6) == 1);

    //test operatore di confronto(uguaglianza) su multiset di tipi custom
    assert(ms_persone1 == ms_persone2);

    //test operatore di confronto(disuguaglianza) su multiset di tipi custom
    assert(ms_persone1 != ms_persone4);

    //test stampa del multiset utilizzando il const_iterator
    std::cout << "Stampa multiset formato da tipi custom(Persona): ";
    stampa_multiset(ms_persone1);

    //test stampa del multiset utilizzando l'operatore di stream
    std::cout << "Stampa multiset formato da tipi custom(Persona),con operatore<<: " << ms_persone1;
    std::cout << std::endl;

    //test metodo 'svuota_multiset' su multiset di tipi custom
    ms_persone1.svuota_multiset();
    assert(ms_persone1.num_elementi() == 0); //controllo che effettivamente il multiset sia stato svuotato
}
//----------------------------------------


int main() {
    test_metodi_multiset_interi();
    std::cout << "---------------------------" << std::endl;
    test_metodi_multiset_stringhe();
    std::cout << "---------------------------" << std::endl;
    test_metodi_multiset_tipo_custom();
    return 0;
}