/*
	gasetools: a set of tools to manipulate SEGA games file formats
	Copyright (C) 2010  Loic Hoguin

	This file is part of gasetools.

	gasetools is free software: you can redistribute it and/or modify
	it under the terms of the GNU General Public License as published by
	the Free Software Foundation, either version 3 of the License, or
	(at your option) any later version.

	gasetools is distributed in the hope that it will be useful,
	but WITHOUT ANY WARRANTY; without even the implied warranty of
	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
	GNU General Public License for more details.

	You should have received a copy of the GNU General Public License
	along with gasetools.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef __GASETOOLS_NBL_H__
#define __GASETOOLS_NBL_H__

/* Filetype identifiers */

#define NBL_ID_NMLL	0x4C4C4D4E /* Low endian. */
#define NBL_ID_NMLB	0x424C4D4E /* Big endian. Currently unsupported. */
#define NBL_ID_TMLL	0x4C4C4D54 /* Unknown. */

/* Positions */

#define NBL_HEADER_IDENTIFIER					0x00
/* Unknown 0x04. */
#define NBL_HEADER_SIZE							0x08
#define NBL_HEADER_NB_CHUNKS					0x0C
#define NBL_HEADER_DATA_SIZE					0x10 /* Uncompressed. */
#define NBL_HEADER_COMPRESSED_DATA_SIZE			0x14 /* Compressed; if 0 then the file isn't compressed. */
#define NBL_HEADER_PTRS_POS						0x18
#define NBL_HEADER_KEY_SEED						0x1C
#define NBL_HEADER_TMLL_HEADER_SIZE				0x20
#define NBL_HEADER_TMLL_DATA_SIZE				0x24
#define NBL_HEADER_TMLL_COMPRESSED_DATA_SIZE	0x28
#define NBL_HEADER_TMLL_NB_CHUNKS				0x2C

#define NBL_HEADER_CHUNKS		0x30
#define NBL_TMLL_HEADER_CHUNKS	0x20

/* Positions from NBL_HEADER_CHUNKS */

#define NBL_CHUNK_SIZE				0x60
#define NBL_CHUNK_IDENTIFIER		0x00
#define NBL_CHUNK_HEADER_SIZE		0x04 /* Apparently isn't 0x60 all the time. Unsafe to use. */
#define NBL_CHUNK_CRYPTED_HEADER	0x10
#define NBL_CHUNK_CRYPTED_SIZE		0x30
/* Encrypted part */
#define NBL_CHUNK_FILENAME			0x10
#define NBL_CHUNK_FILENAME_SIZE		0x20
#define NBL_CHUNK_FILE_POS			0x30
#define NBL_CHUNK_FILE_SIZE			0x34
#define NBL_CHUNK_PTRS_INDEX		0x38
#define NBL_CHUNK_PTRS_SIZE			0x3C
/* After the encrypted part. */
#define NBL_CHUNK_A 0x40 /* NBL_ID_NXIF or empty if the chunk id is STD. If empty then all the following is empty. */
#define NBL_CHUNK_B 0x44
#define NBL_CHUNK_C 0x48
#define NBL_CHUNK_D 0x4C
#define NBL_CHUNK_E 0x50
#define NBL_CHUNK_F 0x54
#define NBL_CHUNK_G 0x58
#define NBL_CHUNK_H 0x5C

/* Padding */

#define NBL_CHUNK_PADDING_SIZE 0x800
#define NBL_CHUNK_SMALL_PADDING_SIZE 0x40

/* Identification and loading */

int nbl_is_nmll(char* pstrBuffer);
int nbl_has_tmll(char* pstrBuffer);
int nbl_get_data_pos(char* pstrBuffer);
int nbl_get_tmll_pos(char* pstrBuffer);
char* nbl_load(char* pstrFilename);

#define NBL_READ_INT(buf, pos) (*((int*)(buf + pos)))
#define NBL_READ_UINT(buf, pos) (*((unsigned int*)(buf + pos)))

/* Decryption */

#include "fakefish.h"
void nbl_decrypt_buffer(struct bf_ctx *pCtx, char* pstrBuffer, int iSize);
void nbl_decrypt_headers(struct bf_ctx *pCtx, char* pstrBuffer, int iHeaderChunksPos);

/* Decompression */

int nbl_is_compressed(char* pstrBuffer);
int nbl_decompress(char* pstrSrc, int iSrcSize, char* pstrDest, int iDestSize);

/* List and extract contents */

void nbl_list_files(char* pstrBuffer, int iHeaderChunksPos);
void nbl_extract_all(char* pstrBuffer, char* pstrData, char* pstrDestPath);

#endif /* __GASETOOLS_NBL_H__ */
