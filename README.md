# DOSrat

[![Version](https://img.shields.io/github/v/tag/Criper98/DOSrat?color=10&label=Versione)]()
[![Version](https://img.shields.io/badge/OS-Windows-orange)]()

DOSrat è un semplice Remote Administration Tool (RAT) scritto in C++, esso permette di eseguire diverse azioni sul PC nel quale è installato il Client.

## Features

- Possibilità di cambiare la porta da utilizzare (5555 default).
- Possibilità di creare un Client personalizzato direttamente dal server.
- Possibilità di gestire più Client connessi contemporaneamente (max 50).
- Il Client persiste anche dopo il riavvio del PC remoto.

## 1.1.3 Novità

- Aggiunto il comando /sfo! (per maggiori info consultare la lista dei comandi qui sotto)
- Aggiunta la cattura dei click del mouse nel comando /mstk!
- Aggiunta un impostazione per abilitare o disabilitare la cattura dei click del mouse nel comando /mstk.
- Cambiato lo stile di navigazione tra i vari menù!

## 1.1.3 Fixes

- Bug fixes per il comando /tpc.

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
  - /ginf     - Ottieni delle informazioni base del Client e del PC.
  - /help     - Mostra la lista dei comandi disponibili.
- **[Mouse & Keyboard]**
  - /ms       - Inverte i tasti del mouse (/MSR per reimpostarli).
  - /czm      - Fa impazzire il mouse (/CZMR per reimpostarlo).
  - /ml       - Blocca il mouse (/MLR per sbloccarlo).
  - /mvb      - Fa vibrare il puntatore (/MVBR per disattivare).
  - /bmt      - Blocca il mouse e la tastiera (richiede UAC).
  - /lkl      - Entra in modalità "LIVE KEYLOGGER".
  - /mstk     - Entra in modalità "MOUSE TRACK".
- **[Desktop]**
  - /moff     - Spegne il monitor.
  - /msgb     - Fa apparire un "MessageBox" personalizzato.
  - /ows      - Apre un sito a scelta (esempio: /ows youtube.com).
  - /tsk      - Entra in modalità "TASKBAR JOKES".
  - /rpx      - Genera pixel randomici sullo schermo (/rpxr per disattivare).
  - /sfo      - Elimina lo sfondo del PC remoto. [1.1.3]
- **[Computer]**
  - /sw       - Spegne il PC.
  - /rb       - Riavvia il PC.
  - /cdo      - Apre il vano CD (/CDC per chiuderlo).
- **[Misc]**
  - /lag      - Fa "laggare" il PC remoto.
  - /tpc      - Termina un processo a scelta. [1.1.3 - Bug fixes ma presenta ancora problemi]
  - /scy      - Permette di eseguire uno script (vbs,cmd,bat) nel PC remoto.
