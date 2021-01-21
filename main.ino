/* ------------- MOVIMENTO PATAS VERSAO 2.2 ------------- 
 *  Desenvolvedores: Daniel Lopes / Enrique Emanuel
 *  ETEC Martin Luther King
 *  Sao Paulo(SP), Brasil - 2019
 *  Contatos: ddanielssoares@gmail.com
 *  enriqueemanuelcontato@gmail.com
 *  
 */

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include <SoftwareSerial.h>


Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);                            //Seleciona o shield com endereco 0x40
SoftwareSerial Bluetooth(10, 11); // RX, TX

//Configuração PWM para o servo motor. Ajuste o pulso de acordo com
//o servo motor que você vai utilizar
#define SERVOMIN  150                                                                   //Comprimento de pulso minimo
#define SERVOMAX  600                                                                   //Comprimento de pulso maximo

//Porta dos Sensores
int motores[6] = {2, 3, 4, 5, 6, 7 };                                              //array que define os pinos dos motores
#define sensorA 2
#define sensorB 3
#define sensorC 4
#define sensorD 5
#define sensorE 6
#define sensorF 7
char bluetooth;

//Declarando Funções que serão utilizadas:
int   graus(int x);
void  front();
void  right();  
void  left();
void  parado();

void setup() {
  
  Bluetooth.begin(9600);
  pwm.begin();                                                                          //Inicia o controle dos servos(PWM)
  pwm.setPWMFreq(50);                                                                   //Frequencia de comunicaçao com o driver em 50Hz

  for(int i = 0; i<7; i++) pinMode(motores[i] , INPUT_PULLUP);                                   //Portas 2 - 8 como entradas com resistor Pullup
    
}

void loop() {
  bluetooth = Bluetooth.read();
  switch (bluetooth) {
        case 'W':
          front();
        break;
        
        case 'A':
          left();
        break;

        case 'D':
          right();
        break;
        
        default:
        parado(0);          
      }
}

void front(){     //Funcao que faz o Hexpod andar para frente
  pwm.setPWM(0, 0, graus(180));     //Motor 0 gira com sentido para frente no robo 
  pwm.setPWM(4, 0, graus(0));       //Motor 4(motor oposto) gira com sentido para frente no robo
  pwm.setPWM(2, 0, graus(180));     //Motor 2 gira com sentido para frente no robo
  delay(900);                       //Delay para iniciar o lado B
  pwm.setPWM(3, 0, graus(0));       //Motor 3 gira com sentido para frente no robo
  pwm.setPWM(1, 0, graus(180));     //Motor 1(motor oposto) gira com sentido para frente no robo
  pwm.setPWM(5, 0, graus(0));       //Motor 5 gira com sentido para frente no robo
  delay(100);                       //Delay para parar o lado A
  pwm.setPWM(0, 0, graus(51));      //Motor 0 parado
  pwm.setPWM(4, 0, graus(51));      //Motor 4 parado
  pwm.setPWM(2, 0, graus(51));      //Motor 2 parado
  delay(900);                       //Delay para parar o lado B
  pwm.setPWM(3, 0, graus(51));      //Motor 3 parado
  pwm.setPWM(1, 0, graus(51));      //Motor 1 parado
  pwm.setPWM(5, 0, graus(51));      //Motor 5 parado
  delay(10);                        //Delay apenas para diminuir a velocidade do processamento
  parado(0);                     //Chama a funaao parado que sincroniza as patas ao chao, com sentido para frente do robo
}

void right(){
  pwm.setPWM(0, 0, graus(180));     //Motor 0 gira com sentido para frente no robo 
  pwm.setPWM(4, 0, graus(0));       //Motor 4(motor oposto) gira com sentido para frente no robo
  pwm.setPWM(2, 0, graus(180));     //Motor 2 gira com sentido para frente no robo
  delay(900);                       //Delay para iniciar o lado B
  pwm.setPWM(3, 0, graus(180));       //Motor 3 gira com sentido para frente no robo
  pwm.setPWM(1, 0, graus(0));     //Motor 1(motor oposto) gira com sentido para frente no robo
  pwm.setPWM(5, 0, graus(180));       //Motor 5 gira com sentido para frente no robo
  delay(100);                       //Delay para parar o lado A
  pwm.setPWM(0, 0, graus(51));      //Motor 0 parado
  pwm.setPWM(4, 0, graus(51));      //Motor 4 parado
  pwm.setPWM(2, 0, graus(51));      //Motor 2 parado
  delay(900);                       //Delay para parar o lado B
  pwm.setPWM(3, 0, graus(51));      //Motor 3 parado
  pwm.setPWM(1, 0, graus(51));      //Motor 1 parado
  pwm.setPWM(5, 0, graus(51));      //Motor 5 parado
  delay(10);                        //Delay apenas para diminuir a velocidade do processamento
  parado(1);                        //Chama a funaao parado que sincroniza as patas ao chao, com sentido para direita do robo
}

