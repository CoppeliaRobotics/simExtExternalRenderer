#ifndef OCTEXTURE_H
#define OCTEXTURE_H

#include <vector>

class COcTexture
{
public:
     COcTexture(int id,const unsigned char* textureBuff,int textureSizeX,int textureSizeY);
    ~COcTexture();

     void decrementUsedCount();
     int getUsedCount();
     int getId();

     void startTexture(bool repeatU,bool repeatV,bool interpolateColors,int applyMode);
     void endTexture();

protected:
     static unsigned int _genTexture();
     static void _delTexture(unsigned int t);
     static std::vector<unsigned int> _allTextureNames;
     static std::vector<bool> _allTextureNamesAv;

     std::vector<unsigned char> _textureBuff;
     int _textureSizeX;
     int _textureSizeY;
     unsigned int _textureName;

     int _usedCount;
     int _id;
};
#endif // OCTEXTURE_H
