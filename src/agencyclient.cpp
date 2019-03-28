#include "agency.h"

#include <fstream>
#include <stdexcept>
#include "vin.h"

void Agency::loadClients(const std::string& fpath){
    std::ifstream is(fpath, std::ios_base::in);
    if(!is.is_open()) throw std::ios_base::failure("failed to open clients file for read");
    vclient.clear();
    Client c; std::string b;
    while(is){
        is >> c;
        vclient.insert(c);
        getline(is, b);
    }
}

void Agency::addClient(){
    Client c;
    if(c.userClient()){
        vclient.insert(c);
        std::cout << "Client added" << std::endl;
    }
}

std::pair<unsigned, bool> Agency::seeClient() const{
    Client::print(vclient.begin(), vclient.end(), "table") << std::endl;
    int i;
    while(true){
        if(!vin("# of client to see: ", i)) return std::make_pair(0, false);
        if(0 <= i && i < (int)vclient.size())      break;
        else std::cout << "Error: # outside valid input range [0," << vclient.size()-1 << "]" << std::endl;
    }
    std::cout << std::endl;
    auto it = vclient.begin(); std::advance(it, i);
    Client::print(it, std::next(it), "screenfull");
    return std::make_pair(i, true);
}

void Agency::changeClient(){
    auto p = seeClient();
    if(!p.second) return;
    auto i = p.first;
    std::string b; std::cout << std::endl;
    int j;{
        while(true){
            if(!vin("# da propriedade a alterar: ", j)) return;
            if(0 <= j && j < 5)      break;
            else std::cout << "Número fora do intervalo permitido [0,4]" << std::endl;
        }
    }
    auto it = vclient.begin(); std::advance(it, i);
    Client cbef = *it;
    Client caft = cbef;
    if(caft.userClientprop(j)){
        vclient.erase(cbef);
        vclient.insert(caft);
        std::cout << "Propriedade alterada" << std::endl;
    }
}

void Agency::deleteClient(){
    auto p = seeClient();
    if(!p.second) return;
    auto i = p.first;
    std::string b; std::cout << std::endl;
    while(true){
        if(!vin("Confirme que pretende eliminar o cliente #"+std::to_string(i)+" [y/n]: ", b)) return;
        b = lower_case(b);
        if(b == "y" || b == "n") break;
        std::cout << "Apenas [y] (sim) ou [n] (não) são possibilidades válidas" << std::endl;
    }
    if(b == "y"){
        auto it = vclient.begin(); std::advance(it, i);
        vclient.erase(it);
        std::cout << "Cliente eliminado" << std::endl;
    }
}
