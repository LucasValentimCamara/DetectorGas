//do_nivel_gas_mq2_buzzerArduino
#include <LiquidCrystal.h>

//declaracao de variáveis ambiente
LiquidCrystal lcd(13, 12, 5, 4, 3, 2);
int buzzer = 8;
int MQ = A0;
int padrao_sensor = 600;
const int led_vermelho = 7;
const int led_amarelo = 6;

void setup() {
  pinMode(MQ, INPUT);       //DEFINE O PINO COMO ENTRADA
  pinMode(buzzer, OUTPUT);  //DEFINE O PINO COMO SAÍDA
  pinMode(led_amarelo, OUTPUT);//DEFINE O PINO COMO SAÍDA
  pinMode(led_vermelho, OUTPUT);//DEFINE O PINO COMO SAÍDA
  Serial.begin(9600);       //INICIALIZA A SERIAL
  //analogReference(EXTERNAL);
  lcd.begin(16, 2);
  lcd.setCursor(0,0);
  lcd.print("Iniciando");
}

void loop() {
  int valor_analogico = analogRead(MQ);  //VARIÁVEL RECEBE O VALOR LIDO NO PINO ANALÓGICO
  Serial.print("Leitura: ");        //EXIBE O TEXTO NO MONITOR SERIAL
  Serial.println(valor_analogico);  // MOSTRA NO MONITOR SERIAL O VALOR LIDO DO PINO ANALÓGICO

  lcd.clear();  //limpa o display
  lcd.setCursor(0,0);//posiciona o cursor na coluna 3 e linha 0
  lcd.print("Medida: ");
  lcd.print(valor_analogico); //mostra o valor recebido pelo sensor
  lcd.print(" ppm");

  //Intervalo que a medida do sensor aumentou para mais da metade do padrão
  if (valor_analogico > (padrao_sensor/2) && valor_analogico < padrao_sensor) {{
      lcd.setCursor(0,1);
      lcd.print("Atencao"); //Alerta na tela LCD
      amarelo(); //Alerta sonoro e luminoso
    }
  } 
  else if (valor_analogico > padrao_sensor) { {
      lcd.setCursor(0,1);
      lcd.print("Perigo");//Alerta na tela LCD
      vermelho(); //Alerta sonoro e luminoso
    }
  } 
  //delisga todos alertas
  else {
    digitalWrite(led_amarelo, LOW);
    digitalWrite(led_vermelho, LOW);
    digitalWrite(buzzer, LOW);
  }
  delay(100); //Leitura do sensor a cada 0,1 segundo
}

//funcao para alerta amarelo, mais da metade do padrão
void amarelo() {
  tone(buzzer,1200); //Ré 6° Oitava
  digitalWrite(led_amarelo, HIGH);
  delay(1000); //intervalo de 1 segundo
  noTone(buzzer);
  digitalWrite(led_amarelo, LOW);
  delay(1000);
}

//funcao para alerta vermelho, mais do que padrão
void vermelho() {
  tone(buzzer,2400); //Ré 7° Oitava
  digitalWrite(led_vermelho, HIGH);
  delay(500); //intervalo de 0,5 segundo
  noTone(buzzer);
  digitalWrite(led_vermelho, LOW);
  delay(500);
}
