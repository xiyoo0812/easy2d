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

        virtual void draw() = 0;
        virtual void update(const uint32& escapeMs) = 0;

        SPtr<Scene> getScene() const;
        SPtr<TransformComponent> getTransform() const;

        virtual bool checkCulling(float32 left, float32 right, float32 top, float32 bottom) const;

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