void left(){     //Funcao que faz o Hexpod andar para frente
  pwm.setPWM(0, 0, graus(0));     //Motor 0 gira com sentido para frente no robo 
  pwm.setPWM(4, 0, graus(180));       //Motor 4(motor oposto) gira com sentido para frente no robo
  pwm.setPWM(2, 0, graus(0));     //Motor 2 gira com sentido para frente no robo
  delay(900);                       //Delay para iniciar o lado B
  pwm.setPWM(3, 0, graus(0));       //Motor 3 gira com sentido para frente no robo
  pwm.setPWM(1, 0, graus(180));     //Motor 1(motor oposto) gira com sentido para frente no robo
  pwm.setPWM(5, 0, graus(0));       //Motor 5 gira com sentido para frente no robo
  delay(100);                       //Delay para parar o lado A
  pwm.setPWM(0, 0, graus(51));      //Motor 0 parado
  pwm.setPWM(4, 0, graus(51));      //Motor 4 parado
  pwm.setPWM(2, 0, graus(51));      //Motor 2 parado
  delay(900);                       //Delay para parar o lado B
  pwm.setPWM(3, 0, graus(51));      //Motor 3 parado
  pwm.setPWM(1, 0, graus(51));      //Motor 1 parado
  pwm.setPWM(5, 0, graus(51));      //Motor 5 parado
  delay(10);                        //Delay apenas para diminuir a velocidade do processamento
  parado(2);                     //Chama a funaao parado que sincroniza as patas ao chao, com sentido para esquerda do robo
}

