# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'final.ui'
#
# Created by: PyQt5 UI code generator 5.15.4
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 is
# run again.  Do not edit this file unless you know what you are doing.


from PyQt5 import QtCore, QtGui, QtWidgets


class Ui_b(object):
    def setupUi(self, b):
        b.setObjectName("b")
        b.resize(854, 649)
        self.centralwidget = QtWidgets.QWidget(b)
        self.centralwidget.setObjectName("centralwidget")
        self.title = QtWidgets.QLabel(self.centralwidget)
        self.title.setGeometry(QtCore.QRect(200, 90, 491, 41))
        font = QtGui.QFont()
        font.setFamily("Yu Gothic UI Light")
        font.setPointSize(25)
        font.setBold(True)
        font.setWeight(75)
        self.title.setFont(font)
        self.title.setObjectName("title")
        self.start = QtWidgets.QPushButton(self.centralwidget)
        self.start.setGeometry(QtCore.QRect(510, 300, 181, 51))
        font = QtGui.QFont()
        font.setFamily("Yu Gothic")
        font.setPointSize(12)
        self.start.setFont(font)
        self.start.setObjectName("start")
        self.pushButton = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton.setGeometry(QtCore.QRect(100, 250, 75, 23))
        self.pushButton.setObjectName("pushButton")
        self.label = QtWidgets.QLabel(self.centralwidget)
        self.label.setGeometry(QtCore.QRect(80, 210, 171, 16))
        self.label.setObjectName("label")
        self.pushButton_2 = QtWidgets.QPushButton(self.centralwidget)
        self.pushButton_2.setGeometry(QtCore.QRect(100, 300, 75, 23))
        self.pushButton_2.setObjectName("pushButton_2")
        self.c = QtWidgets.QPushButton(self.centralwidget)
        self.c.setGeometry(QtCore.QRect(100, 350, 75, 23))
        self.c.setObjectName("c")
        self.d = QtWidgets.QPushButton(self.centralwidget)
        self.d.setGeometry(QtCore.QRect(100, 400, 75, 23))
        self.d.setObjectName("d")
        b.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(b)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 854, 22))
        self.menubar.setObjectName("menubar")
        b.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(b)
        self.statusbar.setObjectName("statusbar")
        b.setStatusBar(self.statusbar)

        self.retranslateUi(b)
        QtCore.QMetaObject.connectSlotsByName(b)

    def retranslateUi(self, b):
        _translate = QtCore.QCoreApplication.translate
        b.setWindowTitle(_translate("b", "MainWindow"))
        self.title.setText(_translate("b", "Dumpling Bot 9000 Dashboard"))
        self.start.setText(_translate("b", "Start Dumplings"))
        self.pushButton.setText(_translate("b", "a"))
        self.label.setText(_translate("b", "Testing Buttons (Serial):"))
        self.pushButton_2.setText(_translate("b", "b"))
        self.c.setText(_translate("b", "c"))
        self.d.setText(_translate("b", "d"))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    b = QtWidgets.QMainWindow()
    ui = Ui_b()
    ui.setupUi(b)
    b.show()
    sys.exit(app.exec_())