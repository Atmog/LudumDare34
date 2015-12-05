#ifndef SES_COMPONENT_HPP
#define SES_COMPONENT_HPP

#include <memory>

namespace ses
{

class Entity;

class Component
{
    public:
        Component();
        virtual ~Component();

        typedef std::unique_ptr<Component> Ptr;

        friend Entity;

    protected:
        Entity* mEntity;
};

} // namespace ses

#endif // SES_COMPONENT_HPP
