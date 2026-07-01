#  Projet STM32 – Vidal / Perez 

Ce dépôt contient le code source du projet réalisé dans le cadre du cours de microcontrôleur (STM32). Il est basé sur la carte **NUCLEO-L152RE**, le SHIELD **X-NUCLEO-IKS01A3**, et notamment l’utilisation de l'acceleromêtre et magnétomêtre **LIS2MDL**.

---

##  Organisation du dépôt

Le dépot est organisé de façon simple le projet se trouve dans le dossier Projet.
Il contient les drivers nécessaires dans le sous dossier Drivers :
   -  `Drivers/` : `Display` contient les fichiers pour l'afficheur MAX7219. 
   - `HAL_Driver` pour les capteurs du SHIELD.
Ainsi que les fichiers de configuration pour STM32CubeIDE.

---

##  Matériel et logiciel utilisé

Logiciel :

- [STM32CubeIDE](https://www.st.com/en/development-tools/stm32cubeide.html) – IDE officiel pour les cartes STM32
- [Git + Git Bash](https://git-scm.com/downloads) – pour cloner le dépôt localement et exécuter les commandes en ligne
- [TeraTerm](https://osdn.net/projects/ttssh2/releases/) (ou équivalent | coolterm pour Mac) – terminal série pour afficher les données UART

Matériel :

- Carte **NUCLEO-L152RE**
- Carte **ISEN32**
- Carte d’extension capteurs : **X-NUCLEO-IKS01A3**
- Capteur utilisé : **LIS2MDL** (Accéléromètre) + Magnéto)


---

##  Installation

### 1. Cloner le dépôt Git

> Placez-vous d'abord dans le **dossier de destination** souhaité sur votre PC, puis entrez :

```bash
git clone https://github.com/CoralieP98/ProjetMicroPro 
```
### 2. Ouvrir un projet dans STM32CubeIDE

    Vous pouvez ouvrir un projet à la fois (datalogger ou classification) comme suit :

    - Ouvrir STM32CubeIDE

    - Aller dans File > Open Projects from File System

    - Cliquer sur Directory... et naviguer vers :

        le dossier "Projet"

    - Cliquer sur Finish

 Le projet s’importe automatiquement dans CubeIDE

 Configuration de l’afficheur MAX7219 :
Pour que l’écran SPI fonctionne correctement avec l’afficheur 7 segments MAX7219, il est nécessaire d'ajouter manuellement ce dossier aux chemins d'inclusion du compilateur dans STM32CubeIDE.

    - Clic droit sur le projet → Properties
    - Allez dans C/C++ General > Paths and Symbols
    - Onglet Includes
    - Add 
    - File System
    - Sélectionner le dossier "display" disponible dans le dossier "Drivers" du projet en cours.
    - Cliquer sur OK

 Vous pouvez ensuite le compiler (Project > Build All) et le téléverser (Run | Debug) sur la carte.

### 3. Instructions d'utilisation

1. Connecter le **shield capteur X-NUCLEO-IKS01A3** sur la carte **NUCLEO-L152RE**, et s'assurer que la carte est bien **encastrée sur la carte mère ISEN32**.
2. Brancher la carte **NUCLEO-L152RE** via le câble **mini USB - USB**
3. Ouvrir **TeraTerm** (ou un terminal série) à **115200 bauds** et sélectionner le port COM associé
4. Compiler et téléverser le projet dans **STM32CubeIDE**
5. Le reste de l'experience utilisateur se deroulera directement sur la carte.



### 4. Instructions de jeux et d'initialisation

initialisation du magnétomètre à la première utilisation du projet:
   -  Appuyer sur le bouton Bleu (B1) pour lancer l'initialisation du magnétomètre.
   -  Tourner la carte sur elle-même dans tous les sens pour calibrer le capteur pendant quelques secondes. 
   -  Rappuyer sur le bouton Bleu (B1) pour terminer l'initialisation. Le message 'done' s'affiche sur le terminal série et vous pouvez commencer à jouer.

1. Le jeu boussole se lance avec le projet.
2. Entrainez-vous à faire tourner la carte pour comprendre le fonctionnement de la boussole. L'affichage SPI indique la direction de la carte par rapport au nord magnétique.
3. Lorsque vous êtes prêt, appuyez sur le BTN1 pour voir l'angle à trouver.
4. Appuyer ensuite sur le BTN2 pour activer l'aide "chaud/froid" des leds, qui vous indique si vous vous rapprochez ou vous éloignez de l'angle à trouver.
5. Puis sur le BTN3 pour valider votre réponse. Si vous trouvez le bon angle vous avez gagné et 'win' s'affichera sur le 7 segments. Sinon ce sera 'fail'.
6. Vous pouvez recommencer une partie en appuyant sur le BTN1 ou changer de mode de jeu en appuyant sur le BTN4.
7. Vous êtes maintenant dans le mode acceleromêtre. Le 7 segment affiche Ready? ('Rdi') et vous pouvez commencer à jouer en appuyant sur le BTN1.
8. Wait s'affichera alors sur le 7 segments et vous devrez attendre que le jeu vous indique 'Go' pour vous précipiter et récuperer la carte le plus vite possible.
9. Votre temps de réaction sera affiché sur le 7 segments et vous pourrez recommencer une partie en appuyant sur le BTN1.
10. Ou retourner au mode boussole en appuyant sur le BTN4.

### 5. Gestion des erreurs

Il peut arriver que le bus SPI ne s'initialise pas correctement. Dans ce cas, le message 'Err' s'affiche sur le 7 segments et le message POWER CYCLE CARD s'affiche sur le terminal série. Il est alors nécessaire de débrancher la carte et de la rebrancher pour relancer le projet.

---

