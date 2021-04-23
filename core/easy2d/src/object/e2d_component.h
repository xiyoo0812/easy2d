#ifndef COMPONENT_H
#define COMPONENT_H

#include "e2d_object.h"

namespace Easy2D
{
    class Scene;
    class Entity;
    class TransformComponent;

    class Component : public Object
    {
    public:
        Component();
        Component(const String& name);
        virtual ~Component();

        void destroy();

        virtual void initialize() = 0;

        virtual void update(const uint32& escapeMs) = 0;

        SPtr<Scene> getScene() const;
        SPtr<TransformComponent> getTransform() const;

        void setEnabled(bool bEnabled);
        bool isEnabled() const;

        void setVisible(bool bVisible);
        bool isVisible() const;

        SPtr<Entity> getMaster() const;
        void setMaster(SPtr<Entity> pMaster);

    protected:
        WPtr<Entity> mMaster = {};
        bool mEnabled = true, mVisible = true;
    };
}

#endif
