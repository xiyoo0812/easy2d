#ifndef TRANSFORM_COMPONENT_H
#define TRANSFORM_COMPONENT_H

#include "e2d_component.h"

namespace Easy2D
{
	class Object;
	class TransformComponent final: public Component
	{
	public:
		enum TransformType : byte
		{
			NONE = 0,
			TRANSLATION = 1,
			ROTATION = 2,
			SCALE = 4,
			ALL = 7
		};

		TransformComponent();
		~TransformComponent();

		virtual void initialize();

		void Update(const Context& context);
		void Draw();
		void IsChanged(bool isChanged);

		void Translate(const Vec2& translation);
		void Translate(float32 x, float32 y);
		void Translate(const Vec2& translation, lay l);
		void Translate(float32 x, float32 y, lay l);
		void Translate(const pos & pos2D);
		void TranslateX(float32 x);
		void TranslateY(float32 y);
		void TranslateL(lay l);

		void Move(const Vec2& translation);
		void Move(float32 x, float32 y);
		void MoveX(float32 x);
		void MoveY(float32 y);

		void Rotate(float32 rotation);
		void Rotate(float32 rotation, const Vec2& centerPoint);

		void Scale(const Vec2& scale);
		void Scale(float32 x, float32 y);
		void Scale(float32 u);
		void ScaleX(float32 x);
		void ScaleY(float32 y);

		void Mirror(bool x, bool y);
		void MirrorX(bool x);
		void MirrorY(bool y);
				
		const pos& GetWorldPosition();
		const pos& GetLocalPosition();
		float32 GetWorldRotation();
		float32 GetLocalRotation() const;
		const Vec2& GetWorldScale();
		const Vec2& GetLocalScale();

		void SetCenterPoint(const Vec2 & centerPoint);
		void SetCenterPoint(float32 x, float32 y);
		void SetCenterX(float32 x);
		void SetCenterY(float32 y);

		void SetDimensions(int32 x, int32 y);
		void SetDimensions(const iVec2 & dimensions);
		void SetDimensionsX(int32 x);
		void SetDimensionsY(int32 y);

		void SetDimensionsSafe(int32 x, int32 y);
		void SetDimensionsSafe(const iVec2 & dimensions);
		void SetDimensionsXSafe(int32 x);
		void SetDimensionsYSafe(int32 y);

		const Mat4& GetWorldMatrix() const;

	private:
		void CheckForUpdate(const bool force = false);
		void CommonUpdate();
		void SingleUpdate(Mat4& world);

		suchar m_IsChanged;
		bool m_Invalidate;

		pos m_WorldPosition, m_LocalPosition;
		float32 m_WorldRotation, m_LocalRotation;
		Vec2 m_WorldScale, m_LocalScale, m_CenterPosition;
		bool m_IsMirroredX;
		bool m_IsMirroredY;
		Mat4 m_World;

		static const String GUID = "transform";
	};
}

#endif
