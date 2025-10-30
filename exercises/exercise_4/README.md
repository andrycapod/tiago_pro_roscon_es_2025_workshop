## TARGET NAVIGATION and HUMAN TARGET DETECTOR

### 🧠 Descripción general
El Framework de Target Navigation permite que los robots detecten y naveguen de forma autónoma hacia diferentes tipos de targets (objetivos).

En este Workshop aprenderás a:

- Comprender cómo funciona el sistema de detección de targets
- Crear tu propio plugin de detección de targets
- Extenderlo para seguir targets dinámicos (como personas)


### 🎯 Detección de Targets

El componente de Detección de Targets es responsable de identificar un objetivo y proporcionar su posición relativa al robot.

En general, cualquier objeto que pueda ser detectado por los sensores del robot puede considerarse un target.
Algunos ejemplos son:

- Marcadores ArUco
- Patrones láser 2D
- Personas

### 👩‍💻 Lo que haremos hoy

En esta sesión práctica, nos centraremos en:

- Implementar un plugin de detección simple — un detector “dummy” que siempre detecta un target falso a 2 metros frente al robot.
- Posteriormente, este detector “dummy” será extendido para detectar personas reales utilizando las APIs de la librería HRI.
- Finalmente, haremos que el robot siga a una persona en movimiento de manera autónoma.

### 🧩 Detección de Personas con la Librería HRI

La librería HRI (Human-Robot Interaction) proporciona un conjunto de APIs en ROS 2 para detectar y rastrear personas en el entorno del robot.
Ofrece interfaces estandarizadas para:
- Humanos, caras, cuerpos y voces
- Sus IDs, posiciones y atributos semánticos (por ejemplo, emoción o atención)
- Seguimiento y actualización continua de cada persona mientras se mueve

Al utilizar las APIs de HRI, nuestro futuro plugin podrá:

- Consultar la lista actual de personas detectadas
- Obtener la posición de una persona específica (por ID o por proximidad)
- Enviar esa posición al Framework de Target Navigation para que el robot pueda seguirla

En otras palabras:
Nuestro Dummy Detector se convertirá en un Human Detector basado en las APIs de HRI.

### 🚶 Navegación hacia Targets Dinámicos

El comportamiento de Dynamic Target Navigation permite al robot:
- Identificar la posición de un target dinámico (por ejemplo, una persona)
- Actualizar continuamente la posición de dicho target mientras se mueve
- Seguirlo en tiempo real

Esto permite comportamientos autónomos de seguimiento de personas u objetos en movimiento.


