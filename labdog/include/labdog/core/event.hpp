#ifndef LABDOG_EVENT_HPP
#define LABDOG_EVENT_HPP

#include <boost/signals2.hpp>

namespace ld
{
    template <class Event>
    class event
    {
    public:

    private:
        boost::signals2::signal<Event> callback_;
    };
}

#endif // LABDOG_EVENT_HPP