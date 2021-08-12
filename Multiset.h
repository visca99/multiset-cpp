#ifndef MULTISET_H
#define MULTISET_H
#include <cstdlib>
#include <iterator>
#include <cstddef>
#include <ostream>

/**
 * @tparam T tipo di dato
 * @tparam E funtore di uguaglianza
 */
template <typename T, typename E>
class Multiset {

    struct elemento{
        const T valore; ///< Valore dell'elemento del multiset
        unsigned int occorrenze; ///< Numero di occorrenze di questo elemento
        elemento *successivo; ///< Puntatore all'elemento successivo

        /**
          Costruttore di default di 'elemento'

          @post successivo==nullptr
         */
        elemento() : successivo(nullptr) {}

        /**
          Costruttore secondario di 'elemento'

          @post successivo==nullptr
          @post valore==val
          @post occorrenze==1
         */
        explicit elemento(const T &val) : valore(val), successivo(nullptr), occorrenze(1) {}

        //costruttori non utilizzati
        elemento(const T &val, unsigned int occ) : valore(val), successivo(nullptr), occorrenze(occ) {}
        elemento(const T &val, elemento *succ) : valore(val), successivo(succ), occorrenze(1) {}
        elemento(const T &val, unsigned int occ, elemento *succ) : valore(val), occorrenze(occ), successivo(succ) {}

        /**
          Distruttore di 'elemento'

          @post successivo==nullptr
        */
        ~elemento() {
            successivo = nullptr;
        }
    }; //struct elemento

    unsigned int _elementi; ///< Numero di elementi presenti nel multiset
    elemento *_testa; ///< Puntatore al primo elemento del multiset

    E _equal; ///< Istanziazione del funtore di uguaglinza

public:
    /**
      Costruttore di default

      @post _testa==nullptr
      @post _elementi==0
     */
    Multiset() : _testa(nullptr), _elementi(0) {}

    /**
      Distruttore
     */
    ~Multiset() {
        svuota_multiset();
    }

    /**
      Costruttore secondario che crea il multiset partendo da una sequenza di dati identificata da
      iteratori generici

      @param inizio iteratore di inizio
      @param fine iteratore di fine
      @throw eccezione di allocazione di memoria
     */
    template <typename Q>
    Multiset(Q inizio, Q fine) : _testa(nullptr), _elementi(0) {
        try{
            while(inizio != fine) {
                aggiungi(static_cast<T>(*inizio));
                ++inizio;
            }
        }
        catch(...) {
            svuota_multiset();
            throw;
        }
    }

    /**
      Copy constructor

      @param other Multiset da copiare
      @throw eccezione di allocazione di memoria
    */
    Multiset(const Multiset<T,E> &other): _testa(nullptr), _elementi(0){
        elemento *curr = other._testa;
        try{
            while(curr != nullptr){
                for(int i = 0; i < other.num_occorrenze(curr->valore); ++i) {
                    aggiungi(curr->valore);
                }
                curr = curr->successivo;
            }
        }
        catch(...){
            svuota_multiset();
            throw;
        }
    }

    /**
      Funzione che ritorna il numero di elementi presenti nel Multiset

      @return il numero di elementi nel Multiset
     */
    unsigned int num_elementi() const {
        return _elementi;
    }

    /**
      Funzione che ritorna il numero di occorrenze di un elemento del Multiset

      @param val valore dell'elemento da cercare
      @return il numero di occorrenze dell'elemento con valore "val"
     */
    unsigned int num_occorrenze(const T &val) const {
        if(contains(val)){
            elemento *curr = _testa;
            while(curr != nullptr){
                if(_equal(curr->valore, val)) {
                    return curr->occorrenze;
                }
                curr = curr->successivo;
            }
        }
        return 0;
    }

