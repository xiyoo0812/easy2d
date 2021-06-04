#include "e2d_event.h"

/* Easy2D */
using namespace Easy2D;

//EventDispatcher
//--------------------------------------------------------------------------------
bool EventDispatcher::addTrigger(String& guid, SPtr<EventListerner> listener)
{
    auto iter = mTriggers.find(guid);
    if (iter == mTriggers.end())
    {
        Set<SPtr<EventListerner>> listeners;
        listeners.insert(listener);
        mTriggers.insert(std::make_pair(guid, listeners));
        return true;
    }
    Set<SPtr<EventListerner>>& listeners = iter->second;
    auto pair = listeners.insert(listener);
    if (!pair.second)
    {
        LOG_ERROR << "EventDispatcher::addTrigger Add EventListerner(" << guid << ") Repeat!";
    }
    return pair.second;
}


bool EventDispatcher::addListener(String& guid, SPtr<EventListerner> listener)
{
    if (mListeners.find(guid) != mListeners.end())
    {
        LOG_ERROR << "EventDispatcher::addListener Add EventListerner(" << guid << ") Repeat!";
        return false;
    }
    mListeners.insert(std::make_pair(guid, listener));
    return true;
}

void EventDispatcher::removeTrigger(String& guid, SPtr<EventListerner> listener)
{
    auto iter = mTriggers.find(guid);
    if (iter != mTriggers.end())
    {
        Set<SPtr<EventListerner>>& listeners = iter->second;
        listeners.erase(listener);
    }
}

void EventDispatcher::removeListener(String& guid)
{
    auto iter = mListeners.find(guid);
    if (iter != mListeners.end())
    {
        mListeners.erase(iter);
    }
}

void EventDispatcher::notifyTrigger(SPtr<Event> event)
{
    auto guid = event->getGuid();
    auto iter = mTriggers.find(guid);
    if (iter != mTriggers.end())
    {
        Set<SPtr<EventListerner>>& listeners = iter->second;
        for (auto listener : listeners)
        {
            listener->onHandleEvent(event);
        }
    }
}

void EventDispatcher::notifyListener(SPtr<Event> event)
{
    auto guid = event->getGuid();
    for (auto iter : mListeners)
    {
        iter.second->onHandleEvent(event);
    }
}

