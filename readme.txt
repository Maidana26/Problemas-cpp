Archivos agregados a la entrega:
- usuarios.txt: Este archivo es el que contiene es la lista de los 100 usuarios con su Nombre, Apellido, Sexo, ID, 
                Contraseña, Rol, Fecha y Hora. Este mismo se usa una sola vez para cargar el archivo Usuarios.bin,
                este es de donde se busca la info de ID y contraseña y donde se hacen las actualizaciones.

- DivinaComedia.txt: Este archivo es el que contiene el libro, lo uncio que tenemos que comentar es que aparecia
                una ä y lo corregimos cambiandola por una a.

- palabrasX.txt: Este es en el que se generan las palabras y repeticiones del incisio de la lista enlazada que 
                 empieza con la letra X (siendo X cualquier letra de la a - z).

- frecuencias.txt: Este es el que se genera para guardar la frecuencia de cada uno de los caracteres que aparecen
                 en el libro y sus repeticiones. 

- plabras-1.txt: El archivo de la etapa 1.

- integrantes.txt: Integrantes del grupo.

Consideraciones en el procesamiento del texto, "DivinaComedia.txt":

Nosotros realizamos la lectrura del archivo linea por linea guardando la informacion en un string y actualizando 
el contenido en cada iteracion. Al momento de la lectura consideramos la aparicion de los caracteres especiales 
tipicos del Idioma (Italiano) pero el unico que encontramos fue ä, lo hablamos con los profes y nos dijieron que
editemos el archivo del libro, cambiando todas las apariciones por a. Ademas nuestro idioma usa constantemente la
abreviacion de palabras con comillas como: l’aere, m’appario, d’ogne, etc. En estos casos las consideramos como dos
palabras por separado, l y aere, m y appario, d y ogne, etc. No tenemos en cuenta que la primera palabra no esta 
completa la tomamos como una nueva palabra.
 
Quisieramos agradecer a toda la catedra de la materia por el año de cursada y los momento compartidos.

atte Matias y Luca