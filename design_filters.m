close all
pkg load signal

%% Constantes
Fs = 44100; % Frecuencias de muestreo

Wp_pb = 440;  % Frecuencia de corte para filtro paso bajos (Hz)
Wp_pa = 600;  % Frecuencia de corte para filtro paso altos (Hz)
Wl    = 220;  % Frecuencia de límite inferior (Hz)
Wh    = 1000; % Frecuencia de límite superior (Hz)

N = 3;   % Orden del filtro
Rp = 1;  % Rizado en banda de paso (dB)
Rs = 50; % Atenuación en banda de rechazo (dB)

%% Normalización (Se toman las constantes de arriba para normalizarlas - No tocar -)
Wp_pb = Wp_pb / (Fs/2); % Frecuencia de corte pasa bajos normalizada
Wp_pa = Wp_pa / (Fs/2); % Frecuencia de corte pasa altos normalizada
Wl    = Wl / (Fs/2);     % Frecuencia de corte inferior para paso bandas y supresores normalizada
Wh    = Wh / (Fs/2);     % Frecuencia de corte superior para paso bandas y supresores normalizada
                        % TODO: Explicar en el README porqué es necesario normalizar


% TODO: Quitar tanto comentario y mejor meterlo en el README
% TODO: Explicar cada tipo de filtro en el README
%% Filtros paso bajos
% ellip (Con parámetros: Orden del filtro, rizado en la banda pasante, atenuación en la
%        banda de rechazo, frecuencia de corte normalizada y tipo de filtro)
[b, a] = ellip(N, Rp, Rs, Wp_pb, 'low'); % Diseño del filtro
                                         % Donde 'a' y 'b' corresponden a los coeficientes
                                         % devueltos por el filtro butter (estos definen la
                                         % ecuación de diferencia del filtro digital)

[h, w] = freqz(b, a, 1024, Fs); % Visualización de la respuesta en frecuencia.

                                  % Freqz permite visualizar cómo los coeficientes del filtro
                                  % afectan diferentes frecuencias de una señal.

                                  % 1024 son los puntos para los que se calcula la respuesta
                                  % en frecuencia.

                                  % En cuanto a la salida, 'h' y 'w' corresponden a:
                                  % - h: Guarda los valores de la respuesta en frecuencia del filtro.
                                  %      Es decir, h es un vector complejo que representa la respuesta
                                  %      en frecuencia del filtro para cada frecuencia del vector w. Cada
                                  %      elemento del vector h es un número complejo donde:
                                  %      + |h|: Indica la magnitud de la respuesta del filtro en esa
                                  %             frecuencia. Esta magnitud muestra cuánto se atenúa o
                                  %             amplifica una señal a esa frecuencia específica.
                                  %      + ∠h: Representa la fase de la respuesta del filtro en esa frecuencia,
                                  %            indicando así cuánto se retrasa o adelanta la señal en esa
                                  %            frecuencia específica.
                                  %
                                  % - w: Contiene los valores de frecuencia (en radianes por segundo) para
                                  %      los cuales se calcula la respuesta en frecuencia almacenada en h.
figure('name', 'Paso bajos con ellip');
plot(w, 20*log10(abs(h))) % Traza la respuesta en frecuencia del filtro.
                          % - w traza las frecuencia en Hz para las cuales se calcula la respuesta en frecuencia.
                          % - 20*log10(abs(h)) convierte la respuesta de frecuencia h de magnitud a decibelios (dB).
title('Respuesta en frecuencia del filtro paso bajos diseñado con ellip')
xlabel('Frecuencia (Hz)')
ylabel('Amplitud (dB)')
grid on;


% butter (Con parámetros: Orden del filtro, frecuencia de corte normalizada y tipo de filtro).
%         Note que: Tiene una respuesta inherentemente plana en la banda pasante, por lo que
%                   no necesita de un tipo de rizado
[b, a] = butter(N, Wp_pb, 'low');

[h, w] = freqz(b, a, 1024, Fs); % Visualización de la respuesta en frecuencia
figure('name', 'Paso bajos con butter');
plot(w, 20*log10(abs(h)))
title('Respuesta en frecuencia del filtro paso bajos diseñado con butter')
xlabel('Frecuencia (Hz)')
ylabel('Amplitud (dB)')
grid on;


