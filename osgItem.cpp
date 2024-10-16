#include "osgItem.h"

#include <QSGRendererInterface>
#include <QQuickWindow>

#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>

OSGItem::OSGItem(QQuickItem *parent)
    : QQuickItem(parent)
{
    // Our item shows something so set the flag.
    setFlag(ItemHasContents);
    setAcceptedMouseButtons(Qt::MouseButton::AllButtons);
    QObject::connect(this, &OSGItem::sourceChanged, this, &OSGItem::setNode);
}

QSGNode *OSGItem::updatePaintNode(QSGNode *node, UpdatePaintNodeData *)
{
    QSGRenderNode *n = static_cast<QSGRenderNode *>(node);

    QSGRendererInterface *ri = window()->rendererInterface();
    if (!ri)
        return nullptr;

    if (!n)
    {
        mOSGRenderNode = new OSGRenderNode(this);
        mOSGRenderNode->setupOSG(x(), y(), width(), height(), 1);

        setNode(mSource);

        mOSGRenderNode->setCameraManipulator(new osgGA::TrackballManipulator);

        n = mOSGRenderNode;
    }
    static_cast<OSGRenderNode *>(n)->sync(this);

    if (!n)
        qWarning("QSGRendererInterface reports unknown graphics API %d", ri->graphicsApi());

    return n;
}

void OSGItem::keyPressEvent(QKeyEvent *event)
{
    if(mOSGRenderNode)
        mOSGRenderNode->keyPressEvent(event);
}

void OSGItem::keyReleaseEvent(QKeyEvent *event)
{
    if(mOSGRenderNode)
        mOSGRenderNode->keyReleaseEvent(event);
}

void OSGItem::mousePressEvent(QMouseEvent *event)
{
    if(mOSGRenderNode)
        mOSGRenderNode->mousePressEvent(event);
}

void OSGItem::mouseMoveEvent(QMouseEvent *event)
{
    if(mOSGRenderNode)
        mOSGRenderNode->mouseMoveEvent(event);
}

void OSGItem::mouseReleaseEvent(QMouseEvent *event)
{
    if(mOSGRenderNode)
        mOSGRenderNode->mouseReleaseEvent(event);
}

void OSGItem::mouseDoubleClickEvent(QMouseEvent *event)
{
    if(mOSGRenderNode)
        mOSGRenderNode->mouseDoubleClickEvent(event);
}
void OSGItem::wheelEvent(QWheelEvent *event)
{
    if(mOSGRenderNode)
        mOSGRenderNode->wheelEvent(event);
}

QUrl OSGItem::source() const
{
    return mSource;
}

void OSGItem::setSource(const QUrl &source)
{
    if(mSource != source)
    {
        mSource = source;
        emit sourceChanged(source);
    }
}

void OSGItem::setNode(const QUrl &source)
{
    if(mOSGRenderNode)
    {
        osg::ref_ptr<osg::Node> node = osgDB::readNodeFile(source.url(QUrl::PreferLocalFile).toStdString());

        osg::ref_ptr<osg::Group> group = new osg::Group;
        group->addChild(node);


        mOSGRenderNode->setSceneData(group);
    }
}
