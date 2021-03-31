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

		void addEntity(SPtr<Entity> pEntity); 
		void addEntity(SPtr<Entity> pEntity, const String& name); 
		void removeEntity(const uint64 guid);
		void removeEntity(SPtr<Entity> pEntity);

		template <typename T = Entity>
		SPtr<T> getEntity(const uint64 guid) const;
		template <typename T = Entity>
		SPtr<T> getEntity(const String& name) const;

		void setEntityDisabled(const uint64 guid, bool disabled);
		void setEntityVisible(const uint64 guid, bool visible);

		void setGroupDisabled(const String& tag, bool disabled);
		void setGroupVisible(const String& tag, bool visable);
		void getGroup(const String& tag, Vector<SPtr<Entity>> & group);

		void setActiveCamera(SPtr<Camera> pCamera);
		SPtr<Camera> getActiveCamera() const;

		static void setCullingIsEnabled(bool enabled);
		static bool isCullingEnabled();

		bool isEntityNameExist(const String& name) const;

		void setCullingOffset(int32 offset);
		void setCullingOffset(int32 offsetX, int32 offsetY);

	protected:
		//std::shared_ptr<CollisionManager> m_pCollisionManager;

		UnorderedMap<uint64, SPtr<Entity>> mEntitys;
		SPtr<Camera> mDefaultCamera, mActiveCamera;

		int32 mCullingOffsetX, mCullingOffsetY;
		static bool CULLING_IS_ENABLED;
	};
}

#endif
