#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QDir>
#include "wrapper.h"
#include <QComboBox>
#include <QMessageBox>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool initialize();
    Wrapper* pyW;
    void changeType();
private:
    Ui::MainWindow *ui;
    void change2New();
    void change2Update();
    void change2Delete();
    void updateOrDelete();
    void changeTestSuite();
    void changeTestCaseID();
    void Finished();
    QComboBox* testCaseID_cb;
    QLineEdit* testCaseID_line;
    QString createTestCaseID();
};
#endif // MAINWINDOW_H
