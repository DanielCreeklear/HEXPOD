/* ------------- CONTROLE HEXPOD VERSÃO 0.4 ------------- 
 *  Desenvolvedores: Daniel Lopes
 *  ETEC Martin Luther King
 *  São Paulo(SP), Brasil - 2019
 *  Contatos: ddanielssoares@gmail.com
 *  
 */
#include <VirtualWire.h>
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
 
#define X     A0                                                          //Analógico horizontal(X)
#define Y     A1                                                          //Analógico vertical(Y)
#define K      8                                                          //Botão K
#define F      7                                                          //Botão F
#define E      6                                                          //Botão E
#define G      5                                                          //Botão G
#define C      4                                                          //Botão C
#define B      3                                                          //Botão B
#define Z      2                                                          //Botão Z
#define pinRF  12
#define pinLED 13

struct tipoPacote {
  char valor1;
};
tipoPacote pacote; 

//SoftwareSerial BT_MasterHC05(11, 12);                                    //Declarando nome da serial emulada com RX = 11 / TX  = 12
LiquidCrystal_I2C lcd(0x27,2,1,0,4,5,6,7,3, POSITIVE);

                                                               
                                                            

void setup() {
  vw_set_tx_pin(pinRF);
  vw_set_ptt_inverted(true);
  vw_setup(2000);
  pinMode(pinLED, OUTPUT);
  lcd.begin (16,2);
//Serial.begin (9600);                                                  //Iniciando comunicação Serial para o USB em 9600               
//BT_MasterHC05.begin(9600);                                             //Iniciando comunicação Serial("BT_MasterHC05") para o módulo HC-06 em 9600

  pinMode(X , INPUT);                                                    //A0 entrada analógica
  pinMode(Y , INPUT);                                                    //A1 entrada analógica
  for(int i = 2; i<9; i++) pinMode(i , INPUT_PULLUP);                    //Portas 2 - 8 como entradas com resistor Pullup

  lcd.setBacklight(HIGH);
  lcd.setCursor(0,0);
  lcd.print(" HEXPOD versão: ");
  lcd.setCursor(0,1);
  lcd.print("      2.33       ");
  delay(600);

}

