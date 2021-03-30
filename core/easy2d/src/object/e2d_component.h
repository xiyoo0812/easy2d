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

		WPtr<Scene> getScene() const;
		SPtr<TransformComponent> getTransform() const;

		virtual bool checkCulling(float32 left, float32 right, float32 top,float32 bottom) const;

		void setEnabled(bool bEnabled);
		bool isEnabled() const;

		void setVisible(bool bVisible);
		bool isVisible() const;

		const Vec2& getDimensions() const;
		virtual int32 getWidth() const;
		virtual int32 getHeight() const;

		WPtr<Entity> getMaster() const;
		void setMaster(SPtr<Entity> pMaster);

	protected:
		WPtr<Entity> mMaster = nullptr;
		Vec2	m_Dimensions = Vec2::ZERO;
		bool	mEnabled = true, mVisible = true;
	};
}

#endif
