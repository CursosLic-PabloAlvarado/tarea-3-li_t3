% Generar ruido blanco
fs = 48000; % Frecuencia de muestreo en Hz
duracion = 5; % Duración en segundos

% Ruido blanco
ruido_blanco = randn(fs * duracion, 1); % Generar señal de ruido blanco
ruido_blanco = ruido_blanco / max(abs(ruido_blanco)); % Normalizar entre -1 y 1
filename_ruido_blanco = 'ruido_blanco.wav';
audiowrite(filename_ruido_blanco, ruido_blanco, fs); % Guardar como archivo .wav

% Generar barrido de frecuencia
f_inicial = 20; % Frecuencia inicial del barrido en Hz
f_final = 20000; % Frecuencia final del barrido en Hz
t = linspace(0, duracion, fs * duracion); % Vector de tiempo

% Generar el barrido de frecuencia (chirp)
barrido_frecuencia = sin(2 * pi * f_inicial * (t + (f_final - f_inicial) / (2 * duracion) * t.^2));

% Normalizar entre -1 y 1
barrido_frecuencia = barrido_frecuencia / max(abs(barrido_frecuencia));

filename_barrido_frecuencia = 'barrido_frecuencia.wav';
audiowrite(filename_barrido_frecuencia, barrido_frecuencia, fs); % Guardar como archivo .wav

disp('Archivos de audio generados: ruido_blanco.wav y barrido_frecuencia.wav');

