# 🐳 Exercise 0 — Preparación del Entorno Docker

Este primer ejercicio explica cómo preparar el entorno de trabajo para el TIAGo PRO Navigation and HRI Workshop utilizando un contenedor Docker preconfigurado.
El contenedor incluye todas las dependencias necesarias para ejecutar los ejercicios de navegación y HRI.

---

## 🧩 Requisitos

🧩 Requisitos

- Docker instalado
👉 [Instrucciones oficiales](https://docs.docker.com/desktop/setup/install/linux/ubuntu/)

- (Opcional) NVIDIA GPU y NVIDIA Container Toolkit
👉 [Guía de instalación](https://docs.nvidia.com/datacenter/cloud-native/container-toolkit/latest/install-guide.html) 

- Sistema operativo Linux con entorno gráfico (soporte X11)

## 🐋 Imagen Docker del Workshop

La imagen oficial del workshio está disponible públicamente en Docker Hub:

```bash
docker pull palrobotics/public-roscon-es-2025-humble-public
```

Esta imagen contiene:

- ROS 2 Humble completo
- Stack de navegación de TIAGo PRO
- Librerías de HRI y Navegacion y herramientas gráficas (RViz, Gazebo, rqt, etc.)

## 🟩 Opción 1 — Con GPU NVIDIA

Si tu sistema dispone de una GPU NVIDIA y tienes instalado el NVIDIA Container Toolkit, ejecuta:

```bash
xhost +local:root

docker run -it \
  --gpus all \
  --net=host \
  --env="DISPLAY" \
  --env="QT_X11_NO_MITSHM=1" \
  --volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" \
  --volume="$HOME/exchange:/root/exchange:rw" \
  palrobotics/public-roscon-es-2025-humble-public
```
## 🟦 Opción 2 — Sin GPU NVIDIA

Si no dispones de una GPU NVIDIA, puedes ejecutar el contenedor sin soporte gráfico acelerado.
Aun así podrás seguir los ejercicios, aunque algunas simulaciones podrían ir más lentas.

```bash
xhost +local:root

docker run -it \
  --net=host \
  --env="DISPLAY" \
  --env="QT_X11_NO_MITSHM=1" \
  --volume="/tmp/.X11-unix:/tmp/.X11-unix:rw" \
  --volume="$HOME/exchange:/root/exchange:rw" \
  palrobotics/public-roscon-es-2025-humble-public
```

## ⚙️ Creación del workspace

Para crear automáticamente el workspace del workshop y descargar todos los paquetes necesarios, ejecuta el siguiente script incluido en esto repositorio.

```bash
cd tiago_pro_roscon_es_2025_workshop/installation_scripts
bash installation_ws_tiago_pro_workshop.sh
```

El script creará una carpeta llamada:

```bash
~/ws_tiago_pro_workshop/src
```

y dentro de ella descargará todos los paquetes requeridos para ejecutar la simulación de TIAGo PRO.

## 📦 Instalación de dependencias

Actualiza los paquetes del sistema e instala las dependencias necesarias:
```bash
sudo apt update && sudo apt upgrade -y
```

Luego, dentro del workspace, instala las dependencias ROS 2 que falten utilizando rosdep:
```bash
cd ~/ws_tiago_pro_workshop
rosdep update
rosdep install --from-paths src --ignore-src -r -y
```
## 🧱 Compilación del workspace

Después de instalar las dependencias, compila el workspace con:
```bash
cd ~/ws_tiago_pro_workshop
colcon build
```

Una vez finalizada la compilación, carga el entorno ejecutando:

```bash
source install/setup.bash
```

## ✅ Comprobación final

Para verificar que la instalación y la compilación se hayan realizado correctamente, ejecuta el siguiente comando para visualizar el modelo del robot TIAGo PRO:

```bash
ros2 launch tiago_pro_description show.launch.py
```

Si todo está correctamente configurado, deberías ver el modelo del robot en RViz.