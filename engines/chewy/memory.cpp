/* ScummVM - Graphic Adventure Engine
 *
 * ScummVM is the legal property of its developers, whose names
 * are too numerous to list here. Please refer to the COPYRIGHT
 * file distributed with this source distribution.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 *
 */

#include "common/memstream.h"
#include "chewy/memory.h"
#include "chewy/globals.h"
#include "chewy/types.h"
#include "chewy/resource.h"

namespace Chewy {

Memory::Memory() {
	file = new Data();
}

Memory::~Memory() {
	delete (file);
}

TafInfo *Memory::taf_adr(const char *filename) {
	SpriteResource *res = new SpriteResource(filename);
	int32 imageCount = res->getChunkCount();
	uint32 size = res->getAllSize() + imageCount * 8 + sizeof(TafInfo);
	uint32 kgroesse = imageCount * sizeof(byte *);

	byte *tmp1 = (byte *)MALLOC(size + PALETTE_SIZE + kgroesse);
	TafInfo *tinfo = (TafInfo *)tmp1;
	tinfo->image = (byte **)(tmp1 + sizeof(TafInfo));
	tinfo->palette = tmp1 + size;
	tinfo->anzahl = imageCount;
	memcpy(tinfo->palette, res->getSpritePalette(), PALETTE_SIZE);
	byte *imgPtr = tmp1 + sizeof(TafInfo) + kgroesse;

	for (int i = 0; i < imageCount; i++) {
		tinfo->image[i] = imgPtr;
		imgPtr += res->getSpriteData(i, &tinfo->image[i], false);
	}

	tinfo->korrektur = (int16 *)(tmp1 + (size + 768l));
	memcpy(tinfo->korrektur, res->getSpriteCorrectionsTable(), imageCount * 2 * sizeof(int16));

	delete res;

	return tinfo;
}

TafSeqInfo *Memory::taf_seq_adr(int16 image_start, int16 image_anz) {
	Common::File *rs = new Common::File();
	rs->open(CH_SPZ_FILE);
	TafFileHeader header;
	TafImageHeader iheader;
	TafSeqInfo *ts_info = nullptr;
	int16 i;

	rs->seek(0, SEEK_SET);
	if (header.load(rs)) {
		int16 id = file->get_id(header.id);
		if (id == TAFDATEI) {
			if (header.korrekt > 1) {
				rs->seek((-(int)((header.count - image_start) * sizeof(uint32))), SEEK_END);
				uint32 ptr = rs->readUint32LE();

				rs->seek(ptr, SEEK_SET);
				uint32 size = 0;
				for (i = 0; i < image_anz; i++) {
					if (iheader.load(rs)) {
						size += iheader.width * iheader.height;
						rs->seek(iheader.next, SEEK_SET);

					} else {
						error("taf_seq_adr error");
					}
				}
				size += image_anz * sizeof(byte *);
				size += image_anz * sizeof(char *);
				size += ((uint32)sizeof(TafSeqInfo));
				byte *tmp1 = (byte *)MALLOC(size + image_anz * sizeof(byte *));

				ts_info = (TafSeqInfo *)tmp1;
				ts_info->anzahl = image_anz;
				ts_info->image = (byte **)(tmp1 + sizeof(TafSeqInfo));
				ts_info->korrektur = (int16 *)(tmp1 + size);
				rs->seek(ptr, SEEK_SET);
				byte *sp_ptr = tmp1 + (((uint32)sizeof(TafSeqInfo)) + (image_anz * sizeof(char *)));

				for (i = 0; i < image_anz; i++) {
					if (iheader.load(rs)) {
						ts_info->image[i] = sp_ptr;
						int16 *abmess = (int16 *)sp_ptr;
						abmess[0] = iheader.width;
						abmess[1] = iheader.height;
						sp_ptr += 4;
						size = (uint32)((uint32)iheader.height) * ((uint32)iheader.width);

						rs->seek(iheader.image, SEEK_SET);
						file->load_tafmcga(rs, iheader.komp, size, sp_ptr);
						rs->seek(iheader.next, SEEK_SET);
						sp_ptr += size;
					} else {
						error("taf_seq_adr error");
					}
				}
				rs->seek((-(int)(((header.count * 2) - image_start) * sizeof(uint32))), SEEK_END);

				if ((rs->size() - rs->pos()) < (int)image_anz * 4) {
					error("taf_seq_adr error");
				} else {
					int16 *p = ts_info->korrektur;
					for (i = 0; i < (int)image_anz * 2; ++i, ++p)
						*p = rs->readSint16LE();
				}
			} else {
				error("taf_seq_adr error");
			}
		} else {
			error("taf_seq_adr error");
		}
	} else {
		error("taf_seq_adr error");
	}

	delete rs;

	return ts_info;

	// TODO: This implementation draws sprites with wrong offsets
#if 0
	TafSeqInfo *ts_info = nullptr;
	SpriteResource *res = new SpriteResource(CH_SPZ_FILE);
	uint32 size = 0;

	for (int16 i = 0; i < image_anz; i++) {
		TAFChunk *sprite = res->getSprite(i + image_start);
		size += sprite->width * sprite->height;
		delete sprite;
	}

	size += image_anz * sizeof(byte *);
	size += image_anz * sizeof(char *);
	size += ((uint32)sizeof(TafSeqInfo));

	byte *tmp1 = (byte *)MALLOC(size + image_anz * sizeof(byte *));
	ts_info = (TafSeqInfo *)tmp1;
	ts_info->anzahl = image_anz;
	ts_info->image = (byte **)(tmp1 + sizeof(TafSeqInfo));
	ts_info->korrektur = (int16 *)(tmp1 + size);
	byte *sp_ptr = tmp1 + (((uint32)sizeof(TafSeqInfo)) + (image_anz * sizeof(char *)));

	for (int16 i = 0; i < image_anz; i++) {
		ts_info->image[i] = sp_ptr;
		sp_ptr += res->getSpriteData(i + image_start, &ts_info->image[i], false);
	}

	memcpy(ts_info->korrektur, res->getSpriteCorrectionsTable(), image_anz * 2 * sizeof(int16));

	delete res;

	return ts_info;
#endif
}

void Memory::tff_adr(const char *filename, byte **speicher) {
	uint32 size = file->size(filename, TFFDATEI);

	*speicher = (byte *)MALLOC(size);
	file->load_tff(filename, *speicher);
}

// Only called from init_load() with filename blende.rnd
byte *Memory::void_adr(const char *filename) {
	byte *ptr = nullptr;
	uint32 size = file->size(filename, 200);

	ptr = (byte *)MALLOC(size * sizeof(uint32));
	WRITE_LE_INT32(ptr, size);
	file->void_load(filename, ptr + sizeof(uint32), size);

	return ptr;
}

} // namespace Chewy
