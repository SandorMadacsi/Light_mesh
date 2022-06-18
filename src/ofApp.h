#pragma once

#include "ofMain.h"
#include "ofxGui.h"

using namespace glm;

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y );
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void mouseEntered(int x, int y);
		void mouseExited(int x, int y);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);

        ofMesh mesh;
        ofEasyCam cam;

        int w, h;
        bool b_messy, b_perlin, b_wire, b_march;

        ofMaterial redMaterial;
        ofLight pointLight;

        ofxPanel gui;

        ofxGuiGroup mesh_gui;
        ofParameter<float> p_range;
        ofParameter<float> p_height;

        //Material
        ofxGuiGroup ambient_material;
        ofParameter<float> am_red;
        ofParameter<float> am_green;
        ofParameter<float> am_blue;

        ofxGuiGroup specular_material;
        ofParameter<float> sm_red;
        ofParameter<float> sm_green;
        ofParameter<float> sm_blue;

        ofxGuiGroup material_shininess;
        ofParameter<float> shininess;

        //Light
        ofxGuiGroup ambient_gui;
        ofParameter<float> a_red;
        ofParameter<float> a_green;
        ofParameter<float> a_blue;

        ofxGuiGroup diffuse_gui;
        ofParameter<float> d_red;
        ofParameter<float> d_green;
        ofParameter<float> d_blue;

        ofxGuiGroup specular_gui;
        ofParameter<float> s_red;
        ofParameter<float> s_green;
        ofParameter<float> s_blue;




        ofSpherePrimitive source;

		
};
