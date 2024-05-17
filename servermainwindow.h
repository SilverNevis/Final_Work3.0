#ifndef SERVERMAINWINDOW_H
#define SERVERMAINWINDOW_H

#include <QMainWindow>
#include <QListWidgetItem>
#include <memory>
#include "Database.h"

namespace Ui {
class ServerMainWindow;
}

class ServerMainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit ServerMainWindow(std::shared_ptr<Database> dbPtr = nullptr, QWidget *parent = nullptr);
    ~ServerMainWindow();

public slots:
    void onDisconnectUserClicked(const QString& username);
    void onBanUserClicked(const QString& username);

private:
    Ui::ServerMainWindow *ui;
    std::shared_ptr<Database> m_dbPtr;
    void updateUserList();
    void addMessageToChat(const QString& message);
};

#endif // SERVERMAINWINDOW_H



