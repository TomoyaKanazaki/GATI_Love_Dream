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
 32;
 13.91025;2.64087;2.80830;,
 15.40248;1.02360;2.80830;,
 15.40248;1.02360;-2.60061;,
 13.91025;2.64087;-2.60061;,
 -0.23085;2.64087;2.80830;,
 -0.23085;2.64087;-2.60061;,
 -0.76269;1.02360;-2.60061;,
 -0.76269;1.02360;2.80830;,
 13.91025;-5.63745;2.80830;,
 -0.23085;-5.63745;2.80830;,
 -0.23085;-5.63745;-2.60061;,
 13.91025;-5.63745;-2.60061;,
 13.91025;1.02360;-4.18578;,
 -0.23085;1.02360;-4.18578;,
 -0.23085;1.93479;-3.55563;,
 13.91025;1.93479;-3.55563;,
 -0.23085;1.02360;4.36833;,
 13.91025;1.02360;4.36833;,
 13.91025;1.93479;3.55563;,
 -0.23085;1.93479;3.55563;,
 -0.23085;-5.01897;3.55563;,
 13.91025;-5.01897;3.55563;,
 -0.23085;-5.01897;-3.55563;,
 13.91025;-5.01897;-3.55563;,
 13.91025;-4.25769;4.36833;,
 15.40248;-4.25769;2.80830;,
 15.40248;-4.25769;-2.60061;,
 13.91025;-4.25769;-4.18578;,
 -0.23085;-4.25769;-4.18578;,
 -0.76269;-4.25769;-2.60061;,
 -0.76269;-4.25769;2.80830;,
 -0.23085;-4.25769;4.36833;;
 
 30;
 4;0,1,2,3;,
 4;4,0,3,5;,
 4;6,7,4,5;,
 4;8,9,10,11;,
 4;12,13,14,15;,
 4;16,17,18,19;,
 4;20,9,8,21;,
 4;19,4,7,16;,
 4;18,0,4,19;,
 4;17,1,0,18;,
 4;3,2,12,15;,
 4;5,3,15,14;,
 4;13,6,5,14;,
 4;11,10,22,23;,
 4;24,25,1,17;,
 4;2,1,25,26;,
 4;12,2,26,27;,
 4;27,28,13,12;,
 4;28,29,6,13;,
 4;29,30,7,6;,
 4;16,7,30,31;,
 4;31,24,17,16;,
 4;21,8,25,24;,
 4;26,25,8,11;,
 4;27,26,11,23;,
 4;23,22,28,27;,
 4;10,29,28,22;,
 4;9,30,29,10;,
 4;31,30,9,20;,
 4;20,21,24,31;;
 
 MeshMaterialList {
  1;
  30;
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
   0.800000;0.800000;0.800000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
   TextureFilename {
    "data\\TEXTURE\\UV\\kids_girl_UV.png";
   }
  }
 }
 MeshNormals {
  44;
  0.202276;-0.734950;0.647250;,
  0.222121;-0.728778;-0.647723;,
  0.216418;0.680357;0.700198;,
  0.236497;0.676126;-0.697799;,
  0.000000;0.696889;0.717179;,
  0.000000;0.695848;-0.718189;,
  0.000000;-0.750460;0.660916;,
  0.000000;-0.747154;-0.664652;,
  0.353884;-0.875073;0.330171;,
  0.000000;-0.940849;0.338826;,
  0.000000;0.929216;0.369538;,
  0.388509;0.848458;0.359416;,
  0.365323;-0.882433;-0.296395;,
  0.399182;0.857921;-0.323459;,
  0.000000;0.949762;-0.312972;,
  0.000000;-0.958999;-0.283408;,
  0.382387;0.346390;0.856618;,
  0.868495;0.346370;0.354605;,
  0.876913;0.336494;-0.343214;,
  0.394938;0.309566;-0.864982;,
  0.000000;0.297929;-0.954588;,
  -0.977813;0.146332;-0.149896;,
  -0.975274;0.153846;0.158657;,
  0.000000;0.356168;0.934422;,
  0.376626;-0.387311;0.841512;,
  0.853357;-0.384841;0.351679;,
  0.862227;-0.374097;-0.341492;,
  0.388790;-0.349868;-0.852312;,
  0.000000;-0.338871;-0.940833;,
  -0.973906;-0.170038;-0.150314;,
  -0.970965;-0.178769;0.158958;,
  -0.934223;-0.170099;0.313519;,
  -0.940881;0.303708;0.150016;,
  -0.947702;0.288982;-0.135462;,
  -0.910486;0.288141;0.296632;,
  -0.938522;0.145626;0.313000;,
  -0.946181;0.131217;-0.295844;,
  -0.927537;0.260109;-0.268363;,
  -0.942645;-0.153366;-0.296479;,
  0.000000;-0.397717;0.917508;,
  -0.932648;-0.334518;-0.135153;,
  -0.914587;-0.303049;-0.267752;,
  -0.924251;-0.351392;0.149281;,
  -0.894687;-0.335237;0.295213;;
  30;
  4;11,17,18,13;,
  4;10,11,13,14;,
  4;21,22,32,33;,
  4;8,9,15,12;,
  4;19,20,5,3;,
  4;23,16,2,4;,
  4;6,9,8,0;,
  4;34,32,22,35;,
  4;2,11,10,4;,
  4;16,17,11,2;,
  4;13,18,19,3;,
  4;14,13,3,5;,
  4;36,21,33,37;,
  4;12,15,7,1;,
  4;24,25,17,16;,
  4;18,17,25,26;,
  4;19,18,26,27;,
  4;27,28,20,19;,
  4;38,29,21,36;,
  4;29,30,22,21;,
  4;35,22,30,31;,
  4;39,24,16,23;,
  4;0,8,25,24;,
  4;26,25,8,12;,
  4;27,26,12,1;,
  4;1,7,28,27;,
  4;40,29,38,41;,
  4;42,30,29,40;,
  4;31,30,42,43;,
  4;6,0,24,39;;
 }
 MeshTextureCoords {
  32;
  0.210479;0.831079;,
  0.210479;0.859342;,
  0.301955;0.859342;,
  0.301955;0.831079;,
  0.210479;0.831079;,
  0.301955;0.831079;,
  0.301955;0.859342;,
  0.210479;0.859342;,
  0.210479;0.975748;,
  0.210479;0.975748;,
  0.301955;0.975748;,
  0.301955;0.975748;,
  0.328764;0.859342;,
  0.328764;0.859342;,
  0.318107;0.843419;,
  0.318107;0.843419;,
  0.184095;0.859342;,
  0.184095;0.859342;,
  0.197839;0.843419;,
  0.197839;0.843419;,
  0.197839;0.964940;,
  0.197839;0.964940;,
  0.318107;0.964940;,
  0.318107;0.964940;,
  0.184095;0.951636;,
  0.210479;0.951636;,
  0.301955;0.951636;,
  0.328764;0.951636;,
  0.328764;0.951636;,
  0.301955;0.951636;,
  0.210479;0.951636;,
  0.184095;0.951636;;
 }
}
