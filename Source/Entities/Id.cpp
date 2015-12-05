#include "Id.hpp"

namespace ses
{

std::size_t Id::idCounter = 0;

Id::Id()
: mKey(to_string(idCounter))
{
    idCounter++;
}

Id::Id(std::size_t id)
: mKey(to_string(id))
{
}

Id::Id(std::string const& id)
: mKey(id)
{
}

Id::Id(const Id& id)
: mKey(id.getKey())
{
}

std::string Id::getKey() const
{
    return mKey;
}

} // namespace ses


bool operator==(const ses::Id& a, const ses::Id& b)
{
    return (a.getKey() == b.getKey());
}

bool operator!=(const ses::Id& a, const ses::Id& b)
{
    return !(a == b);
}

bool operator<(const ses::Id& a, const ses::Id& b)
{
    return (a.getKey().size() < b.getKey().size());
}

bool operator<=(const ses::Id& a, const ses::Id& b)
{
    return (a.getKey().size() <= b.getKey().size());
}

bool operator>(const ses::Id& a, const ses::Id& b)
{
    return !(a <= b);
}

bool operator>=(const ses::Id& a, const ses::Id& b)
{
    return !(a < b);
}

