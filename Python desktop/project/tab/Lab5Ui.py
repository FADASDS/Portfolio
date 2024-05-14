from PyQt5 import QtWidgets, uic
from base.Widget import Widget
from encoders.Redoc import Redoc

class Lab5(Widget):

    def __init__(self, ui_name, parent):
        super().__init__(ui_name, parent)
        self.__init_buttons()
        self.__encoder = Redoc()
        self.plainTextEdit.setPlainText(repr(self.__encoder.bytes_str))

    def __init_buttons(self):
        self.btnBack.clicked.connect(self.__on_back_clicked)
        self.btnEncode.clicked.connect(self.__on_encode_clicked)
        self.btnDecode.clicked.connect(self.__on_decode_clicked)

    def __on_encode_clicked(self):

        self.encodedTxtEdit.clear()
        self.decodedTxtEdit.clear()
        self.__encoder.source_msg = self.sourceTxtEdit.toPlainText()
        self.__encoder.encrypt_data()
        self.encodedTxtEdit.setText(repr(self.__encoder.encrypted_msg))
        
    def __on_decode_clicked(self):
        self.__encoder.decrypt_data()
        self.decodedTxtEdit.setText(self.__encoder.decrypted_msg)
        
    def __on_back_clicked(self):

        super()._Widget__on_back_clicked()
        self.encodedTxtEdit.clear()
        self.decodedTxtEdit.clear()
        self.sourceTxtEdit.clear()

    