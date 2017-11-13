#ifndef OCMESH_H
#define OCMESH_H

#include <vector>
#include "7Vector.h"
#include "ocTexture.h"

class COcMesh
{
public:
    COcMesh(int id,float* vert,int vertL,int* ind,int indL,float* norm,int normL,float* tex,int texL,unsigned char* ed);
    ~COcMesh();

    void render(const C7Vector& tr,const float* colors,bool textured,float shadingAngle,bool translucid,float opacityFactor,bool backfaceCulling,bool repeatU,bool repeatV,bool interpolateColors,int applyMode,COcTexture* texture,bool visibleEdges);
    void decrementUsedCount();
    int getUsedCount();
    int getId();

protected:
    std::vector<float> _vertices;
    std::vector<int> _indices;
    std::vector<float> _normals;
    std::vector<float> _textureCoords;
    std::vector<float> _edges;
    int _usedCount;
    int _id;
};
#endif // OCMESH_H
