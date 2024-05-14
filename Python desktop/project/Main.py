from PyQt5 import QtWidgets, uic
import os
import sys
from tab import Lab1Ui, Lab2Ui, Lab3Ui, Lab4Ui, Lab5Ui
ui_folder = os.path.join("ui")

class MainWindow(QtWidgets.QMainWindow):

    def __init__(self):
        super().__init__()
        uic.loadUi(os.path.join(ui_folder, "MainWindow.ui"), self)

        self.__init_tabs()
        self.__init_buttons()

    def __init_tabs(self):
          
        self.stackedWidget.addWidget(Lab1Ui.Lab1(os.path.join(ui_folder, "Lab1Form.ui"), self))
        self.stackedWidget.addWidget(Lab2Ui.Lab2(os.path.join(ui_folder, "Lab2Form.ui"), self))
        self.stackedWidget.addWidget(Lab3Ui.Lab3(os.path.join(ui_folder, "Lab3Form.ui"), self))
        self.stackedWidget.addWidget(Lab4Ui.Lab4(os.path.join(ui_folder, "Lab4Form.ui"), self))
        self.stackedWidget.addWidget(Lab5Ui.Lab5(os.path.join(ui_folder, "Lab5Form.ui"), self))

    def __init_buttons(self):

        self.btnLab1.clicked.connect(self.__on_lab1_clicked)
        self.btnLab2.clicked.connect(self.__on_lab2_clicked)
        self.btnLab3.clicked.connect(self.__on_lab3_clicked)
        self.btnLab4.clicked.connect(self.__on_lab4_clicked)
        self.btnLab5.clicked.connect(self.__on_lab5_clicked)
    
    def __on_lab1_clicked(self):

        self.stackedWidget.setCurrentIndex(2)
    
    def __on_lab2_clicked(self):

        self.stackedWidget.setCurrentIndex(3)
    
    def __on_lab3_clicked(self):

        self.stackedWidget.setCurrentIndex(4)
    
    def __on_lab4_clicked(self):

        self.stackedWidget.setCurrentIndex(5)

    def __on_lab5_clicked(self):

        self.stackedWidget.setCurrentIndex(6)
        


if __name__ == "__main__":

    app = QtWidgets.QApplication(sys.argv)
    mWnd = MainWindow()
    mWnd.show()
    app.exec()