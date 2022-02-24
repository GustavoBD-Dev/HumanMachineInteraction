#include <MD_Parola.h>
#include <MD_MAX72xx.h>
#include <SPI.h>

// Define the number of devices we have in the chain and the hardware interface
// NOTE: These pin numbers will probably not work with your hardware and may
// need to be adapted
#define HARDWARE_TYPE MD_MAX72XX::FC16_HW
#define MAX_DEVICES 4

#define CLK_PIN   13
#define DATA_PIN  11
#define CS_PIN    10

// HARDWARE SPI
MD_Parola P = MD_Parola(HARDWARE_TYPE, DATA_PIN, CLK_PIN, CS_PIN, MAX_DEVICES);

uint8_t scrollSpeed = 30;    //velocidad de animacion
textEffect_t scrollEffect = PA_SCROLL_LEFT;//animacion entrada
textEffect_t scrollEffect_out = PA_SCROLL_LEFT;//animacion salida
textPosition_t scrollAlign = PA_LEFT;//Alineacion texto
uint16_t scrollPause = 2000; //Pausa en milisegundos

// Global message buffers shared by Serial and Scrolling functions
#define  BUF_SIZE  500
char curMessage[BUF_SIZE] = { "" };

int step = 0;

void setup()
{
  Serial.begin(9600);
  P.begin();
  P.displayText(curMessage, scrollAlign, scrollSpeed, scrollPause, scrollEffect, scrollEffect);
  P.setIntensity(15);
}




char aux[BUF_SIZE] = {"ON AIR"};
int animacion = 0, brillo = 0, velocidad = 30, alineacion = 0, animacion_salida = 0, invert = 0, pausa = 2000;
void loop()
{
  //efectoEntrada,Texto,brillo,
  const char s[2] = ",";
  char *token;
  //cadena_en_bruto,animacion_entrada,texto,brillo,velocidad,alineacion,animacion_salida,invertir,pausa
  String cad = "", cad1 = "", cad2 = "", cad3 = "", cad4 = "", cad5 = "", cad6 = "", cad7 = "", cad8 = "";
  int i = 0;
  if (Serial.available() > 0) {
    cad = Serial.readString();
    Serial.print("Si recibe: " + cad);
    cad.toCharArray(aux, BUF_SIZE);
    token = strtok(aux, s);
    //Serial.println(token);
    /* walk through other tokens */

    while ( token != NULL ) {
      //Serial.println( token );
      if (cad1 == "") {
        cad1 = token;
        animacion = cad1.toInt();
        Serial.println(cad1);
      } else if (cad2 == "") {
        cad2 = token;
        Serial.println(cad2);
      } else if (cad3 == "") {
        cad3 = token;
        brillo = cad3.toInt();
        Serial.println(cad3);
      } else if (cad4 == "") {
        cad4 = token;
        velocidad = cad4.toInt();
        Serial.println(cad4);
      } else if (cad5 == "") {
        cad5 = token;
        alineacion = cad5.toInt();
        Serial.println(cad3);
      } else if (cad6 == "") {
        cad6 = token;
        animacion_salida = cad6.toInt();
        Serial.println(cad6);
      } else if (cad7 == "") {
        cad7 = token;
        invert = cad7.toInt();
        Serial.println(cad7);
      } else if (cad8 == "") {
        cad8 = token;
        pausa = cad8.toInt();
        Serial.println(cad8);
      }
      token = strtok(NULL, s);
    }

    if (cad2 != "") {
      cad2.toCharArray(aux, BUF_SIZE);
    }
  }

  if (P.displayAnimate())
  {
    /*
      UP = 2
      DOWN = 3
      LEFT = 4
      RIGHT = 5
    */
    switch (animacion) {

      case 0:
        scrollEffect = PA_SCROLL_UP;
        break;

      case 1:
        scrollEffect = PA_SCROLL_DOWN;
        break;

      case 2:
        scrollEffect = PA_SCROLL_LEFT;
        break;

      case 3:
        scrollEffect = PA_SCROLL_RIGHT;
        break;

      default:
        scrollEffect = PA_SCROLL_LEFT;
        break;
    }

    switch (animacion_salida) {

      case 0:
        scrollEffect_out = PA_SCROLL_UP;
        break;

      case 1:
        scrollEffect_out = PA_SCROLL_DOWN;
        break;

      case 2:
        scrollEffect_out = PA_SCROLL_LEFT;
        break;

      case 3:
        scrollEffect_out = PA_SCROLL_RIGHT;
        break;

      default:
        scrollEffect_out = PA_SCROLL_LEFT;
        break;
    }

    switch (alineacion) {
      case 0:
        scrollAlign = PA_LEFT;
        break;
      case 1:
        scrollAlign = PA_RIGHT;
        break;
      case 2:
        scrollAlign = PA_CENTER;
        break;

    }

    P.setTextEffect(scrollEffect, scrollEffect_out);
    P.setIntensity(brillo);
    P.setSpeed(velocidad);
    P.setInvert(invert);
    P.setPause(pausa);
    P.setTextAlignment(scrollAlign);
    strcpy(curMessage, aux);

    P.displayReset();

    if (step != 3)
      step++;
    else
      step = 0;
  }
}


//https://www.luisllamas.es/controlar-arduino-con-python-y-la-libreria-pyserial/
//https://programarfacil.com/blog/arduino-blog/matriz-led-arduino-max7219/
