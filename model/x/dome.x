xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 42;
 0.00000;28.18319;0.00000;,
 7.71254;26.01362;-7.71254;,
 0.00000;26.01362;-10.90720;,
 0.00000;28.18319;0.00000;,
 10.90720;26.01362;0.00000;,
 0.00000;28.18319;0.00000;,
 7.71254;26.01362;7.71254;,
 0.00000;28.18319;0.00000;,
 0.00000;26.01362;10.90720;,
 0.00000;28.18319;0.00000;,
 -7.71254;26.01362;7.71254;,
 0.00000;28.18319;0.00000;,
 -10.90720;26.01362;0.00000;,
 0.00000;28.18319;0.00000;,
 -7.71254;26.01362;-7.71254;,
 0.00000;28.18319;0.00000;,
 0.00000;26.01362;-10.90720;,
 14.25092;19.83520;-14.25092;,
 0.00000;19.83520;-20.15385;,
 20.15385;19.83520;0.00000;,
 14.25092;19.83520;14.25092;,
 0.00000;19.83520;20.15385;,
 -14.25092;19.83520;14.25092;,
 -20.15385;19.83520;0.00000;,
 -14.25092;19.83520;-14.25092;,
 0.00000;19.83520;-20.15385;,
 26.33231;10.58854;0.00000;,
 18.61974;10.58854;-18.61974;,
 18.61974;10.58854;18.61974;,
 0.00000;10.58854;26.33231;,
 -18.61974;10.58854;18.61974;,
 -26.33231;10.58854;0.00000;,
 -18.61974;10.58854;-18.61974;,
 0.00000;10.58854;-26.33231;,
 28.50184;-0.31865;-0.00000;,
 20.15385;-0.31865;-20.15385;,
 20.15385;-0.31865;20.15385;,
 0.00000;-0.31865;28.50184;,
 -20.15385;-0.31865;20.15385;,
 -28.50184;-0.31865;0.00000;,
 -20.15385;-0.31865;-20.15385;,
 0.00000;-0.31865;-28.50184;;
 
 60;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,14;,
 4;2,1,17,18;,
 4;1,4,19,17;,
 4;4,6,20,19;,
 4;6,8,21,20;,
 4;8,10,22,21;,
 4;10,12,23,22;,
 4;12,14,24,23;,
 4;14,16,25,24;,
 4;17,19,26,27;,
 4;19,20,28,26;,
 4;20,21,29,28;,
 4;21,22,30,29;,
 4;22,23,31,30;,
 4;23,24,32,31;,
 4;24,25,33,32;,
 4;27,26,34,35;,
 4;26,28,36,34;,
 4;28,29,37,36;,
 4;29,30,38,37;,
 4;30,31,39,38;,
 4;31,32,40,39;,
 4;32,33,41,40;,
 3;2,1,0;,
 3;1,4,3;,
 3;4,6,5;,
 3;6,8,7;,
 3;8,10,9;,
 3;10,12,11;,
 3;12,14,13;,
 3;14,16,15;,
 4;18,17,1,2;,
 4;17,19,4,1;,
 4;19,20,6,4;,
 4;20,21,8,6;,
 4;21,22,10,8;,
 4;22,23,12,10;,
 4;23,24,14,12;,
 4;24,25,16,14;,
 4;27,26,19,17;,
 4;26,28,20,19;,
 4;28,29,21,20;,
 4;29,30,22,21;,
 4;30,31,23,22;,
 4;31,32,24,23;,
 4;32,33,25,24;,
 4;35,34,26,27;,
 4;34,36,28,26;,
 4;36,37,29,28;,
 4;37,38,30,29;,
 4;38,39,31,30;,
 4;39,40,32,31;,
 4;40,41,33,32;;
 
 MeshMaterialList {
  1;
  60;
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.432800;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  66;
  0.000000;1.000000;0.000000;,
  0.000000;0.924736;-0.380610;,
  0.269132;0.924735;-0.269132;,
  0.380610;0.924736;0.000000;,
  0.269132;0.924735;0.269132;,
  0.000000;0.924736;0.380610;,
  -0.269132;0.924735;0.269132;,
  -0.380610;0.924736;0.000000;,
  -0.269132;0.924735;-0.269132;,
  -0.113689;0.749192;-0.652523;,
  0.541794;0.749192;-0.381013;,
  0.704976;0.709231;0.000000;,
  0.498493;0.709231;0.498493;,
  0.000000;0.709231;0.704976;,
  -0.498493;0.709231;0.498493;,
  -0.704976;0.709231;0.000000;,
  -0.498493;0.709231;-0.498493;,
  -0.357145;0.359189;-0.862224;,
  0.862224;0.359189;-0.357145;,
  0.923104;0.384551;0.000000;,
  0.652733;0.384551;0.652733;,
  0.000000;0.384551;0.923104;,
  -0.652733;0.384551;0.652733;,
  -0.923104;0.384551;0.000000;,
  -0.652733;0.384551;-0.652733;,
  -0.376381;0.180742;-0.908664;,
  0.908664;0.180742;-0.376381;,
  0.980786;0.195088;0.000000;,
  0.693520;0.195088;0.693520;,
  0.000000;0.195088;0.980786;,
  -0.693520;0.195088;0.693520;,
  -0.980786;0.195088;0.000000;,
  -0.693520;0.195088;-0.693520;,
  0.000000;-0.924736;0.380610;,
  -0.269132;-0.924735;0.269132;,
  -0.000000;-1.000000;0.000000;,
  -0.380610;-0.924736;0.000000;,
  -0.269132;-0.924735;-0.269132;,
  0.000000;-0.924736;-0.380610;,
  0.269132;-0.924735;-0.269132;,
  0.380610;-0.924736;-0.000000;,
  0.269132;-0.924735;0.269132;,
  0.113689;-0.749192;0.652523;,
  -0.541794;-0.749192;0.381013;,
  -0.704976;-0.709231;0.000000;,
  -0.498493;-0.709231;-0.498493;,
  0.000000;-0.709231;-0.704976;,
  0.498493;-0.709231;-0.498493;,
  0.704976;-0.709231;-0.000000;,
  0.498493;-0.709231;0.498493;,
  -0.862224;-0.359189;0.357145;,
  -0.923104;-0.384551;0.000000;,
  -0.652733;-0.384551;-0.652733;,
  0.000000;-0.384551;-0.923104;,
  0.652733;-0.384551;-0.652733;,
  0.923104;-0.384551;-0.000000;,
  0.652733;-0.384551;0.652733;,
  0.357145;-0.359189;0.862224;,
  -0.908664;-0.180742;0.376381;,
  -0.980786;-0.195088;0.000000;,
  -0.693520;-0.195088;-0.693520;,
  0.000000;-0.195088;-0.980786;,
  0.693520;-0.195088;-0.693520;,
  0.980786;-0.195088;-0.000000;,
  0.693520;-0.195088;0.693520;,
  0.376381;-0.180742;0.908664;;
  60;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,1,8;,
  4;1,2,10,9;,
  4;2,3,11,10;,
  4;3,4,12,11;,
  4;4,5,13,12;,
  4;5,6,14,13;,
  4;6,7,15,14;,
  4;7,8,16,15;,
  4;8,1,9,16;,
  4;10,11,19,18;,
  4;11,12,20,19;,
  4;12,13,21,20;,
  4;13,14,22,21;,
  4;14,15,23,22;,
  4;15,16,24,23;,
  4;16,9,17,24;,
  4;18,19,27,26;,
  4;19,20,28,27;,
  4;20,21,29,28;,
  4;21,22,30,29;,
  4;22,23,31,30;,
  4;23,24,32,31;,
  4;24,17,25,32;,
  3;33,34,35;,
  3;34,36,35;,
  3;36,37,35;,
  3;37,38,35;,
  3;38,39,35;,
  3;39,40,35;,
  3;40,41,35;,
  3;41,33,35;,
  4;42,43,34,33;,
  4;43,44,36,34;,
  4;44,45,37,36;,
  4;45,46,38,37;,
  4;46,47,39,38;,
  4;47,48,40,39;,
  4;48,49,41,40;,
  4;49,42,33,41;,
  4;50,51,44,43;,
  4;51,52,45,44;,
  4;52,53,46,45;,
  4;53,54,47,46;,
  4;54,55,48,47;,
  4;55,56,49,48;,
  4;56,57,42,49;,
  4;58,59,51,50;,
  4;59,60,52,51;,
  4;60,61,53,52;,
  4;61,62,54,53;,
  4;62,63,55,54;,
  4;63,64,56,55;,
  4;64,65,57,56;;
 }
 MeshTextureCoords {
  42;
  0.062500;0.000000;,
  0.125000;0.125000;,
  0.000000;0.125000;,
  0.187500;0.000000;,
  0.250000;0.125000;,
  0.312500;0.000000;,
  0.375000;0.125000;,
  0.437500;0.000000;,
  0.500000;0.125000;,
  0.562500;0.000000;,
  0.625000;0.125000;,
  0.687500;0.000000;,
  0.750000;0.125000;,
  0.812500;0.000000;,
  0.875000;0.125000;,
  0.937500;0.000000;,
  1.000000;0.125000;,
  0.125000;0.250000;,
  0.000000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.250000;0.375000;,
  0.125000;0.375000;,
  0.375000;0.375000;,
  0.500000;0.375000;,
  0.625000;0.375000;,
  0.750000;0.375000;,
  0.875000;0.375000;,
  1.000000;0.375000;,
  0.250000;0.500000;,
  0.125000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;;
 }
}
