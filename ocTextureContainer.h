#ifndef OCTEXTURECONTAINER_H
#define OCTEXTURECONTAINER_H

#include "ocTexture.h"
#include <vector>

class COcTextureContainer
{
public:
     COcTextureContainer();
    ~COcTextureContainer();

     COcTexture* getFromId(int id);
     void add(COcTexture* texture);
     void decrementAllUsedCount();
     void removeAllUnused();

protected:
     std::vector<COcTexture*> _textures;
};
#endif // OCTEXTURECONTAINER_H
