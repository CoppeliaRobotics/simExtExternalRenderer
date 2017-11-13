#ifndef OPENGLBASE_H
#define OPENGLBASE_H

class COpenglBase
{
public:
    COpenglBase(int associatedObjectHandle);
    virtual ~COpenglBase();

    void clearBuffers(float viewAngle,float orthoViewSize,float nearClippingPlane,float farClippingPlane,bool perspectiveOperation,const float* backColor);
    int getAssociatedObjectHandle();
    virtual void initGL();
    virtual void makeContextCurrent();
    virtual void doneCurrentContext();

protected:
    void _frustumSpecial(float left,float right,float bottom,float top,float nearval,float farval);
    void _perspectiveSpecial(float fovy,float aspect,float zNear,float zFar);

    int _associatedObjectHandle;
    int _resX;
    int _resY;
};
#endif // OPENGLBASE_H
