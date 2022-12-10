#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void sendMessageProducer(std::string message);

    void sendMessageConsumer(std::string message);

private slots:
    void on_addProducer_clicked();

    void on_stop_clicked();

    void on_addConsumer_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