% cheby1
% cheby1 - Filtro paso bajos
[b, a] = cheby1(N, Rp, Wp_pb, 'low');
[sos, g] = tf2sos(b, a);  % Conversión a SOS con ganancia
save('cheby1_lowpass.mat', 'sos');  % Guarda los coeficientes en formato .mat

[h, w] = freqz(b, a, 1024, Fs);
figure('name', 'Paso bajos con cheby1');
plot(w, 20*log10(abs(h)))
title('Respuesta en frecuencia del filtro paso bajos diseñado con cheby1')
xlabel('Frecuencia (Hz)')
ylabel('Amplitud (dB)')
grid on;

% cheby2
% cheby2 - Filtro paso bajos
[b, a] = cheby2(N, Rs, Wp_pb, 'low');
[sos, g] = tf2sos(b, a);  % Conversión a SOS con ganancia
save('cheby2_lowpass.mat', 'sos');  % Guarda los coeficientes en formato .mat

[h, w] = freqz(b, a, 1024, Fs);
figure('name', 'Paso bajos con cheby2');
plot(w, 20*log10(abs(h)))
title('Respuesta en frecuencia del filtro paso bajos diseñado con cheby2')
xlabel('Frecuencia (Hz)')
ylabel('Amplitud (dB)')
grid on;


%% Filtros paso altos
% ellip % TODO: Ajustar mejor el eje y para que se vea mejor el efecto de este filtro
[b, a] = ellip(N, Rp, Rs, Wp_pa, 'high'); % Diseño del filtro

[h, w] = freqz(b, a, 1024, Fs); % Visualización de la respuesta en frecuencia.
figure('name', 'Paso altos con elip');
plot(w, 20*log10(abs(h)))
title('Respuesta en frecuencia del filtro paso altos diseñado con ellip')
xlabel('Frecuencia (Hz)')
ylabel('Amplitud (dB)')
grid on;


% butter % TODO: Ajustar mejor el eje y para que se vea mejor el efecto de este filtro
[b, a] = butter(N, Wp_pa, 'high');

[h, w] = freqz(b, a, 1024, Fs); % Visualización de la respuesta en frecuencia
figure('name', 'Paso altos con butter');
plot(w, 20*log10(abs(h)))
title('Respuesta en frecuencia del filtro paso altos diseñado con butter')
xlabel('Frecuencia (Hz)')
ylabel('Amplitud (dB)')
grid on;


% cheby1
% cheby1 - Filtro paso altos
[b, a] = cheby1(N, Rp, Wp_pa, 'high');
[sos, g] = tf2sos(b, a);  % Conversión a SOS con ganancia
save('cheby1_highpass.mat', 'sos');  % Guarda los coeficientes en formato .mat

[h, w] = freqz(b, a, 1024, Fs);
figure('name', 'Paso altos con cheby1');
plot(w, 20*log10(abs(h)))
title('Respuesta en frecuencia del filtro paso altos diseñado con cheby1')
xlabel('Frecuencia (Hz)')
ylabel('Amplitud (dB)')
grid on;


% cheby2
% cheby2 - Filtro paso altos
[b, a] = cheby2(N, Rs, Wp_pa, 'high');
[sos, g] = tf2sos(b, a);  % Conversión a SOS con ganancia
save('cheby2_highpass.mat', 'sos');  % Guarda los coeficientes en formato .mat

[h, w] = freqz(b, a, 1024, Fs);
figure('name', 'Paso altos con cheby2');
plot(w, 20*log10(abs(h)))
title('Respuesta en frecuencia del filtro paso altos diseñado con cheby2')
xlabel('Frecuencia (Hz)')
ylabel('Amplitud (dB)')
grid on;


%% Filtros paso bandas
% ellip % TODO: Ajustar mejor el eje x para que se vea mejor el efecto de este filtro
[b, a] = ellip(N, Rp, Rs, [Wl Wh]); % Diseño del filtro

[h, w] = freqz(b, a, 1024, Fs); % Visualización de la respuesta en frecuencia
figure('name', 'Paso bandas con elip');
plot(w, 20*log10(abs(h)))
title('Respuesta en frecuencia del filtro paso bandas diseñado con ellip')
xlabel('Frecuencia (Hz)')
ylabel('Amplitud (dB)')
grid on;


% butter % TODO: Ajustar mejor el eje x para que se vea mejor el efecto de este filtro
[b, a] = butter(N, [Wl Wh]);

