#ifndef ENTITY_H
#define ENTITY_H

#include "math/e2d_pos.h"
#include "e2d_object.h"
#include "e2d_action.h"
#include "e2d_component.h"

namespace Easy2D
{
    class Scene;
    class TransformComponent;
    class Entity : public Object
    {
    public:
        Entity();
        Entity(const String& name);
        Entity(const String& name, const String& group);
        virtual ~Entity(void);

        virtual void reset();
        virtual void destroy();
        virtual void initialize();
        virtual void draw();
        virtual void update(const uint32& escapeMs);
        virtual void drawWithCulling(float32 left, float32 right, float32 top, float32 bottom);

        virtual void setPosition(const Vec2& pos);
        virtual void setPosition(float32 x, float32 y);
        virtual void setPositionX(float32 x);
        virtual void setPositionY(float32 y);

        void setMirror(bool x, bool y);
        void setMirrorX(bool x);
        void setMirrorY(bool y);

        void setScale(const Vec2& scale);
        void setScale(float32 x, float32 y);
        void setScale(float32 u);
        void setScaleX(float32 x);
        void setScaleY(float32 y);

        const Vec2& getDimensions() const;
        const Vec2& getWorldPosition() const;
        const Vec2& getLocalPosition() const;
        const String& getPhysics() const;
        void setPhysics(const String& physics);
        bool comparePhysics(const String& physics);

        const String& getGroup() const;
        void setGroup(const String& group);
        bool compareGroup(const String& group);

        void sortChild();
        bool addChild(SPtr<Entity> pEntity);
        void removeChild(const uint64 guid);
        void removeChild(const String& name);
        void removeChild(const SPtr<Entity> pEntity);
        const Vector<SPtr<Entity>>& getChildren() const;

        void setChildDisabled(const uint64 guid, bool disabled);
        void setChildVisible(const uint64 guid, bool visible);
        void setChildrenDisabled(bool disable);
        void setChildrenVisible(bool visible);

        bool addAction(SPtr<Action> pAction);
        void removeAction(const SPtr<Action> pAction);
        void removeAction(const uint64 guid);
        void removeAction(const String& name);
        void restartAction(const uint64 guid);
        void pauseAction(const uint64 guid);
        void resumeAction(const uint64 guid);

        bool addComponent(SPtr<Component> pComponent);
        void removeComponent(const SPtr<Component> pComponent);
        void removeComponent(const uint64 guid);
        void removeComponent(const String& name);

        void setVisible(bool visible);
        void setDisabled(bool disabled);
        bool isDisabled() const;
        bool isVisible() const;

        bool isChildNameExist(const String& name) const;
        bool isActionNameExist(const String& name) const;
        bool isComponentNameExist(const String& name) const;
        void Entity::recalculateDimensions();

        int32 getZorder() const;
        void setZorder(int32 order);
        SPtr<Scene> getScene() const;
        void setScene(SPtr<Scene> pScene);
        SPtr<Entity> getParent() const;
        void setParent(SPtr<Entity> pParent);
        SPtr<TransformComponent> getTransform() const;

        template <typename T = Entity>
        SPtr<T> getChild(const uint64 guid) const;
        template <typename T = Entity>
        SPtr<T> getChild(const String& name) const;
        template <typename T = Action>
        SPtr<T> getAction(const uint64 guid) const;
        template <typename T>
        SPtr<T> getComponent(const uint64 guid) const;
        template <typename T = Component>
        SPtr<T> getComponent(const String& name) const;

    protected:
        virtual bool checkCulling(float32 left, float32 right, float32 top, float32 bottom);

        int32 mZorder = 0;
        bool mVisible = true;
        bool mDisable = false;
        String mGroup = "default", mPhysics = "default";

        WPtr<Scene> mScene = {};
        WPtr<Entity> mParent = {};
        SPtr<TransformComponent> mTransform = nullptr;

        Vector<SPtr<Action>> mActions;
        Vector<SPtr<Entity>> mChildrens;
        Vector<SPtr<Component>> mComponents;

    };
}

#include "e2d_entity.hpp"

#endif
