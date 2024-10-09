# Filtrado en el tiempo

Este código permite recibir una lista de archivos .wav, que se ejecutan uno tras otro, reemplazando la entrada de micrófono en tanto hayan datos de los archivos disponibles.  Una vez que todos los archivos terminan de ejecutarse, regresa al modo "pass-through".

## Estructura del código
|- **Audios/**: Directorio con audios para probar los filtros.

|- **SavedFilters/**: Directorio con los archivos `.mat` diseñados con GNU/Octave.

|- **Docs/**: Directorio con los archivos `.pdf`.

|-- `Tarea__3___DSP.pdf`: Informe de la Tarea 3. 

|-- `tarea03.pdf`: Especificación de la Tarea 3.

|- `main.cpp`: Archivo principal que importará, llamará y ejecutará el resto de archivos del proyecto

<br>

## Dependencias

Requiere C++ en su estándar del 2020 (g++ 12, clang 14).

En derivados de debian (ubuntu, etc):

```bash
sudo apt install jackd2 libjack-jackd2-dev qjackctl build-essential meson ninja-build jack-tools libsndfile1-dev libsndfile1 libboost-all-dev 
```
     
Jack requiere que su usuario pertenezca al grupo audio, o de otro modono tendrá privilegios para el procesamiento demandante en tiempo real:

```bash
sudo usermod -aG audio $USER
```

<br>

## Construcción y compilación

Para construir los ejemplos la primera vez en C++ utilice:
```bash
meson setup builddir
ninja -C builddir
```

Si solamente desea compilar el código, ejecute:
```bash
ninja -C builddir
```

<br>

## Ejecución

### GNU/Octave
Para ejecutar el código y obtener las gráficas deseadas:
1. Sitúese en el directorio ``tarea-3-li_t3/``
2. Abra una terminal en esta ubicación
3. Ingrese al modo Octave mediante ejecutar el siguiente comando:
```Bash
octave
```
4. En modo Octave, para diseñar los filtros llame a la función mediante:

```octave
design_filters
```
5. Para escuchar los Filtros digitales llame a la función mediante:

```octave
listen_filter('./SavedFilters/método_tipo.mat', 'Audios/audio.wav')
```

Nota: Para visualizar las Figuras de la Respuesta en Magnitud y Respuesta en Fase así como el Diagrama de Polos y Ceros ejecute, desde la terminal (NO en modo Octave), el siguiente comando:
```bash
./run_octave_figures.sh
```

### C++
Primeramente se deberá de iniciar, manualmente, el servidor de jack. Para ello ejecute:
```bash
qjackctl
```

Posteriormente, ejecute el código base ya compilado mediante:
```bash
./builddir/tarea3
```

En caso de querer agregar algún parámetro, puede utilizar lo siguiente:


     
| Larga      | C. | Tipo  | Descripción                                          |
|------------|----|-------|------------------------------------------------------|
| --files    | -f | string| lista de archivos .wav a reproducir                  |
| --coeffs   | -c | string| archivo .mat para cargar filtro                      |

de esta manera es posible, por ejemplo, agregar archivos al reproductor mediante:
```bash
./builddir/tarea3 -c SavedFilters/butter_lowpass.mat -f Audios/ruido_blanco.wav
```

<br>

## Latencia y tamaño de bloque

Para reducir la latencia por medio del tamaño del "periodo" (esto es, el número de "frames" que cada ciclo de procesamiento recibe, en QjackCtl, en Settings, se indica en Frames/Period.  Eso es un parámetro del servidor de Jack y no lo puede controlar la aplicación como tal.

<br>




## Autores
- José Pablo Alvarado Moya (Autor del código base)
- Lizzy González Alvarado
- Ignacio Grané Rojas

## Referencias utilizadas
- https://octave.sourceforge.io/signal/function/ellip.html
- https://octave.sourceforge.io/signal/function/butter.html
- https://octave.sourceforge.io/signal/function/cheby1.html
- https://octave.sourceforge.io/signal/function/cheby2.html
