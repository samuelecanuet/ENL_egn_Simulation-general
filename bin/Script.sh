 #!/bin/bash

echo "Début de traitement"

#myArr=("0.005" "0.01" "0.05" "0.1" "0.5" "1" "10" "100")

part=proton
emax=100000
e=5

e1=$e
e2=$e
e3=$e
while [ "$e1" -lt "$emax" ]
do
    while [[ $(pgrep -x ENLegnSim | wc -l) -gt 4 ]]
    do
	sleep 10
    done 
        ((e1=$e1*'8/4'))
        # Creation du fichier a partir du fichier de base (fichier temporaire)
        cp vrml_base.mac base_${e1}_fichier_bis1.mac
        # Mise en place de la variable
        sed -e "s/%energy/$e1/g"  base_${e1}_fichier_bis1.mac > base_${e1}_fichier_bis.mac
        sed -e "s/%particle/$part/g" base_${e1}_fichier_bis.mac > base_${e1}_fichier.mac
        # Suppression fichier temporaire
        rm base_${e1}_fichier_bis.mac
        rm base_${e1}_fichier_bis1.mac
	./ENLegnSim ../Resultats/${part}_Si_${e1}keV 10 base_${e1}_fichier.mac
        rm base_${e1}_fichier.mac
        

done
datafile=()
while [ "$e2" -lt "$emax" ]
do
((e2=$e2*'8/4'))
datafile+="../Resultats/${part}_Si_${e2}keV.root "
done

hadd -f ../Resultats/data.root ${datafile[*]}
while [ "$e3" -lt "$emax" ]
do
((e3=$e3*'8/4'))
rm ../Resultats/${part}_Si_${e3}keV.root
done
mv ../Resultats/data.root ../Resultats/$part/
echo "Fin de traitement"


