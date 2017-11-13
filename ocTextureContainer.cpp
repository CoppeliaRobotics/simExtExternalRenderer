#include "ocTextureContainer.h"

COcTextureContainer::COcTextureContainer()
{
}

COcTextureContainer::~COcTextureContainer()
{
    for (int i=0;i<int(_textures.size());i++)
        delete _textures[i];
}

void COcTextureContainer::decrementAllUsedCount()
{
    for (int i=0;i<int(_textures.size());i++)
        _textures[i]->decrementUsedCount();
}

void COcTextureContainer::removeAllUnused()
{
    for (int i=0;i<int(_textures.size());i++)
    {
        if (_textures[i]->getUsedCount()<=0)
        {
            delete _textures[i];
            _textures.erase(_textures.begin()+i);
            i--; // reprocess this position
        }
    }
}

COcTexture* COcTextureContainer::getFromId(int id)
{
    for (int i=0;i<int(_textures.size());i++)
    {
        if (_textures[i]->getId()==id)
            return(_textures[i]);
    }
    return(0);
}

void COcTextureContainer::add(COcTexture* texture)
{
    _textures.push_back(texture);
}
