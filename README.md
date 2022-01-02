# Smart-Home-via-iHomeBot

Autor: Anass Anhari

Web: https://aanhar2013.wixsite.com/casadomotica

Vídeo resum: https://www.youtube.com/watch?v=KhaQHghDxJY

Tota la documentació es troba disponible a `doc/` i tot el codi font a `src/`.

## Guia d'instal·lació / Installation guide

Es recomana preferentment instal·lar un entorn virtual:

``` shell
	$ python3 -m venv <Nom del entorn>
```
Doncs, caldrà afegir amb `pip` (gestor de paquets) les dependències necessàries:

```shell
	$ pip3 install -r MODULES.txt
```

## Executar iHomeBot / Run iHomeBot

Evidentment, per executar iHomeBot caldrà disposar del muntatge (la casa) i d'un TOKEN (explicat a la documentació).

Executar en `Python3`:

```shell
	$ python3 iHomeBot.py
```