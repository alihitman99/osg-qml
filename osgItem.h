#ifndef OSGITEM_H
#define OSGITEM_H

#include <QQuickItem>
#include <QUrl>
#include "osgRenderNode.h"


class OSGItem: public QQuickItem
{
    Q_OBJECT

    Q_PROPERTY(QUrl source READ source WRITE setSource NOTIFY sourceChanged)
public:
    OSGItem(QQuickItem *parent = nullptr);
    QSGNode *updatePaintNode(QSGNode *node, UpdatePaintNodeData *) override;
    QUrl source() const;
public slots:
    void setSource(const QUrl &source);
    void setNode(const QUrl &source);
signals:
    void sourceChanged(const QUrl &source);

protected:
    virtual void keyPressEvent(QKeyEvent *event) override;
    virtual void keyReleaseEvent(QKeyEvent *event) override;
    virtual void mousePressEvent(QMouseEvent *event) override;
    virtual void mouseMoveEvent(QMouseEvent *event) override;
    virtual void mouseReleaseEvent(QMouseEvent *event) override;
    virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
    virtual void wheelEvent(QWheelEvent *event) override;
private:
    OSGRenderNode* mOSGRenderNode{nullptr};
    QUrl mSource;
};

#endif // OSGITEM_H
