/* ------------- MOVIMENTO PATAS VERSAO 2.4.2 -------------  
 *  Desenvolvedores: Daniel Lopes / Enrique Emanuel
 *  ETEC Martin Luther King
 *  Sao Paulo(SP), Brasil - 2019
 *  Contatos: ddanielssoares@gmail.com
 *  enriqueemanuelcontato@gmail.com
 *  
 *  CORE HEXPOD: V2.39A
 *  CONTROLE HEXPOD: V1.3
 *  
 *  =========Log de atualizacoes=============
 *  CONTEUDO NOVO:
 *  - Criada função Giro, que executa o controle de giro dos motores
 *
 * CONTEUDO MODIFICADO: 
 * - Valores delay modificados
 * CONTEUDO EXCLUIDO:
 * 
 * ============INFORMAÇÕES ÚTEIS=============
 *  A ordem atual de sincronização dos motores é 1,5,6,3,2,4
 *  
 * 
 * 
 * 
 * 
 * 
 * 
 */
  boolean sync1 = 0;
  boolean sync2 = 0;
  boolean sync3 = 0;
  boolean sync4 = 0;
  boolean sync5 = 0;
  boolean sync6 = 0;
  
 int delay1;
 int delay2;
 int delay3;
       
//Bibliotecas
#include <VirtualWire.h>
#include <VirtualWire_Config.h>

//Porta das Pontes H
  //Motor 1
  #define IN1  22
  #define IN2  23
  //Motor 2
  #define IN3  42
  #define IN4  43
  //Motor 3
  #define IN5  48
  #define IN6  49
  //Motor 4
  #define IN7  26
  #define IN8  27
  //Motor 5
  #define IN9  38
  #define IN10 39
  //Motor 6
  #define IN11 52
  #define IN12 53
//Porta dos Sensores
uint8_t motores[6] = {2, 3, 4, 5, 6, 7 }; //array que define os pinos dos motores 

//sensorA = Motor 1
#define sensorA 25
//sensorB = Motor 2 
#define sensorB 24
//sensorC = Motor 3 
#define sensorC 34
//sensorD = Motor 4
#define sensorD 40
//sensorE = Motor 5
#define sensorE 33
//sensorF = Motor 6
#define sensorF 28

//Portas de modulos
#define pinRF  12 //Pino antena RF 433MHz
#define trigPin A0 //Pino TRIG do sensor no pino analógico A0
#define echoPin A1 //Pino ECHO do sensor no pino analógico A1

//Variaveis de controle
boolean LED = 0;
boolean CAMERA = 0;

struct tipoPacote {
  char valor1;
};
tipoPacote pacote; 
uint8_t buf[sizeof(pacote)];
uint8_t buflen = sizeof(pacote);

int TempoGirar = 1;//Tempo de giro autonomo
int distanciaObstaculo = 30; //Distancia para o robo identificar obstaculos 

//Delays para movimento das patas
  #define delay1 1000 //Delay para iniciar o lado B
  
  #define delay2 800 //Delay para parar o lado A
  
  #define delay3 1200
  
//Declarando Funções que serão utilizadas:
void front_auto();
int  graus(int x);
void front();
void right();  
void left();
void back();
void parado(int l);
void controle();
void test();
void giro(int num_motor, char sentido);
int lerSonar();
int calcularDistanciaCentro();
int calcularDistanciaDireita();
int calcularDistanciaEsquerda();
char calculaMelhorDistancia();
void posicionaCarroMelhorCaminho();
void reposicionaServoSonar();
void rotacao_Parado();
void rotacao_Frente();
void rotacao_Re();
void rotacao_Direita();
void rotacao_Esquerda();
void test2();

//Variaveis  para o sensor ultrassonico
long duracao;
long distancia_cm=0;
int minimumRange=5; //tempo de resposta do sensor
int maximumRange=200;

