#include "offscreenGlContext.h"

COffscreenGlContext::COffscreenGlContext(int resX,int resY) : QObject()
{
    _qOffscreenSurface=new QOffscreenSurface();
    QSurfaceFormat f;
    f.setSwapBehavior(QSurfaceFormat::SingleBuffer);
    f.setRenderableType(QSurfaceFormat::OpenGL);
    f.setRedBufferSize(8);
    f.setGreenBufferSize(8);
    f.setBlueBufferSize(8);
    f.setAlphaBufferSize(0);
    f.setStencilBufferSize(8);
    f.setDepthBufferSize(24);
    _qOffscreenSurface->setFormat(f);
    _qOffscreenSurface->create();
    if (_qOffscreenSurface->isValid())
    {
        _qContext=new QOpenGLContext();
        _qContext->setFormat(_qOffscreenSurface->format());
        _qContext->create();
    }

    makeCurrent();

    // Init GL:
    glClearDepth(1.0f);
    glDepthFunc(GL_LEQUAL); // Maybe useful with glPolygonOffset?
    glClearColor(0.0f,0.0f,0.0f,1.0f);
    glPolygonMode(GL_FRONT_AND_BACK,GL_FILL);
    glCullFace(GL_BACK);
    glDisable(GL_CULL_FACE);
    glBlendFunc(GL_ONE_MINUS_DST_COLOR,GL_ZERO);
    glLineStipple(1,3855);
    glPixelStorei(GL_PACK_ALIGNMENT,1);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DITHER);
    glEnable(GL_LIGHTING); // keep lighting on for everything, except for temporary operations.
    glShadeModel(GL_SMOOTH);
    glLightModeli(GL_LIGHT_MODEL_TWO_SIDE,1); // Important in order to have both sides affected by lights!
}

COffscreenGlContext::~COffscreenGlContext()
{
    delete _qContext;
    _qOffscreenSurface->destroy();
    delete _qOffscreenSurface;
}

bool COffscreenGlContext::makeCurrent()
{
    _qContext->makeCurrent(_qOffscreenSurface);
    return(true);
}

bool COffscreenGlContext::doneCurrent()
{
    _qContext->doneCurrent();
    return(true);
}

