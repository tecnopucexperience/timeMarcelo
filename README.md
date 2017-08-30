# Automação Do dia a dia

![N|Solid](https://cdn.arduino.cc/homepage/images/arduino-UNO.png)

#### Links Uteis
[Arduino Site](https://www.arduino.cc/) - Site Oficial
[Referência da Linguagem](https://www.arduino.cc/en/Reference/HomePage)
[Referência Medição Temperatura](https://portal.vidadesilicio.com.br/lm35-medindo-temperatura-com-arduino/) - Portal vidadesilicio
[Referência Sensor de Luz](https://portal.vidadesilicio.com.br/sensor-de-luz-com-ldr/) - Portal vidadesilicio

#### Componentes Utilizados

- Arduino 
- Sensor LDR (Para Luminosidade);
- Sensor LM35 (Para Temperatura);
- Leds (Simular as funcionalidades);


#### Luminosidade

![N|Solid](https://portal.vidadesilicio.com.br/wp-content/uploads/2017/05/sensor-de-luz_bb1-1024x452.png)

Código básico:

    //Sensor de luz
    int ledPin = 7; //Led no pino 7
    int ldrPin = 0; //LDR no pino analígico 8
    int ldrValor = 0; //Valor lido do LDR
     
    void setup() {
     pinMode(ledPin,OUTPUT); //define a porta 7 como saída
     Serial.begin(9600); //Inicia a comunicação serial
    }
     
    void loop() {
     ///ler o valor do LDR
     ldrValor = analogRead(ldrPin); //O valor lido será entre 0 e 1023
     
     //se o valor lido for maior que 500, liga o led
     if (ldrValor>= 800) digitalWrite(ledPin,HIGH);
     // senão, apaga o led
     else digitalWrite(ledPin,LOW);
     
     //imprime o valor lido do LDR no monitor serial
     Serial.println(ldrValor);
     delay(100);
    }

#### Temperatura
    
Hardware:
![N|Solid](https://portal.vidadesilicio.com.br/wp-content/uploads/2017/03/lm35_bb.png)

Código básico:

    //Sensor de temperatura usando o LM35
     
    const int LM35 = A0; // Define o pino que lera a saída do LM35
    float temperatura; // Variável que armazenará a temperatura medida
     
    //Função que será executada uma vez quando ligar ou resetar o Arduino
    void setup() {
    Serial.begin(9600); // inicializa a comunicação serial
    }
     
    //Função que será executada continuamente
    void loop() {
    temperatura = (float(analogRead(LM35))*5/(1023))/0.01;
    Serial.print("Temperatura: ");
    Serial.println(temperatura);
    delay(2000);
    }
