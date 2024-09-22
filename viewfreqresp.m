function viewfreqresp(fileName, Fs = 44100)

  % TODO: Cargar la matriz con Data=load("método_tipo.mat", "SOS")
  % TODO: Usar la funcion sos2fs para recuperar el filtro completo con todas las etapas

  % TODO: Construir su propio código que le permita controlar exactamente cómo mostrar la
  % información. Se desea:
  % - La frecuencia (en hertz)
  % - El ángulo (en grados)
  % - La respuesta en magnitud (en decibeles)
  % Nota: NO utilizar la función bode(filt(B,A))

  % TODO: Hacer el plot de fase y magnitud. Se recomienda reconstruir H(z) utilizando polyval
  % para numerador y denominador, y luego evaluar dicha función como corresponda para encontrar
  % la respuesta en frecuencia

  % TODO: Utilizar los ejes logarítmicos o lineales, según corresponda, para lograr que el plot
  % esté dado en decibeles [dB], los ángulos en grados, y la frecuencia de 1 Hz a Fs/2.
  % Nota 1: Las funciones de GNU/Octave logspace, semilogx pueden ser de utilidad.
  % Nota 2: Usted va a tener que manipular la fase, para que aparezca en rangos sencillos de interpretar
  % (usualmente de −360◦ a 0◦).
  % Nota 3: Deberá utilizar axis para que los rangos mostrados no se salgan de control, etiquetar los ejes
  % con xlabel y ylabel, y mostrar la rejilla (grid).

  % TODO: Diagrama de polos y ceros. -> Utilizar zplane


endfunction
