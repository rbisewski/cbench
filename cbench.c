//! cbench.c
/*
 * Description: The main program file for the cbench project.
 */

#include "cbench.h"

//
// TODO: this program is in the process of being rewritten, so
//       might want to ignore the broken stuff
//

struct Sphere { 
    double rad;    // radius

    Vec p, e, c;   // position, emission, color 

    // Reflection type
    //
    // 0 --> DIFFuse
    // 1 --> SPECular,
    // 2 --> REFRactive
    //
    unsigned int refl;

    Sphere(double rad_, Vec p_, Vec e_, Vec c_, int refl_): 
      rad(rad_), p(p_), e(e_), c(c_), refl(refl_) {} 

    // returns distance, 0 if nohit
    double intersect(const Ray &r) const {

        //
        // Solve t^2*d.d + 2*t*(o-p).d + (o-p).(o-p)-R^2 = 0
        //
        Vec op = subVec(p, r.o);

        double t;
        double eps = 1e-4;
        double b   = dot(op, r.d);
        double det = b*b - dot(op, op) + rad * rad;

        // If the determinant is less than zero, assume these never intersect.
        if (det < 0) {
            return 0;
        }

        // Otherwise just grab the square fo the determinant.
        det = sqrt(det); 

        // Finally, calculate and return the distance.
        return ((t=b-det) > eps) ? t : ((t=b+det)>eps ? t : 0); 
    } 
}; 

Sphere spheres[] = {
    //Scene: radius, position, emission, color, material 
    Sphere(1e5,  newVector( 1e5+1,40.8,81.6),    newVector(0, 0, 0),  newVector(.75,.25,.25),               DIFF),//Left 
    Sphere(1e5,  newVector(-1e5+99,40.8,81.6),   newVector(0, 0, 0),  newVector(.25,.25,.75),               DIFF),//Rght 
    Sphere(1e5,  newVector(50.0,40.8, 1e5),      newVector(0, 0, 0),  newVector(.75,.75,.75),               DIFF),//Back 
    Sphere(1e5,  newVector(50.0,40.8,-1e5+170),  newVector(0, 0, 0),  newVector(0.0, 0.0, 0.0),             DIFF),//Frnt 
    Sphere(1e5,  newVector(50.0, 1e5, 81.6),     newVector(0, 0, 0),  newVector(.75,.75,.75),               DIFF),//Botm 
    Sphere(1e5,  newVector(50.0,-1e5+81.6,81.6), newVector(0, 0, 0),  newVector(.75,.75,.75),               DIFF),//Top 
    Sphere(16.5, newVector(27.0,16.5,47),        newVector(0, 0, 0),  multiplyVec(newVector(1,1,1), 0.999), SPEC),//Mirr 
    Sphere(16.5, newVector(73.0,16.5,78),        newVector(0, 0, 0),  multiplyVec(newVector(1,1,1), 0.999), REFR),//Glas 
    Sphere(600,  newVector(50.0,681.6-.27,81.6), newVector(12,12,12), newVector(0,0,0),                     DIFF) //Lite 
}; 

inline double clamp(double x) {
    return x<0 ? 0 : x>1 ? 1 : x;
}

inline int toInt(double x) {
    return int(pow(clamp(x),1/2.2)*255+.5);
}

inline bool intersect(const Ray &r, double &t, int &id) {

    // Generic counter variables.
    int i = 0;

    //	
    double n = sizeof(spheres) / sizeof(Sphere);
    double d = 0.0;
    double inf=t=1e20;

    for(i=int(n); i--;) {
        if ((d=spheres[i].intersect(r)) && d<t) {
	    t=d;
	    id=i;
	} 
    }

    return t<inf; 
}

//! Calculates the radiance of the ray reflection.
/*
 * @param     Ray                given ray expanding outward
 * @param     int                depth of the radiance
 * @param     unsigned short[]   array of requested Xs
 *
 * @return    Vec                vector containing the (x,y,z) of the ray
 */
