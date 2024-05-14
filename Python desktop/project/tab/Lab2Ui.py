from PyQt5 import QtWidgets, uic
from base.Widget import Widget
import os
import sys
from encoders.Changer import Changer

class Lab2(Widget):

    def __init__(self, ui_name, parent):
        super().__init__(ui_name, parent)
        self.__init_buttons()
        self.__encoder = Changer()
    
    def __init_buttons(self):
        self.btnBack.clicked.connect(self.__on_back_clicked)
        self.btnEncode_2.clicked.connect(self.__on_encode_clicked)
        self.btnDecode_2.clicked.connect(self.__on_decode_clicked)

    def __on_encode_clicked(self):

        self.encodedTxtEdit_2.clear()
        self.decodedTxtEdit_2.clear()
        self.__encoder.key = self.keyLineEdit.text()
        self.__encoder.source_msg = self.sourceTxtEdit_2.toPlainText()
        self.__encoder.get_key_nums()
        self.__encoder.code_message()
        self.encodedTxtEdit_2.setText( self.__encoder.encrypted_msg)
    
    def __on_decode_clicked(self):
        self.__encoder.decode_message()
        self.decodedTxtEdit_2.setText(self.__encoder.decrypted_msg)
    
    def __on_back_clicked(self):

        super()._Widget__on_back_clicked()
        self.encodedTxtEdit_2.clear()
        self.decodedTxtEdit_2.clear()
        self.sourceTxtEdit_2.clear()

    