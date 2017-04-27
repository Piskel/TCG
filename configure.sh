#!/bin/bash

#attention : ne fonctionne qu'avec du c/c++

C="FALSE"
CPP="FALSE"

EXENAME="out"
OPTIONS="-std=c++14"
LIB="-lsfml-graphics -lsfml-window -lsfml-system"

EXTENSION="cpp"

if [ -z "$(find . -maxdepth 2 -name "*.${EXTENSION}" -print)" ]
then
	echo "Erreur : aucun fichier ${EXTENSION} sous le répertoire courant ou ses fils (2)"
	exit 3
fi

#cette variable (fichiersCpp) peut aussi désigner les fichiers c en fonction de la compilation choisie
fichiersCpp=$(find . -maxdepth 2 -name "*.${EXTENSION}" -print)
fichiers=""
fichiersO=""

echo -n "OBJ:=" > makefile

for i in ${fichiersCpp}
do
	#On calcule la taille du nom du fichier pour enlever la vilaine extension
	l=$(expr length ${i})
	t=$(expr length ${EXTENSION})
	t=$(expr ${t} + 1)
	l=$(expr ${l} - ${t})

	#on enlève l'extension du fichier
	nomFichier=${i:0:$l}
	fichiersO="${fichiersO} ${nomFichier}.o"
done

echo ${fichiersO} >> makefile
echo "EXENAME:=${EXENAME}" >> makefile
echo "OPTIONS:=${OPTIONS}" >> makefile
echo -e "LIB:=$LIB\n" >> makefile
echo -e "all:exe\nexe:\$(EXENAME)\n\n\$(EXENAME):\$(OBJ)" >> makefile

echo -e "\tg++ \$(OPTIONS) \$(OBJ) \$(LIB) -o \$(EXENAME)" >> makefile


#
# Ici, on s'occupe de la liste des dépendances.
#

include="FALSE"

for i in ${fichiersO}
do
	#On calcule la taille du nom du fichier pour enlever la vilaine extension
	l=$(expr length ${i})
	l=$(expr ${l} - 2)

	#on enlève l'extension du fichier
	nomFichier=${i:0:$l}

    fichierCpp=${nomFichier}.cpp
	
	#La variable résultat contient une ligne de dépendances + la compilation
	RESULTAT=$(echo -n ${i}:${fichierCpp})

	for a in $(cat ${fichierCpp})
	do
		#si le mot précédemment trouvé était '#include'
		if [ ${include} = "TRUE" ]
		then
			#on vérifie que le premier caractère soit un "
			if [ "${a::1}" = '"' ]
			then
				#on enlève alors tous les "
				a=$(echo ${a} |sed -s "s/\"//g")
				a=include/$a
				

				RESULTAT="${RESULTAT} $(echo -n ${a})"
			fi
		fi
		
		# on remet include à false pour ne pas choisir tous les mots
		include="FALSE"

		if [ "$a" = "#include" ]
		then
			include="TRUE"
		fi
	done


    echo -e "\n${RESULTAT}\n\tg++ \$(OPTIONS) -c ${nomFichier}.cpp -I include/ -o ${nomFichier}.o" >> makefile
done

echo -e "\nclean:\n\trm -f \$(OBJ)" >> makefile
