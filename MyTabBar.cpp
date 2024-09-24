#include "MyTabBar.h"

#include <QApplication>
#include <QDebug>
#include <QMouseEvent>
#include <QPainter>

MyTabBar::MyTabBar(QWidget* parent)
    : QTabBar(parent)
{
    setAttribute(Qt::WA_StyledBackground);
    setMovable(true);
    setTabsClosable(true);
}

void MyTabBar::mousePressEvent(QMouseEvent* event)
{
    QTabBar::mousePressEvent(event);
    if (event->button() == Qt::LeftButton && currentIndex() >= 0) {

        theDragPress = true;
    }
}

void MyTabBar::mouseMoveEvent(QMouseEvent* event)
{
    QTabBar::mouseMoveEvent(event);

    if (theDragPress && event->buttons()) {

        if (!theDragOut && !contentsRect().contains(event->pos())) {
            theDragOut = true;
            emit beginDragOut(this->currentIndex());

            QMouseEvent* e = new QMouseEvent(QEvent::MouseButtonRelease,
                this->mapFromGlobal(QCursor::pos()),
                Qt::LeftButton,
                Qt::LeftButton,
                Qt::NoModifier);

            QApplication::postEvent(this, e);
        }
    }
}

void MyTabBar::mouseReleaseEvent(QMouseEvent* event)
{
    QTabBar::mouseReleaseEvent(event);
    theDragPress = false;
    theDragOut = false;
}
