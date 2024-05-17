#include "servermainwindow.h"
#include "ui_servermainwindow.h"
#include <QMessageBox>
#include <QScrollBar>
#include <QPushButton>
#include <QHBoxLayout>
#include <QLabel>

ServerMainWindow::ServerMainWindow(std::shared_ptr<Database> dbPtr, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::ServerMainWindow),
    m_dbPtr(dbPtr)
{
    ui->setupUi(this);

    updateUserList();

    qApp->setStyleSheet(
        "QMainWindow { background-color: #333; }"
        "QLabel { color: #fff; }"
        "QTextEdit, QListWidget { background-color: #666; color: #fff; }"
        "QPushButton { background-color: #555; color: #fff; border: none; padding: 5px; }"
        "QPushButton:hover { background-color: #777; }"
        );
}

ServerMainWindow::~ServerMainWindow()
{
    delete ui;
}

void ServerMainWindow::onDisconnectUserClicked(const QString& username)
{
    m_dbPtr->disconnectUser(username.toStdString());
    updateUserList();
}

void ServerMainWindow::onBanUserClicked(const QString& username)
{
    m_dbPtr->banUser(username.toStdString());
    updateUserList();
}

void ServerMainWindow::updateUserList() {
    ui->usersListWidget->clear();

    for (int i = 0; i < ui->usersListWidget->count(); ++i) {
        QListWidgetItem* item = ui->usersListWidget->item(i);
        QString username = item->text();  // Получите имя пользователя из элемента списка
        QWidget* widget = new QWidget;
        QHBoxLayout* layout = new QHBoxLayout;
        QLabel* label = new QLabel(username);
        QPushButton* disconnectButton = new QPushButton("Отключить");
        QPushButton* banButton = new QPushButton("Забанить");

        disconnectButton->setToolTip("Отключить этого пользователя");
        banButton->setToolTip("Забанить этого пользователя");

        connect(disconnectButton, &QPushButton::clicked, this, [this, username]() {
            onDisconnectUserClicked(username);
        });
        connect(banButton, &QPushButton::clicked, this, [this, username]() {
            onBanUserClicked(username);
        });

        layout->addWidget(label);
        layout->addWidget(disconnectButton);
        layout->addWidget(banButton);
        widget->setLayout(layout);

        item->setSizeHint(widget->sizeHint());
        ui->usersListWidget->setItemWidget(item, widget);
    }
}

void ServerMainWindow::addMessageToChat(const QString& message) {
    ui->messagesTextEdit->append(message);

    ui->messagesTextEdit->verticalScrollBar()->setValue(ui->messagesTextEdit->verticalScrollBar()->maximum());
}











