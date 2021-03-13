#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "manager.h"
#include "qcontainerwidget.h"
#include "qcontainerwidgetexam.h"
#include "dialognewcont.h"
#include "ui_mainwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    Ui::MainWindow* getUi();
    QWidget* getP();
    void setUpBtns();
    void clearWidgets(QLayout * layout);
    ~MainWindow();

public slots:
    void addCont();
    void delConts();
    void addNet();
    void delNets();
    void refresh();

protected:
    manager* uiMan;

private:
    Ui::MainWindow *ui;
    void popContList();
    void popNetList();
    QWidget* p;
};

#endif // MAINWINDOW_H