[h, w] = freqz(b, a, 1024, Fs); % Visualización de la respuesta en frecuencia
figure('name', 'Paso bandas con butter');
plot(w, 20*log10(abs(h)))
title('Respuesta en frecuencia del filtro paso bandas diseñado con butter')
xlabel('Frecuencia (Hz)')
ylabel('Amplitud (dB)')
grid on;


% cheby1
% cheby1 - Filtro paso bandas
[b, a] = cheby1(N, Rp, [Wl Wh]);
[sos, g] = tf2sos(b, a);  % Conversión a SOS con ganancia
save('cheby1_bandpass.mat', 'sos');  % Guarda los coeficientes en formato .mat

[h, w] = freqz(b, a, 1024, Fs);
figure('name', 'Paso bandas con cheby1');
plot(w, 20*log10(abs(h)))
title('Respuesta en frecuencia del filtro paso bandas diseñado con cheby1')
xlabel('Frecuencia (Hz)')
ylabel('Amplitud (dB)')
grid on;

% cheby2
% cheby2 - Filtro paso bandas
[b, a] = cheby2(N, Rs, [Wl Wh]);
[sos, g] = tf2sos(b, a);  % Conversión a SOS con ganancia
save('cheby2_bandpass.mat', 'sos');  % Guarda los coeficientes en formato .mat

[h, w] = freqz(b, a, 1024, Fs);
figure('name', 'Paso bandas con cheby2');
plot(w, 20*log10(abs(h)))
title('Respuesta en frecuencia del filtro paso bandas diseñado con cheby2')
xlabel('Frecuencia (Hz)')
ylabel('Amplitud (dB)')
grid on;


%% Filtros supresores de banda
% ellip % TODO: Ajustar mejor el eje x para que se vea mejor el efecto de este filtro
[b, a] = ellip(N, Rp, Rs, [Wl Wh], 'stop'); % Diseño del filtro

[h, w] = freqz(b, a, 1024, Fs); % Visualización de la respuesta en frecuencia
figure('name', 'Rechaza bandas con ellip');
plot(w, 20*log10(abs(h)))
title('Respuesta en frecuencia del filtro rechaza bandas diseñado con ellip')
xlabel('Frecuencia (Hz)')
ylabel('Amplitud (dB)')
grid on;


% butter
[b, a] = butter(N, [Wl Wh], 'stop');

[h, w] = freqz(b, a, 1024, Fs); % Visualización de la respuesta en frecuencia
figure('name', 'Rechaza bandas con butter');
plot(w, 20*log10(abs(h)))
title('Respuesta en frecuencia del filtro rechaza bandas diseñado con butter')
xlabel('Frecuencia (Hz)')
ylabel('Amplitud (dB)')
grid on;


% cheby1
% cheby1 - Filtro supresor de banda
[b, a] = cheby1(N, Rp, [Wl Wh], 'stop');
[sos, g] = tf2sos(b, a);  % Conversión a SOS con ganancia
save('cheby1_bandstop.mat', 'sos');  % Guarda los coeficientes en formato .mat

[h, w] = freqz(b, a, 1024, Fs);
figure('name', 'Rechaza bandas con cheby1');
plot(w, 20*log10(abs(h)))
title('Respuesta en frecuencia del filtro rechaza bandas diseñado con cheby1')
xlabel('Frecuencia (Hz)')
ylabel('Amplitud (dB)')
grid on;

% cheby2
% cheby2 - Filtro supresor de banda
[b, a] = cheby2(N, Rs, [Wl Wh], 'stop');
[sos, g] = tf2sos(b, a);  % Conversión a SOS con ganancia
save('cheby2_bandstop.mat', 'sos');  % Guarda los coeficientes en formato .mat

[h, w] = freqz(b, a, 1024, Fs);
figure('name', 'Rechaza bandas con cheby2');
plot(w, 20*log10(abs(h)))
title('Respuesta en frecuencia del filtro rechaza bandas diseñado con cheby2')
xlabel('Frecuencia (Hz)')
ylabel('Amplitud (dB)')
grid on;


%%%%%%%%%
% TODO: Agregar referencias en el README:
%       - ttps://octave.sourceforge.io/signal/function/ellip.html
%       - https://octave.sourceforge.io/signal/function/butter.html
% TODO: Utilizar la función tf2sos para las matrices
% TODO: Guardar los filtros con save("método_tipo.mat", "SOS")
