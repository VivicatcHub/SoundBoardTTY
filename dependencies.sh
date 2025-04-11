#!/bin/bash

echo "🌅 Début de l'installation"

ask_install() {
    local package_name=$1
    echo
    read -p "⚔️  Souhaites-tu installer '$package_name' ? [y/n] " answer
    case $answer in
        [Yy\n]* )
            echo "🔧 Installation de $package_name..."
            sudo apt install -y "$package_name"
            ;;
        * )
            echo "⛔ $package_name ne sera pas installé"
            ;;
    esac
}

echo "🔄 Mise à jour des sources..."
sudo apt update

ask_install "libmpg123-dev"
ask_install "libao-dev"
ask_install "libncurses5-dev"
ask_install "libncursesw5-dev"
ask_install "build-essential"

echo
echo "🧘‍♂️ L'installation est terminée !"
