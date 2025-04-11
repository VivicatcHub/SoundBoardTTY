#!/bin/bash

echo "🌅 Bienvenue, jeune développeur. Aujourd'hui, tu forgeras ton environnement C."
echo "À chaque étape, choisis si tu veux installer la dépendance proposée."

ask_install() {
    local package_name=$1
    echo
    read -p "⚔️  Souhaites-tu installer '$package_name' ? [y/n] " answer
    case $answer in
        [Yy]* )
            echo "🔧 Invocation de $package_name..."
            sudo apt install -y "$package_name"
            ;;
        * )
            echo "⛔ $package_name ne sera pas installé. La voie du ninja est semée de choix."
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
echo "🧘‍♂️ L'installation est terminée, selon tes choix."
echo "Que ton code soit propre, stable, et que `valgrind` ne trouve jamais d'erreur."

echo
echo "🌸 Code en silence,"
echo "Les threads dansent sous ton œil —"
echo "La mémoire rit."
