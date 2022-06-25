#include <QGuiApplication>
#include <QQmlApplicationEngine>
#include <QQmlContext>
#include <QNetworkReply>
#include <QApplication>
#include <QProcess>
#include <QMessageBox>
#include <Windows.h>
#include <atlstr.h>
#include "manager.h"
#include "sitemodel.h"

typedef unsigned long long QWORD;

int main(int argc, char *argv[])
{
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
#endif
    QApplication app(argc, argv);

    QQmlApplicationEngine engine;

        Manager manager;

        QQmlContext *context = engine.rootContext();

        context->setContextProperty("siteModel", manager.siteModel); //Перемещаемая модель, которой присваиваем имя
        context->setContextProperty("manager", &manager);

    const QUrl url(QStringLiteral("qrc:/main.qml"));
    QObject::connect(&engine, &QQmlApplicationEngine::objectCreated,
                     &app, [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl)
            QCoreApplication::exit(-1);
    }, Qt::QueuedConnection);
    engine.load(url);

    QProcess *satelite_process = new QProcess();
       int pid = QApplication::applicationPid();
       qDebug() << "pid: " << pid;

       QStringList arguments = {QString::number(pid)};
     //  qDebug() << "arguments: " << arguments;

       satelite_process->start("E:/qtproj/PasswordManager/DebugProtector1.exe", arguments);
    //   qDebug() << satelite_process->errorString();

       bool protector_started = satelite_process->waitForStarted(1000);
       qDebug() << "protector_started: " << protector_started;



    //патчинг
            QWORD moduleBase = (QWORD)GetModuleHandle(NULL);
            QWORD text_segment_start = moduleBase + 0x1000; // сегмент .text располагается с отступом 0x1000
            qDebug() << "text_segment_start = " << Qt::hex << text_segment_start;

    // Определить длину сегмента из заголовка
            PIMAGE_DOS_HEADER pIHD = reinterpret_cast<PIMAGE_DOS_HEADER>(moduleBase);
            PIMAGE_NT_HEADERS pINH = reinterpret_cast<PIMAGE_NT_HEADERS>(moduleBase + pIHD->e_lfanew);

            QWORD size_of_text = pINH->OptionalHeader.SizeOfCode;  // размер сегмента .text


            QByteArray text_segment_contents = QByteArray((char*)text_segment_start, size_of_text);// помещаем содержимое сегмента .text
            QByteArray current_hash = QCryptographicHash::hash(text_segment_contents, QCryptographicHash::Sha256);//получаем хэш сегмента .text
            QByteArray current_hash_base64 = current_hash.toBase64();//переводим в формат Base64

            const QByteArray hash0_base64 = QByteArray("oAiJ1NLta15w8WwxVm6Gw5CJNYyH5tqZYUD2YO10xrU=");//эталонный хэш

            //qDebug() << "text_segment_start = " << Qt::hex << text_segment_start;
            //qDebug() << "size_of_text = " << size_of_text;
            //qDebug() << "text_segment_contents = " << Qt::hex << text_segment_contents.first(100);
            qDebug() << "current_hash_base64 = " << current_hash_base64;
            bool checkresult = (current_hash_base64==hash0_base64);//проверка хэшей
            qDebug() << "checkresult = " << checkresult;


           if (!checkresult){
               QMessageBox msg;
               msg.setWindowTitle("Предупреждение");
               msg.setText("Внимание! Исходный код был модифицирован. Отказ в запуске.");
               msg.setStandardButtons(QMessageBox::Ok);
               msg.exec();
               satelite_process->kill();
               return -1;
           }

    return app.exec();
}
