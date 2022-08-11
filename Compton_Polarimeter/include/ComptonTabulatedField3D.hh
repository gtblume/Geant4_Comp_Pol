#include "globals.hh"
#include "G4MagneticField.hh"
#include "G4ios.hh"

#include <fstream>
#include <vector>
#include <cmath>

class TabulatedField3D
#ifndef STANDALONE
 : public G4MagneticField
#endif
{

  // Storage space for the table
  std::vector< std::vector< std::vector< double > > > xField;
  std::vector< std::vector< std::vector< double > > > yField;
  std::vector< std::vector< std::vector< double > > > zField;
  // The dimensions of the table
  int nx,ny,nz;
  // The physical limits of the defined region
  double minx, maxx, miny, maxy, minz, maxz;
  // The physical extent of the defined region
  double dx, dy, dz;
  double fZoffset;
  bool invertX, invertY, invertZ;

public:
  TabulatedField3D(const char* filename, double zOffset );
  void  GetFieldValue( const  double Point[4],
		       double *Bfield          ) const;
};
