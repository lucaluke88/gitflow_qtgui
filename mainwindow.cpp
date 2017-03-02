#include "mainwindow.h"
#include "ui_mainwindow.h"


bool feature = false;
bool hotfix = false;
bool start = false;
bool finish = false;

bool add = false;
bool commit = false;
bool push = false;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
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

    if(currentFolder.isEmpty())
    {
        currentFolder = QString("/home");
        ui->currentFolderLine->setText(currentFolder);
    }

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
    if(!stdout.isEmpty() || !stderr.isEmpty())
        ui->output->setText(output+QString("-------------------------------"));
    process.close();
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

void MainWindow::on_addCheck_2_toggled(bool checked)
{
    if(checked)
    {
        commit = false;
        push = false;
        ui->commitCheck_2->setChecked(false);
        ui->pushCheck->setChecked(false);
    }

    add = checked;
    ui->addCheck_2->setChecked(checked);

    ui->horizontalLayout->update();
}

void MainWindow::on_commitCheck_2_toggled(bool checked)
{
    if(checked)
    {
        add = false;
        push = false;
        ui->addCheck_2->setChecked(false);
        ui->pushCheck->setChecked(false);
    }

    commit = checked;
    ui->commitCheck_2->setChecked(checked);

    ui->horizontalLayout->update();
}

void MainWindow::on_pushCheck_toggled(bool checked)
{
    if(checked)
    {
        commit = false;
        add = false;
        ui->commitCheck_2->setChecked(false);
        ui->addCheck_2->setChecked(false);
    }

    push = checked;
    ui->pushCheck->setChecked(checked);

    ui->horizontalLayout->update();
}

void MainWindow::on_execute2button_clicked()
{
    QString command("git ");

    if(add)
        command += QString("add * ");
    else if(commit)
    {
        command += QString("commit -m ' ");
        command += ui->gitArgument->text();
        command += QString("' ");
    }
    else
        command += QString("push ");

    executeCommand(command);
}

void MainWindow::on_executeCustomCommand_clicked()
{
    executeCommand(ui->customCommandLabel->text());
}
