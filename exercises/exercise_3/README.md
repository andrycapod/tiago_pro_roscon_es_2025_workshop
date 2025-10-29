## 🧭 Navegación del TIAGo Pro en simulación

En esta sección aprenderás cómo ejecutar la simulación del **TIAGo Pro** con los distintos modos de **navegación y localización**, basados en el stack de [**Nav2**](https://docs.nav2.org/) y las extensiones desarrolladas por **PAL Robotics**.

Toda la documentación detallada se encuentra disponible en la documentación oficial de PAL Robotics:  
🔗 [PAL Navigation](https://docs.pal-robotics.com/25.01/navigation.html)

---

### 🧩 1. Instalación de dependencias

Antes de iniciar la simulación, instala los paquetes necesarios de **Nav2**, sobre los que se basa el sistema de navegación de PAL Robotics:

```bash
sudo apt-get update
sudo apt-get install ros-humble-navigation2*
sudo apt-get install ros-humble-nav2-bringup*
```
Después de la instalación, carga el entorno de ROS:
```bash
source /opt/ros/humble/setup.bash
```

### 🚀 2. Lanzar la simulación con navegación

Para iniciar la simulación en Gazebo con navegación y localización habilitadas, utiliza:
```bash
ros2 launch tiago_pro_gazebo tiago_pro_gazebo.launch.py is_public_sim:=True navigation:=True
```

### 🕹️ 3. Teleoperación del robot

Si deseas controlar el robot manualmente con el teclado dentro de la simulación, sigue el siguiente tutorial oficial de PAL Robotics:

🔗 [Teleop Tutorial – Control del robot desde teclado](https://docs.pal-robotics.com/25.01/navigation/teleop-tutorial.html#teleop-tutorial)


### 🗺️ 4. Navegación autónoma con SLAM

Para ejecutar la simulación en modo navegación autónoma + SLAM, utiliza:
```bash
ros2 launch tiago_pro_gazebo tiago_pro_gazebo.launch.py is_public_sim:=True slam:=True navigation:=True
```
Consulta el tutorial completo sobre mapeado en la documentación oficial:

🔗 [Mapping Tutorial – Creación de mapas con SLAM](https://docs.pal-robotics.com/25.01/navigation/mapping-tutorial.html)

### 📍 5. Localización en un mapa existente

Si ya dispones de un mapa previamente generado, puedes lanzar la simulación con navegación autónoma y localización activadas:

```bash
ros2 launch tiago_pro_gazebo tiago_pro_gazebo.launch.py is_public_sim:=True navigation:=True
```
Tutorial oficial:

🔗 [Localization Tutorial – Uso de un mapa existente](https://docs.pal-robotics.com/25.01/navigation/localization-tutorial.html#localization-tutorial)

### 🎯 6. Enviar un goal en navegación autónoma

Una vez que el robot esté en modo de navegación autónoma, puedes enviarle goal para que se desplace de manera autónoma hacia ese punto.

Consulta el tutorial oficial de PAL Robotics para aprender cómo definir y enviar goals utilizando las herramientas de Nav2 y RViz:
🔗 [Goal Navigation Tutorial – Enviar objetivos de navegación](https://docs.pal-robotics.com/25.01/navigation/goal-navigation-tutorial.html#goal-navigation-tutorial)

### ⚙️ 7. Inspección y modificación de parámetros de navegación

Los nodos de Nav2 y SLAM Toolbox utilizan diferentes parámetros que pueden ajustarse según las necesidades del entorno o del comportamiento del robot.
Estos parámetros se encuentran definidos en los archivos de configuración del paquete:
Puedes inspecionarlo haciendo un:
```bash
cat tiago_pro_workshop/src/omni_base_navigation/omni_base_2dnav/config/nav2_public_sim.yaml
```

🔗 [Nav2 y SLAM Toolbox params por TIAGo Pro](https://github.com/pal-robotics/omni_base_navigation/blob/humble-devel/omni_base_2dnav/config/nav_public_sim.yaml)

Puedes inspeccionar o modificar estos archivos para ajustar aspectos como:

- Planificadores globales y locales
- Parámetros de Local y Global costmap
- Configuración de AMCL (localización)
- Configuración de SLAM Toolbox
- Configuración de Behavior Trees y recovery behaviors

Tras modificar un archivo de configuración, recuerda recompilar el workspace o reiniciar los nodos de navegación para aplicar los cambios.