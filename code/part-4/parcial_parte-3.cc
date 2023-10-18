/*
  deberás modificar la lógica de tu proyecto para que el 7
  segmentos que mostraba los números primos ahora muestre
  los números pares. 
*/

// CÁTODO COMÚN
# define FT_RES A0 // fotorresistor
# define A 3
# define B 4
# define C A1
# define D A2
# define E 6
# define F 2
# define G 5
# define L_DISP A4 // display izquierdo
# define R_DISP A5 // display derecho
# define INC_BTN 10 // boton de incremento
# define DEC_BTN 9 // boton de decremento
# define SWITCH 8 // boton deslizante
# define SENS_BTN 11 // boton para leer sensor
# define SENSOR A3 // sensor de fuerza

int counter;
// arreglo con estados contra los cuales comparar
int btnLastStates[3] = {LOW, LOW, LOW};

void setup()
{
  pinMode(A, OUTPUT);
  pinMode(B, OUTPUT);
  pinMode(C, OUTPUT);
  pinMode(D, OUTPUT);
  pinMode(E, OUTPUT);
  pinMode(F, OUTPUT);
  pinMode(G, OUTPUT);
  pinMode(L_DISP, OUTPUT);
  pinMode(R_DISP, OUTPUT);
  pinMode(INC_BTN, INPUT_PULLUP);
  pinMode(DEC_BTN, INPUT_PULLUP);
  pinMode(SWITCH, INPUT_PULLUP);
  pinMode(SENS_BTN, INPUT_PULLUP);
  pinMode(SENSOR, INPUT);
  pinMode(FT_RES, INPUT);
  counter = 0;
}

void loop()
{
  int resMap = map(analogRead(FT_RES), 6, 679, 0, 10);
  // leyendo el sensor de fuerza
  int readingSensor = analogRead(SENSOR);
  // convirtiendo los valores recibidos del sensor
  int newtonws = map(readingSensor, 0,827,0,10);
  // leyendo constantemente el estado actual de los pulsadores 
  int incCurrentState = digitalRead(INC_BTN);
  int decCurrentState = digitalRead(DEC_BTN);
  int sensCurrentState = digitalRead(SENS_BTN);
  int switchCurrentState = digitalRead(SWITCH);

  // arreglo con los estados actuales de los pulsadores
  int btnStates[3] = {incCurrentState, decCurrentState, sensCurrentState};
  
  if (resMap >= 7)
  {
    if (switchCurrentState == 0) // cuando el switch no este activo (primera posición, contador de uno en uno)
    {
      // al evaluar 3 pulsadores (incremento, decremento y el que activa el sensor), el for tiene 3 iteraciones
      for (int i = 0; i < 3; i++)
      {
        // se compara un cambio en el estado actual del pulsador (detecta un 0 en el pulsador) 
        if(btnStates[i] != btnLastStates[i]) // linea 19
        {
          // si es 0 se presionó (pullup interno)
          if (btnStates[i] == LOW)
          {
            // (aumenta en 1, decrementa en 1, o establece como -1 el contador) solo se accede en caso de presionar el pulsador
            handleNormalCounter(i);
          }
        }
      }
      if (counter <  0) {
        // cuando se presiona el botón n°3 (línea 282) se muestran los valores del sensor
        handleDigits(newtonws);
      }
      else
      {
        // se muestra como el contador se incrementa o decrementa en 1
        handleDigits(counter);
      }
    }
    else // cuando el switch esta activo (segunda posición, contador de numeros primos)
    {
      // al evaluar solo 2 pulsadores (incremento y decremento), el for tiene 2 iteraciones
      for (int i = 0; i < 2; i++)
      {
        // se compara un cambio en el estado actual del pulsador (detecta un 0 en el pulsador) 
        if(btnStates[i] != btnLastStates[i]) // linea 19
        {
          // si es 0 se presionó (pullup interno)
          if (btnStates[i] == LOW)
          {
            // (aumenta o decrementa los numeros pares en el contador) solo al presionar el pulsador
            handleEvenCounter(i);
          }
        }
      }
      // se muestra como el contador se incrementa o decrementa mostrando solo números primos
      handleDigits(counter);
    }
    // se los establece como iguales para la realizar la comparación de las líneas 61 y 87 
    btnLastStates[0] = incCurrentState;
    btnLastStates[1] = decCurrentState;
    btnLastStates[2] = sensCurrentState;
  }
  else
  {
    delay(1);
    lightOn(L_DISP);
    lightOn(R_DISP);
    counter = 0;
  }
}
// funciones de prendido y apagado de pines (reusabilidad)
void lightOn(int pin)
{
  digitalWrite(pin, HIGH);
}
void lightOff(int pin)
{
  digitalWrite(pin, LOW);
}
// funciones para formar numeros en el display 7 segmentos
void numberZeroOn()
{
  lightOn(A);
  lightOn(B);
  lightOn(C);
  lightOn(D);
  lightOn(E);
  lightOn(F);
  lightOff(G);
}
// a partir de aca todos los numeros son realizados a partir de otros (ahorra varias lineas)
void numberOneOn()
{
  numberZeroOn();
  lightOff(A);
  lightOff(D);
  lightOff(E);
  lightOff(F);
}
void numberTwoOn()
{
  numberZeroOn();
  lightOff(C);
  lightOff(F);
  lightOn(G);
}
void numberThreeOn()
{
  numberZeroOn();
  lightOff(E);
  lightOff(F);
  lightOn(G);
}
void numberFourOn()
{
  numberOneOn();
  lightOn(F);
  lightOn(G);
}
void numberFiveOn()
{
  numberZeroOn();
  lightOff(B);
  lightOff(E);
  lightOn(G);
}
void numberSixOn()
{
  numberZeroOn();
  lightOff(B);
  lightOn(G);
}
void numberSevenOn()
{
  numberOneOn();
  lightOn(A);
}
void numberEightOn()
{
  numberZeroOn();
  lightOn(G);
}
void numberNineOn()
{
  numberFourOn();
  lightOn(A);
}
  