void setup() {
  Serial.begin(9600);

  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(IN5, OUTPUT);
  pinMode(IN6, OUTPUT);
  pinMode(IN7, OUTPUT);
  pinMode(IN8, OUTPUT);
  pinMode(IN9, OUTPUT);
  pinMode(IN10, OUTPUT);
  pinMode(IN11, OUTPUT);
  pinMode(IN12, OUTPUT);
  
  pinMode(sensorA, INPUT_PULLUP);
  pinMode(sensorB, INPUT_PULLUP);
  pinMode(sensorC, INPUT_PULLUP);
  pinMode(sensorD, INPUT_PULLUP);
  pinMode(sensorE, INPUT_PULLUP);
  pinMode(sensorF, INPUT_PULLUP);
 
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);

  pinMode(trigPin, OUTPUT); //define o pino TRIG como saida
  pinMode(echoPin, INPUT);  //define o pino ECHO como entrada 

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);

  vw_set_rx_pin(pinRF);
  vw_set_ptt_inverted(true);
  vw_setup(2000);   
  vw_rx_start();
  
}

void loop() {
  test();
  delay(6000);
  sync1 = 0;
  sync2 = 0;
  sync3 = 0;
  sync4 = 0;
  sync5 = 0;
  sync6 = 0;
}                   


void giro(int num_motor, char sentido){

  // p = Parado
  if (sentido == 'p'){
    if (num_motor == 1){
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, HIGH);
    }
    
    if (num_motor == 2){
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, HIGH);
    }
    
    if (num_motor == 3){
      digitalWrite(IN5, HIGH);
      digitalWrite(IN6, HIGH);
    }
    
    if (num_motor == 4){
      digitalWrite(IN7, HIGH);
      digitalWrite(IN8, HIGH);
    }
    
    if (num_motor == 5){
      digitalWrite(IN9, HIGH);
      digitalWrite(IN10, HIGH);
    }
    
    if (num_motor == 6){
      digitalWrite(IN11, HIGH);
      digitalWrite(IN12, HIGH);
    }
  }
  
  // f = Giro para a Frente do robô
  if (sentido == 'f'){
  
    if (num_motor == 1){
      digitalWrite(IN1, HIGH);
      digitalWrite(IN2, LOW);
    }
    
    if (num_motor == 2){
      digitalWrite(IN3, HIGH);
      digitalWrite(IN4, LOW);
    }
    
    if (num_motor == 3){
      digitalWrite(IN5, HIGH);
      digitalWrite(IN6, LOW);
    }
    
    if (num_motor == 4){
      digitalWrite(IN7, HIGH);
      digitalWrite(IN8, LOW);
    }
    
    if (num_motor == 5){
      digitalWrite(IN9, HIGH);
      digitalWrite(IN10, LOW);
    }
    
    if (num_motor == 6){
      digitalWrite(IN11, HIGH);
      digitalWrite(IN12, LOW);
    }
  }
  
  // t = Giro para Trás do robô
  if (sentido == 't'){
  
    if (num_motor == 1){
      digitalWrite(IN1, LOW);
      digitalWrite(IN2, HIGH);
    }
    
    if (num_motor == 2){
      digitalWrite(IN3, LOW);
      digitalWrite(IN4, HIGH);
    }
    
    if (num_motor == 3){
      digitalWrite(IN5, LOW);
      digitalWrite(IN6, HIGH);
    }
    
    if (num_motor == 4){
      digitalWrite(IN7, LOW);
      digitalWrite(IN8, HIGH);
    }
    
    if (num_motor == 5){
      digitalWrite(IN9, LOW);
      digitalWrite(IN10, HIGH);
    }
    
    if (num_motor == 6){
      digitalWrite(IN11, LOW);
      digitalWrite(IN12, HIGH);
    }
  }

}

void back(){
  
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  //Motor 5(oposto) Frente robo:
  digitalWrite(IN10, LOW);
  digitalWrite(IN9, HIGH);
  //Motor 3 Frente robo: 
  digitalWrite(IN5, LOW);
  digitalWrite(IN6, HIGH);
    delay(1100);//Delay para iniciar o lado B
    digitalWrite(IN10, HIGH);
    digitalWrite(IN9, HIGH);
    delay(100);
  //Motor 4 Frente robo:
  digitalWrite(IN7, LOW);
  digitalWrite(IN8, HIGH);
  //Motor 2 Frente robo:
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  //Motor 6 Frente robo:
  digitalWrite(IN11, LOW);
  digitalWrite(IN12, HIGH);
   
  digitalWrite(IN5, HIGH);
  digitalWrite(IN6, HIGH);
    delay(200);//Delay para parar o lado A
  //Motor 1 Frente robo:
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  //Motor 5 Frente robo:
  digitalWrite(IN9, HIGH);
  digitalWrite(IN10,HIGH);
  //Motor 3 Frente robo:
    delay(900);//Delay para parar o lado B
  //Motor 4 Frente robo:
  digitalWrite(IN7, HIGH);
  digitalWrite(IN8, HIGH);
  //Motor 2 Frente robo:
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
  //Motor 6 Frente robo:
  digitalWrite(IN11, HIGH);
  digitalWrite(IN12, HIGH);
}

