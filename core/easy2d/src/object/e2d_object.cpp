#include "e2d_object.h"

/* Easy2D */
using namespace Easy2D;

Object::Object(void)
{
	addComponent(new TransformComponent(this));
}

Object::Object(const String& name)
	: mName(name)
{
	addComponent(new TransformComponent(this));
}

Object::Object(const String& name, const String& group)
	: mName(name), mGroup(group)
{
	addComponent(new TransformComponent(this));
}

Object::~Object()
{
	mActions.clear();
	mChildren.clear();
	mComponents.clear();
}

void Object::Destroy()
{
	if(mParent)
	{
		mParent->RemoveChild(this);
	}
	else
	{
		mScene->RemoveObject(this);
	}
}

Object* Object::GetParent() const
{
	return (mParent);
}

void Object::Initialize()
{
	if (!mInitialized)
	{
		for(auto action : mActions)
		{
			action->Initialize(this);
		}
		for(auto comp : mComponents)
		{
			comp->Initialize(this);
		}
		for(auto child : mChildren)
		{
			child->Initialize(this);
		}
		AfterInitialized();
		mInitialized = true;
	}
}

void Object::AfterInitialized()
{
}

void Object::Update(const Context& context)
{
	if(!m_IsFrozen)
	{
		for(auto action : mActions)
		{
			action->Update(context);
		}
		for(auto component : mComponents)
		{
			component->Update(context);
		}
		for(auto child : mChildren)
		{
			child->Update(context);
		}
	}
}


bool Object::CheckCulling(float32 left, float32 right, float32 top, float32 bottom)
{
	for ( auto component : mComponents)
	{
		if(component->CheckCulling(left, right, top, bottom))
		{
			return true;
		}
	}
	return false;
}

void Object::Draw()
{
	if(mVisible)
	{
		for(auto component : mComponents)
		{
			component->Draw();
		}
		for(auto child : mChildren)
		{
			child->Draw();
		}
	}
}

void Object::DrawWithCulling(float32 left,float32 right,float32 top,float32 bottom)
{
	if(mVisible)
	{
		if(CheckCulling(left, right, top, bottom))
		{
			for(auto component : mComponents)
			{
				component->Draw();
			}
		}
		for(auto child : mChildren)
		{
			child->DrawWithCulling(left, right, top, bottom);
		}
	}
}

const String& Object::GetPhysicsTag() const
{
	return mPhysics;
}

void Object::SetPhysicsTag(const String& tag)
{
	mPhysics = tag;
}

bool Object::ComparePhysicsTag(const String& tag)
{
	return mPhysics == tag;
}

bool CompareName(const String& name)
{
	return mName == name;
}

const String& Object::GetGroupTag() const
{
	return mGroup;
}

void Object::SetGroupTag(const String& tag)
{
	mGroup =tag;
}

bool Object::CompareGroupTag(const String& tag)
{
	return mGroup == tag;
}

void Object::AddComponent(BaseComponent *pComponent)
{
	auto it = mComponents.find(pComponent->getName())
	if (it != mComponents.end())
	{
		pComponent->Initialize(this);
		mComponents.insert(std::make_pair(pComponent->getName(), pComponent);
	}
}	

void Object::AddChild(Object *pChild)
{
	if(IsChildNameExist(pChild->GetName()))
	{
		LOG_DEBUG << _T("Object::AddChild: a child with the name '") << pChild->GetName() << 
			_T("' already exists. Child gets added but beware, duplicate names can become the cause of problems.")
	}
	auto it = mChildren.find(pChild->getName())
	if (it != mChildren.end())
	{
		pChild->Initialize(this);
		mChildren.insert(std::make_pair(pChild->getName(), pChild);
	}
}

void Object::RemoveChild(const Object* pObject)
{
	RemoveChild(pObject->getName());
}

void Object::RemoveChild(const String& name)
{
	auto it = mChildren.find(name)
	if (it != mChildren.end())
	{
		mChildren.erase(it);
	}
}

const UnorderedMap<String, SPtr<Object*>>& Object::GetChildren() const
{
	return mChildren;
}

void Object::SetChildDisabled(const String& name, bool disabled)
{
	auto it = mChildren.find(name)
	if (it != mChildren.end())
	{
		it->second->SetDisabled(disabled);
	}
}

void Object::SetChildVisible(const String& name, bool visible)
{
	auto it = mChildren.find(name)
	if (it != mChildren.end())
	{
		it->second->SetVisible(disabled);
	}
}

void Object::SetChildrenDisabled(bool disable)
{
	for(auto child : mChildren)
	{
		child->SetDisabled(disable);
	}
}

void Object::SetChildrenVisible(bool visible)
{
	for(auto child : mChildren)
	{
		child->SetVisible(visible);
	}
}

void Object::AddAction(Action* pAction)
{
	if(IsActionNameExist(pAction->GetName()))
	{
		LOG_DEBUG << _T("Object::AddAction: a child with the name '") << pAction->GetName() << 
			_T("' already exists. Action gets added but beware, duplicate names can become the cause of problems.")
	}
	auto it = mActions.find(pAction->getName())
	if (it != mActions.end())
	{
		pAction->Initialize(this);
		mActions.insert(std::make_pair(pAction->getName(), pAction);
	}
}

void Object::RemoveAction(Action *pAction)
{
	RemoveAction(pAction->GetName());
}

void Object::RemoveAction(const String& name)
{
	auto it = mActions.find(name)
	if (it != mActions.end())
	{
		mActions.erase(it);
	}
}

void Object::RestartAction(const String& name)
{
	auto it = mActions.find(name)
	if (it != mActions.end())
	{
		it.second->Restart();
	}
}

void Object::PauseAction(const String& name)
{
	auto it = mActions.find(name)
	if (it != mActions.end())
	{
		it.second->Pause();
	}
}

void Object::ResumeAction(const String& name)
{
	auto it = pAction.find(name)
	if (it != pAction.end())
	{
		it.second->Resume();
	}
}

void Object::RemoveComponent(BaseComponent* pComponent)
{
	auto it = mComponents.find(pComponent->getName())
	if (it != mComponents.end())
	{
		mComponents.erase(it);
	}
}

void Object::SetVisible(bool visible)
{
	mVisible = visible;
}

bool Object::IsVisible() const
{
	return mVisible;
}

bool Object::IsChildNameExist(const String& name) const
{
	for(auto pChild : mChildren)
	{
		if(pChild->CompareName(name))
		{
			return true;
		}
	}
	return false;
}

bool Object::IsActionNameExist(const String& name) const
{
	for(auto pAction : mActions)
	{
		if(pAction->CompareName(name))
		{
			return true;
		}
	}
	return false;
}

void Object::SetDisabled(bool disabled)
{
	mVisible = !disabled;
}

bool Object::IsDisabled() const
{
	return !mVisible && m_IsFrozen;
}

bool Object::IsInitialized() const
{
	return mInitialized;
}

int32* Object::GetZorder() const
{
	return mZorder;
}

void Object::SetZorder(int32* order)
{
	mZorder = order;
}

BaseScene* Object::GetScene() const
{
	return mScene;
}

void Object::SetScene(BaseScene* pScene)
{
	mScene = pScene;
	for(auto child : mChildren)
	{
		child->SetScene(pScene);
	}
}

const String & Object::GetName() const
{
	return mName;
}

void Object::SetName(const String& name)
{
	mName = name;
}

void Object::Reset()
{
	for(auto child : mChildren)
	{
		child->Reset();
	}
}

TransformComponent* Object::GetTransform() const
{
	return GetComponent<TransformComponent>();
}
