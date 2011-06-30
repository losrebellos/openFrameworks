#pragma once

#include "ofBaseGui.h"

class ofGuiCollection : public ofBaseGui{
public:
	
	void setup(string collectionName, float x, float y){
		name = collectionName;
		b.x	 = x;
		b.y	 = y;
		header = 18;
		spacing  = 4;
		currentY = header + spacing;
		b.width = 200;
		b.height = 100;
		ofRegisterMouseEvents(this);			
	}
	
	void add(ofBaseGui * element){
		collection.push_back( element );
		
		element->b.y = currentY;
		element->b.x = 0;
		currentY += element->b.height + spacing;
		
		if( currentY >= b.height ){
			b.height += 40;
		}
	}		
	
	void clear(){
		collection.clear();
	}
	
	virtual void mouseMoved(ofMouseEventArgs & args){
		ofMouseEventArgs a = args;
		a.x -= b.x;
		a.y -= b.y;		
		for(int k = 0; k < collection.size(); k++){
			collection[k]->mouseMoved(a);
		}		
	}
	
	virtual void mousePressed(ofMouseEventArgs & args){
		setValue(args.x, args.y, true);
		if( bGuiActive ){
			ofMouseEventArgs a = args;
			a.x -= b.x;
			a.y -= b.y;
			for(int k = 0; k < collection.size(); k++){
				collection[k]->mousePressed(a);
			}
		}
	}
	
	virtual void mouseDragged(ofMouseEventArgs & args){
		setValue(args.x, args.y, false);	
		if( bGuiActive ){
			ofMouseEventArgs a = args;
			a.x -= b.x;
			a.y -= b.y;			
			for(int k = 0; k < collection.size(); k++){
				collection[k]->mouseDragged(a);
			}
		}					
	}
	
	virtual void mouseReleased(ofMouseEventArgs & args){
		bGuiActive = false;
		for(int k = 0; k < collection.size(); k++){
			ofMouseEventArgs a = args;
			a.x -= b.x;
			a.y -= b.y;			
			collection[k]->mouseReleased(a);
		}
	}		
	
	void draw(){
		currentFrame = ofGetFrameNum();
		
		ofPushStyle();
		ofFill();
		
		//ofSetColor(10, 10, 10, 170);
		//ofRect(b);	
		
		ofSetColor(30, 30, 80);
		ofRect(b.x, b.y, b.width, header);			
		
		ofSetColor(230);
		ofDrawBitmapString(name, b.x + 4, b.y + 12);
		
		ofPushMatrix();
		ofTranslate(b.x, b.y, 0);		
		for(int k = 0; k < collection.size(); k++){
			collection[k]->draw();
		}
		ofPopMatrix();
		ofPopStyle();
	}
	
protected:
	
	void setValue(float mx, float my, bool bCheck){
		
		if( ofGetFrameNum() - currentFrame > 1 ){
			bGrabbed = false;
			bGuiActive = false;
			return; 
		}
		if( bCheck ){
			if( b.inside(mx, my) ){
				bGuiActive = true;
				
				if( my > b.y && my <= b.y + header ){
					bGrabbed = true;					
					grabPt.set(mx-b.x, my-b.y);
				}else{
					bGrabbed = false;
				}
			}
		}else if( bGrabbed ){
			b.x = mx - grabPt.x;
			b.y = my - grabPt.y;
		}
	}		
	
	ofPoint grabPt;
	bool bGrabbed;
	float currentY;
	float spacing;
	float header;
	vector <ofBaseGui *> collection;
};
