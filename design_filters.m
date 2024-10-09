close all
pkg load signal

%% Constantes
Fs = 48000; % Frecuencias de muestreo

Wp_pb = 440;  % Frecuencia de corte para filtro paso bajos (Hz)
Wp_pa = 600;  % Frecuencia de corte para filtro paso altos (Hz)
Wl    = 220;  % Frecuencia de límite inferior (Hz)
Wh    = 1000; % Frecuencia de límite superior (Hz)

N = 3;   % Orden del filtro
Rp = 1;  % Rizado en banda de paso (dB)
Rs = 50; % Atenuación en banda de rechazo (dB)

my_route = './SavedFilters/';

%% Normalización (Se toman las constantes de arriba para normalizarlas - No tocar -)
Wp_pb = Wp_pb / (Fs/2); % Frecuencia de corte pasa bajos normalizada
Wp_pa = Wp_pa / (Fs/2); % Frecuencia de corte pasa altos normalizada
Wl    = Wl / (Fs/2);     % Frecuencia de corte inferior para paso bandas y supresores normalizada
Wh    = Wh / (Fs/2);     % Frecuencia de corte superior para paso bandas y supresores normalizada

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%% Filtros paso bajo %%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%

% ellip (Con parámetros: Orden del filtro, rizado en la banda pasante, atenuación en la
%        banda de rechazo, frecuencia de corte normalizada y tipo de filtro)
[b, a] = ellip(N, Rp, Rs, Wp_pb, 'low'); % Diseño del filtro
                                         % Donde 'a' y 'b' corresponden a los coeficientes
                                         % devueltos por el filtro butter (estos definen la
                                         % ecuación de diferencia del filtro digital)
sos = tf2sos(b, a);
save([my_route 'ellip_lowpass.mat'], 'sos');


% butter (Con parámetros: Orden del filtro, frecuencia de corte normalizada y tipo de filtro).
[b, a] = butter(N, Wp_pb, 'low');
sos = tf2sos(b, a);
save([my_route 'butter_lowpass.mat'], 'sos');


% cheby1
[b, a] = cheby1(N, Rp, Wp_pb, 'low');
sos = tf2sos(b, a);  % Conversión a SOS con ganancia
save([my_route '_lowpass.mat'], 'sos');  % Guarda los coeficientes en formato .mat


% cheby2
[b, a] = cheby2(N, Rs, Wp_pb, 'low');
sos = tf2sos(b, a);
save([my_route 'cheby2_lowpass.mat'], 'sos');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%% Filtros paso alto %%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% ellip
[b, a] = ellip(N, Rp, Rs, Wp_pa, 'high');
sos = tf2sos(b, a);
save([my_route 'ellip_highpass.mat'], 'sos');


% butter
[b, a] = butter(N, Wp_pa, 'high');
sos = tf2sos(b, a);
save([my_route 'butter_highpass.mat'], 'sos');


% cheby1
[b, a] = cheby1(N, Rp, Wp_pa, 'high');
sos = tf2sos(b, a);
save([my_route 'cheby1_highpass.mat'], 'sos');


% cheby2
[b, a] = cheby2(N, Rs, Wp_pa, 'high');
sos = tf2sos(b, a);
save([my_route 'cheby2_highpass.mat'], 'sos');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%%%%%%% Filtros paso bandas %%%%%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% ellip
[b, a] = ellip(N, Rp, Rs, [Wl Wh]);
sos = tf2sos(b, a);
save([my_route '.mat'], 'sos');


% butter
[b, a] = butter(N, [Wl Wh]);
sos = tf2sos(b, a);
save([my_route 'butter_bandpass.mat'], 'sos');


% cheby1
[b, a] = cheby1(N, Rp, [Wl Wh]);
sos = tf2sos(b, a);
save([my_route 'cheby1_bandpass.mat'], 'sos');


% cheby2
[b, a] = cheby2(N, Rs, [Wl Wh]);
sos = tf2sos(b, a);
save([my_route 'cheby2_bandpass.mat'], 'sos');

%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
%%%%%%%%%% Filtros supresores de banda %%%%%%%%%%%
%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
% ellip
[b, a] = ellip(N, Rp, Rs, [Wl Wh], 'stop');
sos = tf2sos(b, a);
save([my_route 'ellip_bandstop.mat'], 'sos');


% butter
[b, a] = butter(N, [Wl Wh], 'stop');
sos = tf2sos(b, a);
save([my_route 'butter_bandstop.mat'], 'sos');


% cheby1
[b, a] = cheby1(N, Rp, [Wl Wh], 'stop');
sos = tf2sos(b, a);
save([my_route 'cheby1_bandstop.mat'], 'sos');


% cheby2
[b, a] = cheby2(N, Rs, [Wl Wh], 'stop');
sos = tf2sos(b, a);
save([my_route 'cheby2_bandstop.mat'], 'sos');

