# 🦾 Instalación y Compilación del Workspace

Este documento describe los pasos necesarios para instalar y compilar el workspace utilizado durante el **TIAGo PRO Navigation and HRI Workshop**.

---

## 🧩 Requisitos

Asegúrate de utilizar un entorno basado en **ROS 2 Humble**, por ejemplo, la imagen Docker oficial:

```bash
docker pull osrf/ros:humble-desktop-full
```

También puedes trabajar en tu máquina local si tienes ROS 2 Humble correctamente instalado, aunque esto no te permitirá ejecutar el último ejercicio del workshop.

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