    /**
      Funzione che elimina tutti gli elementi all'interno del multiset

      @post _testa==nullptr
      @post _elementi==0
     */
    void svuota_multiset() {
        elemento *curr = _testa;
        elemento *tmp = nullptr;
        while(curr != nullptr){
            tmp = curr->successivo;
            delete curr;
            curr = tmp;
        }

        _testa = nullptr;
        _elementi = 0;

    }

    /**
      Ridefinizione operatore assegnamento

      @param other Multiset da assegnare
      @return reference al Multiset (this)
      @throw eccezione di allocazione di memoria
     */
    Multiset& operator=(const Multiset<T,E> &other){
        if (this != &other) {
            Multiset<T,E> tmp(other);
            std::swap(this->_testa, tmp._testa);
            std::swap(this->_elementi, tmp._elementi);
        }
        return *this;
    }

    /**
      Ridefinizione operatore di confronto(uguaglianza)

      @param other Multiset da confrontare
      @return true se i multiset contengono gli stessi elementi dello stesso tipo, false altrimenti
     */
    bool operator==(const Multiset<T,E> &other) const {
        if(this == &other)
            return true;
        if(this->num_elementi() != other.num_elementi())
            return false;

        elemento *curr = this->_testa;
        while(curr != nullptr){
            if(other.contains(curr->valore)){
                if(curr->occorrenze != other.num_occorrenze(curr->valore)){
                    return false;
                }
            }
            else{
                return false;
            }
            curr = curr->successivo;
        }
        return true;
    }

    /**
      Ridefinizione operatore di confronto(disuguaglianza)

      @param other Multiset da confrontare
      @return true se i multiset non contengono gli stessi elementi dello stesso tipo, false altrimenti
     */
    bool operator!=(const Multiset<T,E> &other) const {
        return (!(this->operator==(other)));
    }

    /**
      Funzione che cerca un elemento con valore "val" all'interno del Multiset, controlla il campo valore di tutti
      gli elementi

      @param val elemento da cercare
      @return true se l'elemento è stato trovato, false altrimenti
     */
    bool contains(const T &val) const {
        elemento *curr = _testa;

        while (curr != nullptr) {
            if (_equal(curr->valore,val))
                return true;
            curr = curr->successivo;
        }
        return false;
    }

    /**
      Funzione che aggiunge un elemento con valore "val" al Multiset (se è già
      presente un elemento con quel valore incrementa di 1 il campo "occorrenze")

      @param val valore di tipo T da aggiungere al Multiset
      @throw eccezione di allocazione di memoria
     */
    void aggiungi(const T &val) {
        elemento *tmp = new elemento(val);
        _elementi++;

        if(_testa == nullptr) {
            _testa = tmp;
            return;
        }
        else{
            elemento *curr = _testa;

            if(contains(val)){
                while (curr != nullptr) {
                    if (_equal(curr->valore, val)){
                        curr->occorrenze++;
                        delete tmp;
                        tmp = nullptr;
                        return;
                    }
                    curr = curr->successivo;
                }
            }
            else{
                while (curr != nullptr){
                    if (curr->successivo == nullptr){
                        curr->successivo = tmp;
                        return;
                    }
                    curr = curr->successivo;
                }
            }
        }

    }

    /**
      Funzione che rimuove un elemento dal Multiset(se l'elemento ha occorrenze maggiori di 1
      allora il campo "occorrenze" viene decrementato di 1, altrimenti l'elemento viene rimosso)

      @param val valore di tipo T da rimuovere dal Multiset
     */
    void rimuovi(const T &val){
        elemento *curr = _testa;
        elemento *prev = _testa;

        if(contains(val)) {
            _elementi--;
            while (curr != nullptr) {
                if(_equal(_testa->valore, val)) {
                    if(_testa->occorrenze == 1) {
                        _testa = _testa->successivo;
                        delete curr;
                        curr = nullptr;
                        return;
                    }
                    else if(_testa->occorrenze > 1){
                        _testa->occorrenze--;
                        return;
                    }
                }
                else if(_equal(curr->valore, val)){
                    if(curr->occorrenze > 1) {
                        curr->occorrenze--;
                        return;
                    }
                    else if(curr->occorrenze == 1){
                        prev->successivo = curr->successivo;
                        delete curr;
                        curr = nullptr;
                        return;
                    }
                }
                prev = curr;
                curr = curr->successivo;
            }
        }
    }



