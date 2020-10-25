#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openFrameworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(2);

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 280, true, true, true);
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	vector<string> word_list = {
		"XYZ"
	};

	vector<glm::vec2> base_location_list = {
		glm::vec2(ofGetWidth() * 0.5 - this->font.stringWidth(word_list[0]) * 0.5, ofGetHeight() * 0.5 + this->font.stringHeight(word_list[0]) * 0.5)
	};

	for (int i = 0; i < word_list.size(); i++) {

		auto word = word_list[i];
		auto base_location = base_location_list[i];

		int sample_count = 280;
		vector<ofPath> word_path = this->font.getStringAsPoints(word, true, false);

		for (int word_index = 0; word_index < word_path.size(); word_index++) {

			vector<ofPolyline> outline = word_path[word_index].getOutline();
			for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

				outline[outline_index] = outline[outline_index].getResampledByCount(sample_count);
				vector<glm::vec3> vertices = outline[outline_index].getVertices();
				for (int k = 0; k < 100; k++) {

					auto index_start = (int)ofRandom(vertices.size());
					auto speed = ofRandom(0.25, 0.8);
					auto noise_seed = glm::vec2(ofRandom(1000), ofRandom(1000));

					ofNoFill();
					ofBeginShape();
					for (int m = 0; m < 8; m++) {

						int index = (int)(index_start + (ofGetFrameNum() + m) * speed) % vertices.size();
						auto noise_location = glm::vec2(ofMap(ofNoise(noise_seed.x, (ofGetFrameNum() + m) * 0.03), 0, 1, -15, 15), ofMap(ofNoise(noise_seed.y, (ofGetFrameNum() + m) * 0.03), 0, 1, -15, 15));
	
						ofVertex(vertices[index] + base_location + noise_location);

						if (m == 7) { 
						
							ofFill();
							ofDrawCircle(vertices[index] + base_location + noise_location, 3);
							ofNoFill();
						}
					}
					ofEndShape();
				}
			}
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}