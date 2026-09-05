float seno; // Armazena o valor do seno calculado para gerar a frequencia do tom
int frequencia; // Frequência (Hz) envia ao buzzer (Ssaida de som)
int pino = 2; // pino digital ligado ao buzzer (saida e som)
int SonarTrigger = 7; // Pino que envia o pulso ultrassônico (disparo do sensor)
int SonarEcho =6; // pino que recebe o eco (retorno do pulso)
int distancia = 0; // distancia calculada em cm
int tempo = 0; //  Tempo (em microsegundos) que o pulso levou para voltar
int LED1 = 5;  // led acesso quando objeto está longe (>150)
int LED2 = 4; // led acesso quando objeto está em distancia média (90 - 150cm )
int LED3 = 3; // led acesso quando objeto está pserto (1 - 90)
int x = 0; // contador que subistitui o for, avança 1 grau por chamada de loop ()

void setup ()
{
    pinMode(SonarTrigger, OUTPUT); // Trigger é saida: manda o pulso
    pinMode(SonarEcho, INPUT); // Echo é entrada: recebe o retorno do pulso
    pinMode(pino, OUTPUT); // Pino do buzzer configurado como saída
    Serial.begin(9600); // inicia comunicação serial para debug/ monitor

}
void loop ()
{

    digitalWrite(SonarTrigger, LOW); // Garante que o trigger comece em nivel baixo (estabiliza o sensor)
    delayMicroseconds(2); // Pequena espera para estabilizar o sinal
    digitalWrite(SonarTrigger, HIGH); // Envia pulso alto para dispar a medição
    delayMicroseconds(10); // Duração minima recomendada do pulso de disparo
    digitalWrite(SonarTrigger, LOW); // Encerra o pulso de disparo

    tempo = pulseIn(SonarEcho, HIGH); // Mede quanto tempo o pino Echo ficou em HIGH
    distancia = tempo/58.2; // Converte tempo em distância (cm), usando a velocidade do som 

    if (distancia > 1 && distancia < 90) // Objeto perto ( entre 1 e 90)
        digitalWrite(LED1, LOW);  // Apaga led de "longe"
        digitalWrite(LED2, LOW); // Apaga led d "médio"
        digitalWrite(LED3, HIGH); // Acende led de "perto"

        seno = (sin(x*3.1416/180)); // Calcula o seno do angulo atual (x graus, convertido em radianos)
        frequencia = 2000+ (int(seno* 1000)); // Gera frequencia oscilante entre 1000Hz e 3000Hz a partir do seno 
        tone (pino, frequencia); // Pequena pausas entre passos do som
        delay (1);

        x++; // avança o angulo em 1 grau a cada iteração do loop
        if (x >= 180) x = 0; // Reinicia o ciclo ao completar 180 grau a cada iteração do loop
        
    }else  if (distancia > 90 && distancia < 150){ // objeto em distancia media (90 - 150 cm)
        digitalWrite (LED1, LOW); // Apaga o led de "longe"
        digitalWrite (LED2, HIGH); // Acende o led de "medio"        
        digitalWrite (LED3, LOW); // Apaga o led de "perto"
        tone (pino, 550); // Toca de tom fixo de 550Hz
        delay (1); // pequena pausa
        x = 0; // zera  o contador

    }
    Serial.print("Distancia media:  ");// Imprime rotolo no monitor
    Serial.print(distancia); // imprime o valor  da distancia
    Serial.println("cm"); // imprime a unidade e quebra de linha
  
 	delay(50);  // pausa entre leituras do sensor  (~20x por segundo)

}

}
