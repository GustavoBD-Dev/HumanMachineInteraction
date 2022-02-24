import serial.tools.list_ports
from PyQt5 import QtCore, QtWidgets
from PyQt5.QtWidgets import QDialog, QMessageBox
from PyQt5.QtCore import QTimer
from window import *
import serial

class MainWindow(QtWidgets.QMainWindow, Ui_MainWindow):

    def __init__(self, *args, **kwards):
        QtWidgets.QMainWindow.__init__(self, *args, **kwards)
        self.setupUi(self)
        self.init()
        self.setWindowTitle("Asistente de puerto serie")
        self.ser = serial.Serial()
        self.port_check()
        self.Rev = 0


    def init(self):
        # Botón de detección de puerto serie
        self.s1__box_1.clicked.connect(self.port_check)

        # Pantalla de información del puerto serie
        self.s1__box_2.currentTextChanged.connect(self.port_imf)

        # Abra el botón del puerto serie
        self.open_button.clicked.connect(self.port_open)

        # Apague el botón del puerto serie
        self.close_button.clicked.connect(self.port_close)

        # Botón Enviar datos
        self.s3__send_button.clicked.connect(self.validateData)

        # El temporizador recibe los datos
        self.timer = QTimer(self)

        # Selecciona si quiere invertir encendido de LED´s
        self.reverseLEDs.stateChanged.connect(self.checkBoxChangedAction)


    # Detección de puerto serie
    def port_check(self):
        # Detecta todos los puertos serie existentes y almacena la información en el diccionario
        self.Com_Dict = {}
        port_list = list(serial.tools.list_ports.comports())
        self.s1__box_2.clear()
        for port in port_list:
            self.Com_Dict["%s" % port[0]] = "%s" % port[1]
            self.s1__box_2.addItem(port[0])
        if len(self.Com_Dict) == 0:
            self.state_label.setText("Sin puerto serie")

    # Información del puerto serie   
    def port_imf(self):
        imf_s = self.s1__box_2.currentText()
        # Muestra los detalles del puerto serie seleccionado
        if imf_s != "":
            self.state_label.setText(self.Com_Dict[self.s1__box_2.currentText()])


    def port_open(self):
        self.ser.port = self.s1__box_2.currentText()
        self.ser.baudrate = int(self.s1__box_3.currentText())
        self.ser.bytesize = int(self.s1__box_4.currentText())
        self.ser.stopbits = int(self.s1__box_6.currentText())
        self.ser.parity = self.s1__box_5.currentText()

        try:
            self.ser.open()
        except:
            QMessageBox.critical(self, "Port Error", "¡Este puerto serie no se puede abrir!")
            return None

        # Abra el temporizador de recepción del puerto serie con un período de 2 ms
        self.timer.start(2)

        if self.ser.isOpen():
            self.open_button.setEnabled(False)
            self.close_button.setEnabled(True)
            self.formGroupBox.setTitle("Estado del puerto serie (abierto)")
            self.s3__send_button.setEnabled(True)

    # Cierre el puerto serie
    def port_close(self):
        self.timer.stop()
        #self.timer_send.stop()
        try:
            self.ser.close()
        except:
            pass
        self.open_button.setEnabled(True)
        self.close_button.setEnabled(False)
        self.s3__send_button.setEnabled(False)
        #self.lineEdit_3.setEnabled(True)
        #self.formGroupBox.setTitle("Estado del puerto serie (cerrado)")


    # Enviar datos
    def data_send(self, stringData):
        if self.ser.isOpen():
            # Ascii envía - example: 2,has completed!!,1,40,1,2,0,200
            input_s = (stringData + '\r\n').encode('ascii')
            self.ser.write(input_s)
        # Establece el valor de la barra de progreso
        self.progressBar.setValue(100)
        '''
         print("Orden de elementos: animacion_entrada,texto,brillo,velocidad,alineacion,animacion_salida,invertir,pausa")
        '''

    def checkBoxChangedAction(self, state):
        if (QtCore.Qt.Checked == state):
            self.Rev = 1
        else:
            self.Rev = 0

    def validateData(self):
        stringData = ''
        inputDirection = None
        outputDirection = None
        # Establece el valor de la barra de progreso
        self.progressBar.setValue(0)
        try:
            if self.inputAnimation.currentText() == "ABAJO":
                inputDirection = 0
            elif self.inputAnimation.currentText() == "ARRIBA":
                inputDirection = 1
            elif self.inputAnimation.currentText() == "DERECHA":
                inputDirection = 2
            elif self.inputAnimation.currentText() == "IZQUIERDA":
                inputDirection = 3

            if self.outputAnimation.currentText() == "ABAJO":
                outputDirection = 1
            elif self.outputAnimation.currentText() == "ARRIBA":
                outputDirection = 0
            elif self.outputAnimation.currentText() == "DERECHA":
                outputDirection = 3
            elif self.outputAnimation.currentText() == "IZQUIERDA":
                outputDirection = 2

            #2,has completed!!,1,40,1,2,0,200
            stringData += str(inputDirection) + ','
            stringData += str(self.s3__send_text.toPlainText()) + ','
            stringData += str(self.sliderBrightness.value()//20) + ','
            stringData += str(self.sliderSpeed.value()) + ','
            stringData += str('1') + ','
            stringData += str(outputDirection) + ','
            stringData += str(self.Rev) + ','
            stringData += str((self.sliderTimeScreen.value()*100)/2)
            print(stringData)
        except:
            self.show_dialog()
        #print("send -> ",stringData) 
        # Establece el valor de la barra de progreso
        self.progressBar.setValue(50)
        self.data_send(stringData)
            
    def show_dialog(self):
        QMessageBox.about(self, 'Alerta', 'Verificar campos de entrada')

class Dialog(QDialog):
    def __init__(self, *args, **kwards):
        super(Dialog, self).__init__(*args, **kwards)
        self.setWindowTitle('Alerta')
        self.setFixedSize(200, 200)

if __name__=="__main__":
    app = QtWidgets.QApplication([])
    window = MainWindow()
    window.show()
    app.exec_()
