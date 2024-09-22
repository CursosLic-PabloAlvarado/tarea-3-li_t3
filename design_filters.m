pkg load signal

%% Constantes
Fs = 44100; % Frecuencias de muestreo

Wp_pb = 440;  % Frecuencia de corte para filtro paso bajos
Wp_pa = 600;  % Frecuencia de corte para filtro paso altos
Wl    = 220;  % Frecuencia de límite inferior
Wh    = 1000; % Frecuencia de límite superior

N = 3;   % Orden del filtro
Rp = 1;  % Rizado en banda de paso
Rs = 50; % Atenuación en banda de rechazo

%% Normalización (Se toman las constantes de arriba para normalizarlas - No tocar -)
Wp_pb = Wp_pb / (Fs/2); % Frecuencia de corte normalizada



%% Filtros paso bajos
% ellip (Con parámetros: Orden del filtro, rizado en la banda pasante, atenuación en la
%        banda de rechazo, frecuencia de corte normalizada y tipo de filtro)
[b, a] = ellip(N, Rp, Rs, Wp_pb, 'low');

% Visualización de la respuesta en frecuencia
[h, w] = freqz(b, a, 1024, Fs);
figure;
plot(w, 20*log10(abs(h)))
title('Respuesta en frecuencia del filtro paso bajos diseñado con ellip')
xlabel('Frecuencia (Hz)')
ylabel('Amplitud (dB)')
grid on;

% butter



%% Filtros paso altos
% ellip (Con parámetros: Orden del filtro, rizado en la banda pasante, atenuación en la
%        banda de rechazo y frecuencia de corte normalizada)


% butter




%% Filtros paso bandas
% ellip (Con parámetros: Orden del filtro, rizado en la banda pasante, atenuación en la
%        banda de rechazo y frecuencia de corte normalizada)


% butter




%% Filtros supresores de banda
% ellip (Con parámetros: Orden del filtro, rizado en la banda pasante, atenuación en la
%        banda de rechazo y frecuencia de corte normalizada)


% butter

