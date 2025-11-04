# TARGET DETECTION TUTORIAL

Este tutorial explica cómo crear un nuevo plugin de detección de targets (Target Detection Plugin) que detecta un objetivo ficticio situado a 2 metros delante del robot.
El paquete se llama `target_detection_tutorial` y contiene todos los elementos necesarios para aprender a desarrollar un detector básico utilizando el API de PAL Nav2.

Posteriormente, este plugin podrá ampliarse para detectar personas reales mediante el uso de las funciones de libreria HRI.


## Contenido del paquete

El paquete target_detection_tutorial está organizado de la siguiente manera:

- `launch/`: contiene los archivos de lanzamiento que inician el Target Detector Server y ejecutan las transiciones de el Lifecycle Node.

- `params/`: incluye los archivos de configuración con los parámetros del servidor y la lista de plugins de detección que se cargarán automáticamente al inicio.

- `behavior_trees/`: define Behavior Tree utilizado para la detección dinámica de objetivos (Dynamic Target Detection).

- `src/`: contiene el código fuente del plugin de ejemplo `dummy_target_detector.cpp`.


## Dummy Target Detector

El archivo `dummy_target_detector.cpp` muestra cómo implementar tu propio plugin de detección de targets.
En este caso, el comportamiento por defecto consiste en simular un objetivo situado a 2 metros delante del robot.

Este ejemplo sirve como punto de partida para desarrollar detectores más avanzados que utilicen sensores reales o técnicas de percepción e interacción HRI.

## Pipeline de detección

El sistema de detección es independiente del plugin y sigue la siguiente secuencia de pasos:

- Inicialización: al arrancar, el servidor carga los plugins especificados y se suscribe a los temas necesarios.

- Solicitud de detección (Detection Request): cuando se recibe una petición de detección, el servidor invoca el plugin correspondiente para procesar los datos de entrada (por ejemplo, imágenes o nubes de puntos).

- Cálculo de la pose (Pose Calculation) :para cada target detectado, el plugin calcula su pose relativa a la cámara o al marco de referencia correspondiente.

Publicación de resultados (Result Publication): los resultados de la detección, incluyendo la pose del target, se publican en el tema configurado para que puedan ser utilizados por otros componentes del sistema (por ejemplo navegación).

