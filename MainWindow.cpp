#include "MainWindow.hpp"

#include "./ui_MainWindow.h"

#include <QDir>
#include <QFileDialog>
#include <QGridLayout>
#include <QPushButton>
#include <QTextLayout>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle(QApplication::applicationName() + " " +
                         QApplication::applicationVersion());

    centralWidget()->setLayout(new QGridLayout);

    const auto l = qobject_cast<QGridLayout *>(centralWidget()->layout());
    m_button     = new QPushButton("Reorder Directory");
    connect(m_button, &QPushButton::clicked, this, &MainWindow::selectDir);
    l->addWidget(m_button);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::selectDir()
{
    auto dir = QFileDialog::getExistingDirectory(
        this, tr("Open Directory"), "/home",
        QFileDialog::ShowDirsOnly | QFileDialog::DontResolveSymlinks);

    QDir d(dir);
    if (!d.isReadable()) {
        qWarning() << "directory " << dir << "is not readable";
        return;
    }

    scan(std::move(d));
}

void MainWindow::scan(QDir &&dir)
{
    auto files =
        dir.entryList(QDir::Filter::NoDotAndDotDot | QDir::Filter::Files);
    QVector<QString> vect;

    for (auto f : files) {
        const auto extension = f.right(3);
        if (!vect.contains(extension)) {
            vect.append(extension);
            if (!dir.mkdir(extension)) {
                qWarning() << "error creating directory";
                return;
            }
        }

        QFile file(dir.absolutePath() + "/" + f);
        if (!file.copy(dir.absolutePath() + "/" + extension + "/" + f)) {
            qWarning() << "error when copy";
            return;
        }

        file.remove();
    }
}
