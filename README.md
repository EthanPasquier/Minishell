# minishell
#Readme pour la partie parsing de l'exercice MiniShell de l'école 42
La partie parsing de ce projet a pour but de comprendre la commande entrée par l'utilisateur et de la préparer pour son exécution. Pour ce faire, plusieurs fonctions sont utilisées :

#ft_parser
Cette fonction prend en entrée une chaîne de caractères représentant la commande entrée par l'utilisateur. Elle vérifie que la commande ne commence ni ne se termine par des caractères indésirables ou impossibles, comme des espaces ou des tabulations. Ensuite, elle utilise la fonction ft_write_cut pour séparer les différents éléments de la commande en utilisant un caractère invisible et itérable.

Par exemple, si l'utilisateur entre la commande ls -lah | wc > test, ft_parser utilisera ft_write_cut pour la diviser en ls -lah29|29 wc 29>29 test.
