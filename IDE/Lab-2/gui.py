import sys
from PyQt4 import QtCore, QtGui
from PyQt4.QtCore import Qt
import core
import math


class Button(QtGui.QToolButton):
    def __init__(self, text, parent=None):
        super(Button, self).__init__(parent)

        self.setSizePolicy(QtGui.QSizePolicy.Expanding,
                QtGui.QSizePolicy.Preferred)
        self.setText(text)

    def sizeHint(self):
        size = super(Button, self).sizeHint()
        size.setHeight(size.height() + 20)
        size.setWidth(max(size.width(), size.height()))
        return size


class Calculator(QtGui.QDialog):
    NumDigitButtons = 10
    
    def __init__(self, parent=None):
        super(Calculator, self).__init__(parent)

        self.pendingAdditiveOperator = ''
        self.pendingMultiplicativeOperator = ''

        self.sumInMemory = 0.0
        self.sumSoFar = 0.0
        self.factorSoFar = 0.0
        self.waitingForOperand = True

        self.display = QtGui.QLineEdit('0')
        self.display.setReadOnly(True)
        self.display.setAlignment(QtCore.Qt.AlignRight)
        self.display.setMaxLength(15)

        font = self.display.font()
        font.setPointSize(font.pointSize() + 8)
        self.display.setFont(font)

        self.digitButtons = []
        
        for i in range(Calculator.NumDigitButtons):
            self.digitButtons.append(self.createButton(str(i),
                    self.digitClicked))

        self.pointButton = self.createButton(".", self.pointClicked)
        self.changeSignButton = self.createButton("\261",
                self.changeSignClicked)

        self.backspaceButton = self.createButton("Backspace",
                self.backspaceClicked)
        self.clearButton = self.createButton("Clear", self.clear)
        self.clearAllButton = self.createButton("Clear All", self.clearAll)

        self.clearMemoryButton = self.createButton("MC", self.clearMemory)
        self.readMemoryButton = self.createButton("MR", self.readMemory)
        self.setMemoryButton = self.createButton("MS", self.setMemory)
        self.addToMemoryButton = self.createButton("M+", self.addToMemory)

        self.divisionButton = self.createButton("\367",
                self.multiplicativeOperatorClicked)
        self.timesButton = self.createButton("\327",
                self.multiplicativeOperatorClicked)
        self.minusButton = self.createButton("-", self.additiveOperatorClicked)
        self.plusButton = self.createButton("+", self.additiveOperatorClicked)

        self.squareRootButton = self.createButton("Sqrt",
                self.unaryOperatorClicked)
        self.powerButton = self.createButton("Pow",
                self.powerOperatorClicked)
        self.reciprocalButton = self.createButton("1/x",
                self.unaryOperatorClicked)
        self.equalButton = self.createButton("=", self.equalClicked)

        mainLayout = QtGui.QGridLayout()
        mainLayout.setSizeConstraint(QtGui.QLayout.SetFixedSize)

        mainLayout.addWidget(self.display, 0, 0, 1, 6)
        mainLayout.addWidget(self.backspaceButton, 1, 0, 1, 2)
        mainLayout.addWidget(self.clearButton, 1, 2, 1, 2)
        mainLayout.addWidget(self.clearAllButton, 1, 4, 1, 2)

        mainLayout.addWidget(self.clearMemoryButton, 2, 0)
        mainLayout.addWidget(self.readMemoryButton, 3, 0)
        mainLayout.addWidget(self.setMemoryButton, 4, 0)
        mainLayout.addWidget(self.addToMemoryButton, 5, 0)

        for i in range(1, Calculator.NumDigitButtons):
            row = ((9 - i) / 3) + 2
            column = ((i - 1) % 3) + 1
            mainLayout.addWidget(self.digitButtons[i], row, column)

        mainLayout.addWidget(self.digitButtons[0], 5, 1)
        mainLayout.addWidget(self.pointButton, 5, 2)
        mainLayout.addWidget(self.changeSignButton, 5, 3)

        mainLayout.addWidget(self.divisionButton, 2, 4)
        mainLayout.addWidget(self.timesButton, 3, 4)
        mainLayout.addWidget(self.minusButton, 4, 4)
        mainLayout.addWidget(self.plusButton, 5, 4)

        mainLayout.addWidget(self.squareRootButton, 2, 5)
        mainLayout.addWidget(self.powerButton, 3, 5)
        mainLayout.addWidget(self.reciprocalButton, 4, 5)
        mainLayout.addWidget(self.equalButton, 5, 5)
        self.setLayout(mainLayout)

        self.setWindowTitle("Calculator")

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
"    background-color: rgb(255, 0, 0);\n"
"    border-style: inset;\n"
"}"))
        self.pushButton_2.setObjectName(_fromUtf8("pushButton_2"))
        self.pushButton_3 = QtGui.QPushButton(Dialog)
        self.pushButton_3.setGeometry(QtCore.QRect(170, 260, 72, 34))
        self.pushButton_3.setStyleSheet(_fromUtf8("QPushButton {\n"
"color: black;\n"
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
"color: black;\n"
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


if __name__ == '__main__':

    import sys

    app = QtGui.QApplication(sys.argv)
    calc = Calculator()
    sys.exit(calc.exec_())



if __name__ == "__main__":
    import sys
    app = QtGui.QApplication(sys.argv)
    Dialog = QtGui.QDialog()
    ui = Ui_Dialog()
    ui.setupUi(Dialog)
    Dialog.show()
    sys.exit(app.exec_())

