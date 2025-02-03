
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb_image_write.h"

#include <stdio.h>

int main(void)
{
  int width, height, channels;
  char filename[256];
  int BLOCK_SIZE;

  printf("Enter the filename for the input image(with the file extension): ");
  scanf("%255s", filename);

  char *ext = strrchr(filename, '.');
  if (ext == NULL)
  {
    printf("Invalid file extension\n");
    return 1;
  }

  unsigned char *img = stbi_load(filename, &width, &height, &channels, 0);
  if (img == NULL)
  {
    printf("Error loading image\n");
    return 1;
  }

  printf("Enter the block size (8 is a good start): ");
  scanf("%d", &BLOCK_SIZE);

  printf("Pixelating the image...\n");

  for (int y = 0; y < height; y += BLOCK_SIZE)
  {
    for (int x = 0; x < width; x += BLOCK_SIZE)
    {
      long sumR = 0, sumG = 0, sumB = 0;
      int pixelCount = 0;

      int blockEndY = (y + BLOCK_SIZE > height) ? height : y + BLOCK_SIZE;
      int blockEndX = (x + BLOCK_SIZE > width) ? width : x + BLOCK_SIZE;

      for (int j = y; j < blockEndY; j++)
      {
        for (int i = x; i < blockEndX; i++)
        {
          int index = (j * width + i) * channels;
          sumR += img[index];
          sumG += img[index + 1];
          sumB += img[index + 2];
          pixelCount++;
        }
      }

      long avgR = sumR / pixelCount;
      long avgG = sumG / pixelCount;
      long avgB = sumB / pixelCount;

      for (int j = y; j < blockEndY; j++)
      {
        for (int i = x; i < blockEndX; i++)
        {
          int index = (j * width + i) * channels;
          img[index] = avgR;
          img[index + 1] = avgG;
          img[index + 2] = avgB;
        }
      }
    }
  }

  char outputFileName[270];
  size_t length = ext - filename;
  strncpy(outputFileName, filename, length);
  outputFileName[length] = '\0';
  strcat(outputFileName, "_pixelated.jpg");

  if (!stbi_write_jpg(outputFileName, width, height, channels, img,
                      width * channels))
  {
    printf("Error saving image\n");
    stbi_image_free(img);
    return 1;
  }

  printf("Image saved as %s\n", outputFileName);

  stbi_image_free(img);
  return 0;
}
