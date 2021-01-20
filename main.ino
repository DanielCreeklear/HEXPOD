/* ------------- MOVIMENTO PATAS VERSÃO 0.1 ------------- 
 *  Desenvolvedores: Daniel Lopes
 *  ETEC Martin Luther King
 *  São Paulo(SP), Brasil - 2019
 *  Contatos: ddanielssoares@gmail.com
 *  
 */

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);                            //Seleciona o shield com endereço 0x40

//Configuração PWM para o servo motor. Ajuste o pulso de acordo com
//o servo motor que você vai utilizar
#define SERVOMIN  150                                                                   //Comprimento de pulso minimo
#define SERVOMAX  600                                                                   //Comprimento de pulso maximo


void setup() {

  pwm.begin();                                                                          //Inicia o controle dos servos(PWM)
  pwm.setPWMFreq(60);                                                                   //Frequencia de comunicaçao com o driver em 60Hz
  yield();

  
}
int graus(int x) {                                                                      //Funçao 'graus' que recebe um valor Inteiro armazenado em 'x'                                                            
  int graus = x;                                                                        //Variavel inteira 'graus' recebe o valor de 'x'
  graus = map(graus, 0, 180, SERVOMIN, SERVOMAX);                                       //Regra de 3, para converter graus no valor do PWM
  
  return graus;                                                                         //Retorna como resultado da funçao, o valor da variavel 'graus'
}
void giroPata(int motor) {                                                              //Versao A do giro do motor, recebe um valor inteiro indicando o motor
  const int z = 1000;                                                                   //Valor constante do intervalo para o motor girar em torno de 330º                                                    
      
      pwm.setPWM(motor, 0, graus(180));                                                 //Seta o (Motor, valor constante, em 180º[velocidade maxima]) 
      delay(z);                                                                         //Intervalo para o giro completar os 330º
      pwm.setPWM(motor, 0, graus(76));                                                  //Seta o (Motor, valor constante, em 76º[parado])
      delay(3);                                                                         //Intervalo apenas para sincronia
  
}
void posGiroPata(int motor, int x) {                                                    //Funçao que posiciona os motores localizados em 330º para 360º, recebe numero do motor e valor 'x')
  
      pwm.setPWM(motor, 0, graus(180));                                                 //Seta o (Motor, valor constante, em 180º[velocidade maxima]) 
      delay(x);                                                                         //Intervalo para o giro completar os 360º
      pwm.setPWM(motor, 0, graus(76));                                                  //Seta o (Motor, valor constante, em 76º[parado])
      delay(3);                                                                         //Intervalo apenas para sincronia
}
int frente(int z) {                                                                     //Funçao 'frente' que movimenta o robo, recebe um valor 'z' de um contador                                                               
  int x;                                                                                //Variavel 'x' que armazenara o valor do intervalo para o motor completar 360º 
  if (z == 0)  {                                                                        //Caso a funçao tenha sido executado uma vez ela possuira o valor '0'
    x = 220;                                                                            //Variavel 'x' recebe o valor de 220(milisegundos para 360º)
  }
  if (z == 1) {                                                                         //Caso a funçao tenha sido executado pela segunda vez ela possuira o valor '1'
    x = 210;                                                                            //Variavel 'x' recebe o valor de 220(milisegundos para 360º)
  }


  for(int n = 0; n < 6; n++) {                                                          //Laço para girar as 6 patas para 330º
    giroPata(n);                                                                        //Funçao que fara as patas girarem recebe o valor do contador 'n' do for
  }
  for(int n = 0; n < 6; n++) {                                                          //Laço para girar as 6 patas para 360º
    posGiroPata(n, x);                                                                  //Funçao que fara as patas girarem para 360º recebe o valor do contador 'n' do for e o valor 'x' 
  }
  
}


void loop() {
  for(int n = 0; n = 1; n++) {                                                          //Laço para solicitar o avanço duas vezes, que sera executado infinitamente pelo void loop
    frente(n);                                                                          //Funçao que avanaça o robo recebe o valor que alcança no maximo o numero 1, como contador de vezes
  }
  
}
 
