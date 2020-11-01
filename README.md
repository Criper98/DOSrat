# DOSrat

[![Version](https://img.shields.io/github/v/tag/Criper98/DOSrat?color=10&label=Versione)]()
[![Version](https://img.shields.io/badge/OS-Windows-orange)]()

DOSrat è un semplice Remote Administration Tool (RAT) scritto in C++, esso permette di eseguire diverse azioni sul PC nel quale è installato il Client.

## Features

- Possibilità di cambiare la porta da utilizzare (5555 default).
- Possibilità di creare un Client personalizzato direttamente dal server.
- Possibilità di gestire più Client connessi contemporaneamente (max 50).
- Il Client persiste anche dopo il riavvio del PC remoto.

## 1.1.0 Novità

- Un sacco di bug fixes!
- Aggiunto il comando /mstk!
- Aggiornato il comando /lkl. (per maggiori info consultare la lista dei comandi qui sotto)
- Aggiornato il comando /ginf. (per maggiori info consultare la lista dei comandi qui sotto)
- Aggiunto un Update Checker!
- Aggiunte le impostazioni per il comando /lkl e per gli Update!
- Modificata la grafica del comado /help!

## Video tutorial

- https://youtu.be/AAtpKh9KWLs

## Immagini
|Schermata iniziale |In attesa |Impostazioni |
|-------------------|----------|-------------|
|![image 1](https://i.ibb.co/ZMhGgkY/1.png)|![image 2](https://i.ibb.co/XX4YKgm/2.png)|![image 3](https://i.ibb.co/fFSMDf2/3.png)|

## Comandi

- **[Client & Server]**
  - /close    - Chiude la sessione corrente.
  - /cls      - Pulisce la console.
  - /rvc      - Riavvia il Client.
  - /spc      - Chiude il Client.
  - /delc     - Disinstalla il Client dal PC remoto.
  - /ginf     - Ottieni delle informazioni base del Client e del PC. [1.1.0 - Aggiunta la data d'installazione]
  - /help     - Mostra la lista dei comandi disponibili. [1.1.0 - Rivisitato lo stile grafico]
- **[Mouse & Keyboard]**
  - /ms       - Inverte i tasti del mouse (/MSR per reimpostarli).
  - /czm      - Fa impazzire il mouse (/CZMR per reimpostarlo).
  - /ml       - Blocca il mouse (/MLR per sbloccarlo).
  - /mvb      - Fa vibrare il puntatore (/MVBR per disattivare).
  - /bmt      - Blocca il mouse e la tastiera (richiede UAC).
  - /lkl      - Entra in modalità "LIVE KEYLOGGER". [1.1.0 - Invece di cancellare un carattere viene scritto [BACKSPACE]]
  - /mstk     - Entra in modalità "MOUSE TRACK". [1.1.0 - Permette di controllare il mouse della vittima da remoto]
- **[Desktop]**
  - /moff     - Spegne il monitor.
  - /msgb     - Fa apparire un "MessageBox" personalizzato.
  - /ows      - Apre un sito a scelta (esempio: /ows youtube.com).
  - /tsk      - Entra in modalità "TASKBAR JOKES".
  - /rpx      - Genera pixel randomici sullo schermo (/rpxr per disattivare).
- **[Computer]**
  - /sw       - Spegne il PC.
  - /rb       - Riavvia il PC.
  - /cdo      - Apre il vano CD (/CDC per chiuderlo).
- **[Misc]**
  - /lag      - Fa "laggare" il PC remoto.
  - /tpc      - Termina un processo a scelta.
