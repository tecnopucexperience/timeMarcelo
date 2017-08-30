//INPUT
const int LDR = A1; // pino de entrada do LDR
const int LM35 = 0; // Pino Entrada LM35

const int LEITURA_VOLTAGEM = A3;

//OUTPUT
const int pinLuz = 12;
const int pinQuente = 5;
const int pinFrio = 6;

//ATRIBUTES
int valor = 0;
int valorLido = 0;
float temperatura; // Variável que armazenará a temperatura medida

String inputString = "";         // a String to hold incoming data
boolean stringComplete = false;  // whether the string is complete

float somaTemp = 0;
int countTemp = 0;
float tempMedia;
const int countMediaTimes = 10;
float temperaturaMaxima = 24;
float luminosidadeMinima = 40;

float temperaturaAtual;
float luminosidadeAtual;

void setup() {
  Serial.begin(9600);
  Serial.println("Lendo valores a partir de um LDR");

  inputString.reserve(200);

  pinMode(pinLuz, OUTPUT);
  pinMode(pinQuente, OUTPUT);
  pinMode(pinFrio, OUTPUT);
}

  
void loop() {
 leituraLuminosidade();

 leituraTemperatura();

 leituraSerial();
 
 delay(2000);
}

void leituraInstrucao(){
      Serial.println(inputString);

      if(inputString.length() > 3){
         // Entrada == $1=[Valor]
        if(inputString.startsWith("$1=")){
           luminosidadeMinima = inputString.substring(3).toFloat();  
        }else if(inputString.startsWith("$2=")){
           temperaturaMaxima = inputString.substring(3).toFloat();  
        }
      }
      // clear the string:
      inputString = "";
}

void leituraSerial(){
   if (stringComplete) {
      Serial.println(inputString);
      // clear the string:
      inputString = "";
      stringComplete = false;
   }
}


void leituraLuminosidade(){
  valorLido = analogRead(LDR);
  valor = map(valorLido,0,1023,0,100);
 
  if(valor != luminosidadeAtual){
      if(valor >= luminosidadeMinima){
        digitalWrite(pinLuz, HIGH);
      }else{
        digitalWrite(pinLuz, LOW);
      }
     luminosidadeAtual = valor;

     Serial.print("Luminosidade: ");
    Serial.println(valor);
  }
}

void leituraTemperatura(){
  
   temperatura = (float(analogRead(LM35)) * 4.3 / (1023.0)) / 0.01; //Le o sinal enviado do sensor

   //Realiza uma media das leituras **Correção do hardware   
   somaTemp += temperatura; 
   countTemp++;
   tempMedia = somaTemp/countTemp;

   if( tempMedia != temperaturaAtual){

      temperaturaAtual = tempMedia;
    
      if(tempMedia >= temperaturaMaxima){
          digitalWrite(pinQuente, HIGH);
          digitalWrite(pinFrio, LOW);
       }
       else {
          digitalWrite(pinQuente, LOW);
          digitalWrite(pinFrio, HIGH);
       }
       
    
       if(countTemp >= countMediaTimes){
          somaTemp = somaTemp/countTemp;
          countTemp = 1;    
       }

       Serial.print("Media Temp: ");
       Serial.println(tempMedia);
   }
   
   
}

void serialEvent() {
  while (Serial.available()) {
    // get the new byte:
    char inChar = (char)Serial.read();
    Serial.print(inChar);
    // add it to the inputString:
    inputString += inChar;
    // if the incoming character is a newline, set a flag so the main loop can
    // do something about it:
    if (inChar == '13') {
      stringComplete = true;
    }
  }
}

