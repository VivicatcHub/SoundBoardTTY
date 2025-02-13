# SoundBoardTTY 🎵

SoundBoardTTY is a simple and easy-to-use soundboard for the terminal (**TTY**). It allows you to play sounds directly from an **ncurses** interface, with current support for **MP3** and **WAV** formats.

> Voici la version anglaise du README. Pour la version française cliquez ici : [README.fr.md](README.fr.md).

## 🚀 Features
- Intuitive and easy-to-use **ncurses** interface.
- Supports **MP3** and **WAV** formats (extendable to add more formats).
- Works exclusively via **command line**.
- **Minimal dependencies**: Uses only **ncurses** (but can be extended to other audio libraries).

## 🛠 Installation

### **Compilation with Makefile**
```bash
git clone https://github.com/VivicatcHub/SoundBoardTTY.git
cd SoundBoardTTY
make install
```
This will generate a `sbtty` binary.

## 🎮 Usage
Run SoundBoardTTY in TTY graphical interface mode:
```
sbtty
```

### Available options
| Option                     | Description                         |
|----------------------------|-------------------------------------|
| `-h`, `--help`	         | Displays help                       |
| `-a`, `--add <fichier>`    | Adds a sound to the soundboard      |
| `-u`, `--update <fichier>` | Updates an existing sound           |
| `-d`, `--delete <fichier>` | Deletes a sound                     |
| `-p`, `--play <fichier>`	 | Plays a sound from the command line |


## 🖥 Supported systems
✅ Linux only (for now).

## 📌 Future goals
- Add support for more audio formats.
- Make audio dependency management modular (e.g., SDL2_mixer, SoX, ffmpeg...).