// permite elegir que numero mostrar en el display a partir de un parametro
void showNumber(int number)
{
  switch (number)
  {
    case 0:
    {
      numberZeroOn();
      break;
    }
    case 1:
    {
      numberOneOn();
      break;
    }
    case 2:
    {
      numberTwoOn();
      break;
    }
    case 3:
    {
      numberThreeOn();
      break;
    }
    case 4:
    {
      numberFourOn();
      break;
    }
    case 5:
    {
      numberFiveOn();
      break;
    }
    case 6:
    {
      numberSixOn();
      break;
    }
    case 7:
    {
      numberSevenOn();
      break;
    }
    case 8:
    {
      numberEightOn();
      break;
    }
    case 9:
    {
      numberNineOn();
      break;
    }
  }
}
// prendido y apagado constante de los displays (multiplexación)
void handleDigits(int number)
{
  int unit;
  // apago los displays poniendo ambos en HIGH
  lightOn(L_DISP);
  lightOn(R_DISP);
  // enciendo el número
  showNumber(number / 10);
  // muestro la decena:
  lightOff(R_DISP); // apago la unidad
  lightOn(L_DISP); // enciendo la decena
  // 10 ms de retardo para apagar ambos de nuevo
  delay(10); // pocos ms para estabilidad visual
  // apago los displays de nuevo poniendo ambos en HIGH
  lightOn(L_DISP);
  lightOn(R_DISP);
  // en caso de ser un número con decena
  if (number >= 10 && number <= 99)
  {
  // divido el parametro entre 10 para obtener solo la unidad
    unit = number % 10;
  }
  else { // en caso de no tener decena
    unit = number;
  }
  // muestro la unidad:
  showNumber(unit);
  lightOff(L_DISP); // apago la decena
  lightOn(R_DISP); // enciendo la unidad
  // 10 ms de retardo para apagar ambos de nuevo
  delay(10); // pocos ms para estabilidad visual
}
// determina que hacer con el contador al detectar los cambios de estados de los pulsadores (switch en 0, línea 55)
void handleNormalCounter(int btnIndex)
{
  switch (btnIndex)
  {
    case 0: // pulsador de incremento
      if (counter <= 99)
      {
        counter++;
      }
      break;
    case 1: // pulsador de decremento
      if (counter > 0)
      {
        counter--;
      }
      break;
    case 2: // pulsador que activa la lectura del sensor
      counter = -1;
      break;
  }
}

// determina que hacer con el contador al detectar los cambios de estados de los pulsadores (switch en 1, línea 81)
/*void handlePrimeCounter(int btnIndex)
{
  switch (btnIndex)
  {
    case 0: // pulsador de incremento
      if (counter < 97)
      {
        counter++;
        while (isPrime(counter) == false)
        {
          counter++;
        }
      }
      break;
    case 1: // pulsador de decremento
      if (counter > 2)
      {
        counter--;
        while (isPrime(counter) == false)
        {
          counter--;
        }
      }
      break;
  } 
}
// determina si un número es primo dividiendolo por los números que lo componen
bool isPrime(int number)
{
  // cantidad de veces que una división dio resto 0
  int count = 0;

  // el numero no puede ser 0 ni 1
  if (number > 1) {
    for (int i = 0; i < number; i++) // cantidad de iteraciones igual al numero a determinar
    {
      int current = i + 1 ;
      // comparo si el número a determinar tiene resto 0 dividiendolo por cada uno de los números que lo componen
      if (number % current == 0)
      {
        // se agrega uno al contador para validar que se encontró una división de resto 0
        count++;
        if (count > 2)
        {
          // en caso de que hayan más de 2 divisiones, no es un número primo
          return false;
          break;
        }
      } 
    }
    if (count <= 2)
    {
      // si solo se registraron 2 divisiones, entonces es un número primo
      return true;
    }
  }
  else
  {
    return false;
  }
}*/
// Funcion modificada => handlePrimeCounter
void handleEvenCounter(int btnIndex)
{
  switch (btnIndex)
  {
    case 0: // pulsador de incremento
      if (counter < 98)
      {
        counter++;
        while (isEven(counter) == false)
        {
          counter++;
        }
      }
      break;
    case 1: // pulsador de decremento
      if (counter > 1)
      {
        counter--;
        while (isEven(counter) == false)
        {
          counter--;
        }
      }
      break;
  } 
}
// Funcion modificada => isPrime
bool isEven(int number)
{
  if (number % 2 == 0)
  {
    return true;
  }
  else
  {
  	return false;
  }
}