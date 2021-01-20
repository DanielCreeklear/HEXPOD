/* ------------- MOVIMENTO PATAS VERSAO 0.2 ------------- 
 *  Desenvolvedores: Daniel Lopes / Enrique Emanuel
 *  ETEC Martin Luther King
 *  Sao Paulo(SP), Brasil - 2019
 *  Contatos: ddanielssoares@gmail.com
 *  enriqueemanuelcontato@gmail.com
 *  
 */

#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);                            //Seleciona o shield com endereco 0x40

//Configuração PWM para o servo motor. Ajuste o pulso de acordo com
//o servo motor que você vai utilizar
#define SERVOMIN  150                                                                   //Comprimento de pulso minimo
#define SERVOMAX  600                                                                   //Comprimento de pulso maximo

boolean sensors[6] ={ };                                                                //array pros sensores
int motores[6] = { };                                                                   //array que define os pinos dos motores


void setup() {

  pwm.begin();                                                                          //Inicia o controle dos servos(PWM)
  pwm.setPWMFreq(60);                                                                   //Frequencia de comunicaçao com o driver em 60Hz
  yield();

  for(int i = 0; i<7; i++) pinMode(i , INPUT_PULLUP);                                   //Portas 2 - 8 como entradas com resistor Pullup

  
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

boolean redArea_MOTOR(int motor){
  boolean retorno = false;
      if(!digitalRead(sensors[motor])){
        retorno = true;
      }
  return retorno;
}

boolean redarea(boolean lado) {
  
  boolean estadosensor[6] = { };
  boolean yon;
    if (lado == true){
          for (int k = 0; k<3; k++){
            estadosensor[k] = redArea_MOTOR(k);
    }
       if (estadosensor[0] && estadosensor[1] && estadosensor[2]){
       yon = true;
       } else{
          yon = false;
       }
    } else if(lado == false){
          for (int k = 3; k<6; k++){
            estadosensor[k] = redArea_MOTOR(k);
          }
       if (estadosensor[3] && estadosensor[4] && estadosensor[5]){
       yon = true;
       } else{
          yon = false;
          }
      }    
return yon;  
} 

void runPart(boolean parte){
  if(parte){
    for (int servo = 0; servo<3 ; servo++){
        pwm.setPWM(servo, 0, graus(180));   
    }
  } else {
    for (int servo = 3; servo<6 ; servo++){
        pwm.setPWM(servo, 0, graus(180));   
    }
  }
}

void stopleg(int parte){
  if(parte == 0) {
    for (int servo = 0; servo<3 ; servo++){
        pwm.setPWM(servo, 0, graus(76));   
   }
  } else if(parte == 1){
      for (int servo = 3; servo<6 ; servo++){
        pwm.setPWM(servo, 0, graus(76));   
      }
  } else if(parte == 2){
      for (int servo = 0; servo<6 ; servo++){
        pwm.setPWM(servo, 0, graus(76));   
      }
  }
}

void go_out_redarea(boolean lado){
  //Primeiramente roda todos os motores e mantém esse estado até que os sensores sejam ativados
  if(lado) {
    
      do {
        runPart(0);
      }while (!redarea(0));
      
  } else if(!lado) {
    
      do {
        runPart(1);
      }while (!redarea(1));
      
  }
  //Quando todos os motores entrarem na área dos sensores, todos eles são parados
     stopleg(2); 
}



void front() {                                                                     
    //Fun?ao 'frente' que movimenta o robo
    //Se os motores 0 a 2 e 3 a 5 estão com o mesmo estado, então eles começam a girar juntos
    //senão, eles performam o movimento do robô
    
  if (redarea(0) == redarea(1)){
    
    if (!redarea(0)) go_out_redarea(0);
    if (!redarea(1)) go_out_redarea(1);
  
  } else {
      if (redarea(0)){
        if (redarea(1)){
          girarlado(false, true);
          girarlado(true, false);
        }else{
          girarlado(false, false);
          girarlado(true, true);
        }
      } else{
          girarlado(false, true);
          girarlado(true, false);
      }
  }

}

void girarlado(boolean lado, boolean intensidade){

  if (lado == false && intensidade == true){
    //lado A com velocidade máxima
    for (int motor = 0; motor<3 ; motor++){
          //se o motor 2 for selecionado (o que se encontra do lado oposto aos outros 2, girar ele ao contrário
          //isso é para manter o giro na mesma direção na hora que for andar
          if (motor == 2 ){
            pwm.setPWM(motor, 0, graus(0));   
          }
          pwm.setPWM(motor, 0, graus(180));
    }
  }else if (lado == false && intensidade == false){
      for (int motor = 0; motor<3 ; motor++){
          if (motor == 2 ){
            pwm.setPWM(motor, 0, graus(50));   
          }
          pwm.setPWM(motor, 0, graus(90));
      }   
  }else if (lado == true && intensidade == true){
    //lado B com velocidade máxima
    for (int motor = 3; motor<6 ; motor++){
          //se o motor 4 for selecionado (o que se encontra do lado oposto aos outros dois, girar ele ao contrário
          //isso e para manter o giro na mesma direção na hora que for andar
          if (motor == 4){
            pwm.setPWM(motor, 0, graus(180));   
          }
          pwm.setPWM(motor, 0, graus(0));
    }
  } else if (lado == true && intensidade == false){
      for (int motor = 3; motor<6 ; motor++){
          if (motor == 4){
            pwm.setPWM(motor, 0, graus(90));   
          }
          pwm.setPWM(motor, 0, graus(50));
      }   
  }
}

void loop() {
  front();
  delay(200);
  stopleg(2);
}
