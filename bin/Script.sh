 #!/bin/bash

echo "Début de traitement"

#myArr=("0.005" "0.01" "0.05" "0.1" "0.5" "1" "10" "100")

part=gamma
emax=1000000
e=1

pow='1/4'
coef=10**$pow

e1=$e
e2=$e
e3=$e
while [ "$e1" -lt "$emax" ]
do
    while [[ $(pgrep -x ENLegnSim | wc -l) -gt 4 ]]
    do
	sleep 10
    done
        let e1=$e1*$coef
        # Creation du fichier a partir du fichier de base (fichier temporaire)
        cp vrml_base.mac base_${e1}_fichier_bis1.mac
        # Mise en place de la variable
        sed -e "s/%energy/$e1/g"  base_${e1}_fichier_bis1.mac > base_${e1}_fichier_bis.mac
        sed -e "s/%particle/$part/g" base_${e1}_fichier_bis.mac > base_${e1}_fichier.mac
        # Suppression fichier temporaire
        rm base_${e1}_fichier_bis.mac
        rm base_${e1}_fichier_bis1.mac
	      ./ENLegnSim ../Resultats/${part}_Si_${e1}keV 5000 base_${e1}_fichier.mac
        rm base_${e1}_fichier.mac

#merge files in data.root
done
datafile=()
while [ "$e2" -lt "$emax" ]
do
let e2=$e2*$coef
datafile+="../Resultats/${part}_Si_${e2}keV.root "
done

hadd -f ../Resultats/data.root ${datafile[*]}
while [ "$e3" -lt "$emax" ]
do
let e3=$e3*$coef
rm ../Resultats/${part}_Si_${e3}keV.root
done
mv ../Resultats/data.root ../Resultats/$part/
echo "Fin de traitement"
