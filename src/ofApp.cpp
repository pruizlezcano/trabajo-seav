#include "ofApp.h"
#include "utils.h"

//--------------------------------------------------------------
void ofApp::setup(){
    ofBackground(255);
    
    box2d.init();
    box2d.setFPS(60);
    box2d.createBounds();
    box2d.setGravity(0, 0);
    
    
    // Crea una bola en el centro
    ball.name = "ball";
    ball.setPhysics(1.0, 0.5, 1); // TODO: esto habra que ir ajustandolo (densidad, rebote, rozamiento)
    // TODO: el rozamiento no hace absolutamente nada. La bola no reduce la velocidad, unicamente al rebotar
    ball.setup(box2d.getWorld(), ofGetWidth() / 2, ofGetHeight() / 2, 20);
    shooting = false;
}

//--------------------------------------------------------------
void ofApp::update(){
    box2d.update();
}

//--------------------------------------------------------------
void ofApp::draw(){
    ofSetColor(0);
    ofSetLineWidth(2);
    
    // Dibuja la linea de apuntado
    if (ball.getVelocity().lengthSquared()==0) {  // Si la bola esta quieta
        float lineLength = 200;
        ofVec2f direction = ofVec2f(ofGetMouseX(), ofGetMouseY()) - ball.getPosition();
        direction.normalize();
        ofVec2f lineEnd = ball.getPosition() + direction * lineLength;
        ofDrawLine(ball.getPosition().x, ball.getPosition().y, lineEnd.x, lineEnd.y);
        // TODO: podriamos hacer que dependiendo de la potencia de tiro la linea fuese mas largo o mas corta
    }
    
    // Dibuja la bola
    ofSetColor(255, 0, 0);
    ball.draw();
    
    
    // Muestra la potencia del disparo
    if (shooting) {
        float shootPower = Utils::calculateShootPower(mousePressTime);\
        string powerString = "shoot Power: " + ofToString(shootPower);  // TODO: ponemos esto en porcentaje?
        ofSetColor(0, 0, 0);
        ofDrawBitmapString(powerString, 20, 20);
    }
}

//--------------------------------------------------------------
void ofApp::contactStart(ofxBox2dContactArgs &e) {
    
}

//--------------------------------------------------------------
void ofApp::contactEnd(ofxBox2dContactArgs &e) {
    
}

//--------------------------------------------------------------
void ofApp::keyPressed(int key){
    if (key == 'r') {  // Reset de la bola a la posicion inicial
        ofLog(OF_LOG_NOTICE, "ball reset");
        ball.setPosition(ofGetWidth() / 2, ofGetHeight() / 2);
        ball.setVelocity(0, 0);
        ball.setRotation(0);
        // TODO: arreglar. Si la bola estaba girando se mantiene girando al reiniciarla.
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
    if (ball.getVelocity().lengthSquared()==0) {  // Si la bola esta quieta
        shooting = true;
        mousePressTime = ofGetElapsedTimeMillis();
    }
}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){
    if (shooting) {
        ofLog(OF_LOG_NOTICE, "Mouse click");
        
        ofVec2f direction = ofVec2f(x, y) - ball.getPosition();
        direction.normalize();
        
        float shootPower = Utils::calculateShootPower(mousePressTime);
        ofLog(OF_LOG_NOTICE, "ShootPower: "+ofToString(shootPower));
        
        // No encuentro diferencia entre estas dos formas de hacer que la bola se mueva
        ball.setVelocity(direction * shootPower);
        //ball.addForce(direction, shootPower*100);
        
        shooting = false;
    }
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
