float seno;
int frequencia;
int pino = 2;
int SonarTrigger = 7;
int SonarEcho =6;
int distancia = 0;
int tempo = 0;
int LED1 = 5; 
int LED2 = 4;
int LED3 = 3;
int x = 0;

void setup ()
{
    pinMode(SonarTrigger, OUTPUT);
    pinMode(SonarEcho, INPUT);
    pinMode(pino, OUTPUT);
    Serial.begin(9600);

}
void loop ()
{

    digitalWrite(SonarTrigger, LOW);
    delayMicroseconds(2);
    digitalWrite(SonarTrigger, HIGH);
    delayMicroseconds(10);
    digitalWrite(SonarTrigger, LOW);

    tempo = pulseIn(SonarEcho, HIGH);
    distancia = tempo/58.2;

    if (distancia > 1 && distancia < 90){
        digitalWrite(LED1, LOW);
        digitalWrite(LED2, LOW);
        digitalWrite(LED3, HIGH);

        seno = (sin(x*3.1416/180));
        frequencia = 2000+ (int(seno* 1000));
        tone (pino, frequencia);
        delay (1);

        x++;
        if (x >= 180) x = 0;
        
    }else  if (distancia > 90 && distancia < 150){
        digitalWrite (LED1, LOW);
        digitalWrite (LED2, HIGH);
        digitalWrite (LED3, LOW);
        tone (pino, 550);
        delay (1);
        x = 0;

    }
    Serial.print("Distancia media:  ");
    Serial.print(distancia);
    Serial.println("cm");
  
 	delay(50);  

}

}