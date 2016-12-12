#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#define IS_RANGE(x, from, to) ((x >= from) && (x <= to))
#define F00_19(B,C,D) ((B & C) | ((~B) & D))
#define F20_39(B,C,D) (B ^ C ^ D)
#define F40_59(B,C,D) ((B & C) | (B & D) | (C & D))
#define F60_79(B,C,D) (B ^ C ^ D)

static unsigned int _rol32(unsigned int d, int shift)
{
  return ((d << shift) | (d >> (32 - shift)));
}

void sha1_hash(unsigned char *data, unsigned int datalen, unsigned char *digest)
{
  int i, t;
  unsigned int paddinglen = (((datalen + 9) + 63) & ~63); // 512bit境界に拡張.付加データ(9バイト)が収まらない場合も拡張
  int numOfBlocks = paddinglen / 64;
  unsigned char block[64];

  // 付加データを作成
  /// 末尾に0x80を付加
  //paddingdata[datalen] = 0x80;
  /// 末尾に元メッセージのビット数を付加(8バイト)
  unsigned long long datalenBits = datalen * 8;

  const unsigned int K[] = {
    0x5A827999,    //  0-19
    0x6ED9EBA1,    // 20-39
    0x8F1BBCDC,    // 40-59
    0xCA62C1D6     // 60-79
  };

  unsigned int A, B, C, D, E;
  unsigned int H[5];
  unsigned int W[80];
  unsigned int temp;
  H[0] = 0x67452301;
  H[1] = 0xEFCDAB89;
  H[2] = 0x98BADCFE;
  H[3] = 0x10325476;
  H[4] = 0xC3D2E1F0;
  memset(W, 0x00, sizeof(W));

  bool isTerminated = false;
  printf("datalen = %d\n", datalen);
  printf("numOfBlocks = %d\n", numOfBlocks);
  for (i = 0; i < numOfBlocks; i++) {
    int dataIndex = i*64;
    memset(block, 0x00, sizeof(block));

    if (i == (numOfBlocks-1)) {
      memcpy(block, &data[dataIndex], isTerminated ? 0 : datalen%64);
      unsigned long long datalenBits = datalen * 8;
      int j = sizeof(block) - 8;

      block[j]   += (datalenBits >> 56) & 0xFF;
      block[j+1] += (datalenBits >> 48) & 0xFF;
      block[j+2] += (datalenBits >> 32) & 0xFF;
      block[j+3] += (datalenBits >> 24) & 0xFF;
      block[j+4] += (datalenBits >> 16) & 0xFF;
      block[j+6] += (datalenBits >>  8) & 0xFF;
      block[j+7] += (datalenBits      ) & 0xFF;
    }else{
      memcpy(block, &data[dataIndex], sizeof(block));
    }

    if ( IS_RANGE(datalen, dataIndex, dataIndex+63) ) {
      block[datalen%64] = 0x80;
      isTerminated = true;
    }

    for (int k = 0; k < 64; k+=16) {
      printf("%08X : ", k);
      for (int l = k; l < k+16; l++) {
	printf("%02X  ", block[l]);
      }
      printf("\n");
    }

    // 1-a
    for (t = 0; t < 16; t++) {
      W[t]  = block[t*4]   << 24;
      W[t] |= block[t*4+1] << 16;
      W[t] |= block[t*4+2] <<  8;
      W[t] |= block[t*4+3];
    }

    // 1-b
    for (t = 16; t < 80; t++) {
      W[t] = _rol32(W[t-3] ^ W[t-8] ^ W[t-14] ^ W[t-16], 1);
    }

    // 1-c
    A = H[0]; B = H[1]; C = H[2]; D = H[3]; E = H[4];

    // 1-d
    for (t = 0; t < 80; t++) {
      temp = _rol32(A, 5);
      if ( IS_RANGE(t, 0, 19) ) {
	temp += F00_19(B, C, D) + E + W[t] + K[0];
      }
      else if ( IS_RANGE(t, 20, 39) ) {
	temp += F20_39(B, C, D) + E + W[t] + K[1];
      }
      else if ( IS_RANGE(t, 40, 59) ) {
	temp += F40_59(B, C, D) + E + W[t] + K[2];
      }
      else if ( IS_RANGE(t, 60, 79) ) {
	temp += F60_79(B, C, D) + E + W[t] + K[3];
      }
      E = D; D = C; C = _rol32(B, 30);
      B = A; A = temp;
    }
    // 1-e
    H[0] += A; H[1] += B; H[2] += C; H[3] += D; H[4] += E;
  }
  // 4
  for (i = 0; i < 5; i++) {
    digest[4*i]   = (H[i] >> 24) & 0xFF;
    digest[4*i+1] = (H[i] >> 16) & 0xFF;
    digest[4*i+2] = (H[i] >>  8) & 0xFF;
    digest[4*i+3] = (H[i])       & 0xFF;
  }
}


int main(int argc, char **argv)
{
  unsigned char digest[20];
  memset(digest, 0x00, sizeof(digest));

  sha1_hash((unsigned char *)argv[1], strlen(argv[1]), digest);

  for (int i = 0; i < sizeof(digest); i++) {
    printf("%02x", digest[i]);
  }
  printf("\n");
  
  return 0;
}
