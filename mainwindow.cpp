#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{

    ui->setupUi(this);
    setUIExitDebugMode();
    program = new Program();
    runtimeSatate = new RuntimeState();
    parser = new Parser();
    connect(ui->btnDebugMode, &QPushButton::clicked, this, &MainWindow::setUIForDebugMode);
    connect(ui->btnExitDebugMode, &QPushButton::clicked, this, &MainWindow::setUIExitDebugMode);
    connect(ui->btnClearCode, &QPushButton::clicked, this, &MainWindow::clearAllCode);
    connect(ui->cmdLineEdit, &QLineEdit::returnPressed, this, &MainWindow::on_cmdLineEdit_editingFinished);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_cmdLineEdit_editingFinished()
{
    QString cmd = ui->cmdLineEdit->text();
    ui->cmdLineEdit->setText("");
    //from Qstring to std::string
    std::string cmdStr = cmd.toStdString();
    Statement *stmt = parser->getStatement(cmdStr);

    if (stmt != nullptr)
    {
        program->appendStatement(stmt);
    }
    else
    {
        ui->textBrowser->append("Syntax Error: " + cmd);
    }
    auto code = program->toString();
    ui->CodeDisplay->clear();
    for (auto &line : code)
    {
        ui->CodeDisplay->append(QString::fromStdString(line));
    }

    // ui->treeDisplay->setText(QString::fromStdString(program.getSyntaxTree()));

    
}

void MainWindow::setUIForDebugMode(){
    ui->btnClearCode->setVisible(false);
    ui->btnLoadCode->setVisible(false);
    ui->btnDebugMode->setVisible(false);

    ui->btnExitDebugMode->setVisible(true);
    ui->btnDebugResume->setVisible(true);

    ui->labelSyntaxTree->setVisible(false);
    ui->treeDisplay->setVisible(false);

    ui->labelMonitor->setVisible(true);
    ui->monitorDisplay->setVisible(true);
    ui->labelBreakPoints->setVisible(true);
    ui->breakPointsDisplay->setVisible(true);
}

void MainWindow::setUIExitDebugMode(){
    ui->btnClearCode->setVisible(true);
    ui->btnLoadCode->setVisible(true);
    ui->btnDebugMode->setVisible(true);

    ui->btnExitDebugMode->setVisible(false);
    ui->btnDebugResume->setVisible(false);

    ui->labelSyntaxTree->setVisible(true);
    ui->treeDisplay->setVisible(true);

    ui->labelMonitor->setVisible(false);
    ui->monitorDisplay->setVisible(false);
    ui->labelBreakPoints->setVisible(false);
    ui->breakPointsDisplay->setVisible(false);
}

void MainWindow::clearAllCode(){
    ui->CodeDisplay->clear();
    ui->cmdLineEdit->clear();
    ui->monitorDisplay->clear();
    ui->breakPointsDisplay->clear();
    ui->treeDisplay->clear();
    ui->textBrowser->clear();

}
