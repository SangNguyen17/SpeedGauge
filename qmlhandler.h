#ifndef QMLHANDLER_H
#define QMLHANDLER_H

#include "sendmessagewidget.h"
#include <QWidget>
#include <QCanBusDevice>
#include <QCanBusFrame>
#include <QDebug>
#include <QDataStream>
/**
 * @brief The QMLHandler class: middle layer between SendMessageWidget and QML
 */
class QMLHandler : public QObject
{
    Q_OBJECT
    Q_PROPERTY(int speed READ speed NOTIFY speedChanged)

public:
    explicit QMLHandler(QObject *parent = nullptr);
    const int &speed() const;
    ~QMLHandler();
signals:
    void speedChanged();
private slots:
    void readDataFrame();
private:
    int m_speed;
    SendMessageWidget m_messageWidget;

};

#endif // QMLHANDLER_H
