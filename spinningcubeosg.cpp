#include <osgViewer/Viewer>
#include <osg/Geometry>
#include <osg/Geode>
#include <osg/Texture2D>
#include <osgDB/ReadFile>
#include <osgGA/TrackballManipulator>
#include <osg/MatrixTransform>

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

int main() {
    // Crea un visor OSG
    osgViewer::Viewer viewer;

    // Crea la geometría del cubo y aplica la textura
    osg::ref_ptr<osg::Geometry> cubeGeometry = createTexturedCube(1.0f);

    // Crea un nodo Geode para contener la geometría
    osg::ref_ptr<osg::Geode> geode = new osg::Geode;
    geode->addDrawable(cubeGeometry.get());

    // Crea un nodo MatrixTransform para manejar la rotación
    osg::ref_ptr<osg::MatrixTransform> rotationTransform = new osg::MatrixTransform;
    rotationTransform->addChild(geode.get());

    // Añade el nodo MatrixTransform al nodo raíz de la escena
    osg::ref_ptr<osg::Group> root = new osg::Group;
    root->addChild(rotationTransform.get());

    // Establece una manipulación de cámara para permitir la interacción del usuario
    viewer.setCameraManipulator(new osgGA::TrackballManipulator);

    // Establece la escena a renderizar
    viewer.setSceneData(root.get());

    // Bucle para rotar el cubo
    while (!viewer.done()) {
        double time = viewer.elapsedTime();
        osg::Matrix rotationMatrix;
        rotationMatrix.makeRotate(time * 0.5, osg::Vec3(0.5, 1.0, 0.0)); // Rotación sobre el eje Y
        rotationTransform->setMatrix(rotationMatrix);
        viewer.frame();
    }

    return 0;
}
