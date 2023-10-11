// CÁTODO COMÚN
# define A 3
# define B 4
# define C A1
# define D A2
# define E A0
# define F 2
# define G 5
# define L_DISP A4 // display izquierdo
# define R_DISP A5 // display derecho
# define INC_BTN 10 // boton de incremento
# define DEC_BTN 9 // boton de decremento
# define RES_BTN 8 // boton de reinicio

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
  pinMode(RES_BTN, INPUT_PULLUP);
  counter = 0;
}

void loop()
{
  // leyendo constantemente el estado actual de los pulsadores 
  int incCurrentState = digitalRead(INC_BTN);
  int decCurrentState = digitalRead(DEC_BTN);
  int resCurrentState = digitalRead(RES_BTN);
  // arreglo con los estados actuales
  int btnStates[3] = {incCurrentState, decCurrentState, resCurrentState};
  // al evaluar 3 pulsadores (incremento, decremento y reset), el for tiene 3 iteraciones
  for (int i = 0; i < 3; i++)
  {
    // se compara un cambio en el estado actual del pulsador (detecta un 0 en el pulsador) 
    if(btnStates[i] != btnLastStates[i]) // linea 17
    {
      // si es 0 se presionó (pullup interno)
      if (btnStates[i] == LOW)
      {
        // (aumenta en 1, decrementa en 1, o establece en 0 el contador) solo se accede en caso de presionar el pulsador
        handleCounter(i);
      }
    }
  }
  // se los establece como iguales para realizar la comparación de la línea 48
  btnLastStates[0] = incCurrentState;
  btnLastStates[1] = decCurrentState;
  btnLastStates[2] = resCurrentState;
  // se muestra en el display el numero actual del contador
  handleDigits(counter);
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
// determina que hacer con el contador al detectar los cambios de estados de los pulsadores
void handleCounter(int btnIndex)
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
    case 2: // pulsador de reseteo
      counter = 0;
      break;
  }
}