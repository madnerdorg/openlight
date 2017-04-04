[English version](https://github.com/madnerdorg/openlight/)

OpenLight
---------
![openlight_photo](https://github.com/madnerdorg/openlight/raw/master/doc/milightONOFF.jpg)
Openlight est une alternative open source au passerelle milight basé sur un arduino nano (clone).      
Fait à partir des recherches de Henryk Plötz : https://hackaday.io/project/5888-reverse-engineering-the-milight-on-air-protocol     

Les ampoules Milight ne sont pas contrôlés en WIFI mais utilisent sont propre protocôle sur la fréquence **2.4Ghz**.

![openlight Routing](https://github.com/madnerdorg/openlight/raw/master/doc/milightRouting.png)
Notre arduino va contrôler directement les ampoules milight grâce au module radio **nrf24l01+** sans **passer par la passerelle WIFI**.

# Utilisation
* Copier **libraries/openlight** dans le carnet de croquis Arduino
* Téléverser **openlight/openlight.ino**
* Aller sur [TODO]
* Utiliser la passerlle milight pour allumer et éteindre une lampe afin de récupérer vos codes.

Les boutons tactiles ne sont pas obligatoires, but cela permet d'allumer et éteindre une lampe.         
Il faut ajouter les codes de la lampes dans votre code, la dernière valeur hexadécimale sera ignoré car elle est mis à jour incrémentalement: 
```
int on [7] = { 0x00, 0x00, 0x00 ,0x00, 0x00, 0x00, 0x01};
int off [7] = { 0x00, 0x00, 0x00 ,0x00, 0x00, 0x00, 0x01};
```
# Commandes
* /info : Affiche nom:port (openlight:42002)
* Si un code est reçu depuis une autre source, elle sera affiché comme ceci: 0x00, 0x00, 0x00 ,0x00, 0x00, 0x00, 0x01

# Composants
* 1 Arduino nano (ch340g): 2.50€	   
* 1 nrf24l01+ (radio module) : 1€	   
* 2 Tactiles switchs : 2€   
Total : 5.50€    

# Branchements
**Les modules nrf modules utilise du 3.3V pas du 5V**

![nrf_pinout](https://github.com/madnerdorg/openmilight/raw/master/doc/nrf_pinout.png)

![touchsensor](https://github.com/madnerdorg/openmilight/raw/master/doc/touchsensor.png)

```
NRF
D9	: orange
D10	: jaune
D11	: bleu
D12	: violet
D13	: vert
3.3V: rouge

Boutons
D4	OFF SIG
D5	ON SIG
5V: VCC
```

# Licenses

# openlight.ino
* Auteur : Rémi Sarrailh (madnerd.org)
* License : MIT 

# openmili
* Auteur : Henryk Plötz
* License : GPLv3
* Lien: https://github.com/henryk/openmili