Vec radiance(const Ray &r, int depth, unsigned short *Xi) {

    // Variable declaration.
    Vec doubleN; 
    double nrdDotproduct = 0.0;
    Vec transposeN;
    Vec rdMinusTransposeN;

    // Distance from start to intersection.
    double t = 0.0;

    // ID of intersected object.
    int id = 0;

    // If this doesn't intersect, then return black.
    if (!intersect(r, t, id)) {
        return newVector(0,0,0);
    }

    // Sphere w/ hit
    const Sphere &obj = spheres[id];

    Vec x  = multiplyVec(addVec(r.o,r.d), t);
    Vec n  = vectorNormal(subVec(x,obj.p));
    Vec nl = (dot(n,r.d) < 0) ? n : multiplyVec(n,-1);
    Vec f  = obj.c;

    // Determine maximum reflection potential.
    double p = f.x>f.y && f.x > f.z ? f.x : f.y>f.z ? f.y : f.z;

    // If the given depth is greater than 5...
    if (++depth > 5) {

        // If less than the max reflection value, 
        if (erand48(Xi) < p) {
            f = multiplyVec(f, (1/p));

	// Otherwise return the object as-is.
	} else {
            return obj.e;
	}
    }

    // Ideal DIFFUSE reflection 
    if (obj.refl == DIFF) {

        // Calculate the diffuse vector.
        double r1  = 2*M_PI*erand48(Xi);
        double r2  = erand48(Xi);
        double r2s = sqrt(r2); 
        Vec w      = nl;
        Vec uu     = (fabs(w.x) > .1) ? newVector(0,1,0) : newVector(1,1,1);
        Vec u      = vectorNormal(modVec(uu, w));
        Vec v      = modVec(w, u);
        Vec dd1    = multiplyVec(u, cos(r1) * r2s);
        Vec dd2    = multiplyVec(v, sin(r1) * r2s);
        Vec dd3    = multiplyVec(w, sqrt(1-r2));
        Vec dd     = addVec(addVec(dd1, dd2), dd3);
        Vec d      = vectorNormal(dd);

        // Combine with the reflection with the diffuse vector to get the
        // diffuse reflection.
        return addVec(obj.e, multiplyVectors(f, radiance(newRay(x,d),depth,Xi)));
    }

    // Ideal SPECULAR reflection 
    if (obj.refl == SPEC) {

        // Assemble the specular ray.
        doubleN           = multiplyVec(n, 2);
        nrdDotproduct     = dot(n, r.d);
        transposeN        = multiplyVec(doubleN, nrdDotproduct);
        rdMinusTransposeN = subVec(r.d, transposeN);
        Ray specRay       = newRay(x, rdMinusTransposeN);

        // Combine with the reflection with the specular vector to get the
        // specular reflection.
        return addVec(obj.e, multiplyVectors(f, radiance(specRay, depth, Xi)));
    }

    // Otherwise assemble the refraction ray.
    doubleN           = multiplyVec(n, 2);
    nrdDotproduct     = dot(n, r.d);
    transposeN        = multiplyVec(doubleN, nrdDotproduct);
    rdMinusTransposeN = subVec(r.d, transposeN);

    // Ideal dielectric REFRACTION.
    Ray reflRay = newRay(x, rdMinusTransposeN);

    // Boolean that stores whether or not a ray from outside is going in.
    bool into = (dot(n, nl) > 0);

    // Determine the waveform.
    double nc    = 1;
    double nt    = 1.5;
    double nnt   = into ? nc/nt : nt/nc;
    double ddn   = dot(r.d, nl);
    double cos2t = 0;

    // Total internal reflection. 
    if ((cos2t = 1 - nnt * nnt * (1 - ddn * ddn)) < 0) {
        f = multiplyVectors(f, radiance(reflRay, depth, Xi));
        return addVec(obj.e, f);
    }

    // Determine the internal / external ray line.
    double rayLine = (into ? 1 : -1) * ddn * nnt + sqrt(cos2t);

    // Calculate the normal of the ray triangle, which is the direction.
    Vec rdNNT    = multiplyVec(r.d, nnt);
    Vec nRayLine = multiplyVec(n, rayLine);
    Vec rt       = subVec(rdNNT, nRayLine);
    Vec tdir     = vectorNormal(rt);

    // Attempt to calculate the slope (a | b) of the ray.
    double a = nt - nc;
    double b = nt + nc;

    // Safety check, make sure that `b` isn't zero.
    if (b < 1 || (b * b) < 1) {
        return newVector(0,0,0);
    }

    // Use the above values to calculate the ray distance.
    double R0 = a * a / (b * b);
    double c  = 1 - (into ? -1 * ddn : dot(tdir, n));
    double Re = R0 + (1.0 - R0) * c * c * c * c * c;
    double Tr = 1.0 - Re;
    double P  = 0.25 + 0.5 * Re;

    // Safety check, make sure (P) and (1-P) aren't equal to zero.
    if (P == 0 || (1-P) == 0) {
        return newVector(0,0,0);
    }

    // Attempt to calculate the RP and TP.
    double RP = Re / P;
    double TP = Tr / (1 - P);

    // Generate the primary-radiance vector.
    Vec radRP = multiplyVec(radiance(reflRay, depth, Xi), RP);
    Vec radTP = multiplyVec(radiance(newRay(x, tdir), depth, Xi), TP);
    Vec primaryRadianceVec = (erand48(Xi) < P) ? radRP : radTP;

    // Generate the alt-radiance vector.
    Vec altRad1   = radiance(reflRay, depth, Xi);
    Vec altRadRe1 = multiplyVec(altRad1, Re);
    Vec altRad2   = radiance(newRay(x,tdir), depth, Xi);
    Vec altRadTr2 = multiplyVec(altRad2, Tr);
    Vec altRadianceVec = addVec(altRadRe1, altRadTr2);

    // Based on the depth, determine whether to pick the primary or 
    // alternate vector.
    if (depth > 2) {
        f = multiplyVectors(f, primaryRadianceVec);
    } else {
        f = multiplyVectors(f, altRadianceVec);
    }

    // Do a Russian roulette on the object radiance value.
    return addVec(obj.e, f);
}

