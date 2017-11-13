#include "ocMeshContainer.h"

COcMeshContainer::COcMeshContainer()
{
}

COcMeshContainer::~COcMeshContainer()
{
    for (int i=0;i<int(_meshes.size());i++)
        delete _meshes[i];
}

void COcMeshContainer::decrementAllUsedCount()
{
    for (int i=0;i<int(_meshes.size());i++)
        _meshes[i]->decrementUsedCount();
}

void COcMeshContainer::removeAllUnused()
{
    for (int i=0;i<int(_meshes.size());i++)
    {
        if (_meshes[i]->getUsedCount()<=0)
        {
            delete _meshes[i];
            _meshes.erase(_meshes.begin()+i);
            i--; // reprocess this position
        }
    }
}

COcMesh* COcMeshContainer::getFromId(int id)
{
    for (int i=0;i<int(_meshes.size());i++)
    {
        if (_meshes[i]->getId()==id)
            return(_meshes[i]);
    }
    return(0);
}

void COcMeshContainer::add(COcMesh* mesh)
{
    _meshes.push_back(mesh);
}
