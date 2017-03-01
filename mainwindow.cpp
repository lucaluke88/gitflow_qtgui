#include "mainwindow.h"
#include "ui_mainwindow.h"


bool feature = false;
bool hotfix = false;
bool start = false;
bool finish = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QPixmap image("gitflow_model.png");
    ui->label_2->setPixmap(image);
    ui->label_2->update();
}

MainWindow::~MainWindow()
{
    delete ui;
}

// choose folder graphically
QString MainWindow::chooseFolder()
{
    try
    {
        QFileDialog *fd = new QFileDialog;
        QTreeView *tree = fd->findChild <QTreeView*>();
        tree->setRootIsDecorated(true);
        tree->setItemsExpandable(true);
        fd->setFileMode(QFileDialog::Directory);
        fd->setOption(QFileDialog::ShowDirsOnly);
        fd->setViewMode(QFileDialog::Detail);
        int result = fd->exec();
        QString directory;
        if (result)
        {
            directory = fd->selectedFiles()[0];
            return directory;
        }

        return QString("");
    }
    catch(std::exception e)
    {
        return QString::fromStdString("");
    }
}

// execute command
void MainWindow::on_pushButton_clicked()
{
    QString command("git flow ");

    if(feature)
        command += QString("feature ");
    else
        command += QString("hotfix ");

    if(start)
        command += QString("start ");
    else
        command += QString("finish ");

    command += ui->gitName->text();

    executeCommand(command);

}

void MainWindow::executeCommand(QString command)
{
    QProcess process;
    QString currentFolder = ui->currentFolderLine->text();

    process.setWorkingDirectory(currentFolder);

    //process.start(_command);
    process.start(command);
    process.waitForFinished(-1); // will wait forever until finished

    QString stdout = process.readAllStandardOutput();
    QString stderr = process.readAllStandardError();

    QString output = ui->output->toPlainText() + QString("\n");
    if(!stdout.isEmpty())
        ui->output->setText(output+stdout);
    if(!stderr.isEmpty())
        ui->output->setText(output+QString("ERROR: ")+stderr);
}

void MainWindow::on_featureCheck_toggled(bool checked)
{
    if(checked)
    {
        hotfix = false;
        ui->hotFiCheck->setChecked(false);
    }

    feature = checked;
    ui->featureCheck->setChecked(checked);

    ui->horizontalLayout->update();
}

void MainWindow::on_hotFiCheck_toggled(bool checked)
{
    if(checked)
    {
        feature = false;
        ui->featureCheck->setChecked(false);
    }

    hotfix = checked;
    ui->hotFiCheck->setChecked(hotfix);

    ui->horizontalLayout->update();
}

void MainWindow::on_startCheck_toggled(bool checked)
{
    if(checked)
    {
        finish = false;
        ui->finishCheck->setChecked(false);
    }

    start = checked;
    ui->startCheck->setChecked(checked);

    ui->horizontalLayout->update();
}

void MainWindow::on_finishCheck_toggled(bool checked)
{
    if(checked)
    {
        start = false;
        ui->startCheck->setChecked(false);
    }

    finish = checked;
    ui->finishCheck->setChecked(checked);

    ui->horizontalLayout->update();
}

// Choose git project root
void MainWindow::on_actionGit_project_root_path_triggered()
{
    QString folder = chooseFolder();
    ui->currentFolderLine->setText(folder);
    executeCommand(QString("ls -la"));
}

void MainWindow::on_actionGit_branch_triggered()
{
    executeCommand(QString("git branch"));
}

void MainWindow::on_actionGit_flow_init_triggered()
{
    executeCommand(QString("git flow init"));
}