void controle(){

  if (vw_have_message()){
   vw_get_message(buf, &buflen);   
   memcpy(&pacote,&buf,buflen);
    switch (pacote.valor1) {
          case 'W':
            front();
          break;

          case 'S':
            for(int n=0; n<20; n++){ 
            front_auto();
            }
          break;
          
          case 'A':
            left();
          break;
  
          case 'D':
            right();
          break;
  
          case 'C':
            parado(0);
          break;
          
          case'G':
            LED = !LED;
            digitalWrite(8, LED);
          break;

          case'B':
            CAMERA = !CAMERA;
            digitalWrite(9, CAMERA);
          break; 
    }
  }
}

void test2(){
  parado(0);
  delay(2000);
  giro ( 1, 'p');
  for(int g = 0; g <50; g++){
        giro ( 1, 't');
        giro ( 2, 't');
        giro ( 3, 't');
        giro ( 4, 't');
        giro ( 5, 't');
        giro ( 6, 't');
        delay(1);
        giro ( 1, 'p');
        giro ( 2, 'p');
        giro ( 3, 'p');
        giro ( 4, 'p');
        giro ( 5, 'p');
        giro ( 6, 'p');
        delay(1);
      }
    for(int g = 0; g <3000; g++){
    if(g<1800){
  giro ( 1, 't');
  if(g>400) giro ( 4, 't');   
    } else{ 
      giro ( 1, 'f');
      giro ( 4, 'f');
    }
    if(g<900){
  giro ( 5, 'f');
  if(g>400) giro ( 2, 'f');  
    } else {
      giro ( 5, 't');
      if(g<2700) giro ( 2, 't');
    }
    if(g<1500){
  giro ( 3, 't');
  if(g>400) giro ( 6, 't');    
    } else{
      giro ( 3, 'f');
      if(g<2800) giro ( 6, 'f');
    }
    
    if(!sensorA) giro ( 1, 'p');
    if(!sensorB) giro ( 2, 'p');
    if(!sensorC) giro ( 3, 'p');
    if(!sensorD) giro ( 4, 'p');
    if(!sensorE) giro ( 5, 'p');
    if(!sensorF) giro ( 6, 'p');
    
    
  delay(1);
  if(g<1800){
  giro ( 1, 'p');
  if(g>400) giro ( 4, 'f');    
    } else{
      if(sensorA) {
        giro ( 1, 't');
      } else{
        giro ( 1, 'p');
      }
      giro ( 4, 'p');
    }
    if(g<900){
  giro ( 5, 'p');
  if(g>400) giro ( 2, 't');  
    } else {
      giro ( 5, 'f');
      if(g<2500) giro ( 2, 'p');
    }
    if(g<1500){
  giro ( 3, 'p');
  if(g>400) giro ( 6, 'f');    
    } else{
      giro ( 3, 't');
      giro ( 6, 'p');
    }
  delay(1);
  }
    giro ( 1, 'p');
    giro ( 2, 'p');
    giro ( 3, 'p');
    giro ( 4, 'p');
    giro ( 5, 'p');
    giro ( 6, 'p');

      for(int g = 0; g <25; g++){
        giro ( 1, 't');
        giro ( 2, 't');
        giro ( 3, 't');
        giro ( 4, 't');
        giro ( 5, 't');
        giro ( 6, 't');
        delay(1);
        giro ( 1, 'p');
        giro ( 2, 'p');
        giro ( 3, 'p');
        giro ( 4, 'p');
        giro ( 5, 'p');
        giro ( 6, 'p');
        delay(1);
      }
      
  delay(5000); 
}

