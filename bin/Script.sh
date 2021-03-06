#!/bin/bash
echo "Début de traitement"

part=proton

if [[ "$part" == *proton* ]]
then
modif="/process/eLoss/StepFunctionMuHad 0.02 0.01 um"
elif [[ "$part" == *e-* ]]
then
#modif="#"
modif="#"
else
modif="#"
fi

emax=80000
e=5

pow='1/5'
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
        cp vrml_base.mac base_${e1}_fichier_bis.mac
        # Mise en place de la variable
        sed -e "5c$modif" -e "s/%energy/$e1/g" -e "s/%particle/$part/g" base_${e1}_fichier_bis.mac > base_${e1}_fichier.mac
        # Suppression fichier temporaire
        rm base_${e1}_fichier_bis.mac

	      ./ENLegnSim ../Resultats/${part}_Si_${e1}keV 10000 base_${e1}_fichier.mac
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
