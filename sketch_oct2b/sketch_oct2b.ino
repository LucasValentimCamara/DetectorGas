//do_nivel_gas_mq2_buzzerArduino
#include <LiquidCrystal.h>

LiquidCrystal lcd(13, 12, 5, 4, 3, 2);
int buzzer = 8;
int MQ = A0;
int padrao_sensor = 600;
const int led_vermelho = 7;
const int led_amarelo = 6;

void setup() {
  pinMode(MQ, INPUT);       //DEFINE O PINO COMO ENTRADA
  pinMode(buzzer, OUTPUT);  //DEFINE O PINO COMO SAÍDA
  pinMode(led_amarelo, OUTPUT);
  pinMode(led_vermelho, OUTPUT);
  Serial.begin(9600);       //INICIALIZA A SERIAL
  //analogReference(EXTERNAL);
  lcd.begin(16, 2);
  lcd.print("Iniciando");
}

void loop() {
  int valor_analogico = analogRead(MQ);  //VARIÁVEL RECEBE O VALOR LIDO NO PINO ANALÓGICO
  Serial.print("Leitura: ");        //EXIBE O TEXTO NO MONITOR SERIAL
  Serial.println(valor_analogico);  // MOSTRA NO MONITOR SERIAL O VALOR LIDO DO PINO ANALÓGICO

  lcd.clear();  //limpa o display
  lcd.setCursor(0,0);//posiciona o cursor na coluna 3 e linha 0
  lcd.print("Medida: ");
  lcd.print(valor_analogico);
  lcd.print(" ppm");

  if (valor_analogico > (padrao_sensor/2) && valor_analogico < padrao_sensor)
  {
      digitalWrite(buzzer, HIGH);
      digitalWrite(led_amarelo, HIGH);
      delay(1000);
      digitalWrite(buzzer, LOW);
      digitalWrite(led_amarelo, LOW);
      delay(1000);
  }
  if (valor_analogico >= padrao_sensor)
  {
      digitalWrite(buzzer, HIGH);
      digitalWrite(led_vermelho, HIGH);
      delay(500);
      digitalWrite(buzzer, LOW);
      digitalWrite(led_vermelho, LOW);
      delay(500);
  }
  else
  {
      digitalWrite(led_amarelo, LOW);
      digitalWrite(led_vermelho, LOW);
      digitalWrite(buzzer, LOW);
  }
  delay(100);  //INTERVALO DE 100 MILISSEGUNDOS

}
