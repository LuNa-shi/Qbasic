#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QLineEdit>
#include "exp.h"
#include "tokenizer.h"
#include "parser.h"
#include "evalstate.h"
#include "statement.h"
#include "program.h"
#include <bits/stdc++.h>
QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_cmdLineEdit_editingFinished();

private:
    Ui::MainWindow *ui;
    Program program;
    Parser parser;
    

    void setUIForDebugMode();
    void setUIExitDebugMode();
    void clearAllCode();
};
#endif // MAINWINDOW_H
