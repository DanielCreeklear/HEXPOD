/* ------------- CONTROLE HEXPOD VERSÃO 0.2 ------------- 
 *  Desenvolvedores: Daniel Lopes
 *  ETEC Martin Luther King
 *  São Paulo(SP), Brasil - 2019
 *  Contatos: ddanielssoares@gmail.com
 *  
 */

#include <SoftwareSerial.h>                                               //Biblioteca do Serial Emulado
 
#define X     A0                                                          //Analógico horizontal(X)
#define Y     A1                                                          //Analógico vertical(Y)
#define K      8                                                          //Botão K
#define F      7                                                          //Botão F
#define E      6                                                          //Botão E
#define G      5                                                          //Botão G
#define C      4                                                          //Botão C
#define B      3                                                          //Botão B
#define Z      2                                                          //Botão Z

SoftwareSerial BT_MasterHC05(11, 12);                                    //Declarando nome da serial emulada com RX = 11 / TX  = 12

                                                               
                                                            

void setup() {
  Serial.begin (9600);                                                  //Iniciando comunicação Serial para o USB em 9600               
  BT_MasterHC05.begin(9600);                                             //Iniciando comunicação Serial("BT_MasterHC05") para o módulo HC-06 em 9600

  pinMode(X , INPUT);                                                    //A0 entrada analógica
  pinMode(Y , INPUT);                                                    //A1 entrada analógica
  for(int i = 2; i<9; i++) pinMode(i , INPUT_PULLUP);                    //Portas 2 - 8 como entradas com resistor Pullup
  

}

void loop() {    
  int x_read = analogRead(X);                                        //Armazena o valor do Eixo X (0 - 1024)
  int y_read = analogRead(Y);                                        //Armazena o valor do Eixo Y (0 - 1024)

    if ( x_read < 350 && y_read > 200 && y_read < 800) {             //Se Analógico for para esquerda com o eixo Y sem se mover
      char sendBT;                                                   //Variável em caractere para armezenar valores ENVIADOS via Bluetooth                                 
      sendBT = 'A';                                                 //Valor a ser armazenado pela variável 'sendBT'                            
      BT_MasterHC05.write(sendBT);                                  //Envia o que está escrito em 'sendBT'
      Serial.println(sendBT);
    }
    if ( x_read > 650 && y_read > 200 && y_read < 800) {             //Se Analógico for para direita com o eixo Y sem se mover
      char sendBT;                                                   //Variável em caractere para armezenar valores ENVIADOS via Bluetooth                                 
      sendBT = 'D';                                                 //Valor a ser armazenado pela variável 'sendBT'                            
      BT_MasterHC05.write(sendBT);                                  //Envia o que está escrito em 'sendBT'
      Serial.println(sendBT);
    }
    if ( y_read < 350 && x_read > 200 && x_read < 800) {             //Se Analógico for para cima com o eixo X sem se mover
      char sendBT;                                                   //Variável em caractere para armezenar valores ENVIADOS via Bluetooth                                 
      sendBT = 'S';                                                 //Valor a ser armazenado pela variável 'sendBT'                            
      BT_MasterHC05.write(sendBT);                                  //Envia o que está escrito em 'sendBT'
      Serial.println(sendBT);
    }
    if ( y_read > 650 && x_read > 200 && x_read < 800) {             //Se Analógico for para baixo com o eixo X sem se mover
      char sendBT;                                                   //Variável em caractere para armezenar valores ENVIADOS via Bluetooth                                 
      sendBT = 'W';                                                 //Valor a ser armazenado pela variável 'sendBT'                            
      BT_MasterHC05.write(sendBT);                                  //Envia o que está escrito em 'sendBT'
      Serial.println(sendBT);
    }
  
      while (!digitalRead(K)) {                                    //Enquanto o botão for pressionado
         char sendBT;                                                   //Variável em caractere para armezenar valores ENVIADOS via Bluetooth                                 
         sendBT = 'K';                                                 //Valor a ser armazenado pela variável 'sendBT'                            
         BT_MasterHC05.write(sendBT);                                  //Envia o que está escrito em 'sendBT'
         Serial.println(sendBT);
      }
      while (!digitalRead(F)) {                                    //Enquanto o botão for pressionado
         char sendBT;                                                   //Variável em caractere para armezenar valores ENVIADOS via Bluetooth                                 
         sendBT = 'F';                                                 //Valor a ser armazenado pela variável 'sendBT'                            
         BT_MasterHC05.write(sendBT);                                  //Envia o que está escrito em 'sendBT'
         Serial.println(sendBT);
      }
      while (!digitalRead(E)) {                                    //Enquanto o botão for pressionado
         char sendBT;                                                   //Variável em caractere para armezenar valores ENVIADOS via Bluetooth                                 
         sendBT = 'E';                                                 //Valor a ser armazenado pela variável 'sendBT'                            
         BT_MasterHC05.write(sendBT);                                  //Envia o que está escrito em 'sendBT'
         Serial.println(sendBT);
      }
      while (!digitalRead(G)) {                                    //Enquanto o botão for pressionado
         char sendBT;                                                   //Variável em caractere para armezenar valores ENVIADOS via Bluetooth                                 
         sendBT = 'G';                                                 //Valor a ser armazenado pela variável 'sendBT'                            
         BT_MasterHC05.write(sendBT);                                  //Envia o que está escrito em 'sendBT'
         Serial.println(sendBT);
      }
      while (!digitalRead(C)) {                                    //Enquanto o botão for pressionado
         char sendBT;                                                   //Variável em caractere para armezenar valores ENVIADOS via Bluetooth                                 
         sendBT = 'C';                                                 //Valor a ser armazenado pela variável 'sendBT'                            
         BT_MasterHC05.write(sendBT);                                  //Envia o que está escrito em 'sendBT'
         Serial.println(sendBT);
      }
      while (!digitalRead(B)) {                                    //Enquanto o botão for pressionado
         char sendBT;                                                   //Variável em caractere para armezenar valores ENVIADOS via Bluetooth                                 
         sendBT = 'B';                                                 //Valor a ser armazenado pela variável 'sendBT'                            
         BT_MasterHC05.write(sendBT);                                  //Envia o que está escrito em 'sendBT'
         Serial.println(sendBT);
      }
      while (!digitalRead(Z)) {                                    //Enquanto o botão for pressionado
         char sendBT;                                                   //Variável em caractere para armezenar valores ENVIADOS via Bluetooth                                 
         sendBT = 'Z';                                                 //Valor a ser armazenado pela variável 'sendBT'                            
         BT_MasterHC05.write(sendBT);                                  //Envia o que está escrito em 'sendBT'
         Serial.println(sendBT);
      }
                                                                               
  delay(10);                                                          //Atraso para sincronia  
}
