#ifndef ACTION_H
#define ACTION_H

#include "e2d_object.h"

namespace Easy2D
{
    class Entity;
    class Action : public Object
    {
    public:
        Action();
        Action(const String& name);
        virtual ~Action();

        virtual bool setup(SPtr<Entity> master) = 0;
        virtual void update(const uint32& escapeMs) = 0;

        void destroy();
        void restart();
        void pause();
        void resume();

        WPtr<Entity> getMaster() const;
        void setMaster(SPtr<Entity> pMaster);

    protected:
        bool mPaused;
        WPtr<Entity> mMaster{};
    };
}

#endif
