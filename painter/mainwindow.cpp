#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include <QThread>

class WorkerThread : public QThread {
    Q_OBJECT

public:
    WorkerThread(QObject *parent = nullptr) : QThread(parent) {}

    void run() override {
        int progress = 0;

        while (progress < 100) {
            msleep(500);
            progress +=5;
            emit progressChanged(progress);
        }

        emit finished();
    }

signals:
    void progressChanged(int p);
    void finished();

};

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    connect(ui->pbStart, &QPushButton::clicked, this, &MainWindow::startDifficultFunction);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::startDifficultFunction()
{
    ui->pbStart->setDisabled(true);

   auto worker = new WorkerThread();

   connect(worker, &WorkerThread::finished, worker, [worker, this]() { worker->deleteLater(); ui->pbStart->setEnabled(true); });
   connect(worker, &WorkerThread::progressChanged, ui->wdProgresStatus, &ProgresWidget::setProgress);
   connect(this, &MainWindow::destroyed, worker, &QThread::terminate);

   worker->start();
}

#include "mainwindow.moc"
