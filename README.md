# DOSrat

[![Version](https://img.shields.io/github/v/tag/Criper98/DOSrat?color=10&label=Versione)]()
[![Version](https://img.shields.io/badge/OS-Windows-orange)]()

DOSrat è un semplice Remote Administration Tool (RAT) scritto in C++, esso permette di eseguire diverse azioni sul PC nel quale è installato il Client.

## Features

- Possibilità di cambiare la porta da utilizzare (5555 default).
- Possibilità di creare un Client personalizzato direttamente dal server.
- Possibilità di gestire più Client connessi contemporaneamente (max 50).
- Il Client persiste anche dopo il riavvio del PC remoto.

## 1.1.5 Novità

- Aggiornata la grafica del comando TPC.
- Aggiornata la grafica del comando GINF.
- Aggiornata la grafica nella lista delle connessioni.
- Aggiunta possibilità di vedere la versione del Client dalla lista delle connessioni (Se il Client è inferiore alla 1.1.5 verranno visualizzati dei punti di domanda)

## 1.1.5 Fixes

- Quando il Client cerca di connettersi al Server ora aggiorna dinamicamente l'IP ricavato dal DNS.
- Delle volte non veniva creato il file per salvare le sessioni del comando LKL, ora il file e le cartelle vengono create correttamente.
- Se il Server viene chiuso il Client continua ad eseguire i comandi dati. (quindi anche senza connessione)
- Migliorato il protocollo del Client per gestire la perdita di connessione.
- Risolto il bug delle connessioni multiple da un singolo Client.

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
  - LKL      - Entra in modalità "LIVE KEYLOGGER".
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
  - BSOD     - Triggera il Blue Screen Of Death.
  - CDO      - Apre il vano CD (CDC per chiuderlo).
- **[Misc]**
  - LAG      - Fa "laggare" il PC remoto.
  - TPC      - Termina un processo a scelta.
  - SCY      - Permette di eseguire uno script (vbs,cmd,bat) nel PC remoto.
  - BEEP     - Riproduce suoni randomici sul PC remoto (BEEPR per disattivare).
