#include "e2d_scene.h"

/* Easy2D */
using namespace Easy2D;

bool Scene::CULLING_IS_ENABLED = true;

Scene::Scene(const String& name) : Object(name)
{
	// m_pCollisionManager = std::make_shared<CollisionManager>();
}

Scene::~Scene()
{
	for(auto & entity : mEntitys)
	{
		safeDelete(entity);
	}
	mEntitys.clear();
	// m_pCollisionManager = nullptr;
}

void Scene::destroy()
{
	SceneManager::getInstance()->RemoveScene(mName);
}

void Scene::initialize()
{
	if(!mInitialized)
	{
		createEntitys();
		if(mDefaultCamera == nullptr)
		{
			mDefaultCamera = new Camera();
			addEntity(mDefaultCamera);
		}
		mInitialized = true;
		for(auto object : mEntitys)
		{
			object->initialize(this);
		}
		afterInitializedObjects();
	}
}

void Scene::afterInitializedObjects()
{
	setActiveCamera(mDefaultCamera);
}

void Scene::onActivate()
{

}

void Scene::onDeactivate()
{
	for(auto object : mEntitys)
	{
		object->Reset();
	}
}

void Scene::update(const uint32& escapeMs))
{
	for(auto pEntity : mEntitys)
	{
		pEntity->update(context);
	}
	// m_pCollisionManager->Update(context);
}

void Scene::draw()
{
	if (!CULLING_IS_ENABLED)
	{
		for(auto pEntity : mEntitys)
		{
			pEntity->draw();
		}
	}
	else
	{
		pos camPos = mDefaultCamera->GetTransform()->GetWorldPosition();
		int32 screenWidth = GraphicsManager::getInstance()->GetScreenWidth();
		int32 screenHeight = GraphicsManager::getInstance()->GetScreenHeight();
		float32 left = camPos.pos2D().x - mCullingOffsetX;
		float32 right = camPos.pos2D().x + screenWidth + mCullingOffsetX;
		float32 top = camPos.pos2D().y + screenHeight + mCullingOffsetY;
		float32 bottom = camPos.pos2D().y - mCullingOffsetY;
		for(auto pEntity : mEntitys)
		{
			pEntity->drawWithCulling(left, right, top, bottom);
		}
	}
}

void Scene::onSaveState(void** pData, size_t* pSize)
{

}

void Scene::onConfigurationChanged()
{

}

void Scene::onLowMemory()
{

}

void Scene::addEntity(Entity* pEntity)
{
	if(!pEntity)
	{
		LOG_ERROR << _T("Scene::addEntity: You can't add a nullptr object. Adding failed!");
		return;
	}
	auto it = std::find(mEntitys.begin(), mEntitys.end(), pEntity);
	if(it == mEntitys.end())
	{
		if(mInitialized)
		{
			pEntity->initialize(this);
		}
		if(isObjectNameExist(pEntity->GetName()))
		{
			LOG_DEBUG << _T("Scene::addEntity: an object with the name '")
			<< pEntity->GetName() << _T("' already exists. Object gets added but beware, duplicate names can become the cause of problems.");
		}
		mEntitys.push_back(pEntity);
	}
}

void Scene::addEntity(Entity* pEntity, const String& name)
{
	if(!pEntity)
	{
		LOG_ERROR << _T("Scene::addEntity: Trying to add a nullptr object.");
		return;
	}
	pEntity->setName(name);
	addEntity(pEntity);
}

void Scene::removeEntity(Entity* pEntity)
{
	auto it = std::find(mEntitys.begin(), mEntitys.end(), pEntity);
	if(it != mEntitys.end())
	{
		m_pGarbage.push_back(pEntity);
	}
}

void Scene::removeEntity(const String& name)
{
	for(auto pEntity : mEntitys)
	{
		if(pEntity->compareName(name))
		{
			removeEntity(pEntity);
			return;
		}
	}
}

void Scene::setObjectDisabled(const String& name, bool disabled)
{
	for(auto pEntity : mEntitys)
	{
		if(pEntity->compareName(name))
		{
			pEntity->setDisabled(disabled);
			return;
		}
	}
}

void Scene::setObjectVisible(const String& name, bool visible)
{
	for(auto pEntity : mEntitys)
	{
		if(pEntity->compareName(name))
		{
			pEntity->setVisible(visible);
			return;
		}
	}
}

void Scene::setGroupDisabled(const String& tag, bool visible)
{
	for(auto pEntity : mEntitys)
	{
		if(pEntity->compareGroup(tag))
		{
			pEntity->setDisabled(visible);
		}
	}
}

void Scene::setGroupVisible(const String& tag, bool visible)
{
	for(auto pEntity : mEntitys)
	{
		if(pEntity->compareGroup(tag))
		{
			pEntity->setVisible(visible);
		}
	}
}

void Scene::getGroup(const String& tag, std::vector<Object*> & group)
{
	for(auto pEntity : mEntitys)
	{
		if(pEntity->compareGroup(tag))
		{
			group.push_back(pEntity);
		}
	}
}

void Scene::setActiveCamera(Camera* pCamera)
{
	if(!pCamera || mActiveCamera == pCamera)
	{
		return;
	}
	if(mActiveCamera != nullptr)
	{
		mActiveCamera->deactivate();
	}
	mActiveCamera = NewSPtr<Camera>(pCamera);
	mActiveCamera->activate();
}

SPtr<Camera> Scene::getActiveCamera() const
{
	return mActiveCamera;
}

void Scene::setCullingIsEnabled(bool enabled)
{
	CULLING_IS_ENABLED = enabled;
}

bool Scene::isCullingEnabled()
{
	return CULLING_IS_ENABLED;
}

bool Scene::isObjectNameExist(const String& name) const
{
	for(auto object : mEntitys)
	{
		if(object->compareName(name))
		{
			return true;
		}
	}
	return false;
}

void Scene::setCullingOffset(int32 offset)
{
	mCullingOffsetX = offset;
	mCullingOffsetY = offset;
}

void Scene::setCullingOffset(int32 offsetX, int32 offsetY)
{
	mCullingOffsetX = offsetX;
	mCullingOffsetY = offsetY;
}
