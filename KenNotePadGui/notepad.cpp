#include "notepad.h"
#include "ui_notepad.h"
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QTextStream>

NotePad::NotePad(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::NotePad)
{
    ui->setupUi(this);
}

NotePad::~NotePad()
{
    delete ui;
}

void NotePad::on_quitButton_clicked()
{
    qApp->quit();
}

void NotePad::on_actionOpen_triggered()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Open file"), QString(), tr("Text File ( *.txt);; C++ File ( *.cpp *.h);; All ()"));
    if (!fileName.isEmpty()){
        QFile file(fileName);
        if (!file.open(QIODevice::ReadOnly)){
            QMessageBox::critical(this, "Error", "Could not open file!");
            return;
        }
        QTextStream in(&file);
        ui->textEdit->setText(in.readAll());
        file.close();
    }
}

void NotePad::on_actionSave_triggered()
{
    QString fileName = QFileDialog::getSaveFileName(this, tr("Save file"), QString(), tr("Text File ( *.txt);; C++ File ( *.cpp *.h);; All ()"));
    if (!fileName.isEmpty()){
        QFile file(fileName);
        if (!file.open(QIODevice::WriteOnly)){
            QMessageBox::critical(this, "Error", "Could not save file!");
            return;
        }
        QTextStream out(&file);
        out << ui->textEdit->toPlainText();
        out.flush();
        file.close();
    }
}
