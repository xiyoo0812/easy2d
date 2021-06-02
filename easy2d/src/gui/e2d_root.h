#ifndef ROOT_H
#define ROOT_H

#include "object/e2d_entity.h"
#include "base/e2d_singleton.h"

namespace Easy2D
{
    class UIRoot : public Entity
    {
    public:
        UIRoot();
        ~UIRoot(){}

        virtual void initialize();
        virtual void update(const uint32& escapeMs);
        virtual BubbleType onHandlerEvent(SPtr<Event> event);

        inline static String GUID = "gui_root";
    };
}

#endif
