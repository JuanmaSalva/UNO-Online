# UNO Online
Proyecto final de redes consistente de un servidor y un cliente del juego UNO.  
Realizado por Esteban Restrepo y Juan Manuel Salvá

## Planteamiento 

### Protocolo a utilizar

Para lo que queremos hacer pensamos que la mejor opción era utilizar el protocolo TCP, así nos aseguramos de que no se pierde ningún mensaje para no tener que volver a preguntar al jugador en caso de que falle la recepción de algún paquete.  
Los usuales problemas de latencia al utilizar TCP no nos afectan, por cada turno el servidor envía un mensaje a cada uno de los jugadores y recibe solo un mensaje de vuelta del jugador de quien es el turno actual.

### Decisiones de seguridad

Por seguridad los jugadores sólo tienen conocimiento de su propia mano y de la carta que está encima de la pila de descarte, no solo no se les enseña qué tienen los demás si no que esa información ni siquiera se comparte con ellos.  
Así no hay manera de que por manipulación del programa o de análisis de paquetes se pudiera hacer trampas viendo las cartas de los demás. &nbsp;

Cuando el jugador va a escoger qué carta utilizar se verifica el movimiento tanto en el cliente como en el servidor.  
Si un jugador quisiese hacer trampas y enviar un paquete manualmente en el que utiliza una carta que por las normas del juego no podría utilizar el servidor lo detectaría y le pediría otra vez que juegue su turno. &nbsp;

Este patrón deja a los clientes siendo un reflejo interactivo del estado del servidor, lo único que depende de ellos es qué carta de las disponibles elige el jugador jugar, todo lo demás lo lleva el servidor, evitando que se pueda manipular el programa desde el cliente y tener una ventaja injusta en el juego. 

### Estructura de los mensajes

•Desde el servidor: &nbsp;

El servidor envía el estado del juego para cada jugador en cada turno, para asegurarnos de que todo el mundo está en la misma página y sabe qué esta suciediendo.  
Los datos enviados son:  
* Las cartas en la mano del jugador
* La carta que está encima 
* El numero de cartas que tiene el jugador
* Tipo de mensaje enviado
	* Informa al cliente si el mensaje es que empieza la partida, informativo, turno del jugador, si ha perdido turno (por carta de salto o +2) o si ha acabado la partida.
* 2 bytes de información extra
	* Utilizado para marcar quien gana o quienes están a punto de ganar

El tamaño final del mensaje es de 130 bytes. Este mensaje podría variar si cambiamos el tamaño de la mano, hemos escogido que el maximo de cartas que puede tener un jugador es de 30, y si intenta robar más no se le darán.

•Desde el cliente: &nbsp;

El cliente solo tiene que enviar el índice de la carta que escoja jugar y el color escogido en caso de utilizar una carta 'Wild'. Si el índice es -1 se entiende que el jugador quiere robar una carta.

El tamaño del mensaje de jugada es pequeño, ocupando solo 4 bytes.