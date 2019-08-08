// Copies a BMP file

#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char *argv[])
{
  // ensure proper usage
  if (argc != 4)
  {
    fprintf(stderr, "Usage: resize n infile outfile\n");
    return 1;
  }

  // remember size multiplier
  int n = atoi(argv[1]);

  // remember filenames
  char *infile = argv[2];
  char *outfile = argv[3];

  // open input file
  FILE *inptr = fopen(infile, "r");
  if (inptr == NULL)
  {
    fprintf(stderr, "Could not open %s.\n", infile);
    return 2;
  }

  // open output file
  FILE *outptr = fopen(outfile, "w");
  if (outptr == NULL)
  {
    fclose(inptr);
    fprintf(stderr, "Could not create %s.\n", outfile);
    return 3;
  }

  // read infile's BITMAPFILEHEADER
  BITMAPFILEHEADER bf;
  fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

  // read infile's BITMAPINFOHEADER
  BITMAPINFOHEADER bi;
  fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

  // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
  if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
      bi.biBitCount != 24 || bi.biCompression != 0)
  {
    fclose(outptr);
    fclose(inptr);
    fprintf(stderr, "Unsupported file format.\n");
    return 4;
  }

  //code starts to change after this line

  // assign vars to width/height
  int widthOld = bi.biWidth;
  int heightOld = bi.biHeight;
  int widthNew = widthOld * n;
  int heightNew = heightOld * n;

  // figure out padding if needed
  int inPadding = (4 - (widthOld * sizeof(RGBTRIPLE)) % 4) % 4;
  int outPadding = (4 - (widthNew * sizeof(RGBTRIPLE)) % 4) % 4;

  // re assign headers
  bi.biHeight = heightNew;
  bi.biWidth = widthNew;
  bi.biSizeImage = ((sizeof(RGBTRIPLE) * widthNew) + outPadding) * abs(heightNew);
  bf.bfSize = bi.biSizeImage + sizeof(BITMAPFILEHEADER) + sizeof(BITMAPINFOHEADER);

  // write outfile's BITMAPFILEHEADER
  fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

  // write outfile's BITMAPINFOHEADER
  fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

  // assign memory
  RGBTRIPLE scanline[widthNew * sizeof(RGBTRIPLE)];

  // iterate over infile's scanlines
  for (int i = 0, biHeight = abs(heightOld); i < biHeight; i++)
  {
    // iterate over pixels in a scanline
    for (int j = 0; j < widthOld; j++)
    {
      // temp RGB storage
      RGBTRIPLE triple;

      // read RGB triple from infile
      fread(&triple, sizeof(RGBTRIPLE), 1, inptr);

      // create a new scanline in a temporary array
      for (int k = 0; k < n; k++)
      {
        scanline[(j * n) + k] = triple;
      }
    }

    // skip padding
    fseek(inptr, inPadding, SEEK_CUR);

    // loop n times
    for (int j = 0; j < n; j++)
    {
      // write a new scanline once
      fwrite(scanline, sizeof(RGBTRIPLE), widthNew, outptr);

      // write new padding
      for (int k = 0; k < outPadding; k++)
      {
        fputc(0x00, outptr);
      }
    }
  }

  // close infile
  fclose(inptr);

  // close outfile
  fclose(outptr);

  // finish return 0
  return 0;
}