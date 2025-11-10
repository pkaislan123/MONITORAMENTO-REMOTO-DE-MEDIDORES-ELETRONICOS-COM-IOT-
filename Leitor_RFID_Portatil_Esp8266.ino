#include <Wire.h>
#include <LiquidCrystal_I2C.h>
#include <ESP8266WebServer.h>
#include <EEPROM.h>
#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>
#include <SoftwareSerial.h>
#include <MFRC522.h>
#include <SPI.h>
#include <ArduinoJson.h>
#include "Medidor.h"


#define IP_MANUAL false
#define MANUAL_IP_ADDRESS IPAddress(192, 168, 18, 10)  // Endereço IP manual
#define MANUAL_IP_GATEWAY IPAddress(192, 168, 18, 1)    // Gateway manual
#define MANUAL_IP_SUBNET IPAddress(255, 255, 255, 0)   // Máscara de sub-rede manual
WiFiClient wifiClient;
HTTPClient http;


#define seletor A0
#define botao D3


LiquidCrystal_I2C lcd(0x27, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);



const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
  <meta http-equiv="Content-Type" content="text/html; charset=utf-8">
  <title>HTML Form ESP8266 - TITANIWM</title>
  <style>
    body {color: #434343; font-family: "Helvetica Neue",Helvetica,Arial,sans-serif; font-size: 14px; background-color: #eeeeee; margin-top: 100px;}
    .container {margin: 0 auto; max-width: 400px; padding: 30px; box-shadow: 0 10px 20px rgba(0,0,0,0.19), 0 6px 6px rgba(0,0,0,0.23); background-color: #ffffff; border-radius: 10px;}
  h2 {text-align: center; margin-bottom: 20px; margin-top: 0px; color: #0ee6b1; font-size: 35px;}
  #titleGreen {color: #00E1AA;}
  #titleBlack {color: #000000;}
    h3 {text-align: center; margin-bottom: 40px; margin-top: 0px; color: #336859; font-size: 35px;}
    form .field-group {box-sizing: border-box; clear: both; padding: 4px 0; position: relative; margin: 1px 0; width: 100%;}
    .text-field {font-size: 15px; margin-bottom: 4%; -webkit-appearance: none; display: block; background: #fafafa; color: #636363; width: 100%; padding: 15px 0px 15px 0px; text-indent: 10px; border-radius: 5px; border: 1px solid #e6e6e6; background-color: transparent;}
    .text-field:focus {border-color: #00bcd4; outline: 0;}
    .button-container {box-sizing: border-box; clear: both; margin: 1px 0 0; padding: 4px 0; position: relative; width: 100%;}
    .button {background: #00E1AA; border: none; border-radius: 5px; color: #ffffff; cursor: pointer; display: block; font-weight: bold; font-size: 16px; padding: 15px 0; text-align: center; text-transform: uppercase; width: 100%; -webkit-transition: background 250ms ease; -moz-transition: background 250ms ease; -o-transition: background 250ms ease; transition: background 250ms ease;}
    p {text-align: center; text-decoration: none; color: #87c1d3; font-size: 18px;}
    a {text-decoration: none; color: #ffffff; margin-top: 0%;}
    #status {text-align: center; text-decoration: none; color: #336859; font-size: 14px;}
  </style>
  <script>
  function validateForm() {
    var ssid = document.forms["myForm"]["ssid"].value;
    var password = document.forms["myForm"]["password"].value;
    var status = document.getElementById("statusDiv");
    if (ssid == "" && password == "") {
    status.innerHTML = "<p id='status' style='color:red;'>Insira SSID e senha.</p>";
    return false;
    }
    else if (ssid == "") {
    status.innerHTML = "<p id='status' style='color:red;'>Insira SSID.</p>";
    return false;
    }
    else if (password == "") {
    status.innerHTML = "<p id='status' style='color:red;'>Insira senha.</p>";
    return false;
    }
    else {
    status.innerHTML = "<p id='status'>Conectando...</p>";
    return true;
    }
  }
  </script>
</head>
<body>
<div class="container">
  <h2><span id="titleBlack">TITANIWM</span></h2>
  <h3>Conexão ESP8266</h3>
  <form name="myForm" action="/action_new_connection" onsubmit="return validateForm()" method="post">
    <div class="field-group">
  <select class='text-field' name='ssid'></select>
    </div>
    <br>
    <div class="field-group">
    <input class="text-field" type="password" name="password" length=64 placeholder="Password">
    </div>
  <br>
  <div id="statusDiv">
    <br><br>
  </div>
    <div class="button-container">
    <input class="button" type="submit" value="Conectar">
    </div>
  </form>
  <p>OU</p>
  <div class="button-container">
    <button class="button" type="button" onclick="window.location.href='/action_previous_connection'">Conectar à última rede utilizada</button>
  </div>
</div>
</body>
</html>
)=====";

const char *ssid = "PROJETO GUSTAVO RFID"; // Nome da rede WiFi que será criada
const char *password = "gustavo2023";   // Senha para se conectar nesta rede
ESP8266WebServer server(80); //Server utiliza a porta 80

boolean executando = false;
boolean msg_ocioso = true;
long unsigned int tempo_led = millis();


//String BASE_URL = "http://10.0.0.105:11050/";

String BASE_URL = "http://162.240.226.254/apileite/";
String path_listar_medidores = "v1/medidores/listartodos";
String path_buscar_animal_por_uid = "v1/animais/platform/buscarporuid/";
String path_iniciar_sessao = "v1/sessoes/platform/inserir/";


long unsigned int tempo_executando = millis();


#define SS_PIN D8
#define RST_PIN D0

MFRC522 rfid(SS_PIN, RST_PIN);


Medidor medidores[10]; 
int tam_medidores = 0;


int etapa = -1;
//-1 ocioso
//0 selecao de medidor
//1 seleção de animal

struct Animal {
  String uid;
  int idanimal;
  String nome;
  int status_animal;
};


void setup() {

  Serial.begin(115200);

  lcd.begin (20, 4);

  pinMode(seletor, INPUT);
  pinMode(botao, INPUT_PULLUP);



  WiFi.softAP(ssid, password);
  Serial.print("Access Point \"");
  Serial.print(ssid);
  Serial.println("\" iniciado");

  Serial.print("IP address:\t");
  Serial.println(WiFi.softAPIP());

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("AP CONECTADO");
      lcd.setCursor(0,1);
      lcd.print(WiFi.softAPIP());


  //Tratamento de rotas
  server.on("/", handleRoot);
  server.on("/action_new_connection", handleForm);
  server.on("/action_previous_connection", connectEeprom);

  server.begin();
  Serial.println("Servidor HTTP iniciado");

  connectEeprom();


  Serial.print(WiFi.localIP());


  pinMode(LED_BUILTIN, OUTPUT);
  digitalWrite(LED_BUILTIN, LOW);

    SPI.begin(); // Init SPI bus

  rfid.PCD_Init(); // Init MFRC522
  Serial.println();
  Serial.print(F("Reader :"));
  rfid.PCD_DumpVersionToSerial();

}

void loop() {

  if (msg_ocioso) {
    lcd.clear();
    lcd.setCursor(0, 0);
    lcd.print("    OCIOSO");
    lcd.setCursor(0, 1);
    lcd.print("   Aguardando..." );
    msg_ocioso = false;
  }


  piscarLed();


  server.handleClient();          //Trata requisições de clientes
  if (WiFi.status() != WL_CONNECTED) {
  }

  String uid = Leitura();

  if (uid != "" && !executando) {

    Serial.print("Tag lida: ");
    Serial.println(uid);

    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("TAG: ");
    lcd.setCursor(0,1);
    lcd.print(uid);

    delay(5000);

    msg_ocioso  = true;
  }


  if(!digitalRead(botao) && !executando){
    Serial.println("Botao pressionado!");
    buscarMedidores();
    executando = true;
    etapa = 0;
    tempo_executando = millis();
  }

  if(executando && etapa == 0){
      int valor_lido = analogRead(seletor);
      Serial.print("Valor analogico: ");
      Serial.println(valor_lido);
      imprimirMedidorComBaseNoValor(valor_lido);
  }

  if(executando && etapa == 0 && !digitalRead(botao) ){
    //avancar etapa
      int valor_lido = analogRead(seletor);
      Medidor medidorSelecionado = medidores[ mapearValorParaMedidor(valor_lido)];
    if(medidorSelecionado.getStatus() == 1){
      //ocupado
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Medidor Ocupado");
        lcd.setCursor(0,1);
        lcd.print("Selecione Outro");
        delay(5000);
    }else{
    etapa = 1;
    }
  }


  if(etapa == 1 && executando){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Leia a TAG");
  }

  if(etapa == 1 && executando && uid != ""){
    //TAG liga, buscar por tag
     Animal animal = buscarTag(uid);
       if(animal.idanimal > 0 && animal.status_animal == 0){
         lcd.clear();
         lcd.setCursor(0,0);
         lcd.print("Animal: " + animal.nome);
         lcd.setCursor(0,1);
         lcd.print("Confirme: ");

         while(digitalRead(botao)){
          delay(100);
         }

         int valor_lido = analogRead(seletor);
         Medidor medidorSelecionado = medidores[ mapearValorParaMedidor(valor_lido)];
         
         iniciarSessao(medidorSelecionado.getId(),  animal.idanimal);
     
         lcd.clear();
         lcd.setCursor(0,0);
         lcd.print("Inicie a Tarefa");
       
         delay(5000);

          etapa = -1;
  executando = false;
  msg_ocioso = true;

  
       }
       else if(animal.idanimal > 0 && animal.status_animal == 1){
          lcd.clear();
         lcd.setCursor(0,0);
         lcd.print("Ocupado");
         lcd.setCursor(0,1);
         lcd.print("Selecione Outro");
  delay(5000);
       }
       
       else{
         Serial.println("Nenhum animal encontrado com essa TAG");
         lcd.clear();
         lcd.setCursor(0,0);
         lcd.print("Nao encontrado!");
         lcd.setCursor(0,1);
         lcd.print("Reiniciando...");
         delay(5000);
       }
     
  }


 if(millis() - tempo_executando > 30000 && executando){
  etapa = -1;
  executando = false;
  msg_ocioso = true;
 }
  

}




String Leitura()
{
  if ( ! rfid.PICC_IsNewCardPresent())    //ESCUTANDO LEITOR
  {
    return "";                                 //RETORNA SE nao DETECTOU ALGO
  }
  if ( ! rfid.PICC_ReadCardSerial())      //AQUI FAZ A LEITURA SERIADO DO TAG OU CARTÃO
  {
    return "";
  }
  //LIMPA O LCD
  String Codigo = "";                        //CRIAMOS UMA VARIÁVEL LOCAL PARA ARMAZENAR O CODIGO DOS TAGS OU CARTÃO
  for (byte i = 0; i < rfid.uid.size; i++) //LAÇO FOR PARA INCREMENTAR I COM O UID7
  {
    Codigo.concat(String(rfid.uid.uidByte[i] < 0x10 ? "" : "")); //CRIAR A STRING COM O CÓDIGO DA TAG OU CARTÃO
    Codigo.concat(String(rfid.uid.uidByte[i], DEC));                //CONVERTE PARA HEXA DECIMAL
    Codigo.toUpperCase();                                              //CONVERTE AS LETRAS DO HEXA PARA MAIÚSCULAS

  }
  Codigo.replace(" ", "");
  Serial.println(Codigo);
  return Codigo;

}

void piscarLed() {
  if (millis() - tempo_led > 1000) {
    digitalWrite(LED_BUILTIN, !digitalRead(LED_BUILTIN));

    tempo_led =  millis();
  }

}



void handleRoot() {
  String index = listSSID(); //Leia o conteúdo HTML
  server.send(200, "text/html", index); //Enviar pagina Web
}

void handleForm() {
  String ssidWifi = server.arg("ssid");
  String passwordWifi = server.arg("password");

  Serial.printf("SSID: %s\n", ssidWifi);
  Serial.printf("Password: %s\n", passwordWifi);

  if (!ssidWifi.equals("") && !passwordWifi.equals("")) {
    connectToWiFi(ssidWifi, passwordWifi);
  }
}

void connectToWiFi(String ssidWifi, String passwordWifi) {
  int count = 0;

  if (IP_MANUAL) {
    IPAddress manualIP(MANUAL_IP_ADDRESS);
    IPAddress manualGateway(MANUAL_IP_GATEWAY);
    IPAddress manualSubnet(MANUAL_IP_SUBNET);

    WiFi.config(manualIP, manualGateway, manualSubnet);  // Configuração do IP manual
  }



  WiFi.begin(ssidWifi.c_str(), passwordWifi.c_str());     //Conecta com seu roteador
  Serial.println("");

  //Espera por uma conexão
  while ( count < 40 ) {
    delay(500);
    Serial.print(".");
    if (WiFi.status() == WL_CONNECTED) {
      Serial.println("");
      salvarEeprom(ssidWifi, passwordWifi);
      Serial.println("");
      //Se a conexão ocorrer com sucesso, mostre o endereço IP no monitor serial
      Serial.println("Conectado ao WiFi");

    
      Serial.print("IP address: ");
      Serial.println(WiFi.localIP());  //Endereço IP do ESP8266

      lcd.clear();
      lcd.setCursor(0,0);
      lcd.print("WIFI CONECTADO");
      lcd.setCursor(0,1);
      lcd.print(WiFi.localIP());
      

      String responsePage = (const __FlashStringHelper*) MAIN_page; //Leia o conteúdo HTML
      responsePage.replace("<br><br>", "<p id='status'>Conectado!</p>");
      server.send(200, "text/html", responsePage);
      return;
    }
    else if (WiFi.status() == WL_CONNECT_FAILED) {
      String responsePage = (const __FlashStringHelper*) MAIN_page;
      responsePage.replace("<br><br>", "<p id='status' style='color:red;'>Falha na conexão.</p>");
      server.send(200, "text/html", responsePage);
    }
    count++;
  }
  Serial.println();
  Serial.println("Timed out.");
  String responsePage = (const __FlashStringHelper*) MAIN_page;
  responsePage.replace("<br><br>", "<p id='status' style='color:red;'>Erro.</p>");
  server.send(200, "text/html", responsePage);
  return;
}

String listSSID() {
  String index = (const __FlashStringHelper*) MAIN_page; //Leia o conteúdo HTML
  String networks = "";
  int n = WiFi.scanNetworks();
  Serial.println("Scan done.");
  if (n == 0) {
    Serial.println("Nenhuma rede encontrada.");
    index.replace("<select class='text-field' name='ssid'></select>", "<select class='text-field' name='ssid'><option value='' disabled selected>Nenhuma rede encontrada</option></select>");
    index.replace("<br><br>", "<p id='status' style='color:red;'>Rede não encontrada.</p>");
    return index;
  }
  else {
    Serial.printf("%d networks found.\n", n);
    networks += "<select class='text-field' name='ssid'><option value='' disabled selected>SSID</option>";
    for (int i = 0; i < n; ++i)
    {
      // Imprime o SSID de cada rede encontrada
      networks += "<option value='" + WiFi.SSID(i) + "'>" + WiFi.SSID(i) + "</option>";
    }
    networks += "</select>";
  }
  index.replace("<select class='text-field' name='ssid'></select>", networks);
  return index;
}

void salvarEeprom(String ssidWifi, String passwordWifi) {
  EEPROM.begin(98); // Tamanho da FLASH reservado para EEPROM. Pode ser de 4 a 4096 bytes

  if (!compareEeprom(ssidWifi, passwordWifi)) {
    Serial.println("Salvando:");
    EEPROM.write(0, ssidWifi.length());
    Serial.println(ssidWifi.length());

    for (int i = 2; i < 2 + ssidWifi.length(); i++) {
      Serial.print(ssidWifi.charAt(i - 2));
      EEPROM.write(i, ssidWifi.charAt(i - 2));
    }
    Serial.println("");

    Serial.println("Salvando:");
    EEPROM.write(1, passwordWifi.length());
    Serial.println(passwordWifi.length());

    for (int j = 2 + ssidWifi.length(); j < 2 + ssidWifi.length() + passwordWifi.length(); j++) {
      Serial.print(passwordWifi.charAt(j - 2 - ssidWifi.length()));
      EEPROM.write(j, passwordWifi.charAt(j - 2 - ssidWifi.length()));
    }
    Serial.println("");

    EEPROM.commit(); // Salva alterações na FLASH
  }
  EEPROM.end(); // Apaga a cópia da EEPROM salva na RAM
}

boolean compareEeprom(String ssidWifi, String passwordWifi) {
  int idLength = int(EEPROM.read(0)); // Tamanho do SSID armazenado (número de bytes)
  int passLength = int(EEPROM.read(1)); // Tamanho do Password armazenado (número de bytes)
  String id = "";
  String pass = "";

  Serial.println("Lendo SSID:");
  Serial.print("Tamanho:");
  Serial.println(idLength);
  for (int i = 2; i < 2 + idLength; i++) {
    Serial.print("Posição ");
    Serial.print(i);
    Serial.print(": ");
    id = id + char(EEPROM.read(i));
    Serial.println(id[i - 2]);
  }
  Serial.println("");

  Serial.println("Lendo senha:");
  Serial.print("Tamanho:");
  Serial.println(passLength);
  for (int j = 2 + idLength; j < 2 + idLength + passLength; j++) {
    Serial.print("Posição ");
    Serial.print(j);
    Serial.print(": ");
    pass = pass + char(EEPROM.read(j));
    Serial.println(pass[j - 2 - idLength]);
    Serial.println(pass);
  }
  Serial.println("");

  Serial.print("SSID é igual: ");
  Serial.println(id.equals(ssidWifi));

  Serial.print("Senha é igual: ");
  Serial.println(pass.equals(passwordWifi));

  if (id.equals(ssidWifi) && pass.equals(passwordWifi))
  {
    Serial.println("Dados já presentes na memória.");
    return true;
  }
  else
  {
    return false;
  }
}

void connectEeprom() {
  EEPROM.begin(98); // Tamanho da FLASH reservado para EEPROM. Pode ser de 4 a 4096 bytes

  int ssidSize = (int)EEPROM.read(0); // Tamanho do SSID armazenado (número de bytes)
  int passwordSize = (int)EEPROM.read(1); // Tamanho do Password armazenado (número de bytes)
  String ssidWifi = "";
  String passwordWifi = "";

  Serial.println("Lendo:");
  for (int i = 2; i < 2 + ssidSize; i++) {
    Serial.print(char(EEPROM.read(i)));
    ssidWifi.concat(char(EEPROM.read(i)));
  }
  Serial.println("");

  Serial.println("Lendo:");
  for (int j = 2 + ssidSize; j < 2 + ssidSize + passwordSize; j++) {
    Serial.print(char(EEPROM.read(j)));
    passwordWifi.concat(char(EEPROM.read(j)));
  }
  Serial.println("");

  EEPROM.end(); // Apaga a cópia da EEPROM salva na RAM

  Serial.println("Leu:");
  Serial.println(ssidWifi);
  Serial.println(passwordWifi);

  connectToWiFi(ssidWifi, passwordWifi);
}



void buscarMedidores() {

  Serial.println("Buscando acoes...");
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Buscando");
  lcd.setCursor(0,1);
  lcd.print("Aguarde...");

  http.begin(wifiClient, BASE_URL + path_listar_medidores);
  http.addHeader("content-type", "application/json");

int httpCode = http.GET();
  if (httpCode < 0) {
    Serial.println("Erro na requisição - " + String(httpCode));

     lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Erro...");

     
    return;
  }
  if (httpCode != HTTP_CODE_OK) {
    Serial.println("Erro na requisição - " + String(httpCode));

     lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Erro...");

    return ;
    
  }
  
  String response = http.getString();
  http.end();
  
  Serial.print("Medidores Recebidos: ");
  Serial.println(response);

  // Criar um documento JSON para analisar a resposta
  DynamicJsonDocument doc(1024);
  deserializeJson(doc, response);


  int indice = 0;
  JsonArray jsonArray = doc.as<JsonArray>();
  for (JsonObject obj : jsonArray) {
    int id = obj["id_medidor"];
    String descricao = obj["descricao"];
    int status_medidor = obj["status"];

    Medidor novoMedidor(id, descricao,status_medidor);
    medidores[indice] = novoMedidor;
    indice++;


  }

  tam_medidores = indice;
  
  Serial.println("Medidores: ");
  for(int j = 0; j < tam_medidores; j++){
    Serial.print("ID: ");
    Serial.print(medidores[j].getId());
    Serial.print(" | Descrição: ");
    Serial.println(medidores[j].getDescricao());
  }

   

}


int mapearValorParaMedidor(int valorLido) {
  int valor_intervalo = 1024 / tam_medidores;

  //1024/4=256
  int indice = valorLido / valor_intervalo;//
  //900/256= 3
  return constrain(indice, 0, tam_medidores);
}



void imprimirMedidorComBaseNoValor(int valorLido) {
  int indiceMedidor = mapearValorParaMedidor(valorLido);
  Serial.print("Indice a apresentar: ");
  Serial.println(indiceMedidor);
  Medidor medidorSelecionado = medidores[indiceMedidor];
  
  lcd.clear();
  lcd.setCursor(0, 0);

  Serial.print("ID : ");
  Serial.println(medidorSelecionado.getId()); 
  lcd.print("     ID: " + String(medidorSelecionado.getId() ) );
  lcd.setCursor(0, 1);
  lcd.print("<- " + medidorSelecionado.getDescricao()  + " ->");
  delay(200);
}



Animal buscarTag( String uid) {

  Serial.println("Buscar Animal por Uid");

  http.begin(wifiClient, BASE_URL + path_buscar_animal_por_uid + "/" + uid);
  http.addHeader("content-type", "application/json");


  int httpCode = http.GET();
  if (httpCode < 0) {
    Serial.println("request error - " + httpCode);
    return Animal(); 
  }
  if (httpCode != HTTP_CODE_OK) {
    Serial.println("request error - " + httpCode);
    return Animal(); 
  }
  
  String response = http.getString();
  Serial.print("Resposta da API: ");
  Serial.println(response);
  http.end();

  Animal animal;

  // Deserializar a resposta JSON
  DynamicJsonDocument jsonBuffer(1024); // Tamanho adequado ao seu JSON
  DeserializationError jsonError = deserializeJson(jsonBuffer, response);

  if (jsonError) {
    Serial.println("JSON parsing error");
    return Animal(); // Retorna um objeto Animal vazio em caso de erro de parsing JSON
  }

  // Preencher o objeto Animal com os dados do JSON
  animal.uid = jsonBuffer["uid"].as<String>();
  animal.idanimal = jsonBuffer["idanimal"].as<int>();
  animal.nome = jsonBuffer["nome"].as<String>();
  animal.status_animal = jsonBuffer["status"].as<int>();

  Serial.println("Feito");
  
  return animal;


}


String iniciarSessao(int id_medidor, int id_animal) {

  Serial.println("Iniciar sessao");

  http.begin(wifiClient, BASE_URL + path_iniciar_sessao  + id_medidor + "/" + id_animal );
  http.addHeader("content-type", "application/json");


  int httpCode = http.GET();
  if (httpCode < 0) {
    Serial.println("request error - " + httpCode);
    return "request error - " + httpCode;
  }
  if (httpCode != HTTP_CODE_OK) {
    Serial.println("request error - " + httpCode);
    return "";
  }
  String response =  http.getString();
  Serial.print("Responda da api: ");
  Serial.println(response);
  http.end();

  Serial.println("Feito");


  return response;
}
