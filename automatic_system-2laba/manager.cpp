#include "manager.h"

Manager::Manager(QObject *parent)
    : QObject{parent}
{
    siteModel = new SiteModel();
}

void Manager::readFile(QString text)
{
    if (siteModel->rowCount() > 0) {  // Чищу модель, чтобы не дублировались записи
        siteModel->clear();
    }
/*
 *
    QString val;
    QFile file;
    file.setFileName("E:/qtproj/PasswordManager/sites.json");
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    val = file.readAll();
    file.close();
*/
    QString val = decriptFile("", "E:/qtproj/PasswordManager/sites_begin_crypt.json");


    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject root = d.object();
    QJsonValue value = root.value(QString("sites"));
    QJsonArray array = value.toArray();

    QString regular = "*://*";

    if (text.length() > 0){
        if ((text == "http") || (text == "https")){
            regular = "*";
            regular.append(text);
            regular.append("://*");
        }
        else
        {
            regular = "*://";
            regular.append(text);
            regular.append("*");
        }
    }

    QString wildcard = QRegularExpression::wildcardToRegularExpression(regular);
    QRegularExpression rx(wildcard);


 qDebug() << "Махинации с маской" << wildcard;
    rx.setPattern(wildcard);

    qDebug() <<  "Созданная регулярка: " << rx;

    for(int i = 0; i < array.count(); i++){
        QJsonObject value = array.at(i).toObject();

        int id = value.value("id").toInt();
        QString url = value.value("url").toString();
        QString login = value.value("login").toString();
        QString password = value.value("password").toString();
        //qDebug() << rx.match(url);
        if (rx.match(url).hasMatch()){
            siteModel->addItem(SiteObject (id, url, login, password));
        }

    }
}

void Manager::addNewSite(QString url, QString login, QString password){

    QString val = decriptFile("", "E:/qtproj/PasswordManager/sites_begin_crypt.json");
    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject root = d.object();
    QJsonValue value = root.value(QString("sites"));
    QJsonArray array = value.toArray();

    //Бэкап
    makeBackUp(root);
    //Завершение бэкапа

    QJsonObject newSiteInfo;
    login = encriptParam("",login);
    password = encriptParam("",password);

    newSiteInfo.insert("id", array.count());
    newSiteInfo.insert("url", url);
    newSiteInfo.insert("login", login);
    newSiteInfo.insert("password", password);


    array.append(newSiteInfo);                                  // Добавляем объект текста в массив
    root["sites"] = array;

    QFile file("E:/qtproj/PasswordManager/sites_begin.json");  // Перезаписываем в файл со 2 слоем

    file.open(QIODevice::WriteOnly);
    file.write(QJsonDocument(root).toJson(QJsonDocument::Indented));
    file.close();

    encriptFile("","E:/qtproj/PasswordManager/sites_begin.json"); //Заново применяем 1 слой

    readFile(); //Переоткрываем
}

void Manager::deleteSite(int id){
    qDebug() << "ID: " << id;
    QString val = decriptFile("", "E:/qtproj/PasswordManager/sites_begin_crypt.json");
    QByteArray val1 = val.toUtf8();

    QJsonParseError error;
    QJsonDocument doc = QJsonDocument::fromJson(val1, &error);

    QJsonObject root = doc.object();
    QJsonValue value = root.value(QString("sites"));
    QJsonArray array = root.value("sites").toArray();

    //Бэкап
    makeBackUp(root);
    //Завершение бэкапа

    for (int i = 0; i < array.size(); i++){

        int thisElID = array.at(i).toObject()["id"].toInt();

        if (thisElID == id){
            array.removeAt(i);
        }
    }

    QJsonArray newArr;

    for (int i = 0; i < array.size(); i++){   //Убираю пробелы в id после удаления, чтобы были последовательно

        QJsonObject newSiteInfo;

        newSiteInfo.insert("id", i);
        newSiteInfo.insert("url", array.at(i).toObject()["url"]);
        newSiteInfo.insert("login", array.at(i).toObject()["login"]);
        newSiteInfo.insert("password", array.at(i).toObject()["password"]);

        newArr.append(newSiteInfo);
    }

    root["sites"] = newArr;

    QFile file("E:/qtproj/PasswordManager/sites_begin.json");  // Перезаписываем в файл со 2 слоем

    file.open(QIODevice::WriteOnly);
    file.write(QJsonDocument(root).toJson(QJsonDocument::Indented));
    file.close();

    encriptFile("","E:/qtproj/PasswordManager/sites_begin.json"); //Заново применяем 1 слой

    readFile(); //Переоткрываем
}

