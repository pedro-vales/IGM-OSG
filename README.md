# IGM-OSG
Para compilar la práctica se ha creado un makefile y solo se necesita hacer make para generar tanto el compilado como el .ogst que se utilizará para crear el grafo.

1. Se ejecuta el comando **osgconv scene_graph.osgt scene_graph.dot**
2. Una vez creado el archivo .dot se ejecuta el comando **dot -Tpng -o scene_graphX.png scene_graph.dot** poniendo en lugar de scene_graphX el nombre que deseemos y ya nos generará un png con el grafo de la escena OSG.
