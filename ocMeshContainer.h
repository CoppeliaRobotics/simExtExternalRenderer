#ifndef OCMESHCONTAINER_H
#define OCMESHCONTAINER_H

#include "ocMesh.h"

class COcMeshContainer
{
public:
    COcMeshContainer();
    ~COcMeshContainer();

    COcMesh* getFromId(int id);
    void add(COcMesh* mesh);
    void decrementAllUsedCount();
    void removeAllUnused();

protected:
    std::vector<COcMesh*> _meshes;
};
#endif // OCMESHCONTAINER_H
