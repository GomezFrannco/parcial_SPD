![Banner](./img/project-banner.png)
## Parcial de SPD
Este repositorio contiene 2 proyectos (parte 1 y parte 2) que forman parte del parcial de la materia.

### Integrante
- Franco Ezequiel Gomez
- División B


## Proyecto: Contador 0 a 99 (Parte 1)
![Project](./img/Parcial_Parte-1_Franco-Gomez.png)
## 🔗 Links al proyecto
- [Tinkercad](https://www.tinkercad.com/things/fr8l2XzCsWt)
- [Código](https://github.com/GomezFrannco/parcial_SPD/blob/main/code/part-1/parcial_parte-1.cc)

## Descripción
Esta primera parte del proyecto consta de la implementación de 2 displays de 7 segmentos multiplexados (i), 3 pulsadores (ii) y una placa de pruebas (iii).

![Components](./img/components_parte-1.png)

Los displays se usan para mostrar un contador que inicia en 00 y termina en 99, los pulsadores son utilizados para:
- incrementar el contador en 1
- decrementar el contador en 1
- volver el contador a 00

Lo interesante de utilizar 2 displays multiplexados es que, además de compartir recursos, podemos representar 2 números; decena y unidad.

Lo difícil aparece al momento de querer mostrar 2 números a la vez, ya que no pueden estar ambos encendidos al mismo tiempo porque mostrarían el mismo número ambos displays. Para solucionar este problema se hace lo siguiente:

1. Se enciende (con 0 en este caso) el display el cual se requiere mostrar un número.
2. Se forma el número en el display con los pines correctos.
3. Se apaga el el led anteriormente prendido (con 1).
4. Luego de un delay imperceptible se enciende el otro display para realizar lo mismo que con el primero.

Este rapido encendido y apagado constante entre ambos displays genera un efecto visual en el cual pareciera que estan prendidos a la vez.

## Función encargada de generar este efecto.

Esta función recibe como parámetro el número que se quiere mostrar entre los displays. 
* Primero apaga ambos displays y utiliza una función llamada "showNumber" que prende los pines que generan el número del parametro.
* Se lo divide por diez para generar solo la decena, se apaga la unidad (con el propósito de solo mostrar la decena) y luego de 10ms es apagado nuevamente para repetir lo mismo al encender la unidad.

~~~ C (lenguaje en el que esta escrito)
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
~~~

## Proyecto: Switch de Contador a Números Primos (Parte 2)
![Project](./img/Parcial_Parte-2_Franco-Gomez.png)
## 🔗 Links al proyecto
- [Tinkercad](https://www.tinkercad.com/things/5QUxo1zWyx5)
- [Código](https://github.com/GomezFrannco/parcial_SPD/blob/main/code/part-2/parcial_parte-2.cc)

## Descripción
Para esta segunda parte se agrega un botón deslizante o switch (i), un motor de corriente continua (ii) y por ultimo, un sensor de fuerza (iii). También se modifica uno de los pulsadores (iv).

![Components](./img/components_parte-2.png)

El nuevo switch agregado es utilizado para cambiar lo que se muestra en los displays. En la primer posición de este botón deslizante, los displays mostrarán un contador de 1 en 1 con sus respectivos incrementos y decrementos. Al pasarlo a la segunda posición, los displays comenzaran realizar el aumento y el decremento solo mostrando números primos.

El pulsador modificado nos permite mostrar por los displays la fuerza aplicada al sensor de fuerza que mueve el motor. Este pulsador solo es válido en la primera posición del switch.

## Funcionamiento de los Pulsadores

Uno de los desafios más grandes en estas 2 partes del proyecto fue encontrar la manera de contar solo un pulso del pulsador y no si esta constantemente presionado.

Este funcionamiento es el mismo para ambas partes del proyecto, sin embargo, en la parte 2 fue ligeramente modificado.

Básicamente, al inicio de cada loop se registra el valor que tiene el pulsador en ese momento y se los guarda en un arreglo. Luego se inicia un bucle de 3 iteraciones y aparece una condición.

Esta condición compara el estado registrado contra un estado previamente establecida (esto con el propósito de detectar si al inicio del loop se detectó un valor diferente al anterior)

En caso de ser LOW se accede al contador y se lo módifica según el pulsador presionado. Luego del bucle for, se actualiza el valor anterior con el actual para continuar comparando cambios de valores en las proximas iteraciones del loop.

Finalmente se muestran el número del contador en el display.


### Funcionamiento de los pulsadores (código de la parte 1)
~~~ C (lenguaje en el que esta escrito)
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
~~~
## Proyecto: Fotorresistor (Parte 3)
![Project](./img/Parcial_Parte-3_Franco-Gomez.png)
## 🔗 Links al proyecto
- [Tinkercad](https://www.tinkercad.com/things/3UlOjn3naip)
- [Código](https://github.com/GomezFrannco/parcial_SPD/blob/main/code/part-3/parcial_parte-3.cc)

## Descripción

Para la parte 3 se agregó un nuevo componente al proyecto, el fotorresistor (i) (de acuerdo con la terminación del DNI, 0 en mi caso)

![Components](./img/components_parte-3.png)

En esta oportunidad, el fotoresistor es utilizado para bloquear o interferir con el uso de los pulsadores y el display. En caso de que el fotorresistor detecte menos del 70% de luz, los displays estarán apagados y no funcionaran los pulsadores. Caso contrario, si el fotorresistor recibe luz que sobrepase el 70% dejará que funcione todo correctamente.

## Proyecto: Modificar Lógica (Parte 4)
![Project](./img/Parcial_Parte-3_Franco-Gomez.png)
## 🔗 Links al proyecto
- [Tinkercad](https://www.tinkercad.com/things/dt0CtSJGEpq)
- [Código](https://github.com/GomezFrannco/parcial_SPD/blob/main/code/part-4/parcial_parte-4.cc)

## Descripción

Basado en el ejercicio para los documentos que terminen entre 0 y 3, se identificaron las 2 funciones clave a modificar para conseguir el objetivo. Estas funciones fueron las siguientes:
- handlePrimeCounter
- isPrime 

La primera de estas funciones estaba encargada de incrementar o decrementar el contador pero solo mostrando los números primo, dependiendo del pulsador presionado. La segunda función cumplia la tarea de verificar si un número, pasado por parámetro, es primo o no.

Estas dos funciones fueron modificadas dando resultado a las siguientes dos funciones:
- HandleEvenCounter
- isEven

Las dos funciones resultantes de la modificación a las anteriores permiten incrementar o decrementar el contador pero solo mostrando los números pares y verificar si un número es par.

### Modificación de las funciones
~~~ C (lenguaje en el que esta escrito)
bool isEven(int number) // Antes llamada isPrime
{
  // NEW CODE
  if (number % 2 == 0)
  {
    return true;
  }
  else
  {
  	return false;
  }

  // PREVIOUS CODE
  /*int count = 0;
  if (number > 1) {
    for (int i = 0; i < number; i++)
    {
      int current = i + 1 ;
      if (number % current == 0)
      {
        count++;
        if (count > 2)
        {
          return false;
          break;
        }
      } 
    }
    if (count <= 2)
    {
      return true;
    }
  }
  else
  {
    return false;
  }*/
}
void handleEvenCounter(int btnIndex)  // Antes llamada handlePrimeCounter
{
  switch (btnIndex)
  {
    case 0:
      if (counter < 98) // Antes (counter < 97)
      {
        counter++;
        while (isEven(counter) == false) // Anteriormente while (isPrime(counter) == false)
        {
          counter++;
        }
      }
      break;
    case 1:
      if (counter > 2)
      {
        counter--;
        while (isEven(counter) == false) // Anteriormente while (isPrime(counter) == false)
        {
          counter--;
        }
      }
      break;
  } 
}
~~~