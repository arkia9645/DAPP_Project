# DAPP_Project
Progetto Detectors and Accelerators in Particle Physics

I codici sono copie di AnaEx01 a cui sono state apportate piccole modifiche per renderli più idonei al progetto del corso Detectors and Accelerators in Particle Physics.

## Modifiche apportate

- AnaEx01.cc:
  * Ho inserito dei setter per modificare materiali e geometria del detector per ottere un unico blocco di Alluminio di 5X<sub>0</sub>
  * Ho aggiundo un `while` che salva in un file root, con lo stesso nome della macro, gli istogrammi ottenuti alla fine della simulazione(es. gamma.mac->gamma.root). Se la simulazione viene lanciata senza macro gli istogrammi verranno automaticamente salvati in "AnaEx001.root".
  
- ActionInizialize:
  * Ho modificato sia `header` che `source` aggiungendo una variabile stringa che passa il nome della macro a HistoManager

- HistoManager:
  * Ho aggiunto la variabile stringa da passare ad `analysisManager->OpenFile()`
  * Ho modificato le impostazioni di default degli istogrammi portando i bin da 100 a 300, e il massimo da 800 MeV A 5 GeV

- StackingEvent.cc:
  * Ho commentato la riga in cui viene stampato per ogni evento il numero di positroni(nPositrons) stampato su terminale per evitare print inutili
 
- gamma.mac:
  * Ho portato l'energia da 10 Mev a 10 GeV, il numero di eventi a 100.000, settato tutti i `verbose` a 0 e impostato `/vis/disable` e `/tracking/storeTrajectory 0`