void Manager::makeBackUp(QJsonObject root){
    QString filename = "E:/qtproj/PasswordManager/QT_lab2_backups/backup_"
            + QDateTime::currentDateTime().toString("dd-MM-yyyy_HH-mm-ss")
            + ".json";
    QFile backUpFile;
    backUpFile.setFileName(filename);
    backUpFile.open(QIODevice::WriteOnly | QIODevice::Text);
    backUpFile.write(QJsonDocument(root).toJson(QJsonDocument::Indented));
    backUpFile.close();   // Закрываем файл
    encriptFile("",filename); //Заново применяем 1 слой

}

QString Manager::currDate(){
    QDate date = QDate::currentDate();
    return date.toString("dd.MM.yyyy");
}

void Manager::pdf(QString filename){
    QPdfWriter writer(filename);
    writer.setPageSize(QPageSize::A4);
    writer.setPageMargins(QMargins(30, 30, 30, 30));

    QPainter painter(&writer);
    painter.setPen(Qt::black);
    painter.setFont(QFont("Times", 14));

    QRect r = painter.viewport();

    QString citydate = "Москва, ";
    citydate += currDate();

    painter.drawText(r, Qt::AlignRight, citydate);
    QString sender = "Московский Политех. Парольный менеджер\n\n";

    //Получение файла
    QString val = decriptFile("", "E:/qtproj/PasswordManager/sites_begin_crypt.json"); // Беру файл и расшифровываю

    QJsonDocument d = QJsonDocument::fromJson(val.toUtf8());
    QJsonObject root = d.object();
    QJsonValue value = root.value(QString("sites"));
    QJsonArray array = value.toArray();

    //int id;
    QString url;
    QString login;
    QString password;


    for(int i = 0; i < array.count(); i++){
        QJsonObject value = array.at(i).toObject();

        url = value.value("url").toString();
        login = decriptParam("", value.value("login").toString());
        password = decriptParam("", value.value("password").toString());

        sender += "URL: " + url + '\n';
        sender += "Login: " + login + '\n';
        sender += "Password: " + password + "\n\n";
    }

    QImage image(700, 500, QImage::Format_ARGB32_Premultiplied);
    QPainter painter2(&image);
    painter2.fillRect(image.rect(), Qt::white);
    painter2.drawText(image.rect(), Qt::AlignVCenter, sender);
    //image.save("E:/qtproj/PasswordManager/passwords.png");

    //painter.drawText(r, Qt::AlignLeft, sender);
    painter.drawImage(QRect(1000, 0, 12000, 7500), image);

    painter.end();
}

