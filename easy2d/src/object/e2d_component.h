#ifndef COMPONENT_H
#define COMPONENT_H

#include "e2d_object.h"
#include "base/e2d_event.h"

namespace Easy2D
{
    class Scene;
    class Entity;
    class TransformComponent;

    class Component : public Object, public EventListerner
    {
    public:
        Component();
        Component(const String& name);
        virtual ~Component();

        virtual void destroy();

        virtual bool setup(SPtr<Entity> master) = 0;

        virtual void update(const uint32& escapeMs) = 0;
        virtual void onHandleEvent(SPtr<Event> event) {}

        SPtr<Scene> getScene() const;
        SPtr<TransformComponent> getTransform() const;

        void setChanged(bool changed);
        bool isChanged() const;

        SPtr<Entity> getMaster() const;
        void setMaster(SPtr<Entity> pMaster);

    protected:
        WPtr<Entity> mMaster = {};
        bool mbChanged = false;
    };
}

#endif
