#include "e2d_event.h"

/* Easy2D */
using namespace Easy2D;

bool EventDispatcher::addTrigger(String& guid, SPtr<EventListerner> listener)
{
    auto iter = mTriggers.find(guid);
    if (iter == mTriggers.end())
    {
        List<SPtr<EventListerner>> listeners;
        listeners.push_back(listener);
        mTriggers.insert(std::make_pair(guid, listeners));
        return true;
    }
    List<SPtr<EventListerner>>& listeners = iter->second;
    for (auto olistener : listeners)
    {
        if (olistener == listener)
        {
            LOG_ERROR << "EventManager::addListener Add addTrigger(" << guid << ") Repeat!";
            return false;
        }
    }
    listeners.push_back(listener);
    return true;
}


bool EventDispatcher::addListener(String& guid, SPtr<EventListerner> listener)
{
    if (mListeners.find(guid) != mListeners.end())
    {
        LOG_ERROR << "EventManager::addListener Add EventListener(" << guid << ") Repeat!";
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
        List<SPtr<EventListerner>>& listeners = iter->second;
        for (auto it = listeners.begin(), itEnd = listeners.end(); it != itEnd; ++it)
        {
            if (*it == listener)
            {
                listeners.erase(it);
                break;
            }
        }
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
        List<SPtr<EventListerner>>& listeners = iter->second;
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
