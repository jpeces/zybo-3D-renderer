@mainpage SignTalk: 3D Hand Visualizer

*   [Descripcion del proyecto](#overview)
*   [Estructura de carpetas](#folderstruc)
*   [Doc Strategy](#docstrategy)
*   [Informacion adiccional](#info)

* * *

<h2 id="overview">Descripción del proyecto</h2>

Aquí iría una descripción detallada del proyecto

<h2 id="folderstruc">Estructura de carpetas</h2>

En este apartado se muestra y se analiza la distribución de los ficheros y la estructura de carpetas en las que se organiza el código. Esta estructura esta diseñada conforme al patrón Facade.

    |-- app
	|   \-- app.c
	|
	|-- dom
    |   |-- databox.c
	|   |-- databox.h
	|   |-- frame.c
	|   |-- frame.h
	|   |-- hand.c
	|   |-- hand.h
	|   |-- menu.c
	|   |-- menu.h
    |   |-- statusbar.c
	|   \-- statusbar.h
	|	
	|-- hal
	|   |-- display_vga
	|   |   |-- display_ctrl.c
	|   |   |-- display_ctrl.h
	|   |   |-- font8x8.h
	|   |   |-- vga.c
	|   |   |-- vga.h
 	|   |   \-- vga_modes.h
	|	|
	|   \-- hal_core
	|       |-- controls.c
 	|       |-- controls.h
	|       |-- display.c
	|       |-- display.h
	|       |-- sensors.c
	|       \-- sensors.h
	|
	|-- lib
	|   |-- color.c
	|   |-- color.h
	|   |-- i2c.c
	|   |-- i2c.h
    |   |-- logger.c
    |   |-- logger.h
	|   |-- mathmin.c
	|   |-- mathmin.h
	|   |-- state_machine.c
	|   \-- state_machine.h
	|
    |-- res
    |   |-- model.h
    |
	|-- conf.h
	\-- new_types.h

En primer lugar nos encontramos con una carpeta donde se encuentra el archivo fachada *app.c* en el que se implementa la función main de la aplicación. 

Siguiendo con el patrón de diseño, nos encontramos con la capeta de dominio (dom) donde se implementan las funcionalidades básicas de la aplicación. Esta carpeta constituye la segunda capa dentro del patrón facade. 

La siguiente capa se encuentra a nivel de hardware y es la que interactura directamente con la placa cuando la aplicación solicita el uso de algun recurso. Por último exite un carpeta de librerías (lib) que contiene las implementaciones de recursos independientes, necesarios para el correcto funcionamiento de la aplicación.

<h2 id="docstrategy">Doc strategy</h2>

La mayor parte del código está comentado con el tipo de comentario de Doxygen debido a que el estilo definido al comienzo del proyecto lo incluia. 

Para crear la documentación se ha decidido excluir varias partes de proyecto, las cuales se exponen a continuación:

*	__Librerías:__ La carpeta *lib* que incluye se ha excluido de la documentacion. Esto se debe a que, a pesar de haber sido desarrolladas para el proyecto, las librerías son independientes de este.

*	__Modulos de control de hardware:__ La aplicación hace uso de código dedicado al control de los periféricos de la placa Zybo Zync. Este código se ha obtenido de manera externa por lo que se ha decidido excluir de la documentación

Para la documentación del código se han utilizado las técnicas habituales, como por ejemplo el cometario de funciones, de estructuras y el reporte de *todo's*. Además se ha incluido información relevante en la cabecera de los ficheros *.h* y *.c* así como una tabla para representar el historial de versiones que ha sufrido.

A parte de esto, para aclarar el funcionamiento de algunas partes del código, se han añadido imagenes representativas. Un ejemplo lo podemos encontrar en el fichero *menu.c*.

<h2 id="info">Informacion adicional</h2>
@author Javier Peces Chillaron 

@version v0.1

@par THIS SOFTWARE IS PROVIDED "AS IS". NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. ARM SHALL NOT, IN ANY CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL DAMAGES, FOR ANY REASON WHATSOEVER.

@note Copyright (C)  Permission is granted to copy, distribute and/or modify this document under the terms of the GNU Free Documentation License, Version 1.3 or any later version published by the Free Software Foundation; with no Invariant Sections, no Front-Cover Texts,and no Back-Cover Texts. A copy of the license is included in the section entitled "GNU Free Documentation License".

@par ARM Limited (ARM) is supplying this software for use with Cortex-M processor based microcontrollers. This file can be freely distributed within development tools that are supporting such ARM based processors.
  
 
