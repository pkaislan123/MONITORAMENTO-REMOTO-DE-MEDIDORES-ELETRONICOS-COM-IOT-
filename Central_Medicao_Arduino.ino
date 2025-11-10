#include <SoftwareSerial.h>



int pinMedidores[4] = {2, 3, 4, 5};
int pinBotoes[4] = {6, 7, 8, 9};

const int INTERVALO_PULSO = 500;

#define rxPin 11
#define txPin 12
SoftwareSerial nodemcu(rxPin, txPin);


long unsigned int tempo_msg = millis();



void setup() {

  Serial.begin(115200);
  delay(500);

  nodemcu.begin(38400);


  for (int i = 0; i <= 3; i++) {
    pinMode(pinMedidores[i], INPUT_PULLUP);
    pinMode(pinBotoes[i], INPUT_PULLUP);
  }

}

void loop() {


  verificaPulsos();
  verificaBotoes();

/*
  if (millis() - tempo_msg > 2000) {
    nodemcu.println("Enviado para o nodemcu");

    tempo_msg =  millis();
  }

*/
   
}


void verificaPulsos() {

  for (int i = 0; i <= 3 ; i++) {
    //Verifica se o sensor foi a 0v
    if (digitalRead(pinMedidores[i]) == 0) {
      Serial.println("Contador incrementado ");
      //funcao que soma os pulsos
      Serial.println("Informando o servidor ");
      int canal = i + 1;
      String dados = "@1$";
      String sCanal = String(canal);

      dados.concat(sCanal);
      dados.concat("#");
      nodemcu.println(dados); 
      delay(INTERVALO_PULSO); //Intervalo de duração do pulso
    }
  }

}


void verificaBotoes() {

  for (int i = 0; i <= 3 ; i++) {
    //Verifica se o sensor foi a 0v
    if (digitalRead(pinBotoes[i]) == 0) {
      Serial.println("Botao stop pressionado");
      Serial.print("Informando o servidor");
      int canal = i + 1;
      String dados = "@2$";
      String sCanal = String(canal);

      dados.concat(sCanal);
      dados.concat("#");
      nodemcu.println(dados); 
      delay(3000); //debounce do botao
    }
  }

}
