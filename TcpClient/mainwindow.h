#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

class QTcpSocket;

namespace Ui
{
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    explicit MainWindow(QWidget *parent = nullptr);
    virtual ~MainWindow();
private slots:
    void on_connectToServerButton_clicked();
private:
    qint64 getTotalRam() const;

    Ui::MainWindow *ui;
    QTcpSocket *m_client;
};

#endif // MAINWINDOW_H
