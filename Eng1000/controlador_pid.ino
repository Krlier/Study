#include <DualMotor.h>

DualMotor dualmotor;
const int LM35 = 0;
float temperatura = 0;
int ADClido = 0;
int Potenciometro = 1;
float potReal;
float SetTemp;
float ST; 
float erro;
float RVentoinha;

double 
kP = ((temperatura)/(ST-temperatura));


void setup(){
analogReference(INTERNAL);
Serial.begin(9600);
dualmotor.M1parar();


}

void loop(){
erro = temperatura - ST;
  
   potReal = analogRead(Potenciometro);                                                              
   SetTemp = map (potReal, 0, 1023, 25, 35);
   ST = SetTemp; 
   
   ADClido = analogRead(LM35);
  float mv = ( ADClido * 0.1075268817204301); 
  float cel = mv/1;
  
  RVentoinha = (180 + (erro * 2.55));
  
  Serial.print("TEMPERATURA = ");
  Serial.print(cel);
  Serial.print("*C");
  Serial.println();
  delay(1500);
  
  Serial.print("RVentoinha = ");
  Serial.print(RVentoinha);
  Serial.println();
  delay(1000);
  
  Serial.print("SetTemp = ");
  Serial.print(ST);
  Serial.print("*C");
  Serial.println();
  delay(1000);
  
  Serial.print("Erro = ");
  Serial.print(erro);
  Serial.println();
  delay(1000);
  
 Serial.print("-------------------------");
  Serial.println();

ADClido = analogRead(LM35); 
temperatura = ADClido * 0.1075268817204301;
if( erro < 0)
{
dualmotor.M1parar();

}
else{
  dualmotor.M1move(RVentoinha ,1);
}

}
