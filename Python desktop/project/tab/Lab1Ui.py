from PyQt5 import QtWidgets, uic
from base.Widget import Widget
import os
import sys
from encoders import Polibius

class Lab1(Widget):

    def __init__(self, ui_name, parent):
        super().__init__(ui_name, parent)
        self.__init_buttons()
        self.__encoder = Polibius.Polibius()
    
    def __init_buttons(self):
        self.btnBack.clicked.connect(self.__on_back_clicked)
        self.btnEncode.clicked.connect(self.__on_encode_clicked)
        self.btnDecode.clicked.connect(self.__on_decode_clicked)

    def __on_encode_clicked(self):

        self.encodedTxtEdit.clear()
        self.decodedTxtEdit.clear()
        self.__encoder.source_message = self.sourceTxtEdit.toPlainText()
        print(self.__encoder.source_message)
        self.__encoder.code_message()
        self.encodedTxtEdit.setText(' '.join(map(str, self.__encoder.enc)))
    
    def __on_decode_clicked(self):
        self.__encoder.decode_message()
        self.decodedTxtEdit.setText(self.__encoder.decoded_message)
    
    def __on_back_clicked(self):

        super()._Widget__on_back_clicked()
        self.encodedTxtEdit.clear()
        self.decodedTxtEdit.clear()
        self.sourceTxtEdit.clear()

    