void test(){
  boolean ok = 0;
  syncLeg:
for(int g = 0; g <20; g++){
    int pont = 0;
    if(digitalRead(sensorA) && sync1 == 0){
      giro ( 1, 'f');
      
      pont--;
    }
    if(digitalRead(sensorB) && sync2 == 0){
      giro ( 2, 'f');
      
      pont--;
    }
    if(digitalRead(sensorC) && sync3 == 0){
      giro ( 3, 'f');
      
      pont--;
    }
    if(digitalRead(sensorD) && sync4 == 0){
      giro ( 4, 'f');
      
      pont--;
    }
    if(digitalRead(sensorE) && sync5 == 0){
      giro ( 5, 'f');
      
      pont--;
    }
    if(digitalRead(sensorF) && sync6 == 0){
      giro ( 6, 'f');
      
      pont--;
    }
    
    delay(1);
    if(!digitalRead(sensorA)){
      giro ( 1, 'p');
      Serial.println(g);
      pont++;
      sync1 = 1;
    }
    if(!digitalRead(sensorB)){
      giro ( 2, 'p');
      Serial.println(g);
      pont++;
      sync2 = 1;
    }
    if(!digitalRead(sensorC)){
      giro ( 3, 'p');
      pont++;
      Serial.println(g);
      sync3 = 1;
    }
    if(!digitalRead(sensorD)){
      giro ( 4, 'p');
      Serial.println(g);
      pont++;
      sync4 = 1;
    }
    if(!digitalRead(sensorE)){
      giro ( 5, 'p');
      Serial.println(g);
      pont++;
      sync5 = 1;
    }
    if(!digitalRead(sensorF)){
      giro ( 6, 'p');
      Serial.println(g);
      pont++;
      sync6 = 1;
    }
    delay(1);
    if(pont >= 5){
      Serial.println("OK!");
      giro ( 1, 'p');
      giro ( 2, 'p');
      giro ( 3, 'p');
      giro ( 4, 'p');
      giro ( 5, 'p');
      giro ( 6, 'p');
      ok = 1;
      break;
    }
  }
  if(!ok) {
    goto syncLeg;
  }
}
void front(){     //Funcao que faz o Hexpod andar para frente
  parado(0);
  delay(2000);
  giro ( 1, 'p');
  for(int g = 0; g <50; g++){
        giro ( 1, 't');
        giro ( 2, 't');
        giro ( 3, 't');
        giro ( 4, 't');
        giro ( 5, 't');
        giro ( 6, 't');
        delay(1);
        giro ( 1, 'p');
        giro ( 2, 'p');
        giro ( 3, 'p');
        giro ( 4, 'p');
        giro ( 5, 'p');
        giro ( 6, 'p');
        delay(1);
      }
    for(int g = 0; g <2700; g++){
    if(g<1400){
  giro ( 1, 'f');
  if(g>400) giro ( 4, 't');   
    } else{ 
      giro ( 1, 't');
      giro ( 4, 'f');
    }
    if(g<1100){
  giro ( 5, 'f');
  if(g>400) giro ( 2, 't');  
    } else {
      giro ( 5, 't');
      if(g<2500) giro ( 2, 'f');
    }
    if(g<1200){
  giro ( 3, 'f');
  if(g>400) giro ( 6, 't');    
    } else{
      giro ( 3, 't');
      if(g<2400) giro ( 6, 'f');
    }
    
    if(!sensorA) giro ( 1, 'p');
    if(!sensorB) giro ( 2, 'p');
    if(!sensorC) giro ( 3, 'p');
    if(!sensorD) giro ( 4, 'p');
    if(!sensorE) giro ( 5, 'p');
    if(!sensorF) giro ( 6, 'p');
    
    
  delay(1);
  if(g<1400){
  giro ( 1, 'p');
  if(g>400) giro ( 4, 'f');    
    } else{
      if(sensorA) {
        giro ( 1, 'f');
      } else{
        giro ( 1, 'p');
      }
      giro ( 4, 'p');
    }
    if(g<1100){
  giro ( 5, 'p');
  if(g>400) giro ( 2, 'f');  
    } else {
      giro ( 5, 'f');
      if(g<2500) giro ( 2, 'p');
    }
    if(g<1200){
  giro ( 3, 'p');
  if(g>400) giro ( 6, 'f');    
    } else{
      giro ( 3, 'f');
      giro ( 6, 'p');
    }
  delay(1);
  }
    giro ( 1, 'p');
    giro ( 2, 'p');
    giro ( 3, 'p');
    giro ( 4, 'p');
    giro ( 5, 'p');
    giro ( 6, 'p');

      for(int g = 0; g <25; g++){
        giro ( 1, 't');
        giro ( 2, 't');
        giro ( 3, 't');
        giro ( 4, 't');
        giro ( 5, 't');
        giro ( 6, 't');
        delay(1);
        giro ( 1, 'p');
        giro ( 2, 'p');
        giro ( 3, 'p');
        giro ( 4, 'p');
        giro ( 5, 'p');
        giro ( 6, 'p');
        delay(1);
      }
  parado(0);
}

