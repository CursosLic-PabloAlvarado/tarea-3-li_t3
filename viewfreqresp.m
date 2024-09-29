function viewfreqresp(filename, Fs = 48000)
    pkg load signal
    close all

    % Cargar la matriz SOS desde el archivo .mat
    data = load(filename, "sos");
    sos = data.sos;

    % Convertir SOS a numerador/denominador
    [b, a] = sos2tf(sos);

    w = logspace(log10(1), log10(Fs/2), 1000);
    w_rad = w * 2 * pi / Fs; % radianes

    % Evaluar la función de transferencia en estos puntos de numerador y
    % denominador en un conjunto de puntos que representan la transformada Z
    H = polyval(b, exp(1i * w_rad)) ./ polyval(a, exp(1i * w_rad));

    % Plot de magnitud
    figure('name', filename);
    subplot(2, 1, 1);
    semilogx(w, 20*log10(abs(H)), 'Color', [0, 0.447, 0.741], 'LineWidth', 3);  % Magnitud en dB
    grid on;
    title('Respuesta en Magnitud');
    xlabel('Frecuencia [Hz]');
    ylabel('Magnitud [dB]');
    axis tight;

    % Calcular y ajustar la fase
    phase_degrees = angle(H) * (180 / pi);
    phase_degrees = mod(phase_degrees, 360) - 360; % Ajustar la fase a -360 a 0 grados

    % Plot de fase
    subplot(2, 1, 2);
    semilogx(w, phase_degrees, 'Color', [0, 0.447, 0.741], 'LineWidth', 3);  % Fase en grados

    grid on;
    title('Respuesta en Fase');
    xlabel('Frecuencia [Hz]');
    ylabel('Fase (grados)');
    axis tight;

    % Diagrama de polos y ceros
    figure;
    zplane(b, a);
    title('Diagrama de Polos y Ceros');
endfunction

