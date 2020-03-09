#ifndef SENDMESSAGEWIDGET_H
#define SENDMESSAGEWIDGET_H

#include <QWidget>
#include <QCanBus>
#include <QCanBusDevice>
#include <QCanBusFrame>
#include <QDebug>
#include <QCanBusDeviceInfo>
namespace Ui {
class SendMessageWidget;
}

/**
 * @brief The SendMessageWidget class: handles view to configure FrameType, Interface or Plugin and send messages...
 */
class SendMessageWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SendMessageWidget(QWidget *parent = nullptr);
    QCanBusDevice *canBusDevice() const;
    ~SendMessageWidget();
signals:
    void speedOnSliderChanged(int value);
    void sendButtonClicked();
private slots:
    void on_send_clicked();

    void on_canPlugInsComboBox_currentTextChanged(const QString &arg1);

    void on_receiveOwnComboBox_currentTextChanged(const QString &arg1);

    void on_canFDComboBox_currentTextChanged(const QString &arg1);

    void on_exitButon_clicked();

    void on_canInterfacesComboBox_currentTextChanged(const QString &arg1);

private:
    void showErrorLabel(const QString& text);


    Ui::SendMessageWidget *ui;
    const int m_maxSpeed = 280;
    const int m_minSpeed = 0;
    QString m_plugin = "";
    QString m_interface = "";
    QCanBusDevice* m_device = nullptr;
};

#endif // SENDMESSAGEWIDGET_H
