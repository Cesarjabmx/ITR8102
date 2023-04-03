#define ITR8102 2 //Nombre al pin 2, desde el detector

int contador = 0; //Variable para guardar la cuenta de pulsaciones
int estadoAnteriorItr8102 = 0; //Variable para conocer el estado anterior
int valorItr8102 = 0; //Declaramos e inicializamos la variable

void setup() { // Se ejecuta cada vez que el Arduino se inicia
  pinMode(ITR8102, INPUT); //Configura el pin 12 como una entrada
  pinMode(LED_BUILTIN , OUTPUT); //Configura el pin 13 como una salida
  Serial.begin(9600); //Inicia comunicación serie
  while(!Serial);
}

void loop() { // Esta funcion se mantiene ejecutando cuando este alimentado el Arduino
  valorItr8102 = digitalRead(ITR8102); //Leemos el estado del sensor
  if (valorItr8102 != estadoAnteriorItr8102) { //Si hay un cambio de estado, entramos en el if
    if (valorItr8102 == HIGH) {
      contador++; //Aumentamos en una unidad la cuenta
      //Serial.println(contador); //Imprime el valor por consola
      digitalWrite(LED_BUILTIN , HIGH); //Encendemos el led
      Serial.println(": abierto");
    }
    else {
      digitalWrite(LED_BUILTIN , LOW); //Apagamos el led
      Serial.println(": cerrado");
    }
    delay(50);    
  }
  estadoAnteriorItr8102 = valorItr8102; //guardamos el estado actual del sensor para la siguiente iteración
}