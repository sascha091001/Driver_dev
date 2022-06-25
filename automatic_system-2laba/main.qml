import QtQuick 2.12
import QtQuick.Controls 2.5
import QtQuick.Layouts 1.12
import QtQuick.Controls.Material 2.3
import QtMultimedia 5.12
import QtQuick.Window 2.1
import Qt5Compat.GraphicalEffects

ApplicationWindow {
    width: 640
    height: 480
    visible: true

    signal read();

        property string nickname: "1234";
        property bool hideshow: false;
        property int deleteID;

        title: qsTr("Password Manager")

        SwipeView {
            id: swipeView
            anchors.fill: parent
            //currentIndex: tabBar.currentIndex

            Page {
                id: page1

                header: ToolBar{                                    //Хедер
                    height: 40

                    Image {                                         //Аватарка юзера
                        width: 36
                        height: 36
                        source: "Alex.jpg"
                        anchors.left: parent.left
                        anchors.leftMargin: 10
                        anchors.verticalCenter: parent.verticalCenter
                        layer.enabled: true
                        layer.effect: OpacityMask {
                            maskSource: mask
                        }
                    }

                    Rectangle {                                     //Закругление авы
                        id: mask
                        width: 36
                        height: 36
                        radius: 18
                        visible: false
                    }

                    Label {
                        x: 45
                        anchors.verticalCenter: parent.verticalCenter
                        opacity: 1
                        color: "white"
                        text: "Менеджер паролей"
                        font.pixelSize: 14
                        padding: 10
                    }

                    RoundButton{
                        id: print_data
                        visible: false

                        flat: true
                        anchors.right: add.left
                        //anchors.rightMargin: 10
                        anchors.verticalCenter: parent.verticalCenter

                        onClicked: {
                            // Функция добавления записи

                            manager.pdf("E:/qtproj/PasswordManager/passwords.pdf")
                        }

                        Image{
                            source: "print.png"
                            width: 34
                            height: 34
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter
                        }
                    }

                    RoundButton{
                        id: add
                        visible: false

                        flat: true
                        anchors.right: show.left
                        //anchors.rightMargin: 10
                        anchors.verticalCenter: parent.verticalCenter

                        onClicked: {
                            // Функция добавления записи

                            mainLayout.visible = false
                            scroll.visible = false

                            addLayout.visible = true
                        }

                        Image{
                            source: "add_site.png"
                            width: 34
                            height: 34
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter
                        }
                    }

                    RoundButton{
                        id: show

                        flat: true
                        anchors.right: parent.right
                        anchors.rightMargin: 10
                        anchors.verticalCenter: parent.verticalCenter

                        onClicked: {
                            login.text = ''
                            searchText.text = ''

                            scroll.visible = false
                            mainLayout.visible = true
                            nahuy.visible = false
                            add.visible = false
                            print_data.visible = false
                            addLayout.visible = false
                            dialogDelete.visible = false
                        }

                        Image{
                            source: "update.png"
                            width: 34
                            height: 34
                            anchors.horizontalCenter: parent.horizontalCenter
                            anchors.verticalCenter: parent.verticalCenter
                        }
                    }

                    background: Rectangle {
                            color: parent.down ? "#1e1e1e" :
                                    (parent.hovered ? "#1e1e1e" : "#1e1e1e")
                    }
                }

                GridLayout {
                    id: mainLayout
                    columns: 2

                    rowSpacing: 5
                    columnSpacing: 5

                    anchors.verticalCenter: parent.verticalCenter

                    anchors {
                        left: parent.left
                        right: parent.right
                    }

                    TextField {
                        id: login

                        echoMode: TextField.Password
                        leftPadding: 10

                        anchors.left: parent.left
                        anchors.right: parent.right

                        font.pixelSize: 16
                        color: "black"

                        placeholderText: "Введите PIN..."

                        anchors.leftMargin: parent.width / 3.5
                        anchors.rightMargin: parent.width / 3.5

                        background: Rectangle {
                            implicitWidth: parent.width
                            implicitHeight: 25
                            color: login.enabled ? "transparent" : "#1e1e1e"
                            border.color: login.enabled ? "#1e1e1e" : "transparent"
                        }
                    }

                    Button{
                        id: send

                        anchors.top: login.bottom
                        anchors.topMargin: 5
                        anchors.left: parent.left
                        anchors.right: parent.right

                        anchors.leftMargin: parent.width / 3.5
                        anchors.rightMargin: parent.width / 3.5

                        anchors.horizontalCenter: parent.horizontalCenter

                        contentItem: Text {
                            text: "Войти"
                            opacity: enabled ? 1.0 : 0.3
                            color: "white"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            elide: Text.ElideRight
                        }

                        background: Rectangle {
                            color: "#1e1e1e"
                            implicitHeight: 35
                        }

                        onClicked:{
                            if (login.text.length > 0 && login.text == nickname){
                                manager.readFile()

                              manager.encriptFile(111,)
                                manager.decriptFile(111, "D:/QT_PROJECT/Lab2/www_crypt.txt")

                                mainLayout.visible = false
                                scroll.visible = true
                                add.visible = true
                                print_data.visible = true
                            }
                            else{
                                mainLayout.visible = false
                                nahuy.visible = true
                            }
                        }
                    }
                }

                Rectangle{                                              //Прямоугольный блок
                    id: nahuy
                    visible: false

                    anchors.left: parent.left
                    anchors.right: parent.right
                    anchors.top: parent.top
                    anchors.bottom: parent.bottom

                    color: "#1e1e1e"
                    radius: 15
                    scale: 0.5

                    Text{
                        id: text
                        anchors.horizontalCenter: parent.horizontalCenter
                        anchors.verticalCenter: parent.verticalCenter
                        font.pixelSize: 36
                        color: "#ffffff"
                        text: "Введённый код неправильный!!!"
                    }
                }

                GridLayout {
                    id: dialogDelete
                    visible: false

                    rows: 2
                    columns: 2

                    rowSpacing: 5
                    columnSpacing: 5

                    anchors.verticalCenter: parent.verticalCenter

                    anchors {
                        left: parent.left
                        right: parent.right
                    }

                    Label {
                        id: agreementToDelete

                        Layout.row: 0
                        Layout.columnSpan: 2

                        anchors.left: parent.left
                        anchors.right: parent.right

                        font.pixelSize: 18
                        color: "black"

                        anchors.leftMargin: parent.width / 6
                        anchors.rightMargin: parent.width / 3.5

                        text: "Вы уверены, что хотите удалить данную запись?"
                    }

                    Button{
                        id: agree

                        anchors.top: agreementToDelete.bottom
                        anchors.topMargin: 5
                        anchors.left: parent.left
                        anchors.right: parent.right

                        anchors.leftMargin: parent.width / 3.5
                        anchors.rightMargin: parent.width / 3.5

                        anchors.horizontalCenter: parent.horizontalCenter

                        contentItem: Text {
                            text: "Удалить"
                            opacity: enabled ? 1.0 : 0.3
                            color: "white"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            elide: Text.ElideRight
                        }

                        background: Rectangle {
                            color: "#1e1e1e"
                            height: 30
                        }

                        onClicked:{
                            manager.deleteSite(deleteID)
                            scroll.visible = true
                            dialogDelete.visible = false
                        }
                    }

                    Button{
                        id: disagree

                        anchors.top: agree.bottom
                        anchors.topMargin: 5
                        anchors.left: parent.left
                        anchors.right: parent.right

                        anchors.leftMargin: parent.width / 3.5
                        anchors.rightMargin: parent.width / 3.5

                        anchors.horizontalCenter: parent.horizontalCenter

                        contentItem: Text {
                            text: "Отменить"
                            opacity: enabled ? 1.0 : 0.3
                            color: "white"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            elide: Text.ElideRight
                        }

                        background: Rectangle {
                            color: "#1e1e1e"
                            height: 30
                        }

                        onClicked:{
                            scroll.visible = true
                            dialogDelete.visible = false
                        }
                    }
                }

                ScrollView{
                    id: scroll
                    visible: false
                    anchors.fill: parent

                    Image{
                        id: background
                        width: parent.width
                        height: parent.height*2
                        sourceSize.width: -1
                        fillMode: Image.TileHorizontally
                    }

                    ColumnLayout{
                        anchors.top: parent.top
                        anchors.topMargin: 10
                        anchors.fill: parent
                        Layout.alignment: Qt.AlignHCenter

                        RowLayout{
                            Layout.alignment: Qt.AlignHCenter | Qt.AlignTop

                            TextField{
                                id: searchText

                                Layout.fillWidth: true
                                Layout.leftMargin: 25
                                //Layout.rightMargin: 25

                                placeholderText: "Введите URL..."
                            }

                            Button {
                                id: search

                                Layout.rightMargin: 25

                                contentItem: Text {
                                    text: "🔍"
                                    font.pixelSize: 18
                                    opacity: enabled ? 1.0 : 0.3
                                    horizontalAlignment: Text.AlignHCenter
                                    verticalAlignment: Text.AlignVCenter
                                }

                                background: Rectangle {
                                    implicitWidth: 100
                                    implicitHeight: 40
                                    color: "grey"
                                    border.color: "#1e1e1e"
                                    border.width: 1
                                    radius: 2
                                }

                                onClicked: {
                                    manager.readFile(searchText.text)
                                }
                            }
                        }

                        ListView{
                            id: list
                            visible: true
                            Layout.fillHeight: true
                            Layout.fillWidth: true
                            enabled: true
                            model: siteModel

                            spacing: 15

                            Layout.leftMargin: 25
                            Layout.rightMargin: 25

                            delegate: Rectangle{
                                id: childrenRect

                                color: "white"
                                width: parent.width
                                height: 150
                                border.color: "black"

                                radius: 15

                                GridLayout{
                                    anchors.fill: parent
                                    columns: 4
                                    rows: 3

                                    Image{
                                        id: img
                                        source: "logo.png"
                                        Layout.column: 0
                                        Layout.row: 0
                                        Layout.rowSpan: 3

                                        Layout.preferredHeight: 130
                                        Layout.preferredWidth: 130
                                        Layout.margins: 5
                                        fillMode: Image.PreserveAspectFit

                                        property bool rounded: true
                                        property bool adapt: true


                                    }

                                    Rectangle{
                                        id: lBorder
                                        Layout.row: 0
                                        Layout.column: 1
                                        Layout.rowSpan: 3

                                        Layout.topMargin: 20
                                        Layout.bottomMargin: 20
                                        Layout.leftMargin: 20

                                        anchors.left: img.right
                                        anchors.leftMargin: 25

                                        color: "#1e1e1e"
                                        width: 2
                                        Layout.fillHeight: true
                                    }

                                    RoundButton{
                                        id: deleteSite

                                        Layout.row: 0
                                        Layout.column: 3
                                        flat: true
                                        anchors.verticalCenter: parent.verticalCenter

                                        Image{
                                            source: "delete.png"
                                            width: 60
                                            height: 60

                                            anchors.horizontalCenter: parent.horizontalCenter
                                            anchors.verticalCenter: parent.verticalCenter
                                        }

                                        onClicked: {
                                            //manager.deleteSite(myID)
                                            deleteID = myID

                                            dialogDelete.visible = true
                                            scroll.visible = false
                                        }
                                    }

                                    RoundButton{
                                        id: showPasswd

                                        Layout.row: 0
                                        Layout.column: 3

                                        anchors.right: deleteSite.left
                                        anchors.rightMargin: 20

                                        flat: true
                                        anchors.verticalCenter: parent.verticalCenter

                                        Image{
                                            source: "eye.png"
                                            width: 70
                                            height: 55
                                            anchors.horizontalCenter: parent.horizontalCenter
                                            anchors.verticalCenter: parent.verticalCenter
                                        }

                                        onClicked: {
                                            if (siteLogin.visible == false && sitePasswd.visible == false){

                                                myLogin = manager.decriptParam("", myLogin);

                                                siteLogin.visible = true
                                                sitePasswd.visible = true

                                                sitePasswd.text = "Пароль: " + manager.decriptParam("", myPassword);
                                                siteLogin.text = "Логин: " + manager.decriptParam("", myLogin);

                                                siteLoginStars.visible = false
                                                sitePasswdStars.visible = false

                                                hideshow = true
                                            }
                                            else if (siteLogin.visible == true && sitePasswd.visible == true){
                                                siteLogin.visible = false
                                                sitePasswd.visible = false

                                                siteLoginStars.visible = true
                                                sitePasswdStars.visible = true

                                                hideshow = false
                                            }
                                        }
                                    }

                                    Label {
                                        color: "blue"
                                        text: "Домен. имя: " + myURL
                                        Layout.topMargin: 15
                                        Layout.column: 2
                                        Layout.row: 0
                                        Layout.fillHeight: true
                                        Layout.preferredWidth: 150

                                        font.family: "Helvetica"
                                        font.pointSize: 11

                                        anchors.left: lBorder.right
                                        anchors.leftMargin: 15
                                    }

                                    Label{
                                        id: siteLogin
                                        visible: false

                                        color: "blue"
                                        text: "Логин: " + myLogin
                                        Layout.column: 2
                                        Layout.row: 1
                                        Layout.fillHeight: true
                                        Layout.preferredWidth: 150

                                        font.family: "Helvetica"
                                        font.pointSize: 11

                                        anchors.left: lBorder.right
                                        anchors.leftMargin: 15
                                    }

                                    Label{
                                        id: sitePasswd
                                        visible: false

                                        color: "blue"
                                        text: "Пароль: " + myPassword
                                        Layout.column: 2
                                        Layout.row: 2
                                        Layout.fillHeight: true
                                        Layout.preferredWidth: 150

                                        font.family: "Helvetica"
                                        font.pointSize: 11

                                        anchors.left: lBorder.right
                                        anchors.leftMargin: 15
                                    }

                                    Label{
                                        id: siteLoginStars

                                        color: "blue"
                                        text: "Логин: ********"
                                        Layout.column: 2
                                        Layout.row: 1
                                        Layout.fillHeight: true
                                        Layout.preferredWidth: 150

                                        font.family: "Helvetica"
                                        font.pointSize: 11

                                        anchors.left: lBorder.right
                                        anchors.leftMargin: 15
                                    }

                                    Label{
                                        id: sitePasswdStars

                                        color: "blue"
                                        text: "Пароль: ********"
                                        Layout.column: 2
                                        Layout.row: 2
                                        Layout.fillHeight: true
                                        Layout.preferredWidth: 150

                                        font.family: "Helvetica"
                                        font.pointSize: 11

                                        anchors.left: lBorder.right
                                        anchors.leftMargin: 15
                                    }
                                }
                            }
                        }
                    }
                }

                GridLayout {
                    id: addLayout
                    visible: false

                    columns: 2

                    rowSpacing: 5
                    columnSpacing: 5

                    anchors.verticalCenter: parent.verticalCenter

                    anchors {
                        left: parent.left
                        right: parent.right
                    }

                    TextField {
                        id: newURL

                        leftPadding: 10

                        anchors.left: parent.left
                        anchors.right: parent.right

                        font.pixelSize: 18
                        color: "black"

                        placeholderText: "Введите URL сайта..."

                        anchors.leftMargin: parent.width / 4
                        anchors.rightMargin: parent.width / 4

                        background: Rectangle {
                            implicitWidth: parent.width
                            implicitHeight: 25
                            color: login.enabled ? "transparent" : "#1e1e1e"
                            border.color: login.enabled ? "#1e1e1e" : "transparent"
                        }
                    }

                    TextField {
                        id: newLogin

                        leftPadding: 10

                        anchors.top: newURL.bottom
                        anchors.topMargin: 5
                        anchors.left: parent.left
                        anchors.right: parent.right

                        font.pixelSize: 18
                        color: "black"

                        placeholderText: "Введите логин..."

                        anchors.leftMargin: parent.width / 4
                        anchors.rightMargin: parent.width / 4

                        background: Rectangle {
                            implicitWidth: parent.width
                            implicitHeight: 25
                            color: login.enabled ? "transparent" : "#1e1e1e"
                            border.color: login.enabled ? "#1e1e1e" : "transparent"
                        }
                    }

                    TextField {
                        id: newPassword

                        leftPadding: 10

                        echoMode: TextField.Password

                        anchors.top: newLogin.bottom
                        anchors.topMargin: 5
                        anchors.left: parent.left
                        anchors.right: parent.right

                        font.pixelSize: 18
                        color: "black"

                        placeholderText: "Введите пароль..."

                        anchors.leftMargin: parent.width / 4
                        anchors.rightMargin: parent.width / 4

                        background: Rectangle {
                            implicitWidth: parent.width
                            implicitHeight: 25
                            color: login.enabled ? "transparent" : "#1e1e1e"
                            border.color: login.enabled ? "#1e1e1e" : "transparent"
                        }
                    }

                    Button{
                        id: save

                        anchors.top: newPassword.bottom
                        anchors.topMargin: 5
                        anchors.left: parent.left
                        anchors.right: parent.right

                        anchors.leftMargin: parent.width / 4
                        anchors.rightMargin: parent.width / 4

                        anchors.horizontalCenter: parent.horizontalCenter

                        contentItem: Text {
                            text: "Сохранить запись"
                            opacity: enabled ? 1.0 : 0.3
                            color: "white"
                            horizontalAlignment: Text.AlignHCenter
                            verticalAlignment: Text.AlignVCenter
                            elide: Text.ElideRight
                        }

                        background: Rectangle {
                            color: "#1e1e1e"
                            height: 30
                        }

                        onClicked:{
                            //Добавление записи в модель

                            if (newURL.text.length > 0 && newLogin.text.length > 0 && newPassword.text.length > 0){
                                manager.addNewSite(newURL.text, newLogin.text, newPassword.text)

                                addLayout.visible = false
                                scroll.visible = true

                                newURL.text = ''
                                newLogin.text = ''
                                newPassword.text = ''
                            }
                        }
                    }
                }
            }
     }
}
