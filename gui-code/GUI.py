#####################################
##  NAME    : GRADUATION PROJECT   ##
##  AUTHOR  : Embedded Subteam     ##
##  DATE    : 26 FEB 2022          ##
##  VERSION : VO1                  ##
#####################################

##############################################################
from PyQt5.QtCore import *
from PyQt5.QtGui import *
from PyQt5.QtWidgets import *
from PyQt5.uic import loadUiType
import sys
import os
from os import path
import time
import serial
import numpy as np
from matplotlib import pyplot as plt
from matplotlib.backends.backend_qt5agg import FigureCanvasQTAgg as FigureCanvas
import csv
from threading import Thread
##############################################################

MAIN_UI,_ = loadUiType('UTM.ui')
DataSerial = serial.Serial(port='COM4', baudrate=57600, timeout=.1)
time.sleep(2)
DataSerial.close()
DataSerial.open()

##############################################################

class Main(QMainWindow , MAIN_UI):
    def __init__(self,parent=None):
        QMainWindow.__init__(self,parent)
        self.setupUi(self)
        self.Modify_ui()
        self.Home_tab()
        self.Handel_Buttons()
        self.Handel_UI_Changes()
        self.Button()
        self.Inputs()
        self.Select()
        self.Direction_Motor()
        self.Slider()




##############################################################

    def Modify_ui(self):
        self.setWindowTitle("UTM")
        self.setFixedSize(822, 621)

##############################################################

    def Handel_Buttons(self):
         self.Home.clicked.connect(self.Home_tab)
         self.Motor.clicked.connect(self.Motor_tab)
         self.Curve.clicked.connect(self.Curve_tab)

##############################################################

    def Home_tab(self):
         self.tabWidget.setCurrentIndex(0)
    def Motor_tab(self):
         self.tabWidget.setCurrentIndex(1)
    def Curve_tab(self):
        self.tabWidget.setCurrentIndex(2)

##############################################################

    def Handel_UI_Changes(self):
        self.tabWidget.tabBar().setVisible(False)

##############################################################

    def Button(self):
        self.PushPowerOn.clicked.connect(self.PowerOn)
        #self.PushStart.clicked.connect(self.Start)
        self.PushStart.clicked.connect(self.Threadd)
        #self.PushStart.clicked.connect(self.Excel)
        self.PushPowerOff.clicked.connect(self.PowerOff)
        self.PushCurve.clicked.connect(self.DrawCurve)


    def Inputs(self):
        self.InitialLength.textChanged.connect(self.StoreLength)
        self.InitialLength.editingFinished.connect(self.SendLength)
        self.Area.textChanged.connect(self.StoreArea)
        self.Area.editingFinished.connect(self.SendArea)

    def Select(self):
        self.comboBox.currentIndexChanged.connect(self.Test)


    def Direction_Motor(self):
        self.Up.toggled.connect(self.MoveUp)
        self.Down.toggled.connect(self.MoveDown)


    def Slider(self):
        self.SpeedSlider.valueChanged.connect(self.SpeedPwm)

##############################################################

    def PowerOn(self):
        print("hello, from power on")
        DataSerial.write(b'a')
        time.sleep(0.05)



    #def Start(self):
       # print("hello, from Start")
        #DataSerial.write(b'e')
       # time.sleep(0.05)

    def PowerOff(self):
        print("power off")
        DataSerial.write(b'b')
        time.sleep(0.05)


    def StoreLength(self, text):
        self.InitialLength.setText(text)
        global Lengthmm
        Lengthmm = 'L' + text
        print(Lengthmm)

    def SendLength(self):
        DataSerial.write(str(Lengthmm).encode())
        time.sleep(0.05)

    def StoreArea(self, text1):
        self.Area.setText(text1)
        global Areamm
        Areamm = 'A' + text1
        print(Areamm)

    def SendArea(self):
        DataSerial.write(str(Areamm).encode())
        time.sleep(0.05)

    def Test(self):
        TC=self.comboBox.currentText()
        print(TC)
        DataSerial.write(TC.encode())
        time.sleep(0.05)

    def MoveUp(self):
        if self.Up.isChecked() == True:
            DataSerial.write(b"a")
            time.sleep(0.05)

        else:
            DataSerial.write(b"b")
            time.sleep(0.05)

    def MoveDown(self):
        if self.Down.isChecked() == True:
            DataSerial.write(b'c')
            time.sleep(0.05)
        else:
            DataSerial.write(b'd')
            time.sleep(0.05)

    def SpeedPwm(self,text2):
        self.SpeedSlider.setValue(text2)
        print(text2)
        SpeedMotor = 'S' + str(text2)
        print(SpeedMotor)
        DataSerial.write(str(SpeedMotor).encode())
        time.sleep(0.05)

    global Stress
    global Strain
    Stress = []
    Strain = []
    def Threadd(self):
        global t1
        t1 = Thread(target=self.Curves)
        t1.start()

        #time.sleep(1)
        #t1.join()




    def Curves(self):
        global Maximum
        Maximum=0
        i=0
        while (True):

            line = DataSerial.readline()  # read a byte string
            string = line.decode()        # convert the byte string to a unicode string
            if(string==''):
                print("NO data")
            else:
                num = float(string)           # convert the unicode string to a float

                print(num)
                if(num==0.00 and i>10):
                    break

                if (i % 2 == 0):
                    Stress.append(num)        # add float to data list stress
                else:
                    Strain.append(num)        # add float to data list strain
            #QApplication.processEvents()
                i+=1
                time.sleep(0.005)

        if (len(Stress) != len(Strain)):
            Strain.append(0.0)
        print(Stress)
        print(Strain)

        for y in range(len(Stress)):
            if Stress[y] > Maximum:
               Maximum = Stress[y]
        print(Maximum)

    def DrawCurve(self):
        if(len(Stress)!=0):
            self.Display = Tensile()
            self.ViewCurve.addWidget(self.Display)
            self.Max.display(float(Maximum))
        else:
            self.Max.display(0)

    def Excel(self):
        ExcelData = open("Data.csv", 'w', newline="")
        writerto = csv.writer(ExcelData)
        row1=['Strain','Stress']
        writerto.writerow(row1)
        z=0
        for z in range(len(Stress)):
            rows=[Strain[z],Stress[z]]
            writerto.writerow(rows)

##############################################################

class Tensile(FigureCanvas):
    def __init__(self, parent=None):
        self.fig , self.ax = plt.subplots(1,dpi=100, figsize=(10, 20),
            sharey=True, facecolor='white')
        super().__init__(self.fig)

        self.fig.suptitle('Stress Strain Curve',size=11)
        plt.xlabel('Strain')
        plt.ylabel('Stress')
       # self.ax = plt.axes()
        plt.plot(Strain,Stress, color='#3d8ec9')
        print(Stress)

##############################################################

def main():
    app=QApplication(sys.argv)
    Window= Main()
    Window.show()
    app.exec()

if __name__ =='__main__':
    main()

##############################################################