void right(){

  //Motor 1 Frente robo:
  //Motor 1 Frente robo:
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, LOW);
  //Motor 5(oposto) Frente robo:
  digitalWrite(IN10, HIGH);
  digitalWrite(IN9, LOW);
  //Motor 3 Frente robo: 
  digitalWrite(IN5, HIGH);
  digitalWrite(IN6, LOW);
    delay(1100);//Delay para iniciar o lado B
    digitalWrite(IN10, HIGH);
    digitalWrite(IN9, HIGH);
    delay(150);
  //Motor 4 Frente robo:
  digitalWrite(IN7, LOW);
  digitalWrite(IN8, HIGH);
  //Motor 2 Frente robo:
  digitalWrite(IN3, LOW);
  digitalWrite(IN4, HIGH);
  //Motor 6 Frente robo:
  digitalWrite(IN11, LOW);
  digitalWrite(IN12, HIGH);
   delay(50);
  digitalWrite(IN5, HIGH);
  digitalWrite(IN6, HIGH);
    delay(300);//Delay para parar o lado A
  //Motor 1 Frente robo:
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  delay(200);
  //Motor 5 Frente robo:
  digitalWrite(IN9, HIGH);
  digitalWrite(IN10,HIGH);
  //Motor 3 Frente robo:
    delay(900);//Delay para parar o lado B
  //Motor 4 Frente robo:
  digitalWrite(IN7, HIGH);
  digitalWrite(IN8, HIGH);
  //Motor 2 Frente robo:
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
  //Motor 6 Frente robo:
  digitalWrite(IN11, HIGH);
  digitalWrite(IN12, HIGH);
  parado(0);                        //Chama a funaao parado que sincroniza as patas ao chao, com sentido para direita do robo

}

void left(){     //Funcao que faz o Hexpod andar para a esquerda
  //Motor 1 Frente robo:
  digitalWrite(IN1, LOW);
  digitalWrite(IN2, HIGH);
  //Motor 5(oposto) Frente robo:
  digitalWrite(IN10,LOW);
  digitalWrite(IN9, HIGH);
  //Motor 3 Frente robo:
  digitalWrite(IN5, LOW);
  digitalWrite(IN6, HIGH);
    delay(delay1);//Delay para iniciar o lado B
  //Motor 4 Frente robo:
  digitalWrite(IN7, HIGH);
  digitalWrite(IN8, LOW);
  //Motor 2 Frente robo:
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, LOW);
  //Motor 6 Frente robo:
  digitalWrite(IN11, HIGH);
  digitalWrite(IN12, LOW);
    delay(delay2);//Delay para parar o lado A
  //Motor 1 parado:
  digitalWrite(IN1, HIGH);
  digitalWrite(IN2, HIGH);
  //Motor 5 parado:
  digitalWrite(IN9, HIGH);
  digitalWrite(IN10,HIGH);
  //Motor 3 parado:
  digitalWrite(IN5, HIGH);
  digitalWrite(IN6, HIGH);
    delay(delay3);//Delay para parar o lado B
  //Motor 4 parado:
  digitalWrite(IN7, HIGH);
  digitalWrite(IN8, HIGH);
  //Motor 2 parado:
  digitalWrite(IN3, HIGH);
  digitalWrite(IN4, HIGH);
  //Motor 6 parado:
  digitalWrite(IN11, HIGH);
  digitalWrite(IN12, HIGH);
  parado(0); //Chama a funcao parado que sincroniza as patas ao chao, com sentido para esquerda do robo
}

