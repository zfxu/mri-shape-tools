#ifndef __PROCESS_SCAN_H__
#define __PROCESS_SCAN_H__

#include <cairommconfig.h>
#include <cairomm/context.h>
#include <cairomm/surface.h>

#include "ImageStack.h"

#include "image/Image.h"

class ProcessScan {

  /*----------------------------------------------------------------------*/

public:

  ProcessScan(const std::string& path, bool discard) { 

    this->scan.read().from(path);

    if( discard == true ) {
      this->scan.values().discard(0.25, 0.25);
    }
 
    scan.values().scale(0, 255);

  }

  /*----------------------------------------------------------------------*/

  std::shared_ptr<ImageStack>
  get_image_stack() {

    std::vector<Cairo::RefPtr<Cairo::ImageSurface> > slices;

    for(int i = 0; i < this->scan.info().get_nz(); ++i) {
      slices.push_back( create_image_from_slice(i) );
    }

    std::shared_ptr<ImageStack> stack =
      std::make_shared<ImageStack>(slices);


    return stack;

  }


  /*----------------------------------------------------------------------*/

private:

  Image scan;

  /*----------------------------------------------------------------------*/

  Cairo::RefPtr<Cairo::ImageSurface>
  create_image_from_slice( const int& slice ) {

    // get dimensions of image
    const int columns = this->scan.info().get_nx();
    const int rows = this->scan.info().get_ny();

    // create new cairo image surface
    Cairo::RefPtr<Cairo::ImageSurface> cairoImage = 
      Cairo::ImageSurface::create( Cairo::FORMAT_ARGB32, columns, rows);

    const int stride = cairoImage->get_stride();
    const int channelAmount = 4;

    // get access to raw data of cairo surface
    unsigned char* data = cairoImage->get_data();

    // iterate over the pixels
    for( int i = 0; i < columns; ++i) {
      for( int j = 0; j < rows; ++j) {

        // get color at the current voxel
        double currentColor = this->scan.access().at_grid(i, j, slice);

        // get data for current pixels
        unsigned char *p = data + stride * j + i * channelAmount;

        // no transparency
        p[3] = 255;

        // set color
        p[2] = currentColor;
        p[1] = currentColor;
        p[0] = currentColor;
      }
    }

    // notify cairo that the surface was modified by other means than cairo
    cairoImage->mark_dirty();

    return cairoImage;

  }

  /*----------------------------------------------------------------------*/
};
#endif
