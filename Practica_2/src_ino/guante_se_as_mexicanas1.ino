// C++ code
//
int aux;
String letra;
float value,pulgar,indice,anular,medio,menique,muneca;
void setup()
{
  Serial.begin(9600);   
  
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
  pinMode(A4, INPUT);
}

void loop()
{
  aux = analogRead(A0);//1
  menique = fmap(aux, 0, 255, 0.0, 5.0);

  aux = analogRead(A1);//2
  muneca = fmap(aux, 0, 255, 0.0, 5.0);
  
  aux = analogRead(A2);//3
  anular = fmap(aux, 0, 255, 0.0, 5.0);
  
  aux = analogRead(A3);//4
  medio = fmap(aux, 0, 255, 0.0, 5.0);
  
  aux = analogRead(A5);//5
  indice = fmap(aux, 0, 255, 0.0, 5.0);
  
  
  aux = analogRead(A4);//6
  pulgar = fmap(aux, 0, 255, 0.0, 5.0);
  //pulgar = 0.10;
  
  
  delay(1000); // Delay a little bit to improve simulation performance
  /**/
  /*Serial.print(menique);
  Serial.print("------");
  Serial.print(anular);
  Serial.print("------");
  Serial.print(medio);
  Serial.print("------");
  Serial.print(indice);
  Serial.print("------");
  Serial.print(pulgar);
  Serial.print("------");
  Serial.print(muneca);
  Serial.println("");*/
  //Valores de X
  if(menique <= 0.05
     && anular <= 0.12
    && medio <= 0.12
     && indice <= 0.12
    && pulgar <= 20.00
    && muneca <= 0.12){
    
    Serial.println("X");
  }else
  //Valores de DOMINGO
  if(menique <= 0.07
     && anular <= 0.13
    && medio <= 0.11
     && indice <= 0.30
    && pulgar <= 20.0 
    && muneca <= 0.14){
    
    Serial.println("DOMINGO");
  }else
  //Valores de G 
  if(menique <= 0.08
     && anular <= 0.14
    && medio <= 0.12
     && indice >= 0.20
      && pulgar <= 20.06 
    && muneca <= 0.14){
    
    Serial.println("G");
  }else
  //Valores de A
  if(menique <= 0.07
     && anular <= 0.13
    && medio <= 0.13
     && indice <= 0.10
    && pulgar <= 20.07
    && muneca <= 0.14){
    
    Serial.println("A");
  }else
  //Valores de M
  if(menique <= 0.09
     && anular <= 0.22
    && medio <= 0.20
     && indice <= 0.20
      && pulgar <= 20.06
    && muneca <= 0.12){
    
    Serial.println("M");
  }else
  //Valores de R
  if(menique <= 0.07
     && anular <= 0.13 
    && medio <= 0.29
     && indice <= 0.27
    && pulgar <= 20.07
    && muneca <= 0.12){
    
    Serial.println("R");
  }else
  
  //Valores de 4
  if(menique >= 0.25
     && anular >= 0.33
    && medio >= 0.30
     && indice >= 0.29
    && pulgar <= 20.04
    && muneca <= 0.12){
    
    Serial.println("4");
  }else
  //Valores de LUNES
  if(menique <= 0.08
     && anular <= 0.12
    && medio <= 0.12
     && indice <= 0.27 
    && pulgar <= 20.06
    && muneca <= 0.08){
    
    Serial.println("LUNES");
  }else
  //Valores de JUNIO
  if(menique <= 0.28
     && anular <= 0.13
    && medio <= 0.13
     && indice <= 0.08
    && pulgar <= 20.04
    && muneca <= 0.10){
    
    Serial.println("JUNIO");
  }else
  //Valores de DICIEMBRE
  if(menique <= 0.17
     && anular <= 0.23
    && medio <= 0.19
     && indice >= 0.30
    && pulgar <= 20.06
    && muneca <= 0.12){
    
    Serial.println("DICIEMBRE");
  }else{
    Serial.println(".");
  }
}

float fmap(float x, float in_min, float in_max, float out_min, float out_max)
{
   return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min;
}
