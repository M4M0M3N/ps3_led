# Dillinger
## _Progetto con wemos d1 mini per controllare tramite pagina internet dei led rgb_

## Requisiti
- Microcontrollore con wify (wemos/esp)
- led addressabili (Io ho usato i WS2812B)
- cavi
- saldatore

## Circuito
Bisogna fare molta attenzione al pin usato sulla scheda. Infatti questo non ha lo stesso numero identificativo usato nell'ide
Oltre a questo, i pin adressabili hanno un verso. Questo puo' essere riconosciuto dalla freccia su di essa.

## Utilizzo
Alimentare il wemos.
Controllare se si collega.
Se i led eseguono questa sequenza, la board si e' connessa al wifi
![Collegato](https://github.com/M4M0M3N/ps3_led/blob/main/img/ezgif.com-gif-maker.gif?raw=true)

Una volta collegato, scrivere su un qualsiasi browser l'indirizzo ip del wemos. 192.168.1.32 per me.
Per trovarlo potete:
- cercare nelle impostazioni del modem (in questo caso e' piu' comodo impostargli un indirizzo ip fisso.)
- decommentare le righe dalla 134 alla 145, in questo modo potete trovare l'indirizzo ip direttamente nel monitor seriale

Una volta nella pagina principale, potete cambiare i colori ai led a vostro piacimento!

## Screen del sito
![sitp_p](https://github.com/M4M0M3N/ps3_led/blob/main/img/p.png?raw=true)
![sito_s](https://github.com/M4M0M3N/ps3_led/blob/main/img/w.png?raw=true)
![sito_3](https://github.com/M4M0M3N/ps3_led/blob/main/img/3.png?raw=true)
![ps3 impostato](https://github.com/M4M0M3N/ps3_led/blob/main/img/ps3_sito.jpg?raw=true)
