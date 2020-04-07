# Istruzioni per la realizzazione di un prototipo di saturimetro

### NOTA:
### Chi usi questa nota tecnica accetta di agire a titolo personale e sotto propria esclusiva responsabilità. Si declina ogni responsabilità nell’uso di questa nota tecnica per la realizzazione di un saturimetro prototipale.

#### Introduzione
La saturimetria è la misurazione della percentuale di emoglobina legata all’ossigeno. La misura viene effettuata per mezzo di un pulsossimetro (o saturimetro), strumento non invasivo che basa il suo principio di funzionamento sulla “luce” (fotopletismografia).
La sonda è composta da due diodi LED in gradi di emettere due differenti colori (lunghezze d’onda differenti) e da uno/due fotodiodi per la ricezione della luce.
I pulsossimetri si basano sul principio fisico per il quale differenti lunghezze d’onda possono essere assorbite in modo differente da un elemento. I pulsossimetri ottici si basano sui diversi spettri di assorbimento dell’emoglobina non legata (Hb) e dell’emoglobina legata all’ossigeno/ossiemoglobina (HbO2), la stessa differenza che si evince dal diverso colore del sangue arterioso (ossigenato) da quello venoso.
Le due emoglobine assorbono in modo differente le due lunghezze d’onda usate dal saturimetro (rosso e infrarosso o rosso e verde) e danno quindi la possibilità di misurare la percentuale di emoglobina legata all’ossigeno.

Il saturimetro è un dispositivo usato comunemente sia in ospedale, sia sulle ambulanze, perché è il meno invasivo ed è in grado di misurare sia la frequenza cardiaca, sia la saturazione del sangue. Viene solitamente posto sul dito di una mano (solitamente indice o medio) per l’adulto, e sul lobo dell’orecchio o sul piedino per i neonati.
Una sua variante è quella che si trova ormai nella maggior parte dei fitness tracker o degli smartwatch: usando una sola lunghezza d’onda, questi dispositivi sono in grado di rilevare la frequenza cardiaca di chi li indossa. Alcuni smartwatch, per esempio Fitbit Versa o il vecchio Withings, includono un doppio led con due lunghezze d’onda differenti; questo darebbe loro la possibilità di rilevare la saturazione; tuttavia, essendo questi indossati al polso, la misura non è precisa, per cui non vengono comunemente utilizzati per il calcolo della saturazione del sangue bensì per rilevare gli andamenti della respirazione durante il sonno (quando la misura è più precisa grazie al fatto che chi indossa lo smartwatch è addormentato e quindi, solitamente, fermo), per evidenziare possibili apnee notturne.

La saturazione del sangue, in condizioni normali, si aggira attorno al 98%, mentre si comincia a parlare di possibili problematiche al di sotto del 94/95% (principio di ipossia).

#### Perché il saturimetro per il covid-19?
Se il valore della saturazione scende al di sotto della soglia del 95%, ciò significa che lo scambio gassoso tra sangue e aria, che ha luogo negli alveoli polmonari, non sta avvenendo in maniera corretta. In queste condizioni, il paziente inizia a “respirare male”, ha difficoltà a respirare e potrebbe avere un principio di polmonite.
In questo periodo, trovare un saturimetro sul mercato in tempi brevi è quasi impossibile. Per tale motivo abbiamo deciso di creare questo progetto che dà la possibilità, a chi lo volesse, di creare a casa un saturimetro. Ovviamente i risultati sono da considerare come molto accurati non essendo un saturimetro certificato come dispositivo medicale, né di uno strumento professionale; ma è comunque in grado di dare dei dati indicativi dello stato di salute “polmonare” di chi lo realizza e lo usa.

**_Pertanto, si declina ogni responsabilità nell’uso di questa nota tecnica per la realizzazione di un prototipo di saturimetro secondo le istruzioni fornite. Chi usi questa nota tecnica accetta di agire a titolo personale e sotto propria esclusiva responsabilità_**

### Materiali
Cosa serve:
-	Una qualsiasi scheda Arduino o compatibili. (Di seguito alcuni link per reperirla).
-	Una scheda MAXREFDES117# https://bit.ly/3aQU1H7
-	Un cavo USB
-	Un computer con Arduino IDE installato.

![Immagine della board con il sensore](/img/maxrefdes117.jpg?raw=true "MAXREFDES117#")

#### Arduino
Una qualsiasi scheda Arduino o compatibili è compatibile con il progetto
Per il progetto può bastare una scheda Arduino Uno, o una più complessa Arduino Nano BLE per la trasmissione del dato ad uno smartphone.

Se l’obiettivo è invece realizzare un dispositivo portatile e a batteria, senza dover fare troppe saldature, forse è meglio utilizzare  qualcosa di leggermente più costoso ma pronto all’uso come le schede Feather di Adafruit (per esempio la scheda Adafruit Feather 32u4 Bluefruit LE, una copia della scheda Arduino ma con bluetooth, caricabatterie e dimensini ridotte).
Le schede Feather permettono di espandere le capacità di input output attraverso le così dette FeatherWing; un esempio è la la scheda OLED che permette di aggiungere un display con il quale visualizzare la misura.

Altra soluzione può essere l’utilizzo dei più performanti dispositivi di M5.
M5Stick o M5Stack sono dispositivi (Arduino compatibili) che includono di default Bluetooth, Wifi, accelerometro, batteria e caricabatterie, tutto racchiuso in un case espandibile semplicemente con dei pezzi stampati in 3d.

## Dove acquistare

### BOARD CON MICROCONTROLLORE
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

### MAXREFDES117#
Meno costosi:
-	RS components: https://bit.ly/2V9lpcH 
-	Farnel: https://bit.ly/3aTVsEO 

Altri:
-	Seeedstudio: https://bit.ly/2wkDJXS 
-	Amazon: https://amzn.to/2V82sHn 