bool Manager::encriptFile(const QString & mkey, const QString & in_file){

    EVP_CIPHER_CTX *ctx;
    ctx = EVP_CIPHER_CTX_new();

    if (mkey.length() == 32){
        m_iv = (unsigned char*) mkey.constData();

        EVP_EncryptInit_ex(ctx, EVP_aes_256_cfb(), NULL, reinterpret_cast<unsigned char *>(mkey.toUtf8().data()), m_iv); //шифр
    }
    else{
        const unsigned char PseudoKey2[] = "32101230123456789873874547898765";

        EVP_EncryptInit_ex(ctx, EVP_aes_256_cfb(), NULL, PseudoKey2, m_iv);
    }

    unsigned char ciphertext[256] = {0};
    unsigned char plaintexttext[256] = {0};
    int len = 0, plaintext_len = 256;
    memset(ciphertext, 0, 256);
    memset(plaintexttext, 0, 256);

    soursefile = in_file;
    QFile sourse_file(soursefile);
    sourse_file.open(QIODevice::ReadOnly);

    int position = soursefile.lastIndexOf(".");
    QString file_extension = soursefile.mid(position);
    QString soursefile_enc = soursefile.left(position) + "_crypt" + file_extension; //Для создания нового файла


    QFile file_modificate(soursefile_enc);
    file_modificate.open(QFile::ReadWrite | QFile::Truncate);
    plaintext_len = sourse_file.read((char *)plaintexttext, 256);


    QByteArray base64Cipher = "";

    while(plaintext_len > 0){
        if(!EVP_EncryptUpdate(ctx,
                              ciphertext, &len,
                              plaintexttext, plaintext_len))
        {
            return false;
        }

        base64Cipher += QByteArray((char *)ciphertext, len);

        //file_modificate.write((char *)ciphertext, len);
        plaintext_len = sourse_file.read((char *)plaintexttext, 256); //Считывание каждого блока по 256 символов и запись в файл
    }


    memset(ciphertext, 0, 256);
    if(!EVP_EncryptFinal_ex(ctx, ciphertext, &len))
    {
        return false;
    }

    base64Cipher += QByteArray((char *)ciphertext, len);

    file_modificate.write(base64Cipher, base64Cipher.size());
    EVP_CIPHER_CTX_free(ctx);

    //Закрытие файлов
    sourse_file.close();
    file_modificate.close();

    return true;
}

QString Manager::decriptFile(const QString & mkey, const QString & in_file){
    EVP_CIPHER_CTX *ctx;
    if(!(ctx = EVP_CIPHER_CTX_new())){
        return "false";
        qDebug() << "ERROR!!!!!!!!!!!1";
    }

    if (mkey.length() == 32){
        m_iv = (unsigned char*) mkey.data();

        if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cfb(), NULL, reinterpret_cast<unsigned char *>(mkey.toUtf8().data()), m_iv))
        {
            return "false";
            qDebug() << "ERROR!!!!!!!!!!!2";
        }
    }
    else{
        PseudoKey = "32101230123456789873874547898765";

        if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cfb(), NULL, reinterpret_cast<unsigned char *>(PseudoKey.toUtf8().data()), m_iv))
        {
            return "false";
            qDebug() << "ERROR!!!!!!!!!!!3";
        }
    }

    unsigned char ciphertext[256] = {0};
    unsigned char plaintexttext[256] = {0};
    int len = 0, plaintext_len = 0;
    QString struct_decrypted = "";

    soursefile = in_file;
    QFile sourse_file(soursefile);
    sourse_file.open(QIODevice::ReadOnly);

    plaintext_len = sourse_file.read((char *)plaintexttext, 256);

    while(plaintext_len > 0){
        if(1 != EVP_DecryptUpdate(ctx, ciphertext, &len, plaintexttext, plaintext_len))
        {
            return "false";
            qDebug() << "ERROR!!!!!!!!!!!4";
        }

        QByteArray cipher_once_qbyte = QByteArray(((char *) ciphertext), len);
                struct_decrypted += cipher_once_qbyte;

        plaintext_len = sourse_file.read((char *)plaintexttext, 256);

    }

    if(1 != EVP_DecryptFinal_ex(ctx, ciphertext + len, &len))
    {
        return "false";
        qDebug() << "ERROR!!!!!!!!!!!5";
    }

    EVP_CIPHER_CTX_free(ctx);

    sourse_file.close();
    qDebug() << "Struct decrypted: " << struct_decrypted;
    return struct_decrypted;
}

