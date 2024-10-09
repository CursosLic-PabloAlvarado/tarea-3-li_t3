% Script para visualizar la respuesta de 16 filtros diferentes
filter_files = {
    'SavedFilters/butter_lowpass.mat'
    'SavedFilters/butter_highpass.mat'
    'SavedFilters/butter_bandstop.mat',
    'SavedFilters/butter_bandpass.mat',

    'SavedFilters/ellip_lowpass.mat'
    'SavedFilters/ellip_highpass.mat'
    'SavedFilters/ellip_bandstop.mat',
    'SavedFilters/ellip_bandpass.mat',

    'SavedFilters/cheby1_lowpass.mat'
    'SavedFilters/cheby1_highpass.mat'
    'SavedFilters/cheby1_bandstop.mat',
    'SavedFilters/cheby1_bandpass.mat',

    'SavedFilters/cheby2_lowpass.mat'
    'SavedFilters/cheby2_highpass.mat'
    'SavedFilters/cheby2_bandstop.mat',
    'SavedFilters/cheby2_bandpass.mat',
};

Fs = 48000;
for i = 1:length(filter_files)
    filename = filter_files{i};
    printf('Procesando filtro %d: %s\n', i, filename);

    viewfreqresp(filename, Fs);
    pause(1);
end

printf('Procesamiento de todos los filtros completado.\n');
