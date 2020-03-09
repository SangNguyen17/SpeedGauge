#include "qmlhandler.h"

QMLHandler::QMLHandler(QObject *parent) : QObject(parent), m_speed(0)
{
    m_messageWidget.setVisible(true);
    connect(&m_messageWidget, &SendMessageWidget::sendButtonClicked, this, &QMLHandler::readDataFrame);
}

const int &QMLHandler::speed() const
{
    return m_speed;
}

QMLHandler::~QMLHandler()
{

}

void QMLHandler::readDataFrame()
{
    QCanBusDevice* device = m_messageWidget.canBusDevice();
    if (device)
    {
        while (device->framesAvailable())
        {

            QCanBusFrame frame = device->readFrame();
            QString speedAsString = QString::fromUtf8(frame.payload());
            // cast Qstring to int here always success
            m_speed = speedAsString.toInt(nullptr, 10);
            emit speedChanged();
        }
    }
}
