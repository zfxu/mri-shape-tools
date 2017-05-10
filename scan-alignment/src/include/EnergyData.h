#ifndef __ENERGY_DATA_H__
#define __ENERGY_DATA_H__

#include <vector>

#include <vnl/vnl_vector.h>
#include <armadillo>

#include "mesh/Mesh.h"
#include "scan/Scan.h"

class EnergyData{

public:

  /*--------------------------------------------------------------------------*/

  EnergyData(
    const Mesh& sourceMesh,
    const std::vector<arma::vec>& sourceProfiles,
    const Scan& targetScan
    ):
    sourceMesh(sourceMesh), sourceProfiles(sourceProfiles),
    targetScan(targetScan) {

    this->transformation = vnl_vector<double>(6, 0.);

  }

  /*--------------------------------------------------------------------------*/

  Mesh sourceMesh;
  std::vector<arma::vec> sourceProfiles;
  Scan targetScan;

  vnl_vector<double> transformation;
  
  /*--------------------------------------------------------------------------*/

};

#endif