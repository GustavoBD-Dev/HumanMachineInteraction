import serial.tools.list_ports
from PyQt5 import QtCore, QtWidgets
from PyQt5.QtCore import QTimer
from untitled import *
import serial
import time
import pyttsx3

class MainWindow(QtWidgets.QMainWindow, Ui_MainWindow):
    def __init__(self, *args, **kwards):
        QtWidgets.QMainWindow.__init__(self, *args, **kwards)
        self.setupUi(self)
        self.init()
        self.setWindowTitle("Señas Mexicanas")
        #self.ser = serial.Serial()

    def init(self):
        self.pushButton.clicked.connect(self.readData)

    def readData(self):
        # iniciar objeto serial
        serialarduino = serial.Serial("COM3", 9600)

        s = pyttsx3.init()

        # Esperamos un segundo despues de crear la conexion
        time.sleep(1)

        # Realizar la lectura del puerto serie
        cad = serialarduino.readline().decode('ascii')

        while True:
            self.labelText.setText(cad)
            print(cad)
            data = cad
            s.say(data)
            s.runAndWait()
            time.sleep(2)
            print("''''''''''''")
            #self.labelText.setText(cad)
            while True:
                aux = serialarduino.readline().decode('ascii')
                if aux != cad:
                    cad = aux
                    self.labelText.setText(aux)
                    break

if __name__ == "__main__":
    app = QtWidgets.QApplication([])
    window = MainWindow()
    window.show()
    app.exec_()


