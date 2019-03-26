#include "client.h"

#include "vin.h"

std::istream& operator>>(std::istream& is, Client& c){
    std::stringstream dummy;
    if(!vin("",                    c.name_    , is, dummy) ||
       !vin("",                    c.nif_     , is, dummy) ||
       !vin("",                    c.numFam_  , is, dummy) ||
       !vin("", &Address::set    , &c.address_, is, dummy) ||
       !vin("", &Client::setPacks, &c         , is, dummy))
       throw std::invalid_argument("could not read client file");
    return is;
}

std::ostream& operator<<(std::ostream& os, const Client& c){
    os << c.name_      << std::endl;
    os << c.nif_       << std::endl;
    os << c.numFam_    << std::endl;
    os << c.address_   << std::endl;
    os << c.getPacks();
    return os;
}

void Client::setPacks(Client* cptr, std::string s){
    cptr->vtravel_ = makePacks(s);
}

std::vector<ID> Client::makePacks(std::string s){
    std::vector<ID> ret;
    std::vector<std::string> v = parse(s, ';');
    for(auto s:v) ret.push_back(str_to<ID>(s));
    return ret;
}

std::string Client::getPacks() const{
    AQUI
}



bool Client::operator<(const Client& c) const{
    if     (name_    != c.name_   ) return (name_    < c.name_   );
    else if(nif_     != c.nif_    ) return (nif_     < c.nif_    );
    else if(numFam_  != c.numFam_ ) return (numFam_  < c.numFam_ );
    else if(address_ != c.address_) return (address_ < c.address_);
    else                            return (vtravel_ < c.vtravel_);
}
