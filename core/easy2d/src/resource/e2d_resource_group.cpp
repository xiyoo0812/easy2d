#include "e2d_resource_group.h"
//#include <Application.h>

using namespace Easy2D;

ResourcesGroup::ResourcesGroup(const String& rsname, const Path& path)
    :resPath(path), name(rsname)
{
    loadResourceFile();
    subscription(rsname);
}

void ResourcesGroup::subscription(const String& rgname)
{
    //save name
    name=rgname;
    //regist this resource group
    //Application::instance()->subscriptionResourcesGroup(name, this);
    //is subscribed
    isSubscribed=true;
}

void ResourcesGroup::unsubscription()
{
    //unregist this resource group
    //Application::instance()->unsubscriptionResourcesGroup(name);
}

void ResourcesGroup::loadResourceFile()
{
    //recall constructors
//     loadAResource("textures",textures);
//     loadAResource("meshes",meshes);
//     loadAResource("frameSets",frameSets);
//     loadAResource("fonts",fonts);
//     loadAResource("sounds",sounds);
//     loadAResource("scripts",scripts);
//     loadAResource("shaders",shaders);

}

void ResourcesGroup::addResourceFiles(const String& rsname, const Path& path)
{
    name = rsname;
    resPath = path;
    loadResourceFile();
    subscription(rsname);
}

ResourcesGroup::~ResourcesGroup()
{
    //unregist this resource group
    if(isSubscribed)
        unsubscription();
}

/** reload only gpu resource */
void ResourcesGroup::reloadGpuResouce()
{
//     textures.__forceReload();
//     meshes.__forceReload();
//     frameSets.__forceReload();
//     fonts.__forceReload();
//     shaders.__forceReload();
}
