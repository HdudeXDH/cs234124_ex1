//
// Created by User on 4/16/2022.
//

#ifndef EX1_ASCIIARTTOOL_H
#define EX1_ASCIIARTTOOL_H

#endif //EX1_ASCIIARTTOOL_H

/**
 * Read File and encode it with the RLE method.
 * @param in_stream
 * @return RLEList that hold chars of the photo
 */
RLEList asciiArtRead(FILE* in_stream);

/**
 * Print the RLE encoded photo to file (unencoded).
 * @param list RLEList - The RLE list encoded photo for printing
 * @param out_stream FILE* stream object that the photo is designated to.
 * @return
 *  RLE_LIST_NULL_ARGUMENT if a NULL was sent as one of the parameters
 *  RLE_LIST_SUCCESS if successfully completed operation
 */
RLEListResult asciiArtPrint(RLEList list, FILE *out_stream);

/**
 * Print the RLE encoded photo to file (still encoded in RLE)
 * @param list RLEList - The RLE list encoded photo.
 * @param out_stream
 * @return
 *  RLE_LIST_NULL_ARGUMENT if a NULL was sent as one of the parameters
 *  RLE_LIST_SUCCESS if successfully completed operation
 */
RLEListResult asciiArtPrintEncoded(RLEList list, FILE *out_stream);