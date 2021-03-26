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
		Object(const String& name, const String& groupTag);
		virtual ~Object(void);

		void Destroy();

		Object* GetParent() const;

		void Initialize();
		void AfterInitialized();
		void Update(const Context& context);
		void Draw();
		void DrawWithCulling(float32 left,float32 right,float32 top,float32 bottom);

		const String& GetPhysicsTag() const;
		void SetPhysicsTag(const String& tag);
		bool ComparePhysicsTag(const String& tag);

		const String& GetGroupTag() const;
		void SetGroupTag(const String& tag);
		bool CompareGroupTag(const String& tag);

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

		template <typename T>
		T * GetChildByName(const String& name);

		virtual void SetVisible(bool visible);
		bool IsVisible() const;

		virtual void Freeze(bool freeze);
		bool IsFrozen() const;

		bool IsChildNameAlreadyInUse(const String& name) const;
		bool IsActionNameAlreadyInUse(const String& name) const;

		virtual void SetDisabled(bool disabled);
		virtual bool IsDisabled() const;

		bool IsInitialized() const;

		void SetScene(BaseScene * pScene);
		void UnsetScene(); 

		virtual void Reset();

		TransformComponent * GetTransform() const;

		BaseScene * GetScene() const;

		template <typename T>
		void RemoveComponent();

		template <typename T>
		T* GetComponent(bool searchChildren = false) const;

		const Vector<BaseComponent*>& GetComponents() const;

		template <typename T>
		T* GetChild() const;

		template <typename T>
		T* GetChild(const String& name) const;

		template <typename T>
		bool HasComponent(BaseComponent * component) const;

		void RecalculateDimensions();

	protected:
		enum class GarbageType : byte
		{
			ComponentType = 0,
			ObjectType = 1,
			ActionType = 2
		};

		struct GarbageInfo
		{
			GarbageInfo(
				Entity* pEntity,
				GarbageType type
				);

			Entity *element;
			GarbageType type;
		};

		void DestroyGarbageElement(const GarbageInfo & info);

		virtual void Initialize();
		virtual void AfterInitialized();
		virtual void Update(const Context & context);
		virtual void Draw();

		bool BaseCheckCulling(
			float32 left, float32 right, float32 top, float32 bottom
			);

		virtual bool CheckCulling(
			float32 left,
			float32 right,
			float32 top,
			float32 bottom
			);

		bool m_bIsInitialized;
		bool m_IsVisible;
		bool m_IsFrozen;
		Object* m_pParentGameObject;
		PathFindNodeComponent* m_pPathFindComp;
		BaseScene *m_pScene;
		
		Vector<GarbageInfo> m_pGarbageContainer;

		Vector<BaseComponent*> m_pComponents;
		Vector<Object*> m_pChildren;
		Vector<Action*> m_pActions;

		HashTag m_GroupTag, m_PhysicsTag;

	private:
		void CollectGarbage();

		Object(const Object& t);
		Object(Object&& t);
		Object& operator=(const Object& t);
		Object& operator=(Object&& t);
	};
}

#endif
