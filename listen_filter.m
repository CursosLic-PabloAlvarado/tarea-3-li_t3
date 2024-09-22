function listen_filter(filterFileName, audioFileName, Fs = 44100)

  [archivo, fs] = audioread('Audios/voz7.wav');
  if (fs != Fs)
    % TODO: Utilizar la función resample para asegurar que las muestras del archivo
    % utilizan la frecuencia de muestreo indicada en la función (con la que fueron
    % diseñados los filtros)
  endif

  % TODO: Permitir escuchar el audio audioFileName al que le es aplicado el filtro con la función filter

endfunction

% TODO: Cuando ya todo esto esté listo, agregar resultados al README
