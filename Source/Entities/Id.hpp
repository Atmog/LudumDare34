#ifndef SES_ID_HPP
#define SES_ID_HPP

#include <string>

namespace ses
{

class Id
{
    public:
        Id();
        Id(std::size_t id);
        Id(std::string const& id);
        Id(Id const& id);

        std::string getKey() const;

    private:
        std::string mKey;
        static std::size_t idCounter;
};


} // namespace ses

bool operator==(const ses::Id& a, const ses::Id& b);
bool operator!=(const ses::Id& a, const ses::Id& b);
bool operator<(const ses::Id& a, const ses::Id& b);
bool operator<=(const ses::Id& a, const ses::Id& b);
bool operator>(const ses::Id& a, const ses::Id& b);
bool operator>=(const ses::Id& a, const ses::Id& b);

#endif // SES_ID_HPP
