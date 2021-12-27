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

#Utilizzo
Alimentare il wemos.
Controllare se si collega.
##Video collegamento
Una volta collegato, scrivere su un qualsiasi browser l'indirizzo ip del wemos. 192.168.1.32 per me.
Per trovarlo potete:
- cercare nelle impostazioni del modem (in questo caso e' piu' comodo impostargli un indirizzo ip fisso.)
- decommentare le righe dalla 134 alla 145, in questo modo potete trovare l'indirizzo ip direttamente nel monitor seriale

Una volta nella pagina principale, potete cambiare i colori ai led a vostro piacimento!

#Scerrn del sito
foto1
foto2
foto3
foto ps3
