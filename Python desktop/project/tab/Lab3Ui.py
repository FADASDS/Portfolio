from PyQt5 import QtWidgets, uic
from base.Widget import Widget
from encoders.Matrix import Matrix

class Lab3(Widget):

    def __init__(self, ui_name, parent):
        super().__init__(ui_name, parent)
        self.__init_buttons()
        self.__encoder = Matrix()
        self.__init_key_matrix(self.__encoder.key_matrix)

    def __init_buttons(self):
        self.btnBack.clicked.connect(self.__on_back_clicked)
        self.btnEncode.clicked.connect(self.__on_encode_clicked)
        self.btnDecode.clicked.connect(self.__on_decode_clicked)

    def __init_key_matrix(self, key_matrix):
        
        rows, cols = key_matrix.shape
        for row in range(rows):
            for col in range(cols):
                item = QtWidgets.QTableWidgetItem(key_matrix[row][col])
                self.tableWidget.setItem(row, col, item)
        return key_matrix

    def __on_encode_clicked(self):

        self.encodedTxtEdit.clear()
        self.decodedTxtEdit.clear()
        self.__encoder.source_msg = self.sourceTxtEdit.toPlainText()
        self.__encoder.code_message()
        self.encodedTxtEdit.setText(' '.join(map(str, self.__encoder.encrypted_msg)))
        
    def __on_decode_clicked(self):
        self.__encoder.decode_message()
        self.decodedTxtEdit.setText(self.__encoder.decrypted_msg)
        
    def __on_back_clicked(self):

        super()._Widget__on_back_clicked()
        self.encodedTxtEdit.clear()
        self.decodedTxtEdit.clear()
        self.sourceTxtEdit.clear()
        self.keyTable.clear()

    