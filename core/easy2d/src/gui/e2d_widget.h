#ifndef WIDGET_H
#define WIDGET_H

#include "object/e2d_entity.h"

namespace Easy2D
{
	class UIDock;
	class UIWidget : public Entity
	{
	public:
		UIWidget(const tstring & name);
		virtual ~UIWidget();

		virtual void draw();
		virtual void initialize();
		virtual void update(const uint32& escapeMs);

		virtual void translate(const Vec2& translation);
		virtual void translate(float32 x, float32 y);
		virtual void translate(const Vec2& translation, lay l);
		virtual void translate(float32 x, float32 y, lay l);
		virtual void translate(const Pos& pos2D);
		virtual void translateX(float32 x);
		virtual void translateY(float32 y);

		virtual void setHorizontalAlignment(HorizontalAlignment alignment,bool redefineCenter = true);
		virtual void setVerticalAlignment(VerticalAlignment alignment,bool redefineCenter = true);
		void setAlignmentCentered(bool redefineCenter = true);

		void reposition();
		void setRootWidget();
		
	protected:
		Vec2 getDockDimensions() const;

		void translateUI(Pos& pos);
		void translateUIX(float32 x, const Vec2& dimensions);
		void translateUIY(float32 y, const Vec2& dimensions);

		void repositionChildren();

		bool mbRootWidget = false;
		VerticalAlignment mVerticalAlignment;
		HorizontalAlignment mHorizontalAlignment;
	};
}
