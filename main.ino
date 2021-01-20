/* ------------- MOVIMENTO PATAS VERSAO 1.0.1 ------------- 
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

boolean sensors[6] ={ };                                                               //array pros sensores
int     motores[6] = {2, 3, 4, 5, 6, 7 };                                              //array que define os pinos dos motores
char    bluetooth;

//Declarando Funções que serão utilizadas:
int     graus(int x);
void    giroPata(int motor);
void    posGiroPata(int motor, int x);
void    frente(int z);
boolean redArea_MOTOR(int motor);
boolean redarea(boolean lado);
void    runPart(boolean parte);
void    stopleg(int parte);
void    go_out_redarea(boolean lado);
void    front();
void    girarlado(boolean lado, boolean intensidade);
void    toSync_legs(boolean parte);

void setup() {

  Serial.begin(9600);
  pwm.begin();                                                                          //Inicia o controle dos servos(PWM)
  pwm.setPWMFreq(50);                                                                   //Frequencia de comunicaçao com o driver em 50Hz
  yield();

  for(int i = 0; i<7; i++) pinMode(motores[i] , INPUT_PULLUP);                                   //Portas 2 - 8 como entradas com resistor Pullup
    
}

void loop() {

  bluetooth = Bluetooth.read();
    while(Bluetooth.available()) {
      switch (bluetooth) {
        case 'W':
          front();
        break;
        
        case 'S':
          front();
        break;
        
        case 'Z':
          frente(1);
        break;
        
        default:
        toSync_legs(0);
        toSync_legs(1);
        goToRedArea();           
      }
    }
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

void frente(int z) {                                                                     //Funçao 'frente' que movimenta o robo, recebe um valor 'z' de um contador                                                               
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
    sensors[0] = digitalRead(2);
    sensors[1] = digitalRead(3);
    sensors[2] = digitalRead(4);
    sensors[3] = digitalRead(5);
    sensors[4] = digitalRead(6);
    sensors[5] = digitalRead(7);
    if(!sensors[motor]){ 
      retorno = true; 
    } else {
      retorno = false;
    }
 return retorno;
}

boolean redarea(boolean lado) {
  
  boolean estadosensor[6] = { };
  estadosensor[0] = redArea_MOTOR(0);
  estadosensor[1] = redArea_MOTOR(1);
  estadosensor[2] = redArea_MOTOR(2);
  estadosensor[3] = redArea_MOTOR(3);
  estadosensor[4] = redArea_MOTOR(4);
  estadosensor[5] = redArea_MOTOR(5);
  boolean yon;
    if (lado == true){
       if (estadosensor[0] == 1 && estadosensor[1] == 1 && estadosensor[2] == 1){
       yon = true;
       } else{
          yon = false;
       }
    } else if(lado == false){
       if (estadosensor[3] == 1 && estadosensor[4] == 1 && estadosensor[5] == 1){
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
        Serial.println("Girando A Para área vermelha");
        runPart(0);
      }while (!redarea(0));
      
  } else if(!lado) {
    
      do {
        Serial.println("Girando B Para área vermelha");
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
    
  if (redarea(0) == 0 && redarea(1) == 0){
    
    if (!redarea(0)) {
      go_out_redarea(0);
    }
    if (!redarea(1)) {
      go_out_redarea(1);
    }
  } else if(redarea(0) == 1 && redarea(1) == 1) {
    if (!redarea(0)) {
      go_out_redarea(0);
    }
    if (!redarea(1)) {
      go_out_redarea(1);
    }

  } else {
      if (redarea(0)){
        if (redarea(1)){
          girarlado(false, true, true);
            do {
              girarlado(true, false, true); 
            } while(!redarea(0));
        }else{
          girarlado(true, true, true);
            do {
              girarlado(false, false, true);    
            } while(!redarea(1));
        }
      } else{
          girarlado(false, true, true);
            do {
              girarlado(true, false, true);
            } while(!redarea(0));
      }
      if (redarea(1)){
        if (redarea(0)){
          girarlado(true, true, true);
            do {
              girarlado(false, false, true);
          } while(!redarea(1));
        }else{
          girarlado(false, true, true);
            do {
              Serial.println("Lado B/vel: MIN");
              girarlado(true, false, true);
            } while(!redarea(0));
        }
      } else{
          girarlado(true, true, true);
            do {
              girarlado(false, false, true); 
            } while(!redarea(1));          
      }
  }
}

void back() {                                                                     
    //Fun?ao 'frente' que movimenta o robo
    //Se os motores 0 a 2 e 3 a 5 estão com o mesmo estado, então eles começam a girar juntos
    //senão, eles performam o movimento do robô
    
  if (redarea(0) == 0 && redarea(1) == 0){
    
    if (!redarea(0)) {
      go_out_redarea(0);
    }
    if (!redarea(1)) {
      go_out_redarea(1);
    }
  } else if(redarea(0) == 1 && redarea(1) == 1) {
    if (!redarea(0)) {
      go_out_redarea(0);
    }
    if (!redarea(1)) {
      go_out_redarea(1);
    }

  } else {
      if (redarea(0)){
        if (redarea(1)){
          girarlado(false, true, false);
            do {
              girarlado(true, false, true); 
            } while(!redarea(0));
        }else{
          girarlado(true, true, true);
            do {
              girarlado(false, false, false);    
            } while(!redarea(1));
        }
      } else{
          girarlado(false, true, false);
            do {
              girarlado(true, false, true);
            } while(!redarea(0));
      }
      if (redarea(1)){
        if (redarea(0)){
          girarlado(true, true, true);
            do {
              girarlado(false, false, false);
          } while(!redarea(1));
        }else{
          girarlado(false, true, false);
            do {
              girarlado(true, false, true);
            } while(!redarea(0));
        }
      } else{
          girarlado(true, true, true);
            do {
              girarlado(false, false, false); 
            } while(!redarea(1));          
      }
  }
}

void girarlado(boolean lado, boolean intensidade, boolean sentido){

  if (lado == false && intensidade == true && sentido == true){
    //lado A com velocidade máxima frente
    for (int motor = 0; motor<3 ; motor++){
          //se o motor 2 for selecionado (o que se encontra do lado oposto aos outros 2, girar ele ao contrário
          //isso é para manter o giro na mesma direção na hora que for andar
          if (motor == 2 ){
            pwm.setPWM(motor, 0, graus(0));   
          } else {
          pwm.setPWM(motor, 0, graus(180));
          }
    }
  }else if (lado == false && intensidade == false && sentido == true){
      for (int motor = 0; motor<3 ; motor++){
          if (motor == 2 ){
            pwm.setPWM(motor, 0, graus(50));   
          } else{
          pwm.setPWM(motor, 0, graus(90));
          }
      }   
  }else if (lado == true && intensidade == true && sentido == true){
    //lado B com velocidade máxima
    for (int motor = 3; motor<6 ; motor++){
          //se o motor 4 for selecionado (o que se encontra do lado oposto aos outros dois, girar ele ao contrário
          //isso e para manter o giro na mesma direção na hora que for andar
          if (motor == 4){
            pwm.setPWM(motor, 0, graus(180));   
          } else{
          pwm.setPWM(motor, 0, graus(0));
          }
    }
  } else if (lado == true && intensidade == false && sentido == true){
      for (int motor = 3; motor<6 ; motor++){
          if (motor == 4){
            pwm.setPWM(motor, 0, graus(90));   
          } else {
          pwm.setPWM(motor, 0, graus(50));
          }
      }   
  }

  if (lado == false && intensidade == true && sentido == false){
    //lado A com velocidade máxima
    for (int motor = 0; motor<3 ; motor++){
          //se o motor 2 for selecionado (o que se encontra do lado oposto aos outros 2, girar ele ao contrário
          //isso é para manter o giro na mesma direção na hora que for andar
          if (motor == 2 ){
            pwm.setPWM(motor, 0, graus(180));   
          } else {
          pwm.setPWM(motor, 0, graus(0));
          }
    }
  }else if (lado == false && intensidade == false && sentido == false){
      for (int motor = 0; motor<3 ; motor++){
          if (motor == 2 ){
            pwm.setPWM(motor, 0, graus(90));   
          } else{
          pwm.setPWM(motor, 0, graus(50));
          }
      }   
  }else if (lado == true && intensidade == true && sentido == false){
    //lado B com velocidade máxima
    for (int motor = 3; motor<6 ; motor++){
          //se o motor 4 for selecionado (o que se encontra do lado oposto aos outros dois, girar ele ao contrário
          //isso e para manter o giro na mesma direção na hora que for andar
          if (motor == 4){
            pwm.setPWM(motor, 0, graus(0));   
          } else{
          pwm.setPWM(motor, 0, graus(180));
          }
    }
  } else if (lado == true && intensidade == false && sentido == false){
      for (int motor = 3; motor<6 ; motor++){
          if (motor == 4){
            pwm.setPWM(motor, 0, graus(50));   
          } else {
          pwm.setPWM(motor, 0, graus(90));
          }
      }   
  }
}

void toSync_legs(boolean parte){
  if(!parte) {
    int z = 0;
      for(int i = 2; i<8; i++) {
        sensors[z] = digitalRead(motores[i]);
        z++;
      }
      if(sensors[0] == sensors[1] && sensors[1] == sensors[2] && sensors[2] == sensors[0]){
        Serial.print(".");
      } else {
          do {
            pwm.setPWM(0, 0, graus(180));
            pwm.setPWM(1, 0, graus(180));
            pwm.setPWM(2, 0, graus(180));
          }while (!redarea(0));
      }
  stopleg(2);
}
  if(parte) {
   int z = 0;
      for(int i = 2; i<8; i++) {
        sensors[z] = digitalRead(motores[i]);
        z++;
      }
      if(sensors[3] == sensors[4] && sensors[4] == sensors[5] && sensors[5] == sensors[3]){
        Serial.print(".");
      } else {
        
          do {
            pwm.setPWM(3, 0, graus(180));
            pwm.setPWM(4, 0, graus(180));
            pwm.setPWM(5, 0, graus(180));
          }while (!redarea(0));
      }
  stopleg(2);
    
  }
}

void goToRedArea(){
  if(redArea_MOTOR(0) == 0) {
    do {
      pwm.setPWM(0, 0, graus(180)); 
    } while(redArea_MOTOR(0) == 0);
  }
  if(redArea_MOTOR(1) == 0) {
    do {
      pwm.setPWM(1, 0, graus(180)); 
    } while(redArea_MOTOR(1) == 0);
  }
  if(redArea_MOTOR(2) == 0) {
    do {
      pwm.setPWM(2, 0, graus(180)); 
    } while(redArea_MOTOR(2) == 0);
  }
  if(redArea_MOTOR(3) == 0) {
    do {
      pwm.setPWM(3, 0, graus(180)); 
    } while(redArea_MOTOR(3) == 0);
  }
  if(redArea_MOTOR(4) == 0) {
    do {
      pwm.setPWM(4, 0, graus(180)); 
    } while(redArea_MOTOR(4) == 0);
  }
  if(redArea_MOTOR(5) == 0) {
    do {
      pwm.setPWM(5, 0, graus(180)); 
    } while(redArea_MOTOR(5) == 0);
  }
  stopleg(2);
}
