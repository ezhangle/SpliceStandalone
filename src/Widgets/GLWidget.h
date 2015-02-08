#ifndef __GLWIDGET_H__
#define __GLWIDGET_H__

// #include <GL/glew.h>

#include <QtCore/QtCore>
#include <QtGui/QMouseEvent>
#include <QtGui/QMainWindow>
#include <QtGui/QImage>
#include <QtGui/QDialog>
#include <QtOpenGL/QGLWidget>
#include <QtCore/QTime>

#include <FabricSplice.h>
#include <FabricCore.h>

namespace FabricSplice
{
  class GLWidget;

  class GLThread : public QThread
  {
  public:

    GLThread( GLWidget *glWidget );
    void resizeViewport( QSize const &size );
    void run();

  private:

    GLWidget *m_glWidget;
  };

  class GLWidget : public QGLWidget
  {
  	Q_OBJECT

    friend class GLThread;

  public:

  	GLWidget(QGLFormat format, QWidget *parent = NULL);
  	virtual ~GLWidget();

  	FabricCore::RTVal getInlineViewport();
    bool manipulateCamera(QEvent *event);

    void resetRTVals();

    void enableRedraw(bool enable = true) { m_redrawEnabled = enable; }
    bool isRedrawEnabled() { return m_redrawEnabled; }
    float getTime() const;
    void setTime(float time);
    void setWireFrame(bool wireFrame);
    void toggleGrid();
    void toggleGLFullScreen(int screenIndex = -1);
    bool isGLFullScreen() { return m_fullScreenDialog != NULL; }
    
    /// returns the real frames per second of this TimeSlider
    double fps() const { return m_fps; }

  signals:

    void redrawn();

  protected:

    virtual void initializeGL();
    virtual void resizeGL(int w, int h);

    void paintFromGLThread();

    void paintEvent( QPaintEvent *e );
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent *event);

    GLThread m_glThread;

    FabricCore::RTVal m_drawing;
    FabricCore::RTVal m_camera;
    FabricCore::RTVal m_cameraManipulator;
    FabricCore::RTVal m_viewport;
    FabricCore::RTVal m_drawContext;
    FabricCore::RTVal m_timeRTVal;

    bool m_requiresInitialize;
    bool m_requiresResize;
    bool m_resizeEnabled;

    int volatile m_frame;

    QTime m_fpsTimer;
    double m_fps;
    double m_fpsStack[16];
    bool m_redrawEnabled;
    bool m_painting;
    unsigned int m_width;
    unsigned int m_height;

    QWidget * m_prevParent;
    QDialog * m_fullScreenDialog;

  };
};

#endif // __GLWIDGET_H__
