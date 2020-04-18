# Saturimetro M5Stack 

A differenza di Arduino Uno, il dispositivo M5Stack è un sistema prototipale all-in-one.
M5Stack è basato su ESP32, un SOC a doppio core, con connettività WIFI e Bluetooth. Il dispositivo presenta inoltre un display TFT a colori, tre pulsanti, un altoparlante, un tasto di reset/spegnimento, batteria e caricabatterie.
Alcune versioni includono anche un unità inerziale composta da accelerometro, giroscopio e magnetometro.

Il dispositivo comprende inoltre un case facilmente espandibile sia attraverso componenti commerciali, sia tramite stampa 3d.

Per facilitare la realizzazione del saturimetro, in questo caso abbiamo preferito utilizzare una libreria distribuita da Sparkfun. Prima di procedere con il firmware, occorre installare questa libreria.

Per fare ciò basta aprire l'IDE di Arduino, cliccare sul menù "Sketch" e successivamente su "#include libreria."
La prima voce del menu che si aprirà è "Gestione Librerie" ed è l'opzione attraverso il quale è possibile cercare ed installare nuove librerie.

Una volta aperto il gestore librerie, occorre ricercare ed installare: MAX3010x




