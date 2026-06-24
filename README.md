# Autonomous-Maze-Solving-Car---FSM
Autonomous maze-solving robot controlled via a hardware-implemented Moore Finite State Machine (FSM) using 74107 JK Flip-Flops and logic gates. Includes a bare-metal C simulation that emulates the digital circuit's state transitions and boolean logic. The report is written in its original language (Spanish).

## Acerca del proyecto 

Robot autónomo para resolver laberintos, controlado mediante una máquina de estados finitos (FSM) de Moore implementada en hardware, que utiliza biestables JK 74107 y puertas lógicas. Incluye una simulación en C sin sistema operativo que emula las transiciones de estado y la lógica booleana del circuito digital.

*Autores:* Facundo Nicolás Castro, Gerónimo Contreras.<br>
*Cátedra:* Técnicas Digitales (2do cuatrimestre de 2025) <br>
*Carrera:* Ingeniería en Computación (UNS)<br>
*Profesor*: RODRIGO MARTÍN SANTOS  <br>
*Asistente*: CECILIA FERNÁNDEZ MONTEFIORE  <br>


## 1. Introducción
El trabajo de laboratorio realizado tenía como objetivo el diseño, simulación e implementación física de un sistema lógico secuencial para el control de un vehículo autónomo. La problemática planteada consistió en simular el comportamiento de una hormiga que debe recorrer un camino preestablecido siguiendo una estrategia de navegación específica: mantener siempre la pared a su derecha.

El sistema debe interpretar las señales provenientes de dos sensores (izquierdo y derecho) para tomar decisiones de movimiento en tiempo real, controlando la tracción de dos motores independientes.

Para la resolución del problema se diseñó una Máquina de Estados Finitos de tipo Moore, implementada mediante lógica secuencial utilizando Flip-Flops JK (circuito integrado 74107) y lógica combinacional auxiliar. La propuesta final fue validada mediante simulación digital y posteriormente implementada en protoboard, verificando el cumplimiento de la secuencia de control solicitada.

## 2. Desarrollo

## 2.1 Suposiciones y criterios de diseño asumidos

Para modelar el comportamiento del vehículo, se definieron las variables de entrada y salida estableciendo una convención lógica clara.

Convención para las entradas de los sensores SI (Sensor Izquierdo) y SD (Sensor Derecho), donde las combinaciones representan:

<img width="512" height="215" alt="image" src="https://github.com/user-attachments/assets/bc23552c-0dd0-4a45-af9d-3571e8826923" />

En lo que respecta a las convenciones asumidas para las salidas, es decir, los motores MI (Motor Izquierdo) y MD (Motor Derecho) tenemos:

<img width="520" height="165" alt="image" src="https://github.com/user-attachments/assets/22c06b5a-ea74-4920-8e9c-16fb763184d7" />

Luego, como modelamos la solución del problema mediante una máquina secuencial de tipo Moore, definimos los siguientes estados para crear la tabla de transición de estados:

<img width="519" height="165" alt="image" src="https://github.com/user-attachments/assets/e87fedcc-269e-42b9-9aca-e322f8f09de0" />

## 2.2 Tabla de transición de estados

A continuación, se presenta la tabla de transición de estados que modela la lógica secuencial de la solución propuesta.

<img width="375" height="314" alt="image" src="https://github.com/user-attachments/assets/b5eb491f-1488-4fa6-a6eb-3340047d7e06" />

Respecto a la tabla de transición de estados, comúnmente se busca hallar una tabla de transición de estados reducida aplicando métodos de reducción como el método de Paull and Unger. Por caso, como modelamos la solución con una máquina de tipo Moore, donde cada estado tiene asociada una salida única, la tabla de transición de estados no está sujeta a una posible reducción debido a que ya se encuentra en su mínima expresión.

## 2.3 Tabla de transición de estados asignados

Para conformar la tabla de transición de estados asignados, realizamos las siguientes asociaciones:

<img width="519" height="171" alt="image" src="https://github.com/user-attachments/assets/0b40a804-9691-4ce5-9a4c-a36b238cb80b" />

Así, procedemos para conformar la tabla de transición de estados asignados (TTEA), reemplazando cada estado de la tabla de transición de estados original por su correspondiente combinación asignada.

<img width="382" height="344" alt="image" src="https://github.com/user-attachments/assets/48d4f020-83a2-4b8e-a17b-6ae0f230a68f" />


## 2.4 Tabla de excitación de los Flip Flops

Dado que modelamos la solución al problema usando un total de cuatro estados, la cantidad mínima de variables de estado necesarias se calculan como log2(4)=2. Luego, se necesitaron dos flip flops para esta solución. Lo que es conveniente, ya que el micro 74107 cuenta con dos.

En base a la tabla de transición de estados asignados y haciendo uso de la siguiente tabla que representa las transiciones de un flip flop tipo JK:


<img width="521" height="166" alt="image" src="https://github.com/user-attachments/assets/0c9e5d98-ebc0-4431-bc9a-c74901fe8d49" />

Construimos la tabla de excitación de ambos flip flops tipo JK:

<img width="506" height="343" alt="image" src="https://github.com/user-attachments/assets/97d31a3f-7217-4d6e-8273-322d781c10d5" />

## 2.5 Representación en mapas de Karnaugh (K-Maps) y ecuaciones de Flip Flops

Basándonos en la tabla de excitación de los flip flops, construimos los k-maps correspondientes con el fin de buscar una expresión para las ecuaciones de entrada de estos. Resultando en los siguientes mapas y ecuaciones (En K0 se hizo uso de una de las leyes de Morgan para dejar la expresión en formato de salida NAND):