void loop() {
  digitalWrite(pinLED, HIGH);     
  int x_read = analogRead(X);                                        //Armazena o valor do Eixo X (0 - 1024)
  int y_read = analogRead(Y);                                        //Armazena o valor do Eixo Y (0 - 1024)

  lcd.setCursor(0,0);
  lcd.print("Aperte um botão!");
  lcd.setCursor(0,1);
  lcd.print("----------------");

    if ( x_read < 350 && y_read > 200 && y_read < 800) {             //Se Analógico for para esquerda com o eixo Y sem se mover
      char sendBT;                                                   //Variável em caractere para armezenar valores ENVIADOS via Bluetooth                                 
      sendBT = 'A';                                                 //Valor a ser armazenado pela variável 'sendBT'
      pacote.valor1 = sendBT;
      vw_send((uint8_t *)&pacote, sizeof(pacote));
      vw_wait_tx();
      digitalWrite(pinLED, LOW);                             
    //BT_MasterHC05.write(sendBT);                                  //Envia o que está escrito em 'sendBT'
    //Serial.println(sendBT);
    //Serial.write(sendBT);
      lcd.setCursor(0,0);
      lcd.print("  Virando para  ");
      lcd.setCursor(0,1);
      lcd.print("    esquerda    ");
    }
    if ( x_read > 650 && y_read > 200 && y_read < 800) {             //Se Analógico for para direita com o eixo Y sem se mover
      char sendBT;                                                   //Variável em caractere para armezenar valores ENVIADOS via Bluetooth                                 
      sendBT = 'D';                                                 //Valor a ser armazenado pela variável 'sendBT'
      pacote.valor1 = sendBT;
      vw_send((uint8_t *)&pacote, sizeof(pacote));
      vw_wait_tx();
      digitalWrite(pinLED, LOW);                              
    //BT_MasterHC05.write(sendBT);                                  //Envia o que está escrito em 'sendBT'
    //Serial.println(sendBT);
    //Serial.write(sendBT);
      lcd.setCursor(0,0);
      lcd.print("  Virando para  ");
      lcd.setCursor(0,1);
      lcd.print("    direita     ");
    }
    if ( y_read < 350 && x_read > 200 && x_read < 800) {             //Se Analógico for para cima com o eixo X sem se mover
      char sendBT;                                                   //Variável em caractere para armezenar valores ENVIADOS via Bluetooth                                 
      sendBT = 'S';                                                 //Valor a ser armazenado pela variável 'sendBT'
      pacote.valor1 = sendBT;
      vw_send((uint8_t *)&pacote, sizeof(pacote));
      vw_wait_tx();
      digitalWrite(pinLED, LOW);                              
    //BT_MasterHC05.write(sendBT);                                  //Envia o que está escrito em 'sendBT'
    //Serial.println(sendBT);
    //Serial.write(sendBT);
      lcd.setCursor(0,0);
      lcd.print("  Virando para  ");
      lcd.setCursor(0,1);
      lcd.print("      trás      ");
    }
    if ( y_read > 650 && x_read > 200 && x_read < 800) {             //Se Analógico for para baixo com o eixo X sem se mover
      char sendBT;                                                   //Variável em caractere para armezenar valores ENVIADOS via Bluetooth                                 
      sendBT = 'W';                                                 //Valor a ser armazenado pela variável 'sendBT'
      pacote.valor1 = sendBT;
      vw_send((uint8_t *)&pacote, sizeof(pacote));
      vw_wait_tx();
      digitalWrite(pinLED, LOW);                              
    //BT_MasterHC05.write(sendBT);                                  //Envia o que está escrito em 'sendBT'
    //Serial.println(sendBT);
    //Serial.write(sendBT);
      lcd.print("  Andando para  ");
      lcd.setCursor(0,1);
      lcd.print("     frente     ");
    }
  
      if (!digitalRead(K)) {                                    //Enquanto o botão for pressionado
         char sendBT;                                                   //Variável em caractere para armezenar valores ENVIADOS via Bluetooth                                 
         sendBT = 'K';                                                 //Valor a ser armazenado pela variável 'sendBT'
         pacote.valor1 = sendBT;
         vw_send((uint8_t *)&pacote, sizeof(pacote));
         vw_wait_tx();
         digitalWrite(pinLED, LOW);                              
       //BT_MasterHC05.write(sendBT);                                  //Envia o que está escrito em 'sendBT'
       //Serial.println(sendBT);
       //Serial.write(sendBT);
      }
      if (!digitalRead(F)) {                                    //Enquanto o botão for pressionado
         char sendBT;                                                   //Variável em caractere para armezenar valores ENVIADOS via Bluetooth                                 
         sendBT = 'F';                                                 //Valor a ser armazenado pela variável 'sendBT'
         pacote.valor1 = sendBT;
         vw_send((uint8_t *)&pacote, sizeof(pacote));
         vw_wait_tx();
         digitalWrite(pinLED, LOW);                              
       //BT_MasterHC05.write(sendBT);                                  //Envia o que está escrito em 'sendBT'
       //Serial.println(sendBT);
       //Serial.write(sendBT);
      }
      if (!digitalRead(E)) {                                    //Enquanto o botão for pressionado
         char sendBT;                                                   //Variável em caractere para armezenar valores ENVIADOS via Bluetooth                                 
         sendBT = 'E';                                                 //Valor a ser armazenado pela variável 'sendBT'
         pacote.valor1 = sendBT;
         vw_send((uint8_t *)&pacote, sizeof(pacote));
         vw_wait_tx();
         digitalWrite(pinLED, LOW);                              
       //BT_MasterHC05.write(sendBT);                                  //Envia o que está escrito em 'sendBT'
       //Serial.println(sendBT);
       //Serial.write(sendBT);
      }
      if (!digitalRead(G)) {                                    //Enquanto o botão for pressionado
         char sendBT;                                                   //Variável em caractere para armezenar valores ENVIADOS via Bluetooth                                 
         sendBT = 'G';                                                 //Valor a ser armazenado pela variável 'sendBT'
         pacote.valor1 = sendBT;
         vw_send((uint8_t *)&pacote, sizeof(pacote));
         vw_wait_tx();
         digitalWrite(pinLED, LOW);                              
       //BT_MasterHC05.write(sendBT);                                  //Envia o que está escrito em 'sendBT'
       //Serial.println(sendBT);
       //Serial.write(sendBT);
      }
      if (!digitalRead(C)) {                                    //Enquanto o botão for pressionado
         char sendBT;                                                   //Variável em caractere para armezenar valores ENVIADOS via Bluetooth                                 
         sendBT = 'C';                                                 //Valor a ser armazenado pela variável 'sendBT'
         pacote.valor1 = sendBT;
         vw_send((uint8_t *)&pacote, sizeof(pacote));
         vw_wait_tx();
         digitalWrite(pinLED, LOW);                              
       //BT_MasterHC05.write(sendBT);                                  //Envia o que está escrito em 'sendBT'
       //Serial.println(sendBT);
       //Serial.write(sendBT);
      }
      if (!digitalRead(B)) {                                    //Enquanto o botão for pressionado
         char sendBT;                                                   //Variável em caractere para armezenar valores ENVIADOS via Bluetooth                                 
         sendBT = 'B';                                                 //Valor a ser armazenado pela variável 'sendBT'
         pacote.valor1 = sendBT;
         vw_send((uint8_t *)&pacote, sizeof(pacote));
         vw_wait_tx();
         digitalWrite(pinLED, LOW);                              
       //BT_MasterHC05.write(sendBT);                                  //Envia o que está escrito em 'sendBT'
       //Serial.println(sendBT);
       //Serial.write(sendBT);
      }
      if (!digitalRead(Z)) {                                    //Enquanto o botão for pressionado
         char sendBT;                                                   //Variável em caractere para armezenar valores ENVIADOS via Bluetooth                                 
         sendBT = 'Z';                                                 //Valor a ser armazenado pela variável 'sendBT'
         pacote.valor1 = sendBT;
         vw_send((uint8_t *)&pacote, sizeof(pacote));
         vw_wait_tx();
         digitalWrite(pinLED, LOW);                             
       //BT_MasterHC05.write(sendBT);                                  //Envia o que está escrito em 'sendBT'
       //Serial.println(sendBT);
       //Serial.write(sendBT);
      }
}
