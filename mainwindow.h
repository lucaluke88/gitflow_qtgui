#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QTreeView>
#include <QProcess>
#include <QTextEdit>
#include <stdio.h>
#include <iostream>
#include <exception>

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
        Q_OBJECT

    public:
        explicit MainWindow(QWidget *parent = 0);
        ~MainWindow();

    private slots:
        void on_pushButton_clicked();

        void on_featureCheck_toggled(bool checked);

        void on_hotFiCheck_toggled(bool checked);

        void on_startCheck_toggled(bool checked);

        void on_finishCheck_toggled(bool checked);

        void on_actionGit_project_root_path_triggered();

        void on_actionGit_branch_triggered();

        void on_actionGit_flow_init_triggered();

        void on_addCheck_2_toggled(bool checked);

        void on_commitCheck_2_toggled(bool checked);

        void on_pushCheck_toggled(bool checked);

        void on_execute2button_clicked();

        void on_executeCustomCommand_clicked();

    private:
        Ui::MainWindow *ui;
        QString chooseFolder();
        void executeCommand(QString command);
};

#endif // MAINWINDOW_H
