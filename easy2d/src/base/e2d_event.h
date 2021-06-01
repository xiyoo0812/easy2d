#pragma once

#include "e2d_guid.h"

namespace Easy2D
{
    enum class BubbleType
    {
        Stop,
        Next
    };

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

    //-------------------------------------------------------------------------------
    class EventSink
    {
    public:
        virtual std::string getName() = 0;
        virtual BubbleType onHandlerEvent(SPtr<Event> event)
        {
            return BubbleType::Next;
        }
    };

    //-------------------------------------------------------------------------------
    class EventSinkDispatcher : public EventListerner
    {
    public:
        EventSinkDispatcher() {}
        ~EventSinkDispatcher() {}

        bool addEventSink(SPtr<EventSink> sink);
        virtual void onHandleEvent(SPtr<Event> event);

    private:
        Set<SPtr<EventSink>> mEventSinks;
    };
}