//
// Program main
//
int main(int argc, char *argv[])
{
    //
    // TODO: this program is in the process of being rewritten, so
    //       might want to ignore the broken stuff
    //
    
    // Generic counter variables.
    int i = 0;
    unsigned short x = 0;
    unsigned short Xi[3] = {0,0,0};
    int y = 0;

    // Counter variables for samples.
    int s  = 0;
    int sx = 0;
    int sy = 0;

    // Image width / height.
    int w = 1024;
    int h = 768;

    // Terminate the program is width and height are less than 1.
    if (w < 1 || h < 1) {
        return 1;
    }

    // Determine the number of samples (where 0.25 == 1/4)
    int samps = (argc == 2) ? atoi(argv[1]) * 0.25 : 1;
 
    // Camera position.
    Vec camNorm = vectorNormal(newVector(0.0, -0.042612, -1.0));
    Ray cam     = newRay(newVector(50.0, 52.0, 295.6), camNorm);

    // Camera direction.
    Vec cx = newVector(w*.5135/h, w*.5135/h, w*.5135/h);
    Vec cy = multiplyVec(vectorNormal(modVec(cx, cam.d)), 0.5135);
    Vec r  = newVector(0,0,0);
    Vec *c = (Vec*) calloc(w*h, sizeof(Vec));

    // Use OpenMP to loop over image rows.
    #pragma omp parallel for schedule(dynamic, 1) private(r)
    for (y = 0; y < h; y++) {

      // Dump a message to standard error about sample rendering.
      fprintf(stdout, "\rRendering (%d spp) %5.2f%%", samps*4, 100.*y/(h-1));

      // Assign values to each of the x integers.
      Xi[0] = 0;
      Xi[1] = 0;
      Xi[2] = y*y*y;

      // Loop thru the columns.
      for (x = 0; x < w; x++) {

          // For-loop thru 2x2 subpixel rows
          for (sy = 0, i = (h-y-1) * w+x; sy<2; sy++) {
  
  	      // For-loop thru 2x2 subpixel columns.
              for (sx = 0; sx < 2; sx++, r=Vec()) {
  
  		  // For all of the samples.
                  for (s = 0; s < samps; s++) {

		      // First ray sample.
                      double r1=2*erand48(Xi), dx=r1<1 ? sqrt(r1)-1: 1-sqrt(2-r1);

		      // Second ray sample.
                      double r2=2*erand48(Xi), dy=r2<1 ? sqrt(r2)-1: 1-sqrt(2-r2);

                      Vec adjCx = multiplyVec(cx, ((sx+.5 + dx)/2 + x)/w - .5);
                      Vec adjCy = multiplyVec(cy, ((sy+.5 + dy)/2 + y)/h - .5);

                      Vec d = addVec(addVec(adjCx, adjCy), cam.d);

                      // Assemble the camera ray and adjust it based on samples.
                      Vec camRayAdj       = addVec(cam.o,multiplyVec(d,140));
                      Vec normalD         = vectorNormal(d);
                      Ray camRay          = newRay(camRayAdj, normalD);
                      Vec camRadiance     = radiance(camRay,0,Xi);
                      Vec camRadSampleAdj = multiplyVec(camRadiance,1.0/samps);

		      // Camera rays are pushed ^^^^^ up to start in interior
                      r = addVec(r, camRadSampleAdj);
                  }
 
		  // Assign the result to the picture element of the camera
                  // view (i.e. the pixel value).
                  c[i] = addVec(c[i], newVector(clamp(r.x), clamp(r.y), clamp(r.z)));
                  c[i] = multiplyVec(c[i], 0.25);
              }
          }
      }
    }
  
    // Open the image file, with write permissions.
    FILE *f = fopen("image.ppm", "w");
  
    // Print the magic number containing the file format to the image file.
    fprintf(f, "P3\n%d %d\n%d\n", w, h, 255);
    
    // Print the image data to the specified file.
    for (i = 0; i < w * h; i++) { 
        fprintf(f,"%d %d %d ", toInt(c[i].x), toInt(c[i].y), toInt(c[i].z)); 
    }

    // Close the generated image file.
    fclose(f);

    // Append a newline in the event the end-user is using bash.
    fprintf(stdout,"\n");

    // The program ended successfully.
    return 0;
}
