#ifndef __DIFFUSION_SETTINGS_H__
#define __DIFFUSION_SETTINGS_H__

class DiffusionSettings{

public:

  // time steps to take for the evolution
  int timeSteps = 1;
  // time step size -> affects stability of the used explicit scheme
  // use a lower value if any instabilities are observed
  double stepSize = 0.125;
  // parameter affecting what is identified as an edge
  double contrastLambda = 1;
  // determines how much neighborhood information is used for
  // deriving the diffusion tensor
  double integrationRho = 1;
  // standard deviation used for presmoothing the image with a
  // Gaussian convolution
  double presmoothSigma = 1;

};

#endif
