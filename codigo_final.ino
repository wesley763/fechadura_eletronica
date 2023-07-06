#include <DHT.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27,20,4);  // set the LCD address to 0x27 for a 16 chars and 2 line display
#include <Wire.h>//Biblioteca do display LCD
#define TEMPO_ATUALIZACAO 5000

//Variávieis auxiliares
int porta_rele=3;                                                       //Porta digital que o relé está plugado
float temperatura;                                                        //Variável que armazena a temperatura em cada loop
float umidade;                                                            //Variável que armazena a umidade em cada loop

/**PARÂMENTROS DO SENSOR DE TEMPERATURA**/
DHT dht(A0, DHT11);
// SCL -> A5 arduíno NANO
// SDA -> A4 arduíno NANO

void setup() {
  pinMode(porta_rele, OUTPUT);
  digitalWrite(porta_rele,0);
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();                                                    
  dht.begin();  //Inicialização do Sensor de Umidade e Temperatura  
}
  

void loop() {
  temperatura = dht.readTemperature();     //Armazenando a temperatura do loop atual
  umidade = dht.readHumidity();           //Armazenando a umidade do loop atual
  
  //configuração do Display
  lcd.clear();   //Apaga o conteúdo exibido no display
  lcd.setCursor(0, 0);     //posiciona o cursor na coordenada especificada
  lcd.print("TEMP=");     //exibir no LCD
  lcd.print(temperatura,1);  //exibir no LCD (Valor da temperatura)
  lcd.print("C");       
  lcd.setCursor(0, 1);          //posiciona o cursor na coordenada especificada
  lcd.print("UMID=");          //exibir no LCD
  lcd.print(umidade,0);       //exibir no LCD (Valor da umidade)
  lcd.print("%");
  
//Acionamento e desacionamento do relé
  if (umidade>=60) {
    digitalWrite(porta_rele, 0);   //Comando que liga a porta do relé
  }else{
    digitalWrite(porta_rele, 1);   //Comando que desliga a porta do relé
  }

//teste do DHT
  Serial.print("Temperatura: ");
  Serial.println(temperatura);
  Serial.print("Umidade: ");
  Serial.println(umidade);  

  delay(TEMPO_ATUALIZACAO);                                              //Tempo de atualização do Loop

}
