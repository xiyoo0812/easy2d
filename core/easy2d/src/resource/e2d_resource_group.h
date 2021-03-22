#ifndef RESOURCESGROUP_H
#define RESOURCESGROUP_H

#include "e2d_config.h"
#include "e2d_resource_manager.h"
// resources object
// #include <Table.h>
// #include <Texture.h>
// #include <Mesh.h>
// #include <FrameSet.h>
// #include <Font.h>
// #include <Sound.h>
// #include <Script.h>
// #include <Shader.h>

namespace Easy2D
{
    class ResourcesGroup
    {
//         ResourcesManager<Font>* fonts;
//         ResourcesManager<Mesh>* meshes;
//         ResourcesManager<Sound>* sounds;
//         ResourcesManager<Shader>* shaders;
//         ResourcesManager<Texture>* textures;
//         ResourcesManager<FrameSet>* frameSets;

    public:
        template<typename T>
        ResourcesManager<T>& getManager()
        {
            return nullptr;
        }
    
    private:
        //is subscribe
        bool isSubscribed = false;
        //load a resource
        template<class RM>
        void loadAResource(const String& name, RM* object)
        {
            Path path = resPath;
            if (std::filesystem::exists(path.append(name)))
            {
                object = new RM(this, path);
            }
        }
        //
        void loadResourceFile();
        //resource group in map
        String name;
        Path resPath;
        void subscription(const String& name);
        void unsubscription();

    public:
        ResourcesGroup(const String& name, const Path& path);
        /**
         * Set the managers resources
         * @param path table resources
         */
        void addResourceFiles(const String& name, const Path& path);
        /**
        * delete resource goup
        */
        virtual ~ResourcesGroup();

        /*
        * void template
        */
        template<typename T> SPtr<T> load(const String& path)
        {
            return getManager<T>()->load(path);
        }
        template<typename T> SPtr<T> get(const String& path)
        {
            return getManager<T>()->get(path);
        }
        template<typename T> SPtr<T> find(const String& path)
        {
            return getManager<T>()->find(path);
        }
        template<typename T> String getResourceDirectory()
        {
            return getManager<T>()->getPath();
        }


        /** load all resources returned  */
        inline void load()
        {
//             textures.load();
//             meshes.load();
//             frameSets.load();
//             fonts.load();
//             sounds.load();
//             scripts.load();
//             shaders.load();
        }
        /** unload all resources returned  */
        inline void unload(bool destroy)
        {
//             textures.unload(destroy);
//             meshes.unload(destroy);
//             frameSets.unload(destroy);
//             fonts.unload(destroy);
//             sounds.unload(destroy);
//             scripts.unload(destroy);
//             shaders.unload(destroy);
        }
        /** directory of resources */
        String getResourcesDirectory()
        {
            return resPath.string();
        }
        /** reload only gpu resource */
        void reloadGpuResouce();
    };
//     template<>
//     inline ResourcesManager<Texture>& ResourcesGroup::getManager<Texture>()
//     {
//         return textures;
//     }
//     template<>
//     inline ResourcesManager<Mesh>& ResourcesGroup::getManager<Mesh>()
//     {
//         return meshes;
//     }
//     template<>
//     inline ResourcesManager<FrameSet>& ResourcesGroup::getManager<FrameSet>()
//     {
//         return frameSets;
//     }
//     template<>
//     inline ResourcesManager<Font>& ResourcesGroup::getManager<Font>()
//     {
//         return fonts;
//     }
//     template<>
//     inline ResourcesManager<Sound>& ResourcesGroup::getManager<Sound>()
//     {
//         return sounds;
//     }
//     template<>
//     inline ResourcesManager<Shader>& ResourcesGroup::getManager<Shader>()
//     {
//         return shaders;
//     }
};

#endif
