#ifndef CLIENT_H_INCLUDED
#define CLIENT_H_INCLUDED

#include <string>
#include <vector>
#include <iostream>
#include <set>
#include "globaldefs.h"
#include "address.h"
#include "travelpack.h"
#include "convenient.h"


struct Client{
friend std::istream& operator>>(std::istream& is,       Client& c);
friend std::ostream& operator<<(std::ostream& os, const Client& c);
private:
    Name name_;
    NIF nif_;
    int numFam_;
    Address address_;
    std::set<ID> vtravel_;
    //TOTAL DE COMPRAS EFETUADAS?

    static void setPacks(Client& c, std::string s);

public:

    static std::set<ID> makePacks(std::string s);
    /***/
    std::string getPacks(const std::string& delim = " ; ") const;
    /***/
    bool userClient(std::istream& is = std::cin, std::ostream& os = std::cout);
    /***/
    bool userClientprop(int propn, std::istream& is = std::cin, std::ostream& os = std::cout);

    /***/
    const std::string&  name     ()const{ return name_   ; }
    const NIF&          nif      ()const{ return nif_    ; }
    const int&          numFamily()const{ return numFam_ ; }
    const Address&      address  ()const{ return address_; }
    const std::set<ID>& vtravel  ()const{ return vtravel_; }

    /***/
    void sell(ID id){ vtravel_.insert(id); }

    /***/
    template<class ForwardIterator>
    static std::ostream& print(ForwardIterator first, ForwardIterator last, std::string f, std::ostream& os = std::cout);

    /***/
    bool operator<(const Client& obj) const;
};

/***/
std::istream& operator>>(std::istream& is, Client& c);

/***/
std::ostream& operator<<(std::ostream& os, const Client& c);

#endif
