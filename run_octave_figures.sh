#!/bin/bash

# Directorio donde están los archivos .mat
mat_directory="./SavedFilters/"  # Cambia esta ruta si tus archivos están en otro lugar

# Iterar sobre cada archivo .mat en el directorio
for mat_file in "$mat_directory"*.mat; do
    # Ejecutar Octave para cada archivo
    echo "Procesando archivo: $mat_file"
    octave --persist --eval "viewfreqresp('$mat_file', 48000)" &
done

wait
