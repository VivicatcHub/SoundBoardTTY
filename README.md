# SoundBoardTTY 🎵

SoundBoardTTY est une soundboard simple et facile d'utilisation pour le terminal (**TTY**). Il permet de jouer des sons directement depuis une interface en **ncurses**, avec un support actuel des formats **MP3 et WAV**.

## 🚀 Fonctionnalités
- Interface **ncurses** intuitive et facile à utiliser.
- Supporte les formats **MP3** et **WAV** (modulable pour ajouter d'autres formats).
- Fonctionne exclusivement en **ligne de commande**.
- **Dépendance minimale** : Utilise uniquement **ncurses** (mais peut être étendu à d'autres bibliothèques audio).

## 🛠 Installation

### **Compilation avec Makefile**
```bash
git clone https://github.com/VivicatcHub/SoundBoardTTY.git
cd SoundBoardTTY
make install
```
Cela générera un binaire sbtty.

## 🎮 Utilisation
Lancer SoundBoardTTY en mode interface graphique TTY :
```
sbtty
```

### Options disponibles
| Option                     | Description                      |
|----------------------------|----------------------------------|
| `-h`, `--help`	         | Affiche l’aide                   |
| `-a`, `--add <fichier>`    | Ajoute un son à la soundboard    |
| `-u`, `--update <fichier>` | Met à jour un son existant       |
| `-d`, `--delete <fichier>` | Supprime un son                  |
| `-p`, `--play <fichier>`	 | Joue un son en ligne de commande |


## 🖥 Système supporté
✅ Linux uniquement (pour l’instant).

## 📌 Objectifs futurs
Ajouter le support pour plus de formats audio.
Rendre la gestion des dépendances audio modulable (ex: SDL2_mixer, SoX, ffmpeg...).
Fournir une installation via un binaire précompilé.