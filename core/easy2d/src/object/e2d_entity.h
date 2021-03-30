#ifndef ENTITY_H
#define ENTITY_H

#include "e2d_object.h"
#include "e2d_action.h"
#include "e2d_component.h"

namespace Easy2D
{
	class Scene;
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
		virtual void drawWithCulling(float32 left,float32 right,float32 top,float32 bottom);

		const String& GetPhysics() const;
		void setPhysics(const String& physics);
		bool comparePhysics(const String& physics);

		const String& GetGroup() const;
		void setGroup(const String& group);
		bool compareGroup(const String& group);

		void addChild(SPtr<Entity> pEntity);
		void removeChild(const String& name);
		void removeChild(const SPtr<Entity> pEntity);
		const UnorderedMap<String, SPtr<Entity>>& GetChildren() const;

		void setChildDisabled(const String& name, bool disabled);
		void setChildVisible(const String& name, bool visible);
		void setChildrenDisabled(bool disable);
		void setChildrenVisible(bool visible);

		void addAction(SPtr<Action> pAction);
		void removeAction(const SPtr<Action> pAction);
		void removeAction(const String& name);
		void restartAction(const String& name);
		void pauseAction(const String& name);
		void resumeAction(const String& name);

		void addComponent(SPtr<Component> pComponent);
		void removeComponent(const SPtr<Component> pComponent);
		void removeComponent(const String& name);

		void setVisible(bool visible);
		void setDisabled(bool disabled);
		bool isDisabled() const;
		bool isVisible() const;

		bool isChildNameExist(const String& name) const;
		bool isActionNameExist(const String& name) const;
		void Entity::recalculateDimensions()

		int32 getZorder() const;
		void setZorder(int32 order);
		WPtr<Scene> getScene() const;
		void setScene(SPtr<Scene> pScene);
		WPtr<Entity> getParent() const;
		void setParent(SPtr<Entity> pParent);
		SPtr<TransformComponent> getTransform() const;

		template <typename T = Entity>
		SPtr<T> getChild(const String& name) const;
		template <typename T = Action>
		SPtr<T> getAction(const String& name) const;
		template <typename T = Component>
		SPtr<T> getComponent(const String& name) const;

	protected:
		virtual bool checkCulling(float32 left,float32 right,float32 top,float32 bottom);

		int32 mZorder = 0;
		bool mVisible = true;
		String mGroup = "default", mPhysics = "default";

		WPtr<Scene> mScene = nullptr;
		WPtr<Entity> mParent = nullptr;
		
		UnorderedMap<String, SPtr<Action>> mActions;
		UnorderedMap<String, SPtr<Entity>> mChildren;
		UnorderedMap<String, SPtr<Component>> mComponents;
	};
}

#endif
