import sys
from PyQt4 import QtCore, QtGui
from PyQt4.QtCore import Qt
import core

try:
    _fromUtf8 = QtCore.QString.fromUtf8
except AttributeError:
    def _fromUtf8(s):
        return s

try:
    _encoding = QtGui.QApplication.UnicodeUTF8
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig, _encoding)
except AttributeError:
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig)

class Ui_Dialog(object):
    def setupUi(self, Dialog):
        self.Dialog=Dialog
        Dialog.setObjectName(_fromUtf8("Dialog"))
        Dialog.resize(333, 306)
        Dialog.setMinimumSize(QtCore.QSize(333, 306))
        Dialog.setMaximumSize(QtCore.QSize(333, 306))
        Dialog.setStyleSheet(_fromUtf8("background-color: rgb(98, 95, 93);"))
        self.pushButton = QtGui.QPushButton(Dialog)
        self.pushButton.setGeometry(QtCore.QRect(10, 260, 72, 34))
        self.pushButton.setStyleSheet(_fromUtf8("QPushButton {\n"
"color: white;\n"
"border-width: 1px;\n"
"border-color: #339;\n"
"border-style: solid;\n"
"border-radius: 7;\n"
"padding: 3px;\n"
"font-size: 14px;\n"
"padding-left: 5px;\n"
"padding-right: 5px;\n"
"min-width: 60px;\n"
"max-width: 60px;\n"
"min-height: 26px;\n"
"max-height: 26px;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: rgb(75, 75, 75);\n"
"    border-style: inset;\n"
"}"))
        self.pushButton.setObjectName(_fromUtf8("pushButton"))
        self.pushButton.clicked.connect(lambda: core.Switch(self))
        self.pushButton_2 = QtGui.QPushButton(Dialog)
        self.pushButton_2.setGeometry(QtCore.QRect(90, 260, 72, 34))
        self.pushButton_2.setStyleSheet(_fromUtf8("QPushButton {\n"
"color: white;\n"
"background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #88d, stop: 0.1 #99e, stop: 0.49 #77c, stop: 0.5 #66b, stop: 1 #77c);\n"
"border-width: 1px;\n"
"border-color: #339;\n"
"border-style: solid;\n"
"border-radius: 7;\n"
"padding: 3px;\n"
"font-size: 14px;\n"
"padding-left: 5px;\n"
"padding-right: 5px;\n"
"min-width: 60px;\n"
"max-width: 60px;\n"
"min-height: 26px;\n"
"max-height: 26px;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: rgb(75, 75, 75);\n"
"    border-style: inset;\n"
"}"))
        self.pushButton_2.setObjectName(_fromUtf8("pushButton_2"))
        self.pushButton_3 = QtGui.QPushButton(Dialog)
        self.pushButton_3.setGeometry(QtCore.QRect(170, 260, 72, 34))
        self.pushButton_3.setStyleSheet(_fromUtf8("QPushButton {\n"
"color: white;\n"
"border-width: 1px;\n"
"border-color: #339;\n"
"border-style: solid;\n"
"border-radius: 7;\n"
"padding: 3px;\n"
"font-size: 14px;\n"
"padding-left: 5px;\n"
"padding-right: 5px;\n"
"min-width: 60px;\n"
"max-width: 60px;\n"
"min-height: 26px;\n"
"max-height: 26px;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: rgb(75, 75, 75);\n"
"    border-style: inset;\n"
"}"))
        self.pushButton_3.setObjectName(_fromUtf8("pushButton_3"))
        self.pushButton_3.clicked.connect(lambda: core.pointClicked(self))
        self.pushButton_4 = QtGui.QPushButton(Dialog)
        self.pushButton_4.setGeometry(QtCore.QRect(250, 260, 72, 34))
        self.pushButton_4.setStyleSheet(_fromUtf8("QPushButton {\n"
"color: white;\n"
"border-width: 1px;\n"
"border-color: #339;\n"
"border-style: solid;\n"
"border-radius: 7;\n"
"padding: 3px;\n"
"font-size: 14px;\n"
"padding-left: 5px;\n"
"padding-right: 5px;\n"
"min-width: 60px;\n"
"max-width: 60px;\n"
"min-height: 26px;\n"
"max-height: 26px;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: rgb(75, 75, 75);\n"
"    border-style: inset;\n"
"}"))
        self.pushButton_4.setObjectName(_fromUtf8("pushButton_4"))
        self.pushButton_5 = QtGui.QPushButton(Dialog)
        self.pushButton_5.setGeometry(QtCore.QRect(10, 210, 72, 34))
        self.pushButton_5.setStyleSheet(_fromUtf8("QPushButton {\n"
"color: white;\n"
"background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #88d, stop: 0.1 #99e, stop: 0.49 #77c, stop: 0.5 #66b, stop: 1 #77c);\n"
"border-width: 1px;\n"
"border-color: #339;\n"
"border-style: solid;\n"
"border-radius: 7;\n"
"padding: 3px;\n"
"font-size: 14px;\n"
"padding-left: 5px;\n"
"padding-right: 5px;\n"
"min-width: 60px;\n"
"max-width: 60px;\n"
"min-height: 26px;\n"
"max-height: 26px;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: rgb(75, 75, 75);\n"
"    border-style: inset;\n"
"}"))
        self.pushButton_5.setObjectName(_fromUtf8("pushButton_5"))
        self.pushButton_6 = QtGui.QPushButton(Dialog)
        self.pushButton_6.setGeometry(QtCore.QRect(90, 210, 72, 34))
        self.pushButton_6.setStyleSheet(_fromUtf8("QPushButton {\n"
"color: white;\n"
"background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #88d, stop: 0.1 #99e, stop: 0.49 #77c, stop: 0.5 #66b, stop: 1 #77c);\n"
"border-width: 1px;\n"
"border-color: #339;\n"
"border-style: solid;\n"
"border-radius: 7;\n"
"padding: 3px;\n"
"font-size: 14px;\n"
"padding-left: 5px;\n"
"padding-right: 5px;\n"
"min-width: 60px;\n"
"max-width: 60px;\n"
"min-height: 26px;\n"
"max-height: 26px;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: rgb(75, 75, 75);\n"
"    border-style: inset;\n"
"}"))
        self.pushButton_6.setObjectName(_fromUtf8("pushButton_6"))
        self.pushButton_7 = QtGui.QPushButton(Dialog)
        self.pushButton_7.setGeometry(QtCore.QRect(170, 210, 72, 34))
        self.pushButton_7.setStyleSheet(_fromUtf8("QPushButton {\n"
"color: white;\n"
"background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #88d, stop: 0.1 #99e, stop: 0.49 #77c, stop: 0.5 #66b, stop: 1 #77c);\n"
"border-width: 1px;\n"
"border-color: #339;\n"
"border-style: solid;\n"
"border-radius: 7;\n"
"padding: 3px;\n"
"font-size: 14px;\n"
"padding-left: 5px;\n"
"padding-right: 5px;\n"
"min-width: 60px;\n"
"max-width: 60px;\n"
"min-height: 26px;\n"
"max-height: 26px;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: rgb(75, 75, 75);\n"
"    border-style: inset;\n"
"}"))
        self.pushButton_7.setObjectName(_fromUtf8("pushButton_7"))
        self.pushButton_8 = QtGui.QPushButton(Dialog)
        self.pushButton_8.setGeometry(QtCore.QRect(250, 210, 72, 34))
        self.pushButton_8.setStyleSheet(_fromUtf8("QPushButton {\n"
"color: white;\n"
"border-width: 1px;\n"
"border-color: #339;\n"
"border-style: solid;\n"
"border-radius: 7;\n"
"padding: 3px;\n"
"font-size: 14px;\n"
"padding-left: 5px;\n"
"padding-right: 5px;\n"
"min-width: 60px;\n"
"max-width: 60px;\n"
"min-height: 26px;\n"
"max-height: 26px;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: rgb(75, 75, 75);\n"
"    border-style: inset;\n"
"}"))
        self.pushButton_8.setObjectName(_fromUtf8("pushButton_8"))
        self.pushButton_9 = QtGui.QPushButton(Dialog)
        self.pushButton_9.setGeometry(QtCore.QRect(10, 160, 72, 34))
        self.pushButton_9.setStyleSheet(_fromUtf8("QPushButton {\n"
"color: white;\n"
"background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #88d, stop: 0.1 #99e, stop: 0.49 #77c, stop: 0.5 #66b, stop: 1 #77c);\n"
"border-width: 1px;\n"
"border-color: #339;\n"
"border-style: solid;\n"
"border-radius: 7;\n"
"padding: 3px;\n"
"font-size: 14px;\n"
"padding-left: 5px;\n"
"padding-right: 5px;\n"
"min-width: 60px;\n"
"max-width: 60px;\n"
"min-height: 26px;\n"
"max-height: 26px;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: rgb(75, 75, 75);\n"
"    border-style: inset;\n"
"}"))
        self.pushButton_9.setObjectName(_fromUtf8("pushButton_9"))
        self.pushButton_10 = QtGui.QPushButton(Dialog)
        self.pushButton_10.setGeometry(QtCore.QRect(90, 160, 72, 34))
        self.pushButton_10.setStyleSheet(_fromUtf8("QPushButton {\n"
"color: white;\n"
"background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #88d, stop: 0.1 #99e, stop: 0.49 #77c, stop: 0.5 #66b, stop: 1 #77c);\n"
"border-width: 1px;\n"
"border-color: #339;\n"
"border-style: solid;\n"
"border-radius: 7;\n"
"padding: 3px;\n"
"font-size: 14px;\n"
"padding-left: 5px;\n"
"padding-right: 5px;\n"
"min-width: 60px;\n"
"max-width: 60px;\n"
"min-height: 26px;\n"
"max-height: 26px;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: rgb(75, 75, 75);\n"
"    border-style: inset;\n"
"}"))
        self.pushButton_10.setObjectName(_fromUtf8("pushButton_10"))
        self.pushButton_11 = QtGui.QPushButton(Dialog)
        self.pushButton_11.setGeometry(QtCore.QRect(170, 160, 72, 34))
        self.pushButton_11.setStyleSheet(_fromUtf8("QPushButton {\n"
"color: white;\n"
"background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #88d, stop: 0.1 #99e, stop: 0.49 #77c, stop: 0.5 #66b, stop: 1 #77c);\n"
"border-width: 1px;\n"
"border-color: #339;\n"
"border-style: solid;\n"
"border-radius: 7;\n"
"padding: 3px;\n"
"font-size: 14px;\n"
"padding-left: 5px;\n"
"padding-right: 5px;\n"
"min-width: 60px;\n"
"max-width: 60px;\n"
"min-height: 26px;\n"
"max-height: 26px;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: rgb(75, 75, 75);\n"
"    border-style: inset;\n"
"}"))
        self.pushButton_11.setObjectName(_fromUtf8("pushButton_11"))
        self.pushButton_12 = QtGui.QPushButton(Dialog)
        self.pushButton_12.setGeometry(QtCore.QRect(250, 160, 72, 34))
        self.pushButton_12.setStyleSheet(_fromUtf8("QPushButton {\n"
"color: white;\n"
"border-width: 1px;\n"
"border-color: #339;\n"
"border-style: solid;\n"
"border-radius: 7;\n"
"padding: 3px;\n"
"font-size: 14px;\n"
"padding-left: 5px;\n"
"padding-right: 5px;\n"
"min-width: 60px;\n"
"max-width: 60px;\n"
"min-height: 26px;\n"
"max-height: 26px;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: rgb(75, 75, 75);\n"
"    border-style: inset;\n"
"}"))
        self.pushButton_12.setObjectName(_fromUtf8("pushButton_12"))
        self.pushButton_13 = QtGui.QPushButton(Dialog)
        self.pushButton_13.setGeometry(QtCore.QRect(10, 110, 72, 34))
        self.pushButton_13.setStyleSheet(_fromUtf8("QPushButton {\n"
"color: white;\n"
"background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #88d, stop: 0.1 #99e, stop: 0.49 #77c, stop: 0.5 #66b, stop: 1 #77c);\n"
"border-width: 1px;\n"
"border-color: #339;\n"
"border-style: solid;\n"
"border-radius: 7;\n"
"padding: 3px;\n"
"font-size: 14px;\n"
"padding-left: 5px;\n"
"padding-right: 5px;\n"
"min-width: 60px;\n"
"max-width: 60px;\n"
"min-height: 26px;\n"
"max-height: 26px;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: rgb(75, 75, 75);\n"
"    border-style: inset;\n"
"}"))
        self.pushButton_13.setObjectName(_fromUtf8("pushButton_13"))
        self.pushButton_14 = QtGui.QPushButton(Dialog)
        self.pushButton_14.setGeometry(QtCore.QRect(90, 110, 72, 34))
        self.pushButton_14.setStyleSheet(_fromUtf8("QPushButton {\n"
"color: white;\n"
"background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #88d, stop: 0.1 #99e, stop: 0.49 #77c, stop: 0.5 #66b, stop: 1 #77c);\n"
"border-width: 1px;\n"
"border-color: #339;\n"
"border-style: solid;\n"
"border-radius: 7;\n"
"padding: 3px;\n"
"font-size: 14px;\n"
"padding-left: 5px;\n"
"padding-right: 5px;\n"
"min-width: 60px;\n"
"max-width: 60px;\n"
"min-height: 26px;\n"
"max-height: 26px;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: rgb(75, 75, 75);\n"
"    border-style: inset;\n"
"}"))
        self.pushButton_14.setObjectName(_fromUtf8("pushButton_14"))
        self.pushButton_15 = QtGui.QPushButton(Dialog)
        self.pushButton_15.setGeometry(QtCore.QRect(170, 110, 72, 34))
        self.pushButton_15.setStyleSheet(_fromUtf8("QPushButton {\n"
"color: white;\n"
"background-color: QLinearGradient( x1: 0, y1: 0, x2: 0, y2: 1, stop: 0 #88d, stop: 0.1 #99e, stop: 0.49 #77c, stop: 0.5 #66b, stop: 1 #77c);\n"
"border-width: 1px;\n"
"border-color: #339;\n"
"border-style: solid;\n"
"border-radius: 7;\n"
"padding: 3px;\n"
"font-size: 14px;\n"
"padding-left: 5px;\n"
"padding-right: 5px;\n"
"min-width: 60px;\n"
"max-width: 60px;\n"
"min-height: 26px;\n"
"max-height: 26px;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: rgb(75, 75, 75);\n"
"    border-style: inset;\n"
"}"))
        self.pushButton_15.setObjectName(_fromUtf8("pushButton_15"))
        self.pushButton_16 = QtGui.QPushButton(Dialog)
        self.pushButton_16.setGeometry(QtCore.QRect(250, 110, 72, 34))
        self.pushButton_16.setStyleSheet(_fromUtf8("QPushButton {\n"
"color: white;\n"
"border-width: 1px;\n"
"border-color: #339;\n"
"border-style: solid;\n"
"border-radius: 7;\n"
"padding: 3px;\n"
"font-size: 14px;\n"
"padding-left: 5px;\n"
"padding-right: 5px;\n"
"min-width: 60px;\n"
"max-width: 60px;\n"
"min-height: 26px;\n"
"max-height: 26px;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: rgb(75, 75, 75);\n"
"    border-style: inset;\n"
"}"))
        self.pushButton_16.setObjectName(_fromUtf8("pushButton_16"))
        self.pushButton_17 = QtGui.QPushButton(Dialog)
        self.pushButton_17.setGeometry(QtCore.QRect(10, 60, 72, 34))
        self.pushButton_17.setStyleSheet(_fromUtf8("QPushButton {\n"
"color: white;\n"
"border-width: 1px;\n"
"border-color: #339;\n"
"border-style: solid;\n"
"border-radius: 7;\n"
"padding: 3px;\n"
"font-size: 14px;\n"
"padding-left: 5px;\n"
"padding-right: 5px;\n"
"min-width: 60px;\n"
"max-width: 60px;\n"
"min-height: 26px;\n"
"max-height: 26px;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: rgb(75, 75, 75);\n"
"    border-style: inset;\n"
"}"))
        self.pushButton_17.setObjectName(_fromUtf8("pushButton_17"))
        self.pushButton_17.clicked.connect(lambda: core.Sqrt(self))
        self.pushButton_18 = QtGui.QPushButton(Dialog)
        self.pushButton_18.setGeometry(QtCore.QRect(90, 60, 72, 34))
        self.pushButton_18.setStyleSheet(_fromUtf8("QPushButton {\n"
"color: white;\n"
"border-width: 1px;\n"
"border-color: #339;\n"
"border-style: solid;\n"
"border-radius: 7;\n"
"padding: 3px;\n"
"font-size: 14px;\n"
"padding-left: 5px;\n"
"padding-right: 5px;\n"
"min-width: 60px;\n"
"max-width: 60px;\n"
"min-height: 26px;\n"
"max-height: 26px;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: rgb(75, 75, 75);\n"
"    border-style: inset;\n"
"}"))
        self.pushButton_18.setObjectName(_fromUtf8("pushButton_18"))
        self.pushButton_18.clicked.connect(lambda: core.Pow(self))
        self.pushButton_19 = QtGui.QPushButton(Dialog)
        self.pushButton_19.setGeometry(QtCore.QRect(250, 60, 72, 34))
        self.pushButton_19.setStyleSheet(_fromUtf8("QPushButton {\n"
"color: white;\n"
"border-width: 1px;\n"
"border-color: #339;\n"
"border-style: solid;\n"
"border-radius: 7;\n"
"padding: 3px;\n"
"font-size: 14px;\n"
"padding-left: 5px;\n"
"padding-right: 5px;\n"
"min-width: 60px;\n"
"max-width: 60px;\n"
"min-height: 26px;\n"
"max-height: 26px;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: rgb(75, 75, 75);\n"
"    border-style: inset;\n"
"}"))
        self.pushButton_19.setObjectName(_fromUtf8("pushButton_19"))
        self.listView = QtGui.QLineEdit(Dialog)
        self.listView.setReadOnly(True)
        self.listView.setAlignment(Qt.AlignRight)
        self.listView.setGeometry(QtCore.QRect(10, 10, 311, 31))
        self.listView.setStyleSheet(_fromUtf8("QLineEdit {\n"
"    background-color: rgb(255, 255, 255);\n"
"padding: 1px;\n"
"border-style: solid;\n"
"border: 2px solid gray;\n"
"border-radius: 8px;\n"
"}"))
        self.listView.setObjectName(_fromUtf8("listView"))
        self.pushButton_20 = QtGui.QPushButton(Dialog)
        self.pushButton_20.setGeometry(QtCore.QRect(170, 60, 72, 34))
        self.pushButton_20.setStyleSheet(_fromUtf8("QPushButton {\n"
"color: white;\n"
"border-width: 1px;\n"
"border-color: #339;\n"
"border-style: solid;\n"
"border-radius: 7;\n"
"padding: 3px;\n"
"font-size: 14px;\n"
"padding-left: 5px;\n"
"padding-right: 5px;\n"
"min-width: 60px;\n"
"max-width: 60px;\n"
"min-height: 26px;\n"
"max-height: 26px;\n"
"}\n"
"QPushButton:pressed {\n"
"    background-color: rgb(75, 75, 75);\n"
"    border-style: inset;\n"
"}"))
        self.pushButton_20.setObjectName(_fromUtf8("pushButton_20"))
        self.pushButton_20.clicked.connect(lambda: core.AC(self))
        ops = [self.pushButton_19,self.pushButton_16,self.pushButton_12,self.pushButton_8,self.pushButton_4]
        nums = [self.pushButton_2,self.pushButton_5,self.pushButton_6,self.pushButton_7,self.pushButton_9,self.pushButton_10,self.pushButton_11,self.pushButton_13,self.pushButton_14,self.pushButton_15]
        for i in nums:
            i.clicked.connect(lambda: core.Nums(self))
        for i in ops:
            i.clicked.connect(lambda: core.Operator(self))
        self.retranslateUi(Dialog)
        QtCore.QMetaObject.connectSlotsByName(Dialog)

    def retranslateUi(self, Dialog):
        Dialog.setWindowTitle(_translate("Dialog", "Calculator", None))
        self.pushButton.setText(_translate("Dialog", "+/-", None))
        self.pushButton_2.setText(_translate("Dialog", "0", None))
        self.pushButton_3.setText(_translate("Dialog", ".", None))
        self.pushButton_4.setText(_translate("Dialog", "=", None))
        self.pushButton_5.setText(_translate("Dialog", "1", None))
        self.pushButton_6.setText(_translate("Dialog", "2", None))
        self.pushButton_7.setText(_translate("Dialog", "3", None))
        self.pushButton_8.setText(_translate("Dialog", "+", None))
        self.pushButton_9.setText(_translate("Dialog", "4", None))
        self.pushButton_10.setText(_translate("Dialog", "5", None))
        self.pushButton_11.setText(_translate("Dialog", "6", None))
        self.pushButton_12.setText(_translate("Dialog", "-", None))
        self.pushButton_13.setText(_translate("Dialog", "7", None))
        self.pushButton_14.setText(_translate("Dialog", "8", None))
        self.pushButton_15.setText(_translate("Dialog", "9", None))
        self.pushButton_16.setText(_translate("Dialog", "*", None))
        self.pushButton_17.setText(_translate("Dialog", "sqrt", None))
        self.pushButton_18.setText(_translate("Dialog", "pow", None))
        self.pushButton_19.setText(_translate("Dialog", "/", None))
        self.pushButton_20.setText(_translate("Dialog", "AC", None))


if __name__ == "__main__":
    import sys
    app = QtGui.QApplication(sys.argv)
    Dialog = QtGui.QDialog()
    ui = Ui_Dialog()
    ui.setupUi(Dialog)
    Dialog.show()
    sys.exit(app.exec_())

