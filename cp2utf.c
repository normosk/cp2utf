#include <stdio.h>
#include <string.h>
#include <malloc.h>

static const int utf[256] = {
  0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20,21,22,23,24,25,26,27,
  28,29,30,31,32,33,34,35,36,37,38,39,40,41,42,43,44,45,46,47,48,49,50,51,52,
  53,54,55,56,57,58,59,60,61,62,63,64,65,66,67,68,69,70,71,72,73,74,75,76,77,
  78,79,80,81,82,83,84,85,86,87,88,89,90,91,92,93,94,95,96,97,98,99,100,101,
  102,103,104,105,106,107,108,109,110,111,112,113,114,115,116,117,118,119,120,
  121,122,123,124,125,126,127,1026,1027,8218,1107,8222,8230,8224,8225,8364,
  8240,1033,8249,1034,1036,1035,1039,1106,8216,8217,8220,8221,8226,8211,8212,
  8250,8482,1113,8250,1114,1116,1115,1119,160,1038,1118,1032,164,1168,166,167,
  1025,169,1028,171,172,173,174,1031,176,177,1030,1110,1169,181,182,183,1105,
  8470,1108,187,1112,1029,1109,1111,1040,1041,1042,1043,1044,1045,1046,1047,
  1048,1049,1050,1051,1052,1053,1054,1055,1056,1057,1058,1059,1060,1061,1062,
  1063,1064,1065,1066,1067,1068,1069,1070,1071,1072,1073,1074,1075,1076,1077,
  1078,1079,1080,1081,1082,1083,1084,1085,1086,1087,1088,1089,1090,1091,1092,
  1093,1094,1095,1096,1097,1098,1099,1100,1101,1102,1103
};

int filesize(FILE *f) {
  fseek(f, 0, SEEK_END);
  int s = ftell(f);
  fseek(f, 0, SEEK_SET);
  return s;
}

int cp2utf(char* stri, char* res, const int cnt) {
  int i = 0, j = 0;
  for(; i < cnt; ++i) {
    long c = utf[(unsigned char)stri[i]];
    if(c < 0x80) {
      res[j++] = c;
    }
    else if(c < 0x800) {
      res[j++] = (c >> 6) | 0xc0;
      res[j++] = (c & 0x3f) | 0x80;
    } 
    else if(c < 0x10000) {
      res[j++] = (c >> 12) | 0xe0;
      res[j++] = (c >> 6) & (0x3f | 0x80);
      res[j++] = (c & 0x3f) | 0x80;
    }
  }
  res[j] = '\0';
  return j;
}

int main(int argc, char **argv) {
  if (argc != 3) { 
    printf("usage: %s cp1251.txt utf8.txt\n", argv[0]); 
    return 1;
  }
  FILE *f = fopen(argv[1], "r");
  if (f == NULL) {
    printf("Can't open file: %s\n", argv[1]);
    return 1;
  }
  int fs = filesize(f);
  char *i = calloc(fs, 1);
  fread(i, 1, fs, f);
  fclose(f);
  char *u = calloc(fs*6, 1);
  int ws = cp2utf(i, u, fs);
  free(i);
  FILE *o = fopen(argv[2], "w");
  fwrite(u, 1, ws, o);
  fclose(o);
  free(u);
  return 0;
}

