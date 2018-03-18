#!/bin/bash
argc=$#;
requiredArgc=2;
if [[ $argc -ne $requiredArgc ]]; then
    echo "Zla liczba parametrów";
    exit 1;
fi
PROG="$1";
DIR="$2";
if [[ ! -x "$PROG" || -d $PROG ]]; then
    echo "Podana nazwa programu nie wskazuje na plik wykonywalny."
    exit 1
fi
if [[ ! -d "$DIR" ]]; then
    echo "Podana nazwa katalogu nie wskazuje na katalog."
    exit 1
fi
tempfile=$(mktemp)
#ZNAJDUJE START
actfile=""
for file in  $DIR/*; do
    if [[ -f $file ]]; then
        if [[ `head -1 "$file"` = "START" ]]; then
            actfile="$file";
        fi
    fi
done

if [[ ! -f "$actfile" ]]; then
    echo "W podanym katalogu nie ma pliku startowego"
    exit 1
fi

tail -n +2 "$actfile" | head -n -1 | "$PROG" > "$tempfile";
nextfile=`tail -1 "$actfile"`;
#Zaklada poprawnosc danych (zawsze poprawny plik na koncu i plik ze stopem)
while [[ ! "$nextfile" = "STOP" ]]; do
    nextfile=$(echo "$nextfile" | sed -e "s/FILE //");
    actfile="${actfile%/*}/$nextfile";
    head -n -1 "$actfile" >> "$tempfile";
#   "$PROG" < "$tempfile" | sponge "$tempfile"; /nie ma sponge/
    { rm "$tempfile" && "$PROG" > "$tempfile"; } < "$tempfile";
#   ^triczek z http://backreference.org/2011/01/29/in-place-editing-of-files/ (nie in-place)
    nextfile=`tail -1 "$actfile"`;
done;
cat "$tempfile";
rm "$tempfile";
#bez pierwszego wiersza tail -n +2 "$actfile"
#bez ostatniego wiersza head -n -1 "$actfile"

