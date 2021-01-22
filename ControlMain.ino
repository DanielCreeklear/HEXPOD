/* ------------- CONTROLE HEXPOD VERSÃO 0.1 ------------- 
 *  Desenvolvedores: Daniel Lopes
 *  ETEC Martin Luther King
 *  São Paulo(SP), Brasil - 2019
 *  Contatos: ddanielssoares@gmail.com
 *  
 */

#include <SoftwareSerial.h>                                               //Biblioteca do Serial Emulado
#include <Servo.h>                                                       //Biblioteca de controle do servo motor

#define button 8                                                          //Pushbotton instalado no pino 8                                                           

SoftwareSerial BT_MasterHC05(11, 12);                                    //Declarando nome da serial emulada com RX = 11 / TX  = 12
Servo myservo;                                                          //Declarando nome da função que controlará o servo

                                                               
                                                            

void setup() {
  Serial.begin (9600);                                                  //Iniciando comunicação Serial para o USB em 9600               
  myservo.attach(9);                                                    //Pino 9 do servo motor
  BT_MasterHC05.begin(9600);                                             //Iniciando comunicação Serial("BT_MasterHC05") para o módulo HC-06 em 9600

  pinMode(button , INPUT_PULLUP);                                       //Declarando pino do pushbotton como entrada com resistor Pullup
  
       Serial.println("Controle HEXPODE  iniciado.");                  //Mensagem a ser impressa na inicialização do Arduino no monitor Serial
       Serial.println("Versão de teste: 1.0");

}

void loop() {                                                                                           
  
    if (BT_MasterHC05.available() > 0){                                   //Verifica se há caracteres para receber na Serial Emulada
      char msg;                                                           //Variável em caractere para armezenar valores RECEBIDOS via Bluetooth  
      msg = BT_MasterHC05.read();                                         //Valor(Leitura do bluetooth) a ser armazenado pela variável 'msg'  
        Serial.println(msg);                                            //imprime na Serial caso receba caracteres
        delay(10);
        if (msg == 'A') {
      Serial.println("Enviado e recebido");
    } else if (msg == 'P') {
      Serial.println("Conectado");
      delay(10);
      
    }
    }
    
  
      while (digitalRead(button) == 0) {                                //Enquanto o botão for pressionado
         Serial.println("Botão sendo pressionado");                     //Mensagem de aviso no monitor serial
         char sendBT;                                                   //Variável em caractere para armezenar valores ENVIADOS via Bluetooth                                 
         sendBT = 'A';                                                 //Valor a ser armazenado pela variável 'sendBT'                            
         BT_MasterHC05.write(sendBT);                                  //Envia o que está escrito em 'sendBT'
      }
                                                                               
  delay(10);                                                          //Atraso para sincronia  
}
