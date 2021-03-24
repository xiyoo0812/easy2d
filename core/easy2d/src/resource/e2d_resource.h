#ifndef  RESOURCE_H
#define  RESOURCE_H

#include "e2d_config.h"

namespace Easy2D
{
    class ResourcesGroup;
    template<class T> class Resource;
    template<class T> class ResourcesManager;
    //
    template <class T>
    class Resource
    {
    public:
        //create a resource
        Resource(ResourcesManager<T>* rsmr = nullptr, const Path& sfile = "")
            :ptrResources(rsmr), rpath(sfile)
        {
        };
        /*manager show header disable this method*/
        void release(bool dtach = true)
        {
            if (((T*)this)->T::isLoad())
                ((T*)this)->T::unload();
            if (dtach && cbRelease)
                cbRelease(this);
        }
        //getter
        virtual bool isLoad()
        {
            return loaded;
        }
        virtual bool isReloadable()
        {
            return reloadable;
        }
        //load methods
        virtual bool load() = 0;
        virtual bool unload() = 0;
        //no virtual methods
        inline const String& getName() const
        {
            return name;
        }
        inline ResourcesManager<T>* getResourcesManager() const
        {
            return ptrResources;
        }
        inline const Path& getPath() const
        {
            return rpath;
        }

    protected:
        friend class ResourcesGroup;
        friend class ResourcesManager<T>;

        inline void setName(const String& name)
        {
            this->name = name;
        }
        inline void setReleaseCallBack(std::function<void(Resource<T>*)> cbRelease)
        {
            this->cbRelease = cbRelease;
        }

        String name;
        Path rpath;
        bool loaded = false;
        bool reloadable = false;
        ResourcesManager<T>* ptrResources = nullptr;
        Function<void(Resource<T>*)> cbRelease = nullptr;

    };
};

#endif

