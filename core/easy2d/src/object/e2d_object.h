#ifndef OBJECT_H
#define OBJECT_H

#include "e2d_config.h"

namespace Easy2D
{
	class BaseComponent;
	class PathFindNodeComponent;
	class BaseScene;
	class Action;

	class Object
	{
	public:
		Object();
		explicit Object(const String& name);
		Object(const String& name, const String& group);
		Object(const Object& t);
		Object(Object&& t);
		Object& operator=(const Object& t);
		Object& operator=(Object&& t);
		virtual ~Object(void);

		void Destroy();

		Object* GetParent() const;

		virtual void Initialize();
		virtual void AfterInitialized();
		virtual void Draw();
		virtual void Update(const Context& context);
		virtual void DrawWithCulling(float32 left,float32 right,float32 top,float32 bottom);

		const String& GetPhysicsTag() const;
		void SetPhysicsTag(const String& tag);
		bool ComparePhysicsTag(const String& tag);

		const String& GetGroup() const;
		void SetGroup(const String& tag);
		bool CompareGroup(const String& tag);

		void AddComponent(BaseComponent* pComponent);

		virtual void AddChild(Object* pObject);
		void RemoveChild(const Object* pObject);
		void RemoveChild(const String& name);
		const Vector<Object*>& GetChildren() const;

		void SetChildFrozen(const String& name, bool freeze);
		void SetChildDisabled(const String& name, bool disabled);
		void SetChildVisible(const String& name, bool visible);

		void SetChildrenFrozen(bool freeze);
		void SetChildrenDisabled(bool disable);
		void SetChildrenVisible(bool visible);

		void AddAction(Action * pAction);
		void RemoveAction(Action *pAction);
		void RemoveAction(const String& name);
		void RestartAction(const String& name);
		void PauseAction(const String& name);
		void ResumeAction(const String& name);

		void RemoveComponent(BaseComponent * pComponent);

		virtual void SetVisible(bool visible);
		virtual void SetDisabled(bool disabled);
		virtual bool IsDisabled() const;
		bool IsInitialized() const;
		bool IsVisible() const;

		bool IsChildNameExist(const String& name) const;
		bool IsActionNameExist(const String& name) const;

		BaseScene* GetScene() const;
		void SetScene(BaseScene* pScene);
		int32* GetZorder() const;
		void SetZorder(int32* order);
		String* GetName() const;
		void SetName(String* name);

		virtual void Reset();

		TransformComponent* GetTransform() const;

		template <typename T>
		T* GetChildByName(const String& name);
		template <typename T>
		void RemoveComponent();
		template <typename T>
		T* GetComponent(bool searchChildren = false) const;
		template <typename T>
		T* GetChild() const;
		template <typename T>
		T* GetChild(const String& name) const;
		template <typename T>
		bool HasComponent(BaseComponent * component) const;

	protected:
		virtual bool CheckCulling(float32 left,float32 right,float32 top,float32 bottom);

		uint64 mGUID = 0;
		int32 mZorder = 0;
		bool mVisible = true;
		bool mInitialized = false;
		String mName = "", mGroup = "default", mPhysics = "default";

		Object* mParent = nullptr;
		BaseScene* mScene = nullptr;
		
		UnorderedMap<String, SPtr<Action*>> mActions;
		UnorderedMap<String, SPtr<Object*>> mChildren;
		UnorderedMap<String, SPtr<BaseComponent*>> mComponents;
	};
}

#endif
