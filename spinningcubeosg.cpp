#include <osgViewer/Viewer>
#include <osg/Geometry>
#include <osg/Geode>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>
#include <osg/MatrixTransform>
#include <osgUtil/Optimizer>
#include <osgDB/WriteFile>

osg::Geometry* createTexturedCube(float size) {
    osg::ref_ptr<osg::Vec3Array> vertices = new osg::Vec3Array(8);
    (*vertices)[0].set(-size, -size, -size);
    (*vertices)[1].set(size, -size, -size);
    (*vertices)[2].set(size, size, -size);
    (*vertices)[3].set(-size, size, -size);
    (*vertices)[4].set(-size, -size, size);
    (*vertices)[5].set(size, -size, size);
    (*vertices)[6].set(size, size, size);
    (*vertices)[7].set(-size, size, size);

    osg::ref_ptr<osg::Vec2Array> texcoords = new osg::Vec2Array(24);
    (*texcoords)[0].set(0.0f, 0.0f);
    (*texcoords)[1].set(1.0f, 0.0f);
    (*texcoords)[2].set(1.0f, 1.0f);
    (*texcoords)[3].set(0.0f, 1.0f);
    (*texcoords)[4].set(0.0f, 0.0f);
    (*texcoords)[5].set(1.0f, 0.0f);
    (*texcoords)[6].set(1.0f, 1.0f);
    (*texcoords)[7].set(0.0f, 1.0f);
    (*texcoords)[8].set(0.0f, 0.0f);
    (*texcoords)[9].set(1.0f, 0.0f);
    (*texcoords)[10].set(1.0f, 1.0f);
    (*texcoords)[11].set(0.0f, 1.0f);
    (*texcoords)[12].set(0.0f, 0.0f);
    (*texcoords)[13].set(1.0f, 0.0f);
    (*texcoords)[14].set(1.0f, 1.0f);
    (*texcoords)[15].set(0.0f, 1.0f);
    (*texcoords)[16].set(0.0f, 0.0f);
    (*texcoords)[17].set(1.0f, 0.0f);
    (*texcoords)[18].set(1.0f, 1.0f);
    (*texcoords)[19].set(0.0f, 1.0f);
    (*texcoords)[20].set(0.0f, 0.0f);
    (*texcoords)[21].set(1.0f, 0.0f);
    (*texcoords)[22].set(1.0f, 1.0f);
    (*texcoords)[23].set(0.0f, 1.0f);

    osg::ref_ptr<osg::Geometry> geom = new osg::Geometry;
    geom->setVertexArray(vertices.get());
    geom->setTexCoordArray(0, texcoords.get(), osg::Array::BIND_PER_VERTEX);

    osg::ref_ptr<osg::DrawElementsUInt> faces = new osg::DrawElementsUInt(GL_QUADS, 24);
    faces->push_back(0); faces->push_back(1); faces->push_back(2); faces->push_back(3); // Front
    faces->push_back(7); faces->push_back(6); faces->push_back(5); faces->push_back(4); // Back
    faces->push_back(0); faces->push_back(4); faces->push_back(5); faces->push_back(1); // Bottom
    faces->push_back(3); faces->push_back(2); faces->push_back(6); faces->push_back(7); // Top
    faces->push_back(1); faces->push_back(5); faces->push_back(6); faces->push_back(2); // Right
    faces->push_back(0); faces->push_back(3); faces->push_back(7); faces->push_back(4); // Left

    geom->addPrimitiveSet(faces.get());
    return geom.release();
}

osg::Geometry* createIndividualCubes(){
    // Crear la geometría del cubo y aplicar la textura
    osg::ref_ptr<osg::Geometry> cubeGeometry = createTexturedCube(1.0f);
    osg::ref_ptr<osg::Texture2D> texture = new osg::Texture2D;
    osg::ref_ptr<osg::Image> image = osgDB::readImageFile("texture.jpg");
    if (!image) {
        osg::notify(osg::NOTICE) << "Failed to load texture for cube 1." << std::endl;
        return nullptr; // Retorna nullptr si la textura no puede ser cargada
    }
    texture->setImage(image.get());
    cubeGeometry->getOrCreateStateSet()->setTextureAttributeAndModes(0, texture.get());

    return cubeGeometry.release(); // Liberamos la memoria del puntero antes de retornarlo
}

int main() {

    // Crear la geometría del primer cubo y aplicar la textura
    osg::ref_ptr<osg::Geometry> cubeGeometry1 = createIndividualCubes();
    if (!cubeGeometry1) {
        return 1; // Salimos del programa si la geometría del cubo no pudo ser creada correctamente
    }

    // Crear la geometría del segundo cubo y aplicar la textura
    osg::ref_ptr<osg::Geometry> cubeGeometry2 = createIndividualCubes();
    if (!cubeGeometry2) {
        return 1; // Salimos del programa si la geometría del cubo no pudo ser creada correctamente
    }

    // Crear nodos Geode para contener las geometrías
    osg::ref_ptr<osg::Geode> geode1 = new osg::Geode;
    osg::ref_ptr<osg::Geode> geode2 = new osg::Geode;
    geode1->addDrawable(cubeGeometry1.get());
    geode2->addDrawable(cubeGeometry2.get());

    // Crear nodos MatrixTransform para manejar la posición y rotación de los cubos
    osg::ref_ptr<osg::MatrixTransform> transform1 = new osg::MatrixTransform;
    osg::ref_ptr<osg::MatrixTransform> transform2 = new osg::MatrixTransform;
    transform1->addChild(geode1.get());
    transform2->addChild(geode2.get());

    // Establecer las posiciones de los cubos
    osg::Matrix matrix1 = osg::Matrix::translate(osg::Vec3(-2.0, 0.0, 0.0)); // Posición del primer cubo
    osg::Matrix matrix2 = osg::Matrix::translate(osg::Vec3(2.0, 0.0, 0.0)); // Posición del segundo cubo
    transform1->setMatrix(matrix1);
    transform2->setMatrix(matrix2);

    // Crear un nodo raíz de la escena
    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->addChild(transform1.get());
    root->addChild(transform2.get());

    // Crear un visor OSG
    osgViewer::Viewer viewer;

    // Establecer una manipulación de cámara para permitir la interacción del usuario
    viewer.setCameraManipulator(new osgGA::TrackballManipulator);

    // Establecer la escena a renderizar
    viewer.setSceneData(root.get());

    // Bucle para rotar los cubos
    while (!viewer.done()) {
        double time = viewer.elapsedTime();
        osg::Matrix rotationMatrix1, rotationMatrix2;
        rotationMatrix1.makeRotate(time * 0.5, osg::Vec3(0.5, 1.0, 0.0)); // Rotación del primer cubo sobre el eje Y
        rotationMatrix2.makeRotate(time * -0.5, osg::Vec3(1.0, 0.5, 0.0)); // Rotación del segundo cubo sobre el eje X
        transform1->setMatrix(matrix1 * rotationMatrix1);
        transform2->setMatrix(matrix2 * rotationMatrix2);
        viewer.frame();
    }

    // Escribir el grafo de la escena en un archivo .osgt
    osgDB::writeNodeFile(*root, "scene_graph.osgt");

    return 0;
}