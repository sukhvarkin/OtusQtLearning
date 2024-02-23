#include "progreswidget.h"
#include <QPainter>
#include <QPixmapCache>
#include <QDebug>

static constexpr int MAXIMUM = 100;

ProgresWidget::ProgresWidget(QWidget *parent)
    : QWidget{parent},
      mProgress(0),
      mInnerRadius(0.6),
      mOuterRadius(1.0),
      mProgressColor(110,190,235),
      mFinishedColor(Qt::green)
{
}

void ProgresWidget::setProgress(int progress)
{
    if(mProgress == progress) {
        return;
    }

    mProgress = progress;
    update();
}

void ProgresWidget::paintEvent(QPaintEvent *event)
{
    QPixmap pixmap;
    if (!QPixmapCache::find(key(), &pixmap))
    {
        pixmap = generatePixmap();
        QPixmapCache::insert(key(), pixmap);
    }

    QPainter painter(this);
    painter.drawPixmap( 0.5 * ( width() - pixmap.width() ), 0.5 * ( height() - pixmap.height() ), pixmap );
}

QRectF squared(QRectF rect)
{
    if(rect.width() > rect.height())
    {
        qreal diff = rect.width() - rect.height();
        return rect.adjusted(diff/2, 0, -diff/2, 0);
    }
    else
    {
        qreal diff = rect.height() - rect.width();
        return rect.adjusted(0, diff/2, 0, -diff/2);
    }
}

QPixmap ProgresWidget::generatePixmap() const
{
    QPixmap pixmap(squared(rect()).size().toSize());
    pixmap.fill(QColor(0,0,0,0));
    QPainter painter(&pixmap);

    painter.setRenderHint(QPainter::Antialiasing, true);

    QRectF rect = pixmap.rect().adjusted(1,1,-1,-1);
    qreal margin = rect.width()*(1.0 - mOuterRadius)/2.0;
    rect.adjust(margin,margin,-margin,-margin);
    qreal innerRadius = mInnerRadius*rect.width()/2.0;

    //background grey circle
    painter.setBrush(QColor(225,225,225));
    painter.setPen(QColor(225,225,225));
    painter.drawPie(rect, 0, 360*16);

    const auto color = mProgress == 100 ? mFinishedColor : mProgressColor;
    painter.setBrush(color);
    painter.setPen(color);

    int value = qMin(mProgress, 100);
    int startAngle = 90 * 16;
    int spanAngle = -qreal(value) * 360 * 16 / 100;

    painter.drawPie(rect, startAngle, spanAngle);

    painter.setBrush(QColor(255,255,255));
    painter.setPen(QColor(0,0,0, 60));
    painter.drawEllipse(rect.center(), innerRadius, innerRadius);

    painter.drawArc(rect, 0, 360*16);
    painter.drawText(QRect(0, 0, width(), height()), Qt::AlignCenter, QString("%1%").arg(mProgress));

    return pixmap;
}

QString ProgresWidget::key() const
{
    return QString("%1,%2,%3,%4,%5,%6,%7")
            .arg(MAXIMUM)
            .arg(mInnerRadius)
            .arg(mOuterRadius)
            .arg(width())
            .arg(height())
            .arg(mProgress);
}