<img width="440" height="193" alt="image" src="https://github.com/user-attachments/assets/a7bb0a39-505a-4ab5-8ea5-1be6d2d2c7fc" />
<img width="409" height="181" alt="image" src="https://github.com/user-attachments/assets/e3be20c4-2ed8-47d6-b363-14d5e4c358cf" />

## 2.6 Expresiones de las salidas (Motores)

De la siguiente tabla donde se representan los estados involucrados con sus respectivas salidas en términos de valor binario para el motor izquierdo y motor derecho:

<img width="248" height="170" alt="image" src="https://github.com/user-attachments/assets/cce7e1e1-57e9-4e37-96c3-5ffd180bbac3" />

Buscamos las expresiones para las funciones de salida de los motores MI y MD a través de los mapas de Karnaugh:

<img width="471" height="150" alt="image" src="https://github.com/user-attachments/assets/4ca57c54-4ed1-447e-b0d4-85320ffb5665" />

## 2.7 Diseño y diagrama del circuito lógico

Teniendo todas las ecuaciones de entrada de los flip flops y las ecuaciones de salida de ambos motores, concluímos que podíamos diseñar el circuito con los siguientes elementos:

Un micro dual Flip Flop JK 74107.
Un micro inversor 7414/7404.
Un micro DM7408 (AND de 2 entradas x 4 compuertas).

Así, diseñamos el circuito como se muestra en la figura:

<img width="506" height="206" alt="image" src="https://github.com/user-attachments/assets/bec5c4a4-3d70-4641-bc8e-95411bfd7628" />

## 2.8 Implementación en simulador

Posterior al diseño del diagrama del circuito lógico, trasladamos este mismo a una simulación, donde agregamos montamos los componentes en una protoboard, cableamos los componentes y conectamos otros necesarios para el funcionamiento del circuito como fuente, interruptores para simular las entradas de los sensores SISD, LEDS para simular las salidas de los motores MIMD y pulsadores para actualizar el pulso de reloj del CLOCK al cual ambos flip flops van conectados para estar sincronizados.

Quedó implementado de la siguiente manera:

<img width="523" height="353" alt="image" src="https://github.com/user-attachments/assets/be3bd141-3ded-403e-b287-46e393a44999" />

Realizamos sobre el simulador las pruebas necesarias para confirmar que para cada estado QOQ1 y cada entrada SISD de los interruptores se realizaba la transición de estado correspondiente. Así, pasamos a implementar físicamente el circuito.

## 2.9 Implementación física en protoboard y testing

Realizamos las conexiones correspondientes a nuestro diseño. Hicimos uso de los interruptores y de los leds de la fuente para representar las entradas de los sensores SISD y las salidas de los motores MIMD. Volvimos a realizar las pruebas de transición de estados y se pasaron satisfactoriamente.

<img width="362" height="239" alt="image" src="https://github.com/user-attachments/assets/07f490a6-fea0-4e6b-ae8c-149292f7f954" />

## 2.10 Implementación sobre vehículo

Habiendo asegurado el correcto funcionamiento del circuito, pasamos a montarlo sobre un vehículo ya preparado, conectando nuestra protoboard, las entradas de los sensores y salidas de los motores en los pines correspondientes. El vehículo logró superar las pruebas de laberinto, por lo que cumplió con su propósito.

<img width="283" height="178" alt="image" src="https://github.com/user-attachments/assets/3113bf6f-f81a-42fa-9006-419f2595bf78" />

## 3 Conclusión

La realización de este laboratorio permitió validar experimentalmente el proceso completo de diseño de sistemas digitales, desde la abstracción del problema mediante una máquina de estados finitos hasta su implementación física. 

En cuanto a resultados, el circuito implementado cumplió satisfactoriamente con la secuencia de control del vehículo solicitada/esperada, logrando que este resuelva salir de un laberinto previamente acordado.

No presentamos dificultades mayores para la realización del laboratorio, aunque en la instancia de construcción de la tabla de transición de estados estuvimos a punto de caer en un potencial bucle infinito de transiciones, pero logramos evitarlo haciendo un cambio de estado en la tabla.

Al momento de montar el circuito en el vehículo, cuyo diseño ya estaba armado e implementado, cometimos un pequeño error al desmontar nuestra protoboard, armarla nuevamente y sin querer erramos al hacer una conexión en una compuerta. Volvimos a implementarlo nuevamente de cero, y pasó la verificación final antes de montarla en el vehículo.

Finalmente, nos pareció curioso como todos los alumnos realizamos diseños e implementaciones distintas del circuito y aún así todos funcionaron correctamente. Usando diferentes tipos de máquinas Mealy o Moore y diferentes compuertas. Lo que nos lleva a ver claramente el trade-off que existe en el diseño de circuitos secuenciales, así como en distintas áreas de la computación/electrónica. Nosotros que optamos por una máquina de Moore, obtuvimos funciones de salida de los motores muy simples debido a que las salidas dependían solamente de los estados actuales. Lo que llevó a poder diseñar el circuito con solo 3 compuertas. Sin embargo, si hubiésemos diseñado la solución con una máquina de Mealy probablemente hayamos podido reducir estados, y quizá hasta llegar a usar uno solo de los dos flip flops que incorpora el JK74107. Entendimos que es una cuestión de diseño y de elección de qué preferimos tener: Más estados y ecuaciones más simples expresadas con menos compuertas o, Menos estados, ecuaciones más complejas y un flip flop menos.
