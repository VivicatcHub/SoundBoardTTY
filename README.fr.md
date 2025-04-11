# SoundBoardTTY 🎵

SoundBoardTTY est une soundboard simple et facile d'utilisation pour le terminal (**TTY**). Il permet de jouer des sons directement depuis une interface en **ncurses**, avec un support actuel des formats **MP3 et WAV**.

> This is the French version of the README. For the English version, see [README.md](README.md).

## 🚀 Fonctionnalités
- Interface **ncurses** intuitive et facile à utiliser.
- Supporte les formats **MP3** et **WAV** (modulable pour ajouter d'autres formats).
- Fonctionne également en **ligne de commande**.
- **Dépendance minimale** : Utilise uniquement **ncurses**.

## 🛠 Installation

### **Installation rapide via script**
```bash
curl -s https://raw.githubusercontent.com/VivicatcHub/SoundBoardTTY/main/install.sh | bash
```
Cette commande télécharge et installe automatiquement la dernière version stable de `sbtty`.

### **Compilation manuelle avec Makefile**
```bash
git clone https://github.com/VivicatcHub/SoundBoardTTY.git
cd SoundBoardTTY
make install
```

## 🎮 Utilisation
Lancer SoundBoardTTY en mode interface graphique TTY :
```bash
sbtty
```

### Options disponibles
| Option                                            | Description                       |
|---------------------------------------------------|-----------------------------------|
| `-h`, `--help`                                    | Affiche l’aide                    |
| `-a`, `--add <name> <path> <*type*>`              | Ajoute un son à la soundboard     |
| `-u`, `--update <old_name> <name> <path> <type>`  | Met à jour un son existant        |
| `-d`, `--delete <name>`                           | Supprime un son                   |
| `-p`, `--play <name>`                             | Joue un son en ligne de commande  |

## 🖥 Système supporté
✅ Linux uniquement (pour l’instant).

## 📌 Objectifs futurs
- Ajouter le support pour plus de formats audio.
- Ajouter un système de mise à jour automatique via la ligne de commande.
