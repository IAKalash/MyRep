#!/bin/bash

if ! dpkg -l | grep -q dbus-x11; then
  sudo apt update
  sudo apt install -y dbus-x11
fi

ART_FILE="$HOME/bashrc.txt"
cat << 'EOF' > "$ART_FILE"
 _   _  _____  _     _  _           _             
| \ | ||_   _|| |   (_)| |         | |            
|  \| |  | |  | | __ _ | |_  __ _  | |  ___ __  __
| . ` |  | |  | |/ /| || __|/ _` | | | / _ \\ \/ /
| |\  | _| |_ |   < | || |_| (_| | | || (_) |>  < 
\_| \_/ \___/ |_|\_\|_| \__|\__,_| |_| \___//_/\_\
                                                  
                                                  
EOF

if [[ ! -f "$ART_FILE" ]]; then
  exit 1
fi

DISPLAY_SCRIPT="$HOME/bashrc.sh"
cat << EOF > "$DISPLAY_SCRIPT"
#!/bin/bash
gnome-terminal -- bash -c "cat '$ART_FILE'; exec bash"
EOF

chmod +x "$DISPLAY_SCRIPT"

if [[ ! -f "$DISPLAY_SCRIPT" ]]; then
  exit 1
fi

CURRENT_TERMINAL_KEY=$(gsettings get org.gnome.settings-daemon.plugins.media-keys terminal 2>/dev/null)
CURRENT_BINDING=$(echo "$CURRENT_TERMINAL_KEY" | tr -d "[]'" | sed "s/@as //")

gsettings set org.gnome.settings-daemon.plugins.media-keys terminal "['<Control><Super>0']" 2>/dev/null

CUSTOM_KEYS=$(gsettings get org.gnome.settings-daemon.plugins.media-keys custom-keybindings 2>/dev/null)
if [[ "$CUSTOM_KEYS" == "@as []" || -z "$CUSTOM_KEYS" ]]; then
  NEW_KEY_PATH="/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom0/"
  CUSTOM_KEYS="['$NEW_KEY_PATH']"
else
  declare -a EXISTING_NUMS
  while IFS= read -r path; do
    num=$(echo "$path" | grep -o 'custom[0-9]*' | grep -o '[0-9]*')
    EXISTING_NUMS+=("$num")
  done < <(echo "$CUSTOM_KEYS" | grep -o '/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom[0-9]*/')
  
  CUSTOM_COUNT=0
  for num in "${EXISTING_NUMS[@]}"; do
    if [[ "$num" -gt "$CUSTOM_COUNT" ]]; then
      CUSTOM_COUNT="$num"
    fi
  done
  CUSTOM_COUNT=$((CUSTOM_COUNT + 1))
  
  NEW_KEY_PATH="/org/gnome/settings-daemon/plugins/media-keys/custom-keybindings/custom${CUSTOM_COUNT}/"
  
  if [[ "$CUSTOM_KEYS" == "[]" ]]; then
    CUSTOM_KEYS="['$NEW_KEY_PATH']"
  else
    CUSTOM_KEYS="${CUSTOM_KEYS%]}"
    CUSTOM_KEYS="${CUSTOM_KEYS}, '$NEW_KEY_PATH']"
  fi
fi

gsettings set org.gnome.settings-daemon.plugins.media-keys custom-keybindings "$CUSTOM_KEYS" 2>/dev/null
gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:"$NEW_KEY_PATH" name "Open Terminal" 2>/dev/null
gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:"$NEW_KEY_PATH" command "bash $DISPLAY_SCRIPT" 2>/dev/null
if [[ -n "$CURRENT_BINDING" ]]; then
  gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:"$NEW_KEY_PATH" binding "$CURRENT_BINDING" 2>/dev/null
else
  gsettings set org.gnome.settings-daemon.plugins.media-keys.custom-keybinding:"$NEW_KEY_PATH" binding "<Control><Alt>t" 2>/dev/null
fi

echo "Новая тема терминала успешно применена!"
