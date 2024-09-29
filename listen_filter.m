function listen_filter(filterFileName, audioFileName, Fs = 48000)

    my_route = './SavedFilters/';


    % Cargar la matriz SOS
    data = load(filterFileName, 'sos');
    sos = data.sos;

    [file, wavFs] = audioread(audioFileName);

    wavFs

    if wavFs ~= Fs
        disp(['Re-muestreando de ', num2str(wavFs), ' Hz a ', num2str(Fs), ' Hz.']);
        file = resample(file, Fs, wavFs);  % Re-muestrear a la Fs deseada
    end

    % Aplicar el filtro
    file_filtered = sosfilt(sos, file);

    sound(file_filtered, Fs);

endfunction

% TODO: Cuando ya todo esto esté listo, agregar resultados al README
