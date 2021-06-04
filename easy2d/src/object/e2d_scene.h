#ifndef SCENE_H
#define SCENE_H

#include "e2d_entity.h"

namespace Easy2D
{
    class Camera;
    class Scene : public Entity
    {
    public:
        explicit Scene(const String& name);
        virtual ~Scene();

        void destroy();

        virtual void initialize();
        virtual void onActivate();
        virtual void onDeactivate();

        void setActiveCamera(SPtr<Camera> pCamera);
        SPtr<Camera> getActiveCamera() const;

    protected:
        SPtr<Camera> mDefaultCamera, mActiveCamera;
    };
}

#endif
