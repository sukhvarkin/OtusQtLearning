#ifndef PROGRESWIDGET_H
#define PROGRESWIDGET_H

#include <QObject>
#include <QWidget>
#include <QPropertyAnimation>

class ProgresWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(int mProgress READ progress WRITE setProgress NOTIFY progressChanged)
public:
    explicit ProgresWidget(QWidget *parent = nullptr);

    int progress() const { return mProgress; }
    void setProgress(int progress) ;

signals:
    void progressChanged();

protected:
    void paintEvent(QPaintEvent *event);

private:
    QPixmap generatePixmap() const;
    QString key() const;

private:
    int mProgress;

    qreal mInnerRadius;
    qreal mOuterRadius;

    QColor mProgressColor;
    QColor mFinishedColor;
};

#endif // PROGRESWIDGET_H
