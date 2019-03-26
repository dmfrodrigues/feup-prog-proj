#ifndef VIN_H_INCLUDED
#define VIN_H_INCLUDED

inline bool isCancel(std::string s){ return (s == "cancel"); }

template<class T> inline bool vin(const std::string& q, T& obj, std::istream& is = std::cin, std::ostream& os = std::cout){
    std::string b; std::stringstream ss;
    while(true){
        os << q; getline(is, b);
        if(isCancel(b)) return false;
        ss.clear(); ss.str(b); ss >> obj; if(ss) break;
        os << "Input failed, try again" << std::endl;
    }
    return true;
}

template<> inline bool vin(const std::string& q, std::string& obj, std::istream& is, std::ostream& os){
    std::string b;
    os << q; getline(is, b);
    if(isCancel(b)) return false;
    obj = b;
    return true;
}

template<class T> inline bool vin(const std::string& q, void fptr(T&, std::string), T& obj, std::istream& is = std::cin, std::ostream& os = std::cout){
    std::string b;
    while(true){
        os << q; getline(is, b);
        if(isCancel(b)) return false;
        try{
            fptr(obj, b);
            break;
        }catch(...){
            os << "Input failed, try again" << std::endl;
        }
    }
    return true;
}

#endif
