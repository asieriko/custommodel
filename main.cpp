#include <QtGui/QApplication>
#include "mainwindow.h"

#include "exercisemodel.h"
#include "stringproxymodel.h"
#include <QTableView>
#include <QListView>
#include <QSplitter>



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    ExerciseModel model("A");
    QSplitter *splitter = new QSplitter;

    QTableView tableView(splitter);
    tableView.setModel(&model);
    tableView.sortByColumn(3);
    tableView.show();

    StringProxyModel spm(&model);
    spm.setSourceModel(&model);


    QListView listView(splitter);
    listView.setModel(&spm);
//    listView.setModelColumn(0);
    listView.show();

    splitter->setWindowTitle("Two views onto the same file system model");
         splitter->show();
//    MainWindow w;
//    w.show();

    return a.exec();
}
