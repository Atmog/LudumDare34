#ifndef SES_UTILITY_HPP_INCLUDED
#define SES_UTILITY_HPP_INCLUDED

#include <iostream>
#include <string>
#include <typeinfo>
#include <sstream>

#ifdef __GNUG__ // GCC

#include <cxxabi.h>
#include <cstdlib>

namespace ses
{

static std::string readable_name( const char* mangled_name )
{
    int status ;
    char* temp = __cxxabiv1::__cxa_demangle( mangled_name, nullptr, nullptr, &status ) ;
    if(temp)
    {
        std::string result(temp) ;
        std::free(temp) ;
        return result ;
    }
    else return mangled_name ;
}

} // namespace ses

#else // not GCC

namespace ses
{

std::string readable_name( const char* mangled_name ) { return mangled_name ; }

} // namespace ses

#endif // __GNUG__

namespace ses
{

// Code found here : http://www.cplusplus.com/forum/beginner/100627/
// Thanks to http://www.cplusplus.com/user/JLBorges/ for this

template<typename T>
std::string type()
{
    return readable_name(typeid(T).name());
}

template<typename T>
std::string type(const T& obj)
{
    return readable_name(typeid(obj).name());
}


// Code found here : http://cpp.developpez.com/faq/cpp/?page=Conversions#Comment-convertir-une-string-en-un-objet-de-n-importe-quel-type
// Thanks to http://www.developpez.com/user/profil/19733/Aurelien-Regat-Barrel

template<typename T>
bool from_string(const std::string& str, T& dest)
{
    std::istringstream iss(str);
    return iss >> dest != 0;
}

template <typename T>
std::string to_string(T& value)
{
    std::ostringstream oss;
    oss << value;
    return oss.str();
}

} // namespace ses


#endif // SES_UTILITY_HPP_INCLUDED
