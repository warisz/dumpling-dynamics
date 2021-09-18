from PyQt5 import QtCore, QtGui, QtWidgets
import serial

class Ui_DumplingBot9000(object):
    def setupUi(self, DumplingBot9000):
        self.ser = serial.Serial('/COM5', baudrate = 9600, timeout= 0.25)

        DumplingBot9000.setObjectName("DumplingBot9000")
        DumplingBot9000.resize(1086, 785)
        self.centralwidget = QtWidgets.QWidget(DumplingBot9000)
        self.centralwidget.setObjectName("centralwidget")
        self.DumpMeat = QtWidgets.QPushButton(self.centralwidget)
        self.DumpMeat.setGeometry(QtCore.QRect(70, 90, 191, 71))
        self.DumpMeat.setObjectName("DumpMeat")
        self.DumpMeat.clicked.connect(self.DumpMeatFunc)

        self.MeatCutter = QtWidgets.QPushButton(self.centralwidget)
        self.MeatCutter.setGeometry(QtCore.QRect(70, 210, 191, 81))
        self.MeatCutter.setObjectName("MeatCutter")
        self.MeatCutter.clicked.connect(self.MeatCutterFunc)

        self.MeatSpinner = QtWidgets.QPushButton(self.centralwidget)
        self.MeatSpinner.setGeometry(QtCore.QRect(70, 330, 191, 91))
        self.MeatSpinner.setObjectName("MeatSpinner")
        self.DumplingPresser = QtWidgets.QPushButton(self.centralwidget)
        self.DumplingPresser.setGeometry(QtCore.QRect(70, 460, 191, 81))
        self.DumplingPresser.setObjectName("DumplingPresser")
        self.label = QtWidgets.QLabel(self.centralwidget)

        self.label.setGeometry(QtCore.QRect(440, 360, 47, 14))
        self.label.setObjectName("label")

        DumplingBot9000.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(DumplingBot9000)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 1086, 22))
        self.menubar.setObjectName("menubar")
        DumplingBot9000.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(DumplingBot9000)
        self.statusbar.setObjectName("statusbar")
        DumplingBot9000.setStatusBar(self.statusbar)

        self.retranslateUi(DumplingBot9000)
        QtCore.QMetaObject.connectSlotsByName(DumplingBot9000)

    def DumpMeatFunc(self):
        self.ser.write("a".encode())
        print("a")
        self.label.setText("a")

    def MeatCutterFunc(self):
        self.ser.write("b".encode())
        print("b")
        self.label.setText("b")




    def retranslateUi(self, DumplingBot9000):
        _translate = QtCore.QCoreApplication.translate
        DumplingBot9000.setWindowTitle(_translate("DumplingBot9000", "MainWindow"))
        self.DumpMeat.setText(_translate("DumplingBot9000", "Dump Meat"))
        self.MeatCutter.setText(_translate("DumplingBot9000", "Meat Cutter"))
        self.MeatSpinner.setText(_translate("DumplingBot9000", "Meat Spinner"))
        self.DumplingPresser.setText(_translate("DumplingBot9000", "Dumpling Presser"))
        self.label.setText(_translate("DumplingBot9000", "TextLabel"))


if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    DumplingBot9000 = QtWidgets.QMainWindow()
    ui = Ui_DumplingBot9000()
    ui.setupUi(DumplingBot9000)
    DumplingBot9000.show()
    sys.exit(app.exec_())