void parado(int sentido){       //Funcao que sincroniza as patas no chao, recebe valor: sentido de rotacao, para sincronizar
  if(sentido == 0) {                    //Se sentido for 0, sincroniza as patas para tras do robo

      //Sincronizar Motor 1:  
      if(!digitalRead(sensorA)){    //Se o sensor B, localizado na porta 3, estiver ativado
        giro ( 1, 'p');
      } else {                      //Se não
          do{                       //Executa uma vez o que estiver dentro de "do"
            giro ( 1, 'f');
          }while(digitalRead(sensorA));//Enquanto sensor B estiver desativado ele executa "do"
          if(!digitalRead(sensorA)){//Se o sensor B, localizado na porta 3, estiver ativado
            giro ( 1, 'p');
          }                         //
      }                             //

      //Sincronizar Motor 5:
      if(!digitalRead(sensorE)){
        giro ( 5, 'p');
      } else {
          do{
            giro ( 5, 'f');
          } while(digitalRead(sensorE));
          if(!digitalRead(sensorE)){
            giro ( 5, 'p');          
          }
      }

      //Sincronizar Motor 6:
      if(!digitalRead(sensorF)){
        giro ( 6, 'p');
      } else {
          do{
            giro ( 6, 'f');
          }while(digitalRead(sensorF));
          if(!digitalRead(sensorF)){
            giro ( 6, 'p');
          }
      }
      
      //Sincronizar Motor 3:
      if(!digitalRead(sensorC)){    //Se o sensor C, localizado na porta 4, estiver ativado
        giro ( 3, 'p');
      } else {                      //Se não
          do{                       //Executa uma vez o que estiver dentro de "do"
            giro ( 3, 'f');
          }while(digitalRead(sensorC));//Enquanto sensor B estiver desativado ele executa "do"
          if(!digitalRead(sensorC)){//Se o sensor C, localizado na porta 4, estiver ativado
            giro ( 3, 'p');
          }                         //
      }                             //

      
    //Sincronizar Motor 2:
      if(!digitalRead(sensorB)){
        giro ( 2, 'p');
      } else {
          do{
            giro ( 2, 'f');
          }while(digitalRead(sensorB));
          if(!digitalRead(sensorB)){
            giro ( 2, 'p');
          }
      }

    //Sincronizar Motor 4:               
      if(!digitalRead(sensorD)){    //Se o sensor A, localizado na porta 2, estiver ativado
        giro ( 4, 'p');
      } else {                      //Se não
          do {                      //Executa uma vez o que estiver dentro de "do"
            giro ( 4, 'f'); 
          } while(digitalRead(sensorD));//Enquanto sensor A estiver desativado ele executa "do"
          if(!digitalRead(sensorD)){//Se o sensor A, localizado na porta 2, estiver ativado
            giro ( 4, 'p');
          }                         //
      }                             //
      giro(1, 't');
      giro(2, 't');
      //giro(3, 't');
      giro(4, 't');
      giro(5, 't');
      giro(6, 't');
      delay(25);
      giro(4, 'p');
      giro(5, 'p');
      giro(6, 'p');
      delay(25);
      giro(1, 'p');
      giro(2, 'p');
      giro(3, 'p');
  }


  /*
  if(sentido == 1) {                    //Se sentido for 1, sincroniza as patas para direita do robo


    //Sincronizar Motor 2:
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


      //Sincronizar Motor 5:
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


      //Sincronizar Motor 6:
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


      //Sincronizar Motor 3:
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


      
    //Sincronizar Motor 1:
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

      
      
    //Sincronizar Motor 4:
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
  }//end if
  
  if(sentido == 3) {                    //Se sentido for 0, sincroniza as patas para esquerda do robo


    //Sincronizar Motor 2:
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


      //Sincronizar Motor 5:
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


      //Sincronizar Motor 6:
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



  //Sincronizar Motor 3:
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



    //Sincronizar Motor 1:
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


      
    //Sincronizar Motor 4:
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
  }//end if
  */
}//end void parado

/*
int graus(int x) { //Funçao 'graus' que recebe um valor Inteiro armazenado em 'x'                                                            
  int graus = x; //Variavel inteira 'graus' recebe o valor de 'x'
  graus = map(graus, 0, 180, SERVOMIN, SERVOMAX); //Regra de 3, para converter graus no valor do PWM
  
  return graus; //Retorna como resultado da funcao, o valor da variavel 'graus'
}
*/

