#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup(){
    mesh.setMode(OF_PRIMITIVE_TRIANGLES);

    w = 50;
    h =50;

    b_messy = false;
    ofBackground(0);
    ofSetColor(200);
    cam.setPosition(vec3(0.0f, 1.0f, 100.0f));
//    cam.setTarget(vec3(0.0f, 1.0f, 0.0f));
//    cam.setNearClip(0.05f);
//    cam.setFarClip(100.0f);
//    cam.setAutoDistance(false);
    source.setRadius(1.0f);






    gui.setup("GUI");

    mesh_gui.setup("Mesh GUI");
    //mesh_gui.add(intSlide.setup("hello", 0,1,50));
    mesh_gui.add(p_range.set("Perlin Range", 1,1,10));
    mesh_gui.add(p_height.set("Perlin Height", 1,1,10));
    gui.add(&mesh_gui);
//    guis.add(p_range.set("Range", 1, 0, 50));

    //Material
    ambient_material.setup("Ambient Material");
    ambient_material.add(am_red.set("Ambient Material Red", 1,0,1));
    ambient_material.add(am_green.set("Ambient Material Green", 1,0,1));
    ambient_material.add(am_blue.set("Ambient Material Blue", 1,0,1));
    gui.add(&ambient_material);

    specular_material.setup("Specular Material");
    specular_material.add(sm_red.set("Specular Material Red", 1,0,1));
    specular_material.add(sm_green.set("Specular MaterialGreen", 1,0,1));
    specular_material.add(sm_blue.set("Specular MaterialBlue", 1,0,1));
    gui.add(&specular_material);

    material_shininess.setup("Material Shininess");
    material_shininess.add(shininess.set("Shininess", 100,0,1000));
    gui.add(&material_shininess);


    //Light
    ambient_gui.setup("Ambient GUI");
    ambient_gui.add(a_red.set("Ambient Red", 1,0,1));
    ambient_gui.add(a_green.set("Ambient Green", 1,0,1));
    ambient_gui.add(a_blue.set("Ambient Blue", 1,0,1));
    gui.add(&ambient_gui);

    diffuse_gui.setup("Diffuse GUI");
    diffuse_gui.add(d_red.set("Diffuse Red", 1,0,1));
    diffuse_gui.add(d_green.set("Diffuse Green", 1,0,1));
    diffuse_gui.add(d_blue.set("Diffuse Blue", 1,0,1));
    gui.add(&diffuse_gui);

    specular_gui.setup("Specular GUI");
    specular_gui.add(s_red.set("Specular Red", 1,0,1));
    specular_gui.add(s_green.set("Specular Green", 1,0,1));
    specular_gui.add(s_blue.set("Specular Blue", 1,0,1));
    gui.add(&specular_gui);


    redMaterial.setSpecularColor(ofFloatColor(sm_red, sm_green, sm_blue));
    redMaterial.setAmbientColor(ofFloatColor(am_red, am_green, am_blue));
    redMaterial.setShininess(shininess);

    pointLight.setDiffuseColor(ofFloatColor(d_red, d_green, d_blue));
    pointLight.setSpecularColor(ofFloatColor(s_red, s_green, s_blue));
    pointLight.setPosition(vec3(10.0f, 10.0f, 20.0f));


    ofSetGlobalAmbientColor(ofFloatColor(a_red, a_green, a_green));


    pointLight.enable();

    //MESH SETUP -----------------------------------------------
    for(int y = 0; y < h; y++)
    {
        for(int x = 0; x < w; x++)
        {
            mesh.addVertex(ofPoint(x - w / 2 , y - h /2, 0));
            mesh.addColor(ofFloatColor(50,50,100));
        }
    }

    for(int y = 0; y < h - 1; y++)
    {
        for(int x = 0; x < w - 1; x++)
        {
          mesh.addIndex(x + y * w);
          mesh.addIndex((x + 1) + y * w);
          mesh.addIndex(x + (y + 1) * w);

          mesh.addIndex((x + 1) + y * w);
          mesh.addIndex((x + 1) + (y + 1) * w);
          mesh.addIndex(x+ (y + 1) * w);
        }
    }

}

//--------------------------------------------------------------
void ofApp::update(){
    ofVec3f n_pos;
//    ofColor n_color;
    float time = ofGetSystemTimeMillis()/ 100.0;
    redMaterial.setSpecularColor(ofFloatColor(sm_red, sm_green, sm_blue));
    redMaterial.setAmbientColor(ofFloatColor(am_red, am_green, am_blue));
    redMaterial.setShininess(shininess);

    pointLight.setDiffuseColor(ofFloatColor(d_red, d_green, d_blue));
    pointLight.setSpecularColor(ofFloatColor(s_red, s_green, s_blue));
    ofSetGlobalAmbientColor(ofFloatColor(a_red, a_green, a_green));
//    if (b_messy)
//    {
//        for(int i = 0; i< mesh.getNumVertices(); i++)
//        {
//            n_pos = mesh.getVertex(i);
//            n_pos.z = ofRandom(-intSlide,intSlide);
//            mesh.setVertex(i, n_pos);
//        }
//    }

//    if (b_perlin)
//    {
        int i = 0;
        for(int y = 0; y < h; y++)
        {
            for(int x = 0; x < w; x++)
            {
                n_pos = mesh.getVertex(i);
                n_pos.z = ofNoise( ofMap( x + time, 0, w, 0, p_range),
                                   ofMap( y, 0, h, 0, p_range)) * p_height;
            //    n_color.setHsb(200, 255 - ofMap(n_pos.z, 0, p_height, 0, 255), 150);
                mesh.setVertex(i, n_pos);
//                mesh.setColor(i, n_color);
                i++;
            }
        }
    //}
}

//--------------------------------------------------------------
void ofApp::draw(){
    gui.draw();

    ofEnableDepthTest();
    ofEnableLighting();

    cam.begin();
    ofPushMatrix();
    ofTranslate(vec3(10.0f, 10.0f, 20.0f));
    source.draw();
    ofPopMatrix();

    redMaterial.begin();
    mesh.draw();
    redMaterial.end();
    cam.end();

    ofDisableLighting();
    ofDisableDepthTest();


}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    switch (key) {
        case ' ':
            b_messy = !b_messy;
        break;
        case 'p':
            b_perlin = !b_perlin;
        break;
    }
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y ){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseEntered(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseExited(int x, int y){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
