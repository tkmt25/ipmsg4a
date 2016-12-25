package jp.tkmt25.androidtest.util;

import android.graphics.Bitmap;

public class ImageConverter {
	
	// �O���[�X�P�[��RAW�摜����Bitmap������
	public static Bitmap createGrayBitmapFromRaw(int width, int height, byte[] raw){
		int[] pixels = new int[width*height];
		
		for (int i = 0; i < pixels.length; i++) {
			int v = raw[i] & 0xFF;
			pixels[i] = 0xff000000 | (v << 16) | (v << 8) | v;
		}
		
		return Bitmap.createBitmap(pixels, width, height, Bitmap.Config.ARGB_8888);
	}
	
	// ���m�N��RAW�摜(1�o�C�g���E)����Bitmap������
	public static Bitmap createMonoBitmapFromRaw(int width, int height, byte[] raw){
		byte[] grays = new byte[width*height];
		
		// �O���[�X�P�[���ɕϊ�
		int offset = 0;
		for (int i = 0; i < height; i++, offset++) {
			for (int j = 0; j < width; j++) {
				if ((raw[offset+(j/8)] & (0x80 >> (j%8))) > 0) {
					grays[(i*width)+j] = (byte)0x00;
				}else{
					grays[(i*width)+j] = (byte)0xFF;
				}
				if (j%8 == 0 && j != 0){
					offset++;
				}
			}
		}
		
		return createGrayBitmapFromRaw(width, height, grays);
	}
	
	// ���m�N��RAW��DWORD(4�o�C�g)�ȉ摜����Bitmap������
	public static Bitmap createMonoBitmapFromRawDW(int width, int height, byte[] rawDW){
		//int paddingWidth = (width+3) & ~3;
		int noPaddingLineSize = ((width+7) & ~7) / 8;
		int paddingLineSize = ((width+31) / 32) * 4; // 1�s���̃o�C�g��
		byte[] be = new byte[rawDW.length];
		byte[] mono = new byte[noPaddingLineSize*height];
		
		// �G���f�B�A���ϊ�
		for (int i = 0; i < be.length; i+=4) {
			be[i]   = rawDW[i+3];
			be[i+1] = rawDW[i+2];
			be[i+2] = rawDW[i+1];
			be[i+3] = rawDW[i];
		}
		
		
		// �p�f�B���O��؂�l�߂�
		int offsetNoPad = 0;
		int offsetPad = 0;
		for (int i = 0; i < height; i++) {
			for (int j = 0; j < width; j++) {
				mono[offsetNoPad+(j/8)] |= (be[offsetPad+(j/8)] & (0x80 >> (j%8)));
			}
			offsetNoPad += noPaddingLineSize;
			offsetPad   += paddingLineSize;
		}
		
		return createMonoBitmapFromRaw(width, height, mono);
	}
}
