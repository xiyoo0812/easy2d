#ifndef RESOURCEMANAGER_H
#define RESOURCEMANAGER_H

#include "e2d_config.h"

namespace Easy2D
{
    class ResourcesGroup;

    template <class T>
    class ResourcesManager
    {
        friend class ResourcesGroup;
    public:
        ResourcesManager(ResourcesGroup* rsgr, const Path& path)
            :rsgr(rsgr), resPath(path)
        {
        }
        ~ResourcesManager()
        {
            //dt all resources
            for (auto rs : resMap)
            {
                rs.second.lock()->Resource<T>::setReleaseCallBack([](Resource<T>* rs) {});
            }
        }
        //manager mathos
        SPtr<T> find(const String& objectname)
        {
            //search in this pool
            auto it = resMap.find(objectname);
            if (it != resMap.end())
                return it->second.lock();
            return nullptr;
        }
        SPtr<T> get(const String& objectname)
        {
            //search
            auto resource = find(objectname);
            if (resource) return resource;
            //else make resource
            Path path = resPath;
            if (std::filesystem::exists(path.append(objectname)))
            {
                SPtr<T> resource = NewSPtr<T>(this, path);
                //set into map
                resMap[objectname] = resource;
                resource->Resource<T>::setName(objectname);
                resource->Resource<T>::setReleaseCallBack(
                    [this](Resource<T>* rs)
                {
                    this->resMap.erase(rs->getName());
                });
                return resource;
            }
            return SPtr<T>();
        }
        SPtr<T> load(const String& objectname)
        {
            //get resource
            SPtr<T> resource = get(objectname);
            if (resource && !resource->isLoad())
                resource->load();
            return resource;
        }
        //
        void load()
        {
            //load resources
            for (auto& itr : resMap)
                if (!itr.second.lock()->isLoad())
                    itr.second.lock()->load();

        }
        void unload(bool destroy = false)
        {
            //unload resources
            for (auto& it : resMap)
                if (it.second.lock()->isLoad())
                    it.second.lock()->unload();
            //destroy resources references
            if (destroy) resMap.clear();
        }
        //
        void erase(const String& objectname)
        {
            //find
            auto it = resMap.find(objectname);
            //if not find, return
            if (it == resMap.end()) return;
            //dt object
            it->second.lock()->
                Resource<T>::setReleaseCallBack([](Resource<T>* rs) {});
            //erase a resources reference
            resMap.erase(it);
        }
        //
        ResourcesGroup* getResourcesGroup()
        {
            return rsgr;
        }
        String& getPath()
        {
            return resPath.string();
        }

    private:
        Path resPath;
        //ptr resource group
        ResourcesGroup* rsgr = nullptr;
        //resources map
        UnorderedMap<String, WPtr<T>> resMap;
        //for only ResourcesGroup
        void __forceReload()
        {
            //load resources
            for (auto& itr : resMap)
                itr.second.lock()->load();
        }
    };
};

#endif
