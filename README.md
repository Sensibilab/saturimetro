# Istruzioni per la realizzazione di un prototipo di saturimetro

## NOTA:
### Chi usi questa nota tecnica accetta di agire a titolo personale e sotto propria esclusiva responsabilità. Si declina ogni responsabilità nell’uso di questa nota tecnica per la realizzazione di un saturimetro prototipale.

### _Perché il saturimetro per il covid-19?_
### Se il valore della saturazione scende al di sotto della soglia del 95%, ciò significa che lo scambio gassoso tra sangue e aria, che ha luogo negli alveoli polmonari, non sta avvenendo in maniera corretta. In queste condizioni, il paziente inizia a “respirare male”, ha difficoltà a respirare e potrebbe avere un principio di polmonite.
### In questo periodo, trovare un saturimetro sul mercato in tempi brevi è quasi impossibile. Per tale motivo abbiamo deciso di creare questo progetto che dà la possibilità, a chi lo volesse, di creare a casa un saturimetro. Ovviamente i risultati sono da considerare accurati ma non medicalmente accettabili, non trattandosi di un saturimetro certificato come dispositivo medicale, né di uno strumento professionale; ma è comunque in grado di dare dei dati indicativi dello stato di salute “polmonare” di chi lo realizza e lo usa.

## Introduzione
La saturimetria è la misurazione della percentuale di emoglobina legata all’ossigeno. La misura viene effettuata per mezzo di un pulsossimetro (o saturimetro), strumento non invasivo che basa il suo principio di funzionamento sulla “luce” (fotopletismografia).
La sonda è composta da due diodi LED in gradi di emettere due differenti colori (lunghezze d’onda differenti) e da uno/due fotodiodi per la ricezione della luce.
I pulsossimetri si basano sul principio fisico per il quale differenti lunghezze d’onda possono essere assorbite in modo differente da un elemento. I pulsossimetri ottici si basano sui diversi spettri di assorbimento dell’emoglobina non legata (Hb) e dell’emoglobina legata all’ossigeno/ossiemoglobina (HbO2), la stessa differenza che si evince dal diverso colore del sangue arterioso (ossigenato) da quello venoso.
Le due emoglobine assorbono in modo differente le due lunghezze d’onda usate dal saturimetro (rosso e infrarosso o rosso e verde) e danno quindi la possibilità di misurare la percentuale di emoglobina legata all’ossigeno.

Il saturimetro è un dispositivo usato comunemente sia in ospedale, sia sulle ambulanze, perché è il meno invasivo ed è in grado di misurare sia la frequenza cardiaca, sia la saturazione del sangue. Viene solitamente posto sul dito di una mano (solitamente indice o medio) per l’adulto, e sul lobo dell’orecchio o sul piedino per i neonati.
Una sua variante è quella che si trova ormai nella maggior parte dei fitness tracker o degli smartwatch: usando una sola lunghezza d’onda, questi dispositivi sono in grado di rilevare la frequenza cardiaca di chi li indossa. Alcuni smartwatch, per esempio Fitbit Versa o il vecchio Withings, includono un doppio led con due lunghezze d’onda differenti; questo darebbe loro la possibilità di rilevare la saturazione; tuttavia, essendo questi indossati al polso, la misura non è precisa, per cui non vengono comunemente utilizzati per il calcolo della saturazione del sangue bensì per rilevare gli andamenti della respirazione durante il sonno (quando la misura è più precisa grazie al fatto che chi indossa lo smartwatch è addormentato e quindi, solitamente, fermo), per evidenziare possibili apnee notturne.

La saturazione del sangue, in condizioni normali, si aggira attorno al 98%, mentre si comincia a parlare di possibili problematiche al di sotto del 94/95% (principio di ipossia).

## Perché il saturimetro per il covid-19?
Se il valore della saturazione scende al di sotto della soglia del 95%, ciò significa che lo scambio gassoso tra sangue e aria, che ha luogo negli alveoli polmonari, non sta avvenendo in maniera corretta. In queste condizioni, il paziente inizia a “respirare male”, ha difficoltà a respirare e potrebbe avere un principio di polmonite.
In questo periodo, trovare un saturimetro sul mercato in tempi brevi è quasi impossibile. Per tale motivo abbiamo deciso di creare questo progetto che dà la possibilità, a chi lo volesse, di creare a casa un saturimetro. Ovviamente i risultati sono da considerare accurati ma non medicalmente accettabili, non trattandosi di un saturimetro certificato come dispositivo medicale, né di uno strumento professionale; ma è comunque in grado di dare dei dati indicativi dello stato di salute “polmonare” di chi lo realizza e lo usa.