    class const_iterator {

    private:

        unsigned int occ_contate; ///< memorizza le occorrenze gia' considerate(stampate, memorizzate, ecc.) di ogni elemento

    public:
        typedef std::forward_iterator_tag iterator_category;
        typedef T                         value_type;
        typedef ptrdiff_t                 difference_type;
        typedef const T*                  pointer;
        typedef const T&                  reference;

        const_iterator() : ptr(nullptr), occ_contate(0) {
        }

        const_iterator(const const_iterator &other) : ptr(other.ptr), occ_contate(0) {
        }

        const_iterator& operator=(const const_iterator &other) {
            ptr = other.ptr;
            this->occ_contate = other.occ_contate;
            return *this;
        }

        ~const_iterator() {}

        // Dereferenzia il puntatore
        reference operator*() const {
            return ptr->valore;
        }

        // Ritorna il puntatore al dato riferito dall'iteratore
        pointer operator->() const {
            return &(ptr->valore);
        }

        //Ritorna il numero di occorrenze del dato riferito dall'iteratore
        unsigned int num_occ_it() const {
            return ptr->occorrenze;
        }

        // Operatore di iterazione post-incremento (i++)
        const_iterator operator++(int) {
            if(num_occ_it() == 1){
                const_iterator tmp(*this);
                ptr = ptr->successivo;
                occ_contate = 0;
                return tmp;
            }
            else{
                if(occ_contate < (num_occ_it()-1)){
                    occ_contate++;
                    return *this;
                }
                else{
                    const_iterator tmp(*this);
                    ptr = ptr->successivo;
                    occ_contate = 0;
                    return tmp;
                }
            }
        }

        // Operatore di iterazione pre-incremento (++i)
        const_iterator& operator++() {
            if(num_occ_it() == 1){
                ptr = ptr->successivo;
                occ_contate = 0;
                return *this;
            }
            else{
                if(occ_contate < (num_occ_it()-1)){
                    occ_contate++;
                    return *this;
                }
                else{
                    ptr = ptr->successivo;
                    occ_contate = 0;
                    return *this;
                }
            }
        }

        // Uguaglianza
        bool operator==(const const_iterator &other) const {
            return (ptr == other.ptr);
        }

        // Diversita'
        bool operator!=(const const_iterator &other) const {
            return (ptr != other.ptr);
        }

    private:
        const elemento *ptr;

        friend class Multiset;

        const_iterator(const elemento *elemento) : ptr(elemento), occ_contate(0) {
        }

    }; // classe const_iterator

    /**
      Funzione che ritorna l'iteratore all'inizio della sequenza di dati

      @return iteratore begin
     */
    const_iterator begin() const {
        return const_iterator(_testa);
    }

    /**
      Funzione che ritorna l'iteratore alla fine della sequenza di dati

      @return iteratore end
     */
    const_iterator end() const {
        return const_iterator(nullptr);
    }

}; // classe Multiset

/**
  Ridefinizione operatore stream di output per stampare il contenuto del Multiset

  @param os stream di output
  @param m Multiset
  @return reference all'ostream
 */
template <typename T, typename E>
std::ostream& operator<<(std::ostream &os, const Multiset<T,E> &m){
    typename Multiset<T,E>::const_iterator inizio, fine;
    inizio  = m.begin();
    fine = m.end();

    os<<"{";
    while(inizio != fine) {
        unsigned int occ_curr = inizio.num_occ_it();
        os << "<" << *inizio << "," << occ_curr << ">";
        while(occ_curr != 0) {
            ++inizio;
            occ_curr--;
        }
    }
    os<<"}";
    return os;
}


#endif