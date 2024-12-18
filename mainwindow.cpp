#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    connect(ui->action_5, &QAction::triggered, this, &MainWindow::saveToFile);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::saveToFile()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("存檔"), "", tr("Text Files (*.txt);;All Files (*)"));

    if (fileName.isEmpty()) {
        return;
    }

    QFile file(fileName);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::warning(this, tr("錯誤"), tr("無法打開檔案: %1").arg(file.errorString()));
        return;
    }

    QTextStream out(&file);
    out << ui->textEdit->toPlainText();
    file.close();

    QMessageBox::information(this, tr("成功"), tr("檔案儲存成功!"));
}
