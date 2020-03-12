# DOSrat

DOSrat è un semplice Remote Administration Tool (RAT) scritto in C++, esso permette di eseguire diverse azioni sul PC nel quale è installato il Client.

## Features

- Possibilità di cambiare la porta da utilizzare (5555 default).
- Possibilità di creare un Client personalizzato direttamente dal server.
- Possibilità di gestire più Client connessi contemporaneamente (max 50).

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
  
**------------------[1.0.3]------------------**
- /moff
  - Spegne il monitor.
- /msgb
  - Fa apparire un "MessageBox".
- /ginf
  - Ottieni delle informazioni base del Client e del PC.
- /ows <example.ex>
  - Apre un sito a scelta (esempio: /ows youtube.com).
