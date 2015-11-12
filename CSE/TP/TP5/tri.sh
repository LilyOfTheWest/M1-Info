#!/bin/bash

# On supprime les fichiers si il existe déjà
rm -f resultat_sequentiel.txt resultat_thread.txt log_sequentiel.txt log_thread.txt

# Si on a pas le bon nombre d'arguments on indique comment utilisé la commande
if [ $# != 5 ]; then
        echo 'Usage : ./tri.sh <Nombre de test> <Taille du vecteur> <Min> <Max> <Nombre de threads>'
        exit
fi

# On créé notre vecteur
./creer_vecteur --size $2 --min $3 --max $4 > vecteur.txt

# On récupère le(s) résultat(s) du tri sequentiel dans le fichier log_sequentiel.txt
touch log_sequentiel.txt
for i in `seq 1 $1`;
do
        ./tri_sequentiel --quiet --time --rusage < vecteur.txt >> log_sequentiel.txt
done

# on récupère le(s) résultat(s) du tri avec threads dans le fichier log_thread.txt
touch log_threads.txt
for i in `seq 1 $1`;
do
        ./tri_threads --quiet --time --rusage --parallelism $5 < vecteur.txt >> log_thread.txt
done

# Puis on calcule la moyenne et on stocke le résultat dans le fichier resultat_sequentiel.txt
touch resultat_sequentiel.txt
i=1
while read aLine;
do
        tab[$i]=$aLine
        i=$(($i+1))
done < log_sequentiel.txt

count=$(($i-1))

counttime=1
countcpu=1
for i in `seq 1 $count`;
do
        if (( $i%2 != 0 )); then
                tabtime[$counttime]=${tab[$i]}
                counttime=$(($counttime+1))
        fi
        if (( $i%2 == 0 )); then
                tabcpu[$countcpu]=${tab[$i]}
                countcpu=$(($countcpu+1))
        fi
done

counttime=$(($counttime-1))
countcpu=$(($countcpu-1))

echo 'Temps global' >> resultat_sequentiel.txt

moyenne=0
for i in `seq 1 $counttime`;
do
        echo "Test $i : ${tabtime[$i]} µs" >> resultat_sequentiel.txt
        moyenne=$(($moyenne+${tabtime[$i]}))
done
moyenne=$(($moyenne/$counttime))

echo "Moyenne (sur $counttime tests) : $moyenne" >> resultat_sequentiel.txt

echo 'Temps CPU' >> resultat_sequentiel.txt

moyenne=0
for i in `seq 1 $countcpu`;
do
        arr=(${tabcpu[$i]})
        echo "Test $i : ${arr[0]}" >> resultat_sequentiel.txt
        moyenne=$(($moyenne+${arr[0]}))
done
moyenne=$(($moyenne/$countcpu))

echo "Moyenne (sur $countcpu tests) : $moyenne" >> resultat_sequentiel.txt

# Puis on calcule la moyenne et on stocke le résultat dans le fichier resultat_thread.txt
touch resultat_thread.txt
i=1
while read aLine;
do
        tab[$i]=$aLine
        i=$(($i+1))
done < log_thread.txt

count=$(($i-1))

counttime=1
countcpu=1
for i in `seq 1 $count`;
do
        if (( $i%2 != 0 )); then
                tabtime[$counttime]=${tab[$i]}
                counttime=$(($counttime+1))
        fi
        if (( $i%2 == 0 )); then
                tabcpu[$countcpu]=${tab[$i]}
                countcpu=$(($countcpu+1))
        fi
done

counttime=$(($counttime-1))
countcpu=$(($countcpu-1))

echo "Avec $5 threads" >> resultat_thread.txt
echo 'Temps global' >> resultat_thread.txt

moyenne=0
for i in `seq 1 $counttime`;
do
        echo "Test $i : ${tabtime[$i]}" >> resultat_thread.txt
        moyenne=$(($moyenne+${tabtime[$i]}))
done
moyenne=$(($moyenne/$counttime))

echo "Moyenne (sur $counttime tests) : $moyenne" >> resultat_thread.txt

echo 'Temps CPU' >> resultat_thread.txt

moyenne=0
for i in `seq 1 $countcpu`;
do
        arr=(${tabcpu[$i]})
        echo "Test $i : ${arr[0]}" >> resultat_thread.txt
        moyenne=$(($moyenne+${arr[0]}))
done
moyenne=$(($moyenne/$countcpu))

echo "Moyenne (sur $countcpu tests) : $moyenne" >> resultat_thread.txt

# Enfin on affiche les résultats
cat resultat_sequentiel.txt
cat resultat_thread.txt