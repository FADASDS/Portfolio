from PyQt5 import QtWidgets, uic, Qt
from abc import abstractmethod
import os
import sys

class Widget(Qt.QWidget):

    def __init__(self, ui_name, parent):
        super().__init__()
        uic.loadUi(ui_name, self)
        self.__parent = parent

    @abstractmethod
    def __init_buttons(self):
       self.btnBack.clicked.connect(self.__on_back_clicked)
    @abstractmethod
    def __on_back_clicked(self):

        self.__parent.stackedWidget.setCurrentIndex(0)