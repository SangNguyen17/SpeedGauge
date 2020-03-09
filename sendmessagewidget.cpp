#include "sendmessagewidget.h"
#include "ui_sendmessagewidget.h"

SendMessageWidget::SendMessageWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SendMessageWidget)
{
    ui->setupUi(this);
    ui->canPlugInsComboBox->addItems(QCanBus::instance()->plugins());
    ui->errorLabel->setVisible(false);
    ui->errorLabel->setStyleSheet("QLabel { color : red; }");

    // default device
    m_device = QCanBus::instance()->createDevice(QStringLiteral("virtualcan"), QStringLiteral("can0"));
    ui->receiveOwnComboBox->addItems(QStringList({"true", "false"}));
    ui->canFDComboBox->addItems(QStringList({"true", "false"}));
    m_device->connectDevice();
}

QCanBusDevice *SendMessageWidget::canBusDevice() const
{
    return m_device;
}

SendMessageWidget::~SendMessageWidget()
{
    delete ui;
}

void SendMessageWidget::on_send_clicked()
{
    QString frameIdText = ui->idTextEdit->toPlainText();
    QString messageText = ui->messageTextEdit->toPlainText();

    bool toUintOkId, toIntOkMsg;
    frameIdText.toUInt(&toUintOkId, 10);
    int speedToSend = messageText.toInt(&toIntOkMsg, 10);

    if (toIntOkMsg && (speedToSend > m_maxSpeed || speedToSend < m_minSpeed))
    {
        showErrorLabel("Minimum speed: 0, maximum speed: 280.");
        return;
    }

    if (toUintOkId && toIntOkMsg && speedToSend < 0)
    {
        showErrorLabel("Minimum speed: 0, maximum speed: 280.");
        return;
    }

    if (toUintOkId && toIntOkMsg)
    {
        ui->errorLabel->setVisible(false);
        QByteArray payload = messageText.toUtf8();
        uint frameId = frameIdText.toUInt();

        QCanBusFrame frame(frameId, payload);
        if (ui->errorRadio->isChecked())          frame.setFrameType(QCanBusFrame::FrameType::ErrorFrame);
        else if (ui->dataFrameRadio->isChecked()) frame.setFrameType(QCanBusFrame::FrameType::DataFrame);
        else                                      frame.setFrameType(QCanBusFrame::FrameType::RemoteRequestFrame);
        m_device->writeFrame(frame);

        emit sendButtonClicked();
    }
    else showErrorLabel("FrameId and Message must be integers.");
}


void SendMessageWidget::on_canPlugInsComboBox_currentTextChanged(const QString &arg1)
{
    ui->canInterfacesComboBox->clear();
    m_plugin = arg1;
    for (const QCanBusDeviceInfo& info: QCanBus::instance()->availableDevices(arg1))
    {
        ui->canInterfacesComboBox->addItem(info.name());
    }
}

void SendMessageWidget::on_receiveOwnComboBox_currentTextChanged(const QString &arg1)
{
    if (arg1 == "true") m_device->setConfigurationParameter(3, true);
    else                m_device->setConfigurationParameter(3, false);
}

void SendMessageWidget::on_canFDComboBox_currentTextChanged(const QString &arg1)
{
    if (arg1 == "true") m_device->setConfigurationParameter(5, true);
    else                m_device->setConfigurationParameter(5, false);
}

void SendMessageWidget::on_exitButon_clicked()
{
    this->close();
}

void SendMessageWidget::on_canInterfacesComboBox_currentTextChanged(const QString &arg1)
{
    m_interface = arg1;
}

void SendMessageWidget::showErrorLabel(const QString &text)
{
    ui->errorLabel->setText(text);
    ui->errorLabel->setVisible(true);
}
