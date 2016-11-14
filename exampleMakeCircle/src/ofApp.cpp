#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {
	auto frame = make_shared<ofxIldaFile::Frame_Format0>();

	size_t count = 100;
	for (int i = 0; i < count; i++) {
		ofxIldaFile::Records::Format0 record;
		double theta = (double) i / (double) count * TWO_PI;
		record.x = (double)(std::numeric_limits<int16_t>::max() - 1) * sin(theta);
		record.y = (double)(std::numeric_limits<int16_t>::max() - 1) * cos(theta);
		record.z = 0;
		
		//record.statusCode = i != count - 1
		//	? ofxIldaFile::Records::StatusCode::NoStatus
		//	: ofxIldaFile::Records::StatusCode::LastPoint;
		record.statusCode = ofxIldaFile::Records::StatusCode::NoStatus;

		record.colorIndex = 57; // white

		frame->addRecord(record);
	}
	
	this->sequence.addFrame(frame);

	this->sequence.save("circle.ild");




// 	frame->clear();
// 	ofxIldaFile::Records::Format0 record;
// 	record.x = 0;
// 	record.y = 0;
// 	record.z = 0;
// 	record.statusCode = ofxIldaFile::Records::StatusCode::NoStatus;
// 	record.colorIndex = 57;
// 	frame->addRecord(record);
// 	this->sequence.save("point.ild");
}

//--------------------------------------------------------------
void ofApp::update(){

}

//--------------------------------------------------------------
void ofApp::draw(){
	ofBackground(0);
	this->sequence.draw(0, 0, ofGetWidth(), ofGetHeight());
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){

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
