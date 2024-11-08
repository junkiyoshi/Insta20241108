#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetWindowTitle("openFrameworks");
	ofSetFrameRate(25);

	ofBackground(239);
	ofSetColor(0);
	ofSetLineWidth(2);

	this->font_size = 50;
	this->font.loadFont("fonts/msgothic.ttc", this->font_size, true, true, true);

	this->charactor_list = { 'a', 'n', 't', 'h', 'o', 'l', 'o', 'g', 'y', '(', ')', ';'};
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();
	ofRotateX(180);

	int sample_count = 180;

	for (int x = -360; x <= 360; x += 60) {

		for (int y = -288; y <= 288; y += 72) {

			ofPath path = this->font.getCharacterAsPoints(this->charactor_list[(x + 360) / 60], true, false);
			vector<ofPolyline> outline = path.getOutline();
			int frame_param = (x + 360) * -0.25 + (y + 288) * -2 + ofGetFrameNum() * 6 + 15000;

			for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

				outline[outline_index] = outline[outline_index].getResampledByCount(sample_count);
				vector<glm::vec3> vertices = outline[outline_index].getVertices();

				ofBeginShape();
				for (int vertices_index = 0; vertices_index < vertices.size(); vertices_index++) {

					glm::vec3 vertex = glm::vec3(x + 18, y + 27, 0) + glm::vec3(vertices[vertices_index].x, vertices[vertices_index].y, vertices[vertices_index].z);

					if (frame_param % (sample_count * 2) < sample_count) {

						if (vertices_index < frame_param % sample_count) {

							ofVertex(vertex);
						}
					}
					else {

						if (vertices_index > frame_param % sample_count) {

							ofVertex(vertex);
						}
					}

					if (vertices_index == frame_param % sample_count) {

						ofFill();
						ofDrawSphere(vertex, 2);
						ofNoFill();
					}

				}
				ofEndShape();
			}

		}
	}

	this->cam.end();

	/*
	int start = 250;
	if (ofGetFrameNum() > start) {

		ostringstream os;
		os << setw(4) << setfill('0') << ofGetFrameNum() - start;
		ofImage image;
		image.grabScreen(0, 0, ofGetWidth(), ofGetHeight());
		image.saveImage("image/cap/img_" + os.str() + ".jpg");
		if (ofGetFrameNum() - start >= 25 * 20) {

			std::exit(1);
		}
	}
	*/
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}