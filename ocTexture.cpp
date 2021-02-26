#include "simLib.h"
#include "ocTexture.h"
#include <qopengl.h>

#define TEXTURE_INIT_USED_COUNT 10

std::vector<unsigned int> COcTexture::_allTextureNames;
std::vector<bool> COcTexture::_allTextureNamesAv;

unsigned int COcTexture::_genTexture()
{
    unsigned int retVal=0;
    int bugFix1;
    simGetInt32Parameter(sim_intparam_bugfix1,&bugFix1);
    if (bugFix1>0)
    {
        static bool first=true;
        if (first)
        {
            first=false;
            _allTextureNames.resize(bugFix1);
            _allTextureNamesAv.resize(bugFix1,true);
            glGenTextures(bugFix1,&_allTextureNames[0]);
        }
        for (size_t i=0;i<bugFix1;i++)
        {
            if (_allTextureNamesAv[i])
            {
                _allTextureNamesAv[i]=false;
                retVal=_allTextureNames[i];
                break;
            }
        }
    }
    else
    {
        if (bugFix1==-1)
            glGenTextures(1,&retVal);
    }
    return(retVal);
}

void COcTexture::_delTexture(unsigned int t)
{
    int bugFix1;
    simGetInt32Parameter(sim_intparam_bugfix1,&bugFix1);
    if (bugFix1>0)
    {
        for (size_t i=0;i<bugFix1;i++)
        {
            if (_allTextureNames[i]==t)
            {
                _allTextureNamesAv[i]=true;
                break;
            }
        }
    }
    else
    {
        if (bugFix1==-1)
            glDeleteTextures(1,&t);
    }
}

COcTexture::COcTexture(int id,const unsigned char* textureBuff,int textureSizeX,int textureSizeY)
{
    _id=id;
    _textureSizeX=textureSizeX;
    _textureSizeY=textureSizeY;
    for (int i=0;i<4*textureSizeX*textureSizeY;i++)
        _textureBuff.push_back(textureBuff[i]);
    _textureName=_genTexture();
    _usedCount=TEXTURE_INIT_USED_COUNT;
}

COcTexture::~COcTexture()
{
    _delTexture(_textureName);
}

void COcTexture::decrementUsedCount()
{
    _usedCount--;
}

int COcTexture::getUsedCount()
{
    return(_usedCount);
}

int COcTexture::getId()
{
    return(_id);
}

void COcTexture::startTexture(bool repeatU,bool repeatV,bool interpolateColors,int applyMode)
{
    _usedCount=TEXTURE_INIT_USED_COUNT;

    glBindTexture(GL_TEXTURE_2D,_textureName);
    glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,_textureSizeX,_textureSizeY,0,GL_RGBA,GL_UNSIGNED_BYTE,&_textureBuff[0]);
    GLint colInt=GL_NEAREST;
    if (interpolateColors)
        colInt=GL_LINEAR;
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR); // keep to GL_LINEAR here!!
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,colInt);
    GLint repS=GL_CLAMP;
    if (repeatU)
        repS=GL_REPEAT;
    glTexParameteri (GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,repS);
    GLint repT=GL_CLAMP;
    if (repeatV)
        repT=GL_REPEAT;
    glTexParameteri (GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,repT);
    GLint dec=GL_MODULATE;
    if (applyMode==1)
        dec=GL_DECAL;
    if (applyMode==2)
        dec=GL_ADD;
    if (applyMode==3)
        dec=GL_BLEND;
    glTexEnvi (GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,dec);
    glEnable(GL_TEXTURE_2D);
    glBindTexture(GL_TEXTURE_2D,_textureName);
    glColor3f(1.0f,1.0f,1.0f);
}

void COcTexture::endTexture()
{
    glDisable(GL_TEXTURE_2D);
}