void front_auto(){
  int distancia = lerSonar(); // Ler o sensor de distancia  
    if (distancia > distanciaObstaculo) {  // Se a distancia for maior que 20 cm  
      rotacao_Frente(); //robo anda para frente   
    }else{   
    rotacao_Parado();  //para o robo  
    posicionaCarroMelhorCaminho(); //calcula o melhor caminho    
    front_auto();    
    }
}

// Funcao para ler e calcular a distancia do sensor ultrassonico    
int lerSonar(){    
  digitalWrite(trigPin, LOW); //nao envia som
    delayMicroseconds(2);
  digitalWrite(trigPin,HIGH); //envia som 
    delayMicroseconds(10);
  digitalWrite(trigPin,LOW); //nao envia o som e espera o retorno do som enviado
      duracao = pulseIn(echoPin,HIGH); //Captura a duracao em tempo do retorno do som.
      distancia_cm = duracao/56; //Calcula a distancia
  delay(30);  
return distancia_cm;             // Retorna a distancia  
}
   
// Funcao para calcular a distancia do centro    
int calcularDistanciaCentro(){    
  parado(0);    
    delay(20);   
  int leituraDoSonar = lerSonar();// Ler sensor de distância  
    delay(500);   
  leituraDoSonar = lerSonar();   
    delay(500);   
return leituraDoSonar;// Retorna a distancia  
}
    
// Funcao para calcular a distancia da direita    
int calcularDistanciaDireita(){    
  right();   
   delay(200);  
  int leituraDoSonar = lerSonar();   
    delay(500);   
  leituraDoSonar = lerSonar();   
    delay(500);   
return leituraDoSonar;    
}
    
// Funcao para calcular a distancia da esquerda    
int calcularDistanciaEsquerda(){    
  left();   
    delay(200);  
  int leituraDoSonar = lerSonar();   
    delay(500);   
  leituraDoSonar = lerSonar();   
    delay(500);   
return leituraDoSonar;    
}
    
// Funcao para captar as distancias lidas e calcular a melhor distancia    
char calculaMelhorDistancia(){    
  int esquerda = calcularDistanciaEsquerda();    
  int centro = calcularDistanciaCentro();    
  int direita = calcularDistanciaDireita();    
    reposicionaServoSonar();    
  int maiorDistancia = 0;   
  char melhorDistancia = '0';     
    if (centro > direita && centro > esquerda){    
      melhorDistancia = 'c';    
      maiorDistancia = centro;    
    }else   
    if (direita > centro && direita > esquerda){    
      melhorDistancia = 'd';    
      maiorDistancia = direita;    
    }else  
    if (esquerda > centro && esquerda > direita){    
      melhorDistancia = 'e';    
      maiorDistancia = esquerda;    
    }    
    if (maiorDistancia <= distanciaObstaculo) { //distancia limite para parar o robo   
      rotacao_Re();    
      posicionaCarroMelhorCaminho();    
    }    
    reposicionaServoSonar();  
return melhorDistancia;    
} 
   
// Funcao para colocar o carrinho na melhor distancia    
void posicionaCarroMelhorCaminho(){    
  char melhorDist = calculaMelhorDistancia();     
  if (melhorDist == 'c'){    
    front_auto();    
  }else if (melhorDist == 'd'){    
    rotacao_Direita();    
  }else if (melhorDist == 'e'){    
    rotacao_Esquerda();     
  }else{    
    rotacao_Re();    
  }    
  reposicionaServoSonar();    
} 
   
// Funcao para deixar o sensor do robo no centro    
void reposicionaServoSonar(){
  parado(0);   
  delay(200);   
}    

// Funcao para fazer o robo parar    
void rotacao_Parado(){    
  parado(0); 
}    
// Funcao para fazer o robo andar para frente    
void rotacao_Frente(){    
  front();    
}    
// Funcao que faz o robo andar para tras    
void rotacao_Re(){
    back();
}    
    
void rotacao_Direita(){
  right();    
}    
// Função que faz o robô virar à esquerda    
void rotacao_Esquerda(){    
  left();
} 
