#include "cinder/app/AppNative.h"
#include "cinder/gl/gl.h"

#include <fstream>
#include <stdexcept>

#include "procon/ground.hpp"
#include "procon/constant.hpp"

using namespace ci;
using namespace ci::app;

class VisualizerApp : public AppNative {
	procon::ground _ground;

public:
	void setup();
	void mouseDown( MouseEvent event );	
	void update();
	void draw();
};

void VisualizerApp::setup()
{
	auto path = getOpenFilePath("", {"txt"});
	std::ifstream ifs(path.string(), std::ifstream::in);

	if(!ifs){
		throw std::runtime_error("cannot open " + path.string());
	}

	_ground = procon::ground(procon::ground::read_ground(ifs));
}

void VisualizerApp::mouseDown( MouseEvent event )
{
}

void VisualizerApp::update()
{
}

void VisualizerApp::draw()
{
	// clear out the window with black
	gl::clear( Color( 1.f, 1.f, 1.f ) ); 

	for(int i = 0; i < procon::ground_size; i++){
		for(int j = 0; j < procon::ground_size; j++){
			Color c(1.f, 1.f, 1.f);

			if(_ground[i][j].is_barrier()){
				c = Color(0, 0, 0);
			}

			gl::color(c);
			gl::drawSolidRect(Rectf(j * 5, i * 5, (j + 1) * 5, (i + 1) * 5));
		}
	}
}

CINDER_APP_NATIVE( VisualizerApp, RendererGl )
