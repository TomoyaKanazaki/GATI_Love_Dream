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
 86;
 0.00000;38.90880;-6.16441;,
 4.35891;38.90880;-4.35891;,
 4.35891;0.08332;-4.35891;,
 0.00000;0.08332;-6.16441;,
 6.16441;38.90880;0.00000;,
 6.16441;0.08332;0.00000;,
 4.35891;38.90880;4.35891;,
 4.35891;0.08332;4.35891;,
 0.00000;38.90880;6.16441;,
 0.00000;0.08332;6.16441;,
 -4.35891;38.90880;4.35891;,
 -4.35891;0.08332;4.35891;,
 -6.16441;38.90880;0.00000;,
 -6.16441;0.08332;0.00000;,
 -4.35891;38.90880;-4.35891;,
 -4.35891;0.08332;-4.35891;,
 0.00000;38.90880;-6.16441;,
 0.00000;0.08332;-6.16441;,
 0.00000;38.90880;0.00000;,
 0.00000;38.90880;0.00000;,
 0.00000;38.90880;0.00000;,
 0.00000;38.90880;0.00000;,
 0.00000;38.90880;0.00000;,
 0.00000;38.90880;0.00000;,
 0.00000;38.90880;0.00000;,
 0.00000;38.90880;0.00000;,
 0.00000;0.08332;0.00000;,
 0.00000;0.08332;0.00000;,
 0.00000;0.08332;0.00000;,
 0.00000;0.08332;0.00000;,
 0.00000;0.08332;0.00000;,
 0.00000;0.08332;0.00000;,
 0.00000;0.08332;0.00000;,
 0.00000;0.08332;0.00000;,
 0.00000;21.55424;-20.81668;,
 0.00000;56.19885;0.00000;,
 14.71959;21.55424;-14.71959;,
 0.00000;56.19885;0.00000;,
 20.81668;21.55424;0.00000;,
 0.00000;56.19885;0.00000;,
 14.71959;21.55424;14.71959;,
 0.00000;56.19885;0.00000;,
 0.00000;21.55424;20.81668;,
 0.00000;56.19885;0.00000;,
 -14.71959;21.55424;14.71959;,
 0.00000;56.19885;0.00000;,
 -20.81668;21.55424;0.00000;,
 0.00000;56.19885;0.00000;,
 -14.71959;21.55424;-14.71959;,
 0.00000;56.19885;0.00000;,
 0.00000;21.55424;-20.81668;,
 0.00000;21.55424;0.00000;,
 0.00000;21.55424;-20.81668;,
 14.71959;21.55424;-14.71959;,
 20.81668;21.55424;0.00000;,
 14.71959;21.55424;14.71959;,
 0.00000;21.55424;20.81668;,
 -14.71959;21.55424;14.71959;,
 -20.81668;21.55424;0.00000;,
 -14.71959;21.55424;-14.71959;,
 0.00000;39.07623;-20.81668;,
 0.00000;73.72086;0.00000;,
 14.71959;39.07623;-14.71959;,
 0.00000;73.72086;0.00000;,
 20.81668;39.07623;0.00000;,
 0.00000;73.72086;0.00000;,
 14.71959;39.07623;14.71959;,
 0.00000;73.72086;0.00000;,
 0.00000;39.07623;20.81668;,
 0.00000;73.72086;0.00000;,
 -14.71959;39.07623;14.71959;,
 0.00000;73.72086;0.00000;,
 -20.81668;39.07623;0.00000;,
 0.00000;73.72086;0.00000;,
 -14.71959;39.07623;-14.71959;,
 0.00000;73.72086;0.00000;,
 0.00000;39.07623;-20.81668;,
 0.00000;39.07623;0.00000;,
 0.00000;39.07623;-20.81668;,
 14.71959;39.07623;-14.71959;,
 20.81668;39.07623;0.00000;,
 14.71959;39.07623;14.71959;,
 0.00000;39.07623;20.81668;,
 -14.71959;39.07623;14.71959;,
 -20.81668;39.07623;0.00000;,
 -14.71959;39.07623;-14.71959;;
 
 56;
 4;0,1,2,3;,
 4;1,4,5,2;,
 4;4,6,7,5;,
 4;6,8,9,7;,
 4;8,10,11,9;,
 4;10,12,13,11;,
 4;12,14,15,13;,
 4;14,16,17,15;,
 3;18,1,0;,
 3;19,4,1;,
 3;20,6,4;,
 3;21,8,6;,
 3;22,10,8;,
 3;23,12,10;,
 3;24,14,12;,
 3;25,16,14;,
 3;26,3,2;,
 3;27,2,5;,
 3;28,5,7;,
 3;29,7,9;,
 3;30,9,11;,
 3;31,11,13;,
 3;32,13,15;,
 3;33,15,17;,
 3;34,35,36;,
 3;36,37,38;,
 3;38,39,40;,
 3;40,41,42;,
 3;42,43,44;,
 3;44,45,46;,
 3;46,47,48;,
 3;48,49,50;,
 3;51,52,53;,
 3;51,53,54;,
 3;51,54,55;,
 3;51,55,56;,
 3;51,56,57;,
 3;51,57,58;,
 3;51,58,59;,
 3;51,59,52;,
 3;60,61,62;,
 3;62,63,64;,
 3;64,65,66;,
 3;66,67,68;,
 3;68,69,70;,
 3;70,71,72;,
 3;72,73,74;,
 3;74,75,76;,
 3;77,78,79;,
 3;77,79,80;,
 3;77,80,81;,
 3;77,81,82;,
 3;77,82,83;,
 3;77,83,84;,
 3;77,84,85;,
 3;77,85,78;;
 
 MeshMaterialList {
  4;
  56;
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
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1;;
  Material {
   0.520800;0.326400;0.088000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.633600;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.765600;0.596000;0.486400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.586400;0.313600;0.103200;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  32;
  0.000000;1.000000;0.000000;,
  0.000000;0.000000;-1.000000;,
  0.707107;0.000000;-0.707107;,
  1.000000;0.000000;0.000000;,
  0.707107;0.000000;0.707107;,
  0.000000;0.000000;1.000000;,
  -0.707107;0.000000;0.707107;,
  -1.000000;0.000000;0.000000;,
  -0.707107;0.000000;-0.707107;,
  0.000000;-1.000000;-0.000000;,
  0.000000;0.515040;-0.857166;,
  0.606108;0.515039;-0.606108;,
  0.857166;0.515040;0.000000;,
  0.606108;0.515039;0.606108;,
  0.000000;0.515040;0.857166;,
  -0.606108;0.515039;0.606108;,
  -0.857166;0.515040;0.000000;,
  -0.606108;0.515039;-0.606108;,
  0.760491;0.567825;-0.315005;,
  0.000000;-1.000000;-0.000000;,
  -0.315005;0.567825;0.760491;,
  0.000000;0.515040;-0.857166;,
  0.606108;0.515039;-0.606108;,
  0.857166;0.515040;0.000000;,
  0.606108;0.515039;0.606108;,
  0.000000;0.515040;0.857166;,
  -0.606108;0.515039;0.606108;,
  -0.857166;0.515040;0.000000;,
  -0.606108;0.515039;-0.606108;,
  0.760491;0.567825;-0.315005;,
  0.000000;-1.000000;-0.000000;,
  -0.315005;0.567825;0.760491;;
  56;
  4;1,2,2,1;,
  4;2,3,3,2;,
  4;3,4,4,3;,
  4;4,5,5,4;,
  4;5,6,6,5;,
  4;6,7,7,6;,
  4;7,8,8,7;,
  4;8,1,1,8;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;0,0,0;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;9,9,9;,
  3;10,18,11;,
  3;11,18,12;,
  3;12,18,13;,
  3;13,20,14;,
  3;14,20,15;,
  3;15,20,16;,
  3;16,17,17;,
  3;17,17,10;,
  3;19,19,19;,
  3;19,19,19;,
  3;19,19,19;,
  3;19,19,19;,
  3;19,19,19;,
  3;19,19,19;,
  3;19,19,19;,
  3;19,19,19;,
  3;21,29,22;,
  3;22,29,23;,
  3;23,29,24;,
  3;24,31,25;,
  3;25,31,26;,
  3;26,31,27;,
  3;27,28,28;,
  3;28,28,21;,
  3;30,30,30;,
  3;30,30,30;,
  3;30,30,30;,
  3;30,30,30;,
  3;30,30,30;,
  3;30,30,30;,
  3;30,30,30;,
  3;30,30,30;;
 }
 MeshTextureCoords {
  86;
  0.000000;0.000000;,
  0.125000;0.000000;,
  0.125000;1.000000;,
  0.000000;1.000000;,
  0.250000;0.000000;,
  0.250000;1.000000;,
  0.375000;0.000000;,
  0.375000;1.000000;,
  0.500000;0.000000;,
  0.500000;1.000000;,
  0.625000;0.000000;,
  0.625000;1.000000;,
  0.750000;0.000000;,
  0.750000;1.000000;,
  0.875000;0.000000;,
  0.875000;1.000000;,
  1.000000;0.000000;,
  1.000000;1.000000;,
  0.062500;0.000000;,
  0.187500;0.000000;,
  0.312500;0.000000;,
  0.437500;0.000000;,
  0.562500;0.000000;,
  0.687500;0.000000;,
  0.812500;0.000000;,
  0.937500;0.000000;,
  0.062500;1.000000;,
  0.187500;1.000000;,
  0.312500;1.000000;,
  0.437500;1.000000;,
  0.562500;1.000000;,
  0.687500;1.000000;,
  0.812500;1.000000;,
  0.937500;1.000000;,
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;1.000000;,
  0.062500;0.000000;,
  0.125000;1.000000;,
  0.125000;0.000000;,
  0.250000;1.000000;,
  0.187500;0.000000;,
  0.375000;1.000000;,
  0.250000;0.000000;,
  0.500000;1.000000;,
  0.312500;0.000000;,
  0.625000;1.000000;,
  0.375000;0.000000;,
  0.750000;1.000000;,
  0.437500;0.000000;,
  0.875000;1.000000;,
  0.500000;0.000000;,
  1.000000;1.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}
