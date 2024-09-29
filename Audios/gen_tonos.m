% Parámetros para el audio
fs = 44100;  % Frecuencia de muestreo en Hz
t = 0:1/fs:2-1/fs;  % Vector de tiempo para 2 segundos de audio
silencio = zeros(1, fs);  % Vector de silencio de 1 segundo

% Generación de tonos
tono1 = sin(2*pi*330*t);   % Tono de 330 Hz
tono2 = sin(2*pi*400*t);   % Tono de 400 Hz
tono3 = sin(2*pi*800*t);   % Tono de 800 Hz
tono4 = sin(2*pi*1500*t);  % Tono de 1500 Hz

% Combinar los tonos y los silencios
audio = [tono1, silencio, tono2, silencio, tono3, silencio, tono4];

% Reproducir el audio
sound(audio, fs);

% Opcionalmente, guardar el audio en un archivo .wav
audiowrite('tonos.wav', audio, fs);

