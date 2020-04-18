# Saturimetro M5Stack 

A differenza di Arduino Uno, il dispositivo M5Stack è un sistema prototipale all-in-one.
M5Stack è basato su ESP32, un SOC a doppio core, con connettività WIFI e Bluetooth. Il dispositivo presenta inoltre un display TFT a colori, tre pulsanti, un altoparlante, un tasto di reset/spegnimento, batteria e caricabatterie.
Alcune versioni includono anche un unità inerziale composta da accelerometro, giroscopio e magnetometro.

Il dispositivo comprende inoltre un case facilmente espandibile sia attraverso componenti commerciali, sia tramite stampa 3d.

Per facilitare la realizzazione del saturimetro, in questo caso abbiamo preferito utilizzare una libreria distribuita da Sparkfun. Prima di procedere con il firmware, occorre installare questa libreria.

Per fare ciò basta aprire l'IDE di Arduino, cliccare sul menù "Sketch" e successivamente su "#include libreria."
La prima voce del menu che si aprirà è "Gestione Librerie" ed è l'opzione attraverso il quale è possibile cercare ed installare nuove librerie.

Una volta aperto il gestore librerie, occorre ricercare ed installare: MAX3010x

![Installazione della libreria](https://github.com/Sensibilab/saturimetro/blob/master/M5Stack/image/libreria.png)

Nonostante le ottime caratteristiche del dispositivo M5Stack, questi non fa parte propriamente della famiglia Arduino, e per tale motivo deve essere installato manualmente.

Dapprima occorre installare il driver: 
- Win10 [download](https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/drivers/CP210x_VCP_Windows.zip)
- MacOs [download](https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/drivers/CP210x_VCP_MacOS.zip)
- Linux [download](https://m5stack.oss-cn-shenzhen.aliyuncs.com/resource/drivers/CP210x_VCP_Linux.zip)

Passo successivo è l'installazione di ESP32 Board Manager in modo che il device M5Stack sia programmabile dall'IDE Arduino.

Ecco i passi da seguire:
1. Aprire le preferenze di Arduino:
- Su windows attraverso il menu File/Preferences
- Su Max attraverso il menu Arduino/Preferences

2. Nell'opzione "URL aggiuntivo per il Gestore schede" copiare il seguente link:  https://dl.espressif.com/dl/package_esp32_index.json

3. Premere ok

4. Dal menu Strumenti, selezionare Schede: e successivamente Gestore schede

5. Nella barra di ricerca inserire "ESP32" (senza virgolette).

6. Selezionare ESP32 ed installare. Questa operazione, a seconda della connessione internet, potrebbe richiedere fino a 20/30 min.

Ora avrete installato il gestore schede per la maggior parte dei dispositivi basati su ESP32. Nella selezione delle schede potete quindi selezionare M5Stack-Core-ESP32 e la porta al quale è collegato.

Ultimissima operazione è l'installazione della libreria M5stack. Procediamo come per la libreria MAX3010x, ma ricercando questa volta "m5stack". Installiamo la libreria m5stack by m5stack.

Siamo ora pronti per il firmware.

Il file M5Stack.ino include il firmware per il saturimetro.
Una volta programmato, il dispositivo mostrerà un menu in basso, con il quale è possibile sceglire se visualizzare la frequenza cardiaca ed il tracciato dell'onda dicrota (in questo caso, solo il led infrarossi è attivo); oppure, con il tasto centrale, visualizzare il valore dell'SpO2.

In questo ultimo caso, per i primi 5/10 secondi verrà eseguita una inizializzazione del sensore, campionando una parte di segnale in modo da ottimizzare l'esecuzione dell'algoritmo. Successivamente verrà mostrato il valore della saturazione.
Se la scritta rimane ROSSA, il segnale letto dal sensore è di scarsa qualità, ed il valore non è affidabile.
Se la scritta diventa VERDE, il segnale è buono., ed i valori iniziano ad essere sensati. Occorre qualche secondo affinche il segnale si stabilizzi. Se all'inizio viene visualizzato un valore molto basso non occorre spaventarsi, il valore potrebbe essere errato a causa di una cattiva inizializzazione o posizionamento iniziale del dito: aspettate ancora qualche secondo affinche il segnale si stabilizzi.

Il saturimetro è uno strumento molto sensibile; anche i saturimetri ospedalieri spesso danno dati sbagliati a causa di movimenti delle dita o mal posizionamento.

Misurazione dell'SpO2

<img src="https://github.com/Sensibilab/saturimetro/blob/master/M5Stack/image/IMG_20200417_114131.jpg" height="250">

Misurazione dell'HR. Quanto il dito viene tolto dal sensore, la misurazione viene interrotta e appara un messaggio a schermo. Se non si mantiene il dito stabilmente sul sensore, il segnale pletismografico diventa poco stabile e la misurazione impossibile.

<img src="https://github.com/Sensibilab/saturimetro/blob/master/M5Stack/image/IMG_20200417_114237_MP.jpg" height="250">

            