QString Manager::decriptParam(
        const QString & mkey,// ключ
        const QString &in_file // либо логин, либо пароль
)
{
    EVP_CIPHER_CTX *ctx;

    qDebug() << "Infile: " << in_file;

    if(!(ctx = EVP_CIPHER_CTX_new())){
        return "false";
        qDebug() << "ERROR!!!!!!!!!!!1";
    }

    if (mkey.length() == 32){
        m_iv = (unsigned char*) mkey.data();

        if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cfb(), NULL, reinterpret_cast<unsigned char *>(mkey.toUtf8().data()), m_iv))
        {
            return "false";
            qDebug() << "ERROR!!!!!!!!!!!2";
        }
    }
    else{
        //PseudoKey = "32101230123456789873874547898765";
        const unsigned char PseudoKey2[] = "32101230123456789873874547898765";

        if(1 != EVP_DecryptInit_ex(ctx, EVP_aes_256_cfb(), NULL, PseudoKey2, m_iv))
        {
            return "false";
            qDebug() << "ERROR!!!!!!!!!!!3";
        }
    }

    unsigned char ciphertext[256] = {0};
    unsigned char plaintexttext[256] = {0};
    int len = 0, plaintext_len = 256;

    memset(ciphertext, 0, 256);
    memset(plaintexttext, 0, 256);
    //soursefile = in_file; - Важно

    //QByteArray qb = QByteArray::fromBase64(soursefile.toUtf8());

    //qDebug() << "QString: " << soursefile; - Важно
    //qDebug() << "QString.toUtf8: " << soursefile.toUtf8(); - Важно
    //qDebug() << "FromBase64: " << qb;

    //plaintext_len = qb.size();
    //TODO
    QByteArray tmpArray = QByteArray::fromBase64(in_file.toUtf8());

    qDebug() << "tmpArray: " << tmpArray.size();

    memcpy(plaintexttext, tmpArray.data(), tmpArray.size());


    EVP_DecryptUpdate(ctx,
                              ciphertext, &len, // выходные
                              plaintexttext, plaintext_len);// входные


    QByteArray cipher_double_qbyte = QByteArray(((char *) ciphertext), tmpArray.size());
    //struct_decrypted += cipher_double_qbyte;

     //   plaintext_len = sourse_file.read((char *)plaintexttext, 256);



 //   qDebug() << "Decrypted: " << cipher_double_qbyte;

    return cipher_double_qbyte;
}

QString Manager::encriptParam(
        const QString & mkey,// ключ
        const QString &in_file // либо логин, либо пароль
)
{
    EVP_CIPHER_CTX *ctx;

    qDebug() << "Infile: " << in_file;
    if(!(ctx = EVP_CIPHER_CTX_new())){
        return "false";
        qDebug() << "ERROR!!!!!!!!!!!1";
    }

    if (mkey.length() == 32){
        m_iv = (unsigned char*) mkey.data();

        if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cfb(), NULL, reinterpret_cast<unsigned char *>(mkey.toUtf8().data()), m_iv))
        {
            return "false";
            qDebug() << "ERROR!!!!!!!!!!!2";
        }
    }
    else{
        //PseudoKey = "32101230123456789873874547898765";
        const unsigned char PseudoKey2[] = "32101230123456789873874547898765";

        if(1 != EVP_EncryptInit_ex(ctx, EVP_aes_256_cfb(), NULL, PseudoKey2, m_iv))
        {
            return "false";
            qDebug() << "ERROR!!!!!!!!!!!3";
        }
    }

    unsigned char ciphertext[256] = {0};
    unsigned char plaintexttext[256] = {0};
    int len = 0, plaintext_len = 256;

    memset(ciphertext, 0, 256);
    memset(plaintexttext, 0, 256);

    QByteArray tmpArray = in_file.toUtf8();

    memcpy(plaintexttext, tmpArray.data(), tmpArray.size());

    EVP_EncryptUpdate(ctx,
                              ciphertext, &len, // выходные
                              plaintexttext, plaintext_len);// входные


    QByteArray cipher_double_qbyte = QByteArray(((char *) ciphertext), tmpArray.size());
    qDebug() << "Crypted: " << cipher_double_qbyte;

    cipher_double_qbyte = cipher_double_qbyte.toBase64();


    qDebug() << "Crypted to base64: " << cipher_double_qbyte;

    return cipher_double_qbyte;
}