void parado(int sentido){       //Funcao que sincroniza as patas no chao, recebe valor: sentido de rotacao, para sincronizar
  if(sentido == 0) {                    //Se sentido for 0, sincroniza as patas para tras do robo
      if(!digitalRead(sensorA)){    //Se o sensor A, localizado na porta 2, estiver ativado
        pwm.setPWM(0, 0, graus(51));//Motor 0 parado
      } else {                      //Se não
          do {                      //Executa uma vez o que estiver dentro de "do"
            pwm.setPWM(0, 0, graus(180));//Motor 0 gira com sentido para frente no robo 
          } while(digitalRead(sensorA));//Enquanto sensor A estiver desativado ele executa "do"
          if(!digitalRead(sensorA)){//Se o sensor A, localizado na porta 2, estiver ativado
            pwm.setPWM(0, 0, graus(51));//Motor 0 parado
          }                         //
      }                             //
      delay(1);                     //Delay apenas para diminuir a velocidade do processamento
      if(!digitalRead(sensorB)){    //Se o sensor B, localizado na porta 3, estiver ativado
        pwm.setPWM(1, 0, graus(51));//Motor 1 parado
      } else {                      //Se não
          do{                       //Executa uma vez o que estiver dentro de "do"
            pwm.setPWM(1, 0, graus(180));//Motor 1 gira com sentido para frente no robo 
          }while(digitalRead(sensorB));//Enquanto sensor B estiver desativado ele executa "do"
          if(!digitalRead(sensorB)){//Se o sensor B, localizado na porta 3, estiver ativado
            pwm.setPWM(1, 0, graus(51));//Motor 1 parado
          }                         //
      }                             //
      delay(1);                     //Delay apenas para diminuir a velocidade do processamento
      if(!digitalRead(sensorC)){    //Se o sensor C, localizado na porta 4, estiver ativado
        pwm.setPWM(2, 0, graus(51));//Motor 2 parado
      } else {                      //Se não
          do{                       //Executa uma vez o que estiver dentro de "do"
            pwm.setPWM(2, 0, graus(180));//Motor 2 gira com sentido para frente no robo
          }while(digitalRead(sensorC));//Enquanto sensor B estiver desativado ele executa "do"
          if(!digitalRead(sensorC)){//Se o sensor C, localizado na porta 4, estiver ativado
            pwm.setPWM(2, 0, graus(51));//Motor 2 parado
          }                         //
      }                             //
      delay(1);                     
      if(!digitalRead(sensorD)){
        pwm.setPWM(3, 0, graus(51));
      } else {
          do{
            pwm.setPWM(3, 0, graus(0));
          }while(digitalRead(sensorD));
          if(!digitalRead(sensorD)){
            pwm.setPWM(3, 0, graus(51));
          }
      }
      delay(1);
      if(!digitalRead(sensorE)){
        pwm.setPWM(4, 0, graus(51));
      } else {
          do{
            pwm.setPWM(4, 0, graus(0));
          } while(digitalRead(sensorE));
          if(!digitalRead(sensorE)){
            pwm.setPWM(4, 0, graus(51));
          }
      }
      delay(1);
      if(!digitalRead(sensorF)){
        pwm.setPWM(5, 0, graus(51));
      } else {
          do{
            pwm.setPWM(5, 0, graus(0));
          }while(digitalRead(sensorF));
          if(!digitalRead(sensorF)){
            pwm.setPWM(5, 0, graus(51));
          }
      }
  }
  if(sentido == 1) {                    //Se sentido for 1, sincroniza as patas para direita do robo
      if(!digitalRead(sensorA)){    //Se o sensor A, localizado na porta 2, estiver ativado
        pwm.setPWM(0, 0, graus(51));//Motor 0 parado
      } else {                      //Se não
          do {                      //Executa uma vez o que estiver dentro de "do"
            pwm.setPWM(0, 0, graus(180));//Motor 0 gira com sentido para frente no robo 
          } while(digitalRead(sensorA));//Enquanto sensor A estiver desativado ele executa "do"
          if(!digitalRead(sensorA)){//Se o sensor A, localizado na porta 2, estiver ativado
            pwm.setPWM(0, 0, graus(51));//Motor 0 parado
          }                         //
      }                             //
      delay(1);                     //Delay apenas para diminuir a velocidade do processamento
      if(!digitalRead(sensorB)){    //Se o sensor B, localizado na porta 3, estiver ativado
        pwm.setPWM(1, 0, graus(51));//Motor 1 parado
      } else {                      //Se não
          do{                       //Executa uma vez o que estiver dentro de "do"
            pwm.setPWM(1, 0, graus(0));//Motor 1 gira com sentido para tras no robo 
          }while(digitalRead(sensorB));//Enquanto sensor B estiver desativado ele executa "do"
          if(!digitalRead(sensorB)){//Se o sensor B, localizado na porta 3, estiver ativado
            pwm.setPWM(1, 0, graus(51));//Motor 1 parado
          }                         //
      }                             //
      delay(1);                     //Delay apenas para diminuir a velocidade do processamento
      if(!digitalRead(sensorC)){    //Se o sensor C, localizado na porta 4, estiver ativado
        pwm.setPWM(2, 0, graus(51));//Motor 2 parado
      } else {                      //Se não
          do{                       //Executa uma vez o que estiver dentro de "do"
            pwm.setPWM(2, 0, graus(180));//Motor 2 gira com sentido para frente no robo
          }while(digitalRead(sensorC));//Enquanto sensor B estiver desativado ele executa "do"
          if(!digitalRead(sensorC)){//Se o sensor C, localizado na porta 4, estiver ativado
            pwm.setPWM(2, 0, graus(51));//Motor 2 parado
          }                         //
      }                             //
      delay(1);                     
      if(!digitalRead(sensorD)){
        pwm.setPWM(3, 0, graus(51));
      } else {
          do{
            pwm.setPWM(3, 0, graus(180));
          }while(digitalRead(sensorD));
          if(!digitalRead(sensorD)){
            pwm.setPWM(3, 0, graus(51));
          }
      }
      delay(1);
      if(!digitalRead(sensorE)){
        pwm.setPWM(4, 0, graus(51));
      } else {
          do{
            pwm.setPWM(4, 0, graus(0));
          } while(digitalRead(sensorE));
          if(!digitalRead(sensorE)){
            pwm.setPWM(4, 0, graus(51));
          }
      }
      delay(1);
      if(!digitalRead(sensorF)){
        pwm.setPWM(5, 0, graus(51));
      } else {
          do{
            pwm.setPWM(5, 0, graus(180));
          }while(digitalRead(sensorF));
          if(!digitalRead(sensorF)){
            pwm.setPWM(5, 0, graus(51));
          }
      }
  }
  if(sentido == 3) {                    //Se sentido for 0, sincroniza as patas para esquerda do robo
      if(!digitalRead(sensorA)){    //Se o sensor A, localizado na porta 2, estiver ativado
        pwm.setPWM(0, 0, graus(51));//Motor 0 parado
      } else {                      //Se não
          do {                      //Executa uma vez o que estiver dentro de "do"
            pwm.setPWM(0, 0, graus(0));//Motor 0 gira com sentido para tras no robo 
          } while(digitalRead(sensorA));//Enquanto sensor A estiver desativado ele executa "do"
          if(!digitalRead(sensorA)){//Se o sensor A, localizado na porta 2, estiver ativado
            pwm.setPWM(0, 0, graus(51));//Motor 0 parado
          }                         //
      }                             //
      delay(1);                     //Delay apenas para diminuir a velocidade do processamento
      if(!digitalRead(sensorB)){    //Se o sensor B, localizado na porta 3, estiver ativado
        pwm.setPWM(1, 0, graus(51));//Motor 1 parado
      } else {                      //Se não
          do{                       //Executa uma vez o que estiver dentro de "do"
            pwm.setPWM(1, 0, graus(180));//Motor 1 gira com sentido para frente no robo 
          }while(digitalRead(sensorB));//Enquanto sensor B estiver desativado ele executa "do"
          if(!digitalRead(sensorB)){//Se o sensor B, localizado na porta 3, estiver ativado
            pwm.setPWM(1, 0, graus(51));//Motor 1 parado
          }                         //
      }                             //
      delay(1);                     //Delay apenas para diminuir a velocidade do processamento
      if(!digitalRead(sensorC)){    //Se o sensor C, localizado na porta 4, estiver ativado
        pwm.setPWM(2, 0, graus(51));//Motor 2 parado
      } else {                      //Se não
          do{                       //Executa uma vez o que estiver dentro de "do"
            pwm.setPWM(2, 0, graus(0));//Motor 2 gira com sentido para tras no robo
          }while(digitalRead(sensorC));//Enquanto sensor B estiver desativado ele executa "do"
          if(!digitalRead(sensorC)){//Se o sensor C, localizado na porta 4, estiver ativado
            pwm.setPWM(2, 0, graus(51));//Motor 2 parado
          }                         //
      }                             //
      delay(1);                     
      if(!digitalRead(sensorD)){
        pwm.setPWM(3, 0, graus(51));
      } else {
          do{
            pwm.setPWM(3, 0, graus(0));
          }while(digitalRead(sensorD));
          if(!digitalRead(sensorD)){
            pwm.setPWM(3, 0, graus(51));
          }
      }
      delay(1);
      if(!digitalRead(sensorE)){
        pwm.setPWM(4, 0, graus(51));
      } else {
          do{
            pwm.setPWM(4, 0, graus(180));
          } while(digitalRead(sensorE));
          if(!digitalRead(sensorE)){
            pwm.setPWM(4, 0, graus(51));
          }
      }
      delay(1);
      if(!digitalRead(sensorF)){
        pwm.setPWM(5, 0, graus(51));
      } else {
          do{
            pwm.setPWM(5, 0, graus(0));
          }while(digitalRead(sensorF));
          if(!digitalRead(sensorF)){
            pwm.setPWM(5, 0, graus(51));
          }
      }
  }
}
  
int graus(int x) {                                                                      //Funçao 'graus' que recebe um valor Inteiro armazenado em 'x'                                                            
  int graus = x;                                                                        //Variavel inteira 'graus' recebe o valor de 'x'
  graus = map(graus, 0, 180, SERVOMIN, SERVOMAX);                                       //Regra de 3, para converter graus no valor do PWM
  
  return graus;                                                                         //Retorna como resultado da funcao, o valor da variavel 'graus'
}
