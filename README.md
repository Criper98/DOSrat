# DOSrat

[![Version](https://img.shields.io/github/v/tag/Criper98/DOSrat?color=10&label=Versione)]()
[![Version](https://img.shields.io/badge/OS-Windows-orange)]()

DOSrat è un semplice Remote Administration Tool (RAT) scritto in C++, esso permette di eseguire diverse azioni sul PC nel quale è installato il Client.

## Features

- Possibilità di cambiare la porta da utilizzare (5555 default).
- Possibilità di creare un Client personalizzato direttamente dal server.
- Possibilità di gestire più Client connessi contemporaneamente (max 50).
- Il Client persiste anche dopo il riavvio del PC remoto.

## 1.1.4 Novità

- Aggiunto il comando BSOD! (per maggiori info consultare la lista dei comandi qui sotto)
- Aggiunto il comando BEEP! (per maggiori info consultare la lista dei comandi qui sotto)
- Aggiunta la possibilità di salvare su file le sessioni del comando LKL!
- Aggiunta una relativa opzione per disabilitare la funzione sopra citata.
- Rimosso lo "/" prima dei comandi per rendere la digitazione più immediata.

## 1.1.4 Fixes

- Aggiunto un controllo per verificare la/l' presenza/accessibilità del file dosc.cpp, che, se mancante causava l'arresto del programma.
- Aggiornata l'estetica del comando SCY.
- Fixato il bug delle "connessioni fantasma".

## Video tutorial

- https://youtu.be/AAtpKh9KWLs

## Immagini
|Schermata iniziale |In attesa |Impostazioni |
|-------------------|----------|-------------|
|![image 1](https://i.ibb.co/ZMhGgkY/1.png)|![image 2](https://i.ibb.co/XX4YKgm/2.png)|![image 3](https://i.ibb.co/fFSMDf2/3.png)|

## Comandi

- **[Client & Server]**
  - CLOSE    - Chiude la sessione corrente.
  - CLS      - Pulisce la console.
  - RVC      - Riavvia il Client.
  - SPC      - Chiude il Client.
  - DELC     - Disinstalla il Client dal PC remoto.
  - GINF     - Ottieni delle informazioni base del Client e del PC.
  - HELP     - Mostra la lista dei comandi disponibili.
- **[Mouse & Keyboard]**
  - MS       - Inverte i tasti del mouse (MSR per reimpostarli).
  - CZM      - Fa impazzire il mouse (CZMR per reimpostarlo).
  - ML       - Blocca il mouse (MLR per sbloccarlo).
  - MVB      - Fa vibrare il puntatore (MVBR per disattivare).
  - BMT      - Blocca il mouse e la tastiera (richiede UAC).
  - LKL      - Entra in modalità "LIVE KEYLOGGER". [1.1.4 - Le sessioni ora sono salvabili su file]
  - MSTK     - Entra in modalità "MOUSE TRACK".
- **[Desktop]**
  - MOFF     - Spegne il monitor.
  - MSGB     - Fa apparire un "MessageBox" personalizzato.
  - OWS      - Apre un sito a scelta (esempio: ows youtube.com).
  - TSK      - Entra in modalità "TASKBAR JOKES".
  - RPX      - Genera pixel randomici sullo schermo (RPXR per disattivare).
  - SFO      - Elimina lo sfondo del PC remoto.
- **[Computer]**
  - SW       - Spegne il PC.
  - RB       - Riavvia il PC.
  - BSOD     - Triggera il Blue Screen Of Death. [1.1.4]
  - CDO      - Apre il vano CD (CDC per chiuderlo).
- **[Misc]**
  - LAG      - Fa "laggare" il PC remoto.
  - TPC      - Termina un processo a scelta.
  - SCY      - Permette di eseguire uno script (vbs,cmd,bat) nel PC remoto. [1.1.4 - Estetica aggiornata]
  - BEEP     - Riproduce suoni randomici sul PC remoto (BEEPR per disattivare). [1.1.4]