**_Pertanto, si declina ogni responsabilità nell’uso di questa nota tecnica per la realizzazione di un prototipo di saturimetro secondo le istruzioni fornite. Chi usi questa nota tecnica accetta di agire a titolo personale e sotto propria esclusiva responsabilità_**

## Materiali
Cosa serve:
-	Una qualsiasi scheda Arduino o compatibili. (Di seguito alcuni link per reperirla).
-	Una scheda MAXREFDES117# https://bit.ly/3aQU1H7
-	Un cavo USB
-	Un computer con Arduino IDE installato.

![Immagine della board con il sensore](https://github.com/Sensibilab/saturimetro/blob/master/images/maxrefdes117.jpg?raw=true "MAXREFDES117#")

### Arduino
Una qualsiasi scheda Arduino o compatibili è compatibile con il progetto
Per il progetto può bastare una scheda Arduino Uno, o una più complessa Arduino Nano BLE per la trasmissione del dato ad uno smartphone.

Se l’obiettivo è invece realizzare un dispositivo portatile e a batteria, senza dover fare troppe saldature, forse è meglio utilizzare  qualcosa di leggermente più costoso ma pronto all’uso come le schede Feather di Adafruit (per esempio la scheda Adafruit Feather 32u4 Bluefruit LE, una copia della scheda Arduino ma con bluetooth, caricabatterie e dimensini ridotte).
Le schede Feather permettono di espandere le capacità di input output attraverso le così dette FeatherWing; un esempio è la la scheda OLED che permette di aggiungere un display con il quale visualizzare la misura.

Altra soluzione può essere l’utilizzo dei più performanti dispositivi di M5.
M5Stick o M5Stack sono dispositivi (Arduino compatibili) che includono di default Bluetooth, Wifi, accelerometro, batteria e caricabatterie, tutto racchiuso in un case espandibile semplicemente con dei pezzi stampati in 3d.

### Dove acquistare

#### BOARD CON MICROCONTROLLORE
Arduino Uno:
-	Arduino store: https://store.arduino.cc/
-	Amazon: 
  Original: https://amzn.to/2RiS9iA 
  Compatible: https://amzn.to/39TKQEq 

Arduino Nano BLE:
-	Arduino store: https://store.arduino.cc/
-	Amazon: https://amzn.to/34k6ReE 
 
Feather:
-	Adafruit: https://www.adafruit.com/feather
-	Amazon: https://amzn.to/2Rjr1QF 

M5 Stack:
-	M5Stack store: https://m5stack.com/
-	Amazon: https://amzn.to/2JLXcnx 
-	https://bit.ly/2Xj3KSy
-	https://bit.ly/2XgLqJS

#### MAXREFDES117#
Meno costosi:
-	RS components: https://bit.ly/2V9lpcH 
-	Farnel: https://bit.ly/3aTVsEO 

Altri:
-	Seeedstudio: https://bit.ly/2wkDJXS 
-	Amazon: https://amzn.to/2V82sHn 

## I collegamenti

La componente principale del progetto, quella che fa funzionare il tutto è la scheda con microcontrollore (quella che viene erroneamente definita “l’Arduino”). La scelta di quale utilizzare dipende da molteplici fattori (dimensione, usabilità, reperibilità…) ma non influisce sul funzionamento del dispositivo. Il sensore (MAXREFDES117) è infatti un dispositivo digitale, basato su protocollo I2C, ed utilizza solamente 4 collegamenti: due di alimentazione (GND e VCC) e due per la comunicazione (SCL, SDA). 
SCL e SDA sono comunemente riportati su tutte le schede riportate nel paragrafo Arduino, per cui il collegamento risulta semplificato e pressoché identico per tutte le schede.
Qui di seguito vengono riportati alcuni esempi di collegamento.

Per realizzare il dispositivo nel modo più semplice e stabile, se non si ha a disposizione un saldatore a stagno, basta una breadboard e dei collegamenti realizzati in modo decente. Posizionando il sensore (MAXREFDES117) stabile sulla breadboard, la misura potrà essere più stabile e veritiera. 


Se invece si ha a disposizione un saldatore, buone capacità di saldatura ed una stampante 3d, si può realizzare anche l’anello (trovate il file stl nei download) in cui posizionare il sensore e realizzare una misura ancora più precisa e stabile.

### Arduino Uno
![Collegamenti per Arduino Uno](https://github.com/Sensibilab/saturimetro/blob/master/images/Arduino.png?raw=true "Arduino Uno")
![Collegamenti per Arduino Uno con Breadboard](https://github.com/Sensibilab/saturimetro/blob/master/images/arduino_breadboard.png?raw=true "Arduino Uno")

### Arduino Nano BLE
![Collegamenti per Arduino Uno con breadboard](https://github.com/Sensibilab/saturimetro/blob/master/images/arduino_nano.png?raw=true "Arduino Uno")

### Feather 32u4 Bluefruit LE
![Collegamenti per Feather 32u4 Bluefruit LE](https://github.com/Sensibilab/saturimetro/blob/master/images/feather_max.png?raw=true "Feather")

### M5Stack
![Collegamenti per M5Stack](https://github.com/Sensibilab/saturimetro/blob/master/images/m5stack_max.png?raw=true "M5Stack")

## Firmware

Il firmware è leggermente differente a seconda della scheda utilizzata, ma il concetto du funzionamento è simile per tutte. 
Nella sezione download verranno riportati man mano dei file per differenti schede, mentre qui di seguito vengono riportati porzioni di codice con la loro spiegazione.

###Arduino Uno
1. Scaricare la cartella ArduinoUno e tutto il suo contenuto
2. Installare Arduino IDE sul proprio computer
3. Cliccare due volte sul file ArduinoUno.ino all'interno della cartella
4. Se la cartella è stata rinominata, verrà creata una sottocartella con il nome ArduinoUno; spostare tutti i file .cpp e .h scaricati all'interno di questa cartella.
5. Nell'IDE Arduino, cliccare sul menù strumenti, scheda e selezionare la scheda arduino uno.
6. Sempre nel menu strumenti, selezionare la porta COM corretta.
7. Cliccare sul comando carica (la freccia che punta a destra, secondo bottone tondo da sinistra).
8. Attendere la compilazione ed il caricamento.
9. Cliccare sulla lente di ingrandimento (ultimo bottone sulla sinistra): si aprirà il montor seriale.
10. Nel menu in basso a destra, nel monitor seriale, selezionare 115200 baud
11. Porre l'indice appoggiato al sensore (con il polpastrello rivolto verso il sensore)
12. Premere un tasto qualsiasi sulla tastiera per iniziare l'acquisizione

Verranno continuamente mostrate righe del tipo:

red=572, ir=509<br/>
red=565, ir=566<br/>

Dopo circa 4 secondi (necessari per tarare il sensore), le righe cambieranno diventando:<br/>
red=5691, ir=4004, HR=266, HRvalid=0, SPO2=-999, SPO2Valid=0<br/>

HRvalid e SPO2Valid indicano la validità della misura.<br/>
Se il numero mostrato è 0, la misura non è valida;<br/>
Se il numero mostrato è 1, la misura è valida.<br/>

Se la misura non è valida, mantenere il dito sopra al sensore, tenendolo il più fermo possibile, senza premere eccessivamente. La riga mostrata diventerà in breve tempo del tipo:<br/>
red=5691, ir=4004, HR=76, HRvalid=1, SPO2=98, SPO2Valid=1<br/>


## CASE

In questa sezione verranno inseriti possibili case per la stampa 3d. Riportiamo al momento un esempio di case per il sensore, stampato in 3d, da posizionare sul dito.
https://www.thingiverse.com/thing:2755977


## PER UNA MISURAZIONE OTTIMALE

1. occorre tenerlo qualche decina di secondi per stabilizzare la lettura;
2. la lettura non è corretta con dita fredde (nel caso, abbassate la mano verso terra per fare arrivare "sangue caldo" ai polpastrelli);
3. il movimento può dare origine a errori di misura: pertanto si suggerisce di usare il sistema stando seduti e con il sistema+dito abbastanza fermi.


## Progetto realizzato da
<img src="https://github.com/Sensibilab/saturimetro/blob/master/images/Giallo_pngRisorsa%202.png" width=200>
<img src="https://github.com/Sensibilab/saturimetro/blob/master/images/Risorsa%202.png" width=50>
