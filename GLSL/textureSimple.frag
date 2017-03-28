// simple volume rendering ray caster
// maximum ray steps to allow
const int MAXSTEPS=500;

// textures and shader parameters
uniform sampler2D volumeLUT;	    // table mapping value to color & opacity
uniform sampler3D volumeTexture; // volume texture data
uniform vec3 volumeSize;         // geometric size (volume is +/-volumeSize/2)
uniform vec3 voxelSize ;	        // dimensions in voxels in each direction
uniform float raystep ;	        // minimum ray step to take (in voxels)
uniform float opticalScale ;      // scale between geometric size and optical depth


// info passed from vertex shader
varying vec4 Eo;		// eye location in object space
varying vec4 Vo;		// position in object space

void main() {

    // Ray origin and direction
    vec3 pVol = Vo.xyz/Vo.w;                // origin on proxy surface
    vec3 pVox = .5 + pVol/volumeSize;       // ray origin in voxel space
    vec3 d = normalize(pVol*Eo.w - Eo.xyz); // unit-length ray direction [1]
	
    // single ray step
    float stepVol = raystep * volumeSize.x/voxelSize.x; // step in volume space
    float stepOptical = stepVol * opticalScale;         // step in optical scale
    vec3 dVox = d * stepVol / volumeSize;               // step vector in voxels

    // find ray exit point from box [2]
    vec3 box = (sign(d)*volumeSize*0.5 - pVol)/d;
    float exitVox = min(box.x,min(box.y,box.z)) * voxelSize.x / volumeSize.x;

    // loop through volume, accumulating integral contribution for each step
    vec4 result = vec4(0.); float s=0.;
    for(int i=0; i<MAXSTEPS && s<=exitVox; ++i, s+=raystep, pVox+=dVox) {
      vec4 vol = texture3D(volumeTexture, pVox);
      vec4 color = texture2D(volumeLUT, vol.xx) * stepOptical; // [3]
    	result = result + (1.-result.a)*color;
    }

    gl_FragColor = result;
}
/*
void main() {
// Test Every var first
// TExture2D volumeLUT tested
// Texture3D volumeTexture tested(I still don't know why glGetUniform returns -1 for it.
    vec4 color = texture2D(volumeLUT, gl_TexCoord[0].st);//vec4(1.,0.,1.,1.0);
	vec4 color2 = texture3D(volumeTexture, vec3(gl_TexCoord[1].stp));
	color = texture2D(volumeLUT, color2.xy);
	//vec3 testvec = vec3(2.0, 2.0, 2.0);
	if(volumeSize.x != 20.0)
		gl_FragColor = vec4(1.,0.,0.,0.);
	else
		gl_FragColor = color;
}
*/

