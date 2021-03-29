#ifndef SCENE_H
#define SCENE_H

#include "e2d_entity.h"

namespace Easy2D 
{
	class Camera;
	class CameraComponent;

	class Scene : public Object
	{
	public:
		explicit Scene(const String& name);
		virtual ~Scene();

		void destroy();
		
		virtual void initialize();
		virtual void onActivate();
		virtual void onDeactivate();
		virtual void update(const uint32& escapeMs));
		virtual void draw();

		virtual void onSaveState(void** pData, size_t* pSize);
		virtual void onConfigurationChanged();
		virtual void onLowMemory();

		virtual void addEntity(Entity* pEntity); 
		void addEntity(Entity* pEntity, const String& name); 
		virtual void removeEntity(Entity* pEntity);
		void removeEntity(const String& name);

		template <typename T>
		T* getEntity(const String& name) const;

		void setEntityDisabled(const String& name, bool disabled);
		void setEntityVisible(const String& name, bool visible);

		void setGroupDisabled(const String& tag, bool disabled);
		void setGroupVisible(const String& tag, bool visable);
		void getGroup(const String& tag, std::vector<Entity*> & group);

		void setActiveCamera(Camera* pCamera);
		SPtr<Camera> getActiveCamera() const;

		static void setCullingIsEnabled(bool enabled);
		static bool isCullingEnabled();

		bool isEntityNameExist(const String& name) const;

		void setCullingOffset(int32 offset);
		void setCullingOffset(int32 offsetX, int32 offsetY);

	protected:
		virtual void createEntitys() = 0;

		//std::shared_ptr<CollisionManager> m_pCollisionManager;

		std::vector<Entity*> mEntitys;
		SPtr<Camera> *mDefaultCamera, *mActiveCamera;

		int32 mCullingOffsetX, mCullingOffsetY;
		static bool CULLING_IS_ENABLED;
	};
}

#endif
