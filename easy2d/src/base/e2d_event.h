#pragma once

#include "e2d_guid.h"

namespace Easy2D
{

    //-------------------------------------------------------------------------------
    class Event
    {
    public:
        Event(String& guid) : mGuid(guid) {}
        const String& getGuid() { return mGuid; }

    protected:
        String mGuid = "";
    };

    //-------------------------------------------------------------------------------
    class EventListerner
    {
    public:
        virtual void onHandleEvent(SPtr<Event> event) = 0;
    };

    //-------------------------------------------------------------------------------
    class EventDispatcher
    {
    public:
        EventDispatcher() {}
        ~EventDispatcher() {}

        bool addTrigger(String& guid, SPtr<EventListerner> listener);
        bool addListener(String& guid, SPtr<EventListerner> listener);
        void removeTrigger(String& guid, SPtr<EventListerner> listener);
        void removeListener(String& guid);

        void notifyTrigger(SPtr<Event> event);
        void notifyListener(SPtr<Event> event);

    private:
        UnorderedMap<String, SPtr<EventListerner>> mListeners;
        UnorderedMap<String, Set<SPtr<EventListerner>>> mTriggers;
    };
}
