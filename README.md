# DOSrat

DOSrat è un semplice Remote Administration Tool (RAT) scritto in C++, esso permette di eseguire diverse azioni sul PC nel quale è installato il Client.

## Features

- Possibilità di cambiare la porta da utilizzare (5555 default).
- Possibilità di creare un Client personalizzato direttamente dal server.
- Possibilità di gestire più Client connessi contemporaneamente (max 50).
- Il Client persiste anche dopo il riavvio del PC remoto.

## 1.0.4 Novità

- Aggiunti 7 nuovi comandi!
- Aggiornato il comando /msgb.
- Aggiunta la possibilità di salvare le impostazioni.
- Aggiunti suoni di notifica per la connessione e disconnessione dei Client.
- Un sacco di bug fixes.

## Comandi

- /help
  - Mostra la lista dei comandi disponibili.
- /cls
  - Pulisce la console.
- /close
  - Ti disconnette dalla sessione corrente.
- /shc
  - Rende visibile il Client (/HDC per nasconderlo).
- /spc
  - Chiude il Client.
- /rvc
  - Riavvia il Client.
- /ms
  - Inverte i tasti del mouse (/MSR per reimpostarli).
- /czm
  - Fa impazzire il mouse (/CZMR per reimpostarlo).
- /ml
  - Blocca il mouse (/MLR per sbloccarlo).
- /mvb
  - Fa vibrare il puntatore (/MVBR per disattivare).
- /sw
  - Spegne il PC.
- /rb
  - Riavvia il PC.
- /cdo
  - Apre il vano CD (/CDC per chiuderlo).
- /moff
  - Spegne il monitor.
- /ginf
  - Ottieni delle informazioni base del Client e del PC.
- /ows <example.ex>
  - Apre un sito a scelta (esempio: /ows youtube.com).
  
**------------------[1.0.4]------------------**

- /delc
  - Disinstalla il Client dal PC remoto.
- /msgb
  - Fa apparire un "MessageBox" personalizzato.
- /msgbi
  - Da più informazioni sul comando /msgb.
- /lkl
  - Entra in modalità "LIVE KEYLOGGER". BETA (Contiene ancora dei Bug)
- /lag
  - Fa "laggare" il PC remoto.
- /tsk
  - Entra in modalità "TASKBAR JOKES".
- /bmt
  - Blocca il mouse e la tastiera (richiede UAC).
- /tpc
  - Termina un processo a scelta.
