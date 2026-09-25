# Información General
## Proyecto 2: System Calls en xv6.
### Integrantes: 
Samuel Ramirez, Isabela Ruiz.

## Descripción de la Solución

El proyecto extiende el kernel de xv6-riscv implementando dos nuevas llamadas al sistema orientadas a la introspección: trace y sysinfo. Para lograrlo de manera eficiente, nos dividimos la investigación inicial. Isabela lideró la lógica de intercepción de trace en el despachador central, mientras que Samuel estructuró la extracción de métricas para sysinfo en los módulos de memoria y procesos. Durante la integración, trabajamos en conjunto para depurar errores de compilación y asegurar la transferencia segura de datos hacia el espacio de usuario.   

## Archivos Modificados

Modificamos de manera conjunta kernel/syscall.c, kernel/syscall.h, y kernel/sysproc.c para registrar y habilitar ambas syscalls en el kernel. Para sysinfo, añadimos kernel/sysinfo.h definiendo la estructura compartida, e intervinimos kernel/proc.c y kernel/kalloc.c para implementar los contadores lógicos. En el espacio de usuario, creamos user/trace.c y user/sysinfo.c, modificando user/user.h, user/usys.pl y el archivo Makefile para garantizar su correcta compilación.

## Diseño Realizado

Optamos por utilizar arreglos globales en C para mapear los nombres de las syscalls y una variable global para almacenar el objetivo de monitoreo de trace, permitiendo una intercepción rápida en tiempo de ejecución. Para sysinfo, centralizamos la recolección de recursos directamente en el administrador de memoria (kalloc), asegurando que los datos se transfieran de forma segura usando la función nativa copyout para evitar corrupciones de memoria.   

## Compilación y Ejecución

Para compilar la solución, se debe ubicar en la raíz del proyecto xv6-riscv y ejecutar los comandos make clean seguido de make qemu. Una vez dentro del emulador, se puede ejecutar la herramienta de rastreo ingresando trace seguido del nombre de la syscall objetivo (por ejemplo, trace sys_kill), o visualizar las métricas del sistema ejecutando el comando sysinfo de manera directa.   

## Uso de IA

Durante el desarrollo de este proyecto, utilizamos herramientas de Inteligencia Artificial como apoyo complementario. Específicamente, empleamos la IA para aclarar conceptos sobre la arquitectura del sistema, resolver errores de compilación o lógica durante las pruebas, como asistencia en la redacción de algunos fragmentos de código y para apoyar la escritura de los documentos de texto (.md). Todo el código generado fue analizado, adaptado y validado por el equipo para asegurar que cumpliera con los requerimientos. Declaramos que comprendemos en su totalidad la implementación entregada y nos hacemos responsables de su correcto funcionamiento
