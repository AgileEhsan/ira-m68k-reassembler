/*
 * ira_2.h
 *
 *  Created on: 8 may 2015
 *      Author   : Nicolas Bastien
 *      Project  : IRA  -  680x0 Interactive ReAssembler
 *      Part     : ira_2.h
 *      Purpose  : Headers for subroutines for IRA
 *      Copyright: (C)2014-2016 Nicolas Bastien
 */

#ifndef IRA_2_H_
#define IRA_2_H_

uint32_t CheckEquate(ira_t *, uint32_t, uint32_t);
uint32_t FileLength(uint8_t *);
char *GetEquate(int, uint32_t);
void GetExtName(uint32_t);
void GetLabel(int32_t, uint16_t);
void *GetNewPtrBuffer(void *, uint32_t);
void *GetNewStructBuffer(void *, uint32_t, uint32_t);
void *GetNewVarBuffer(void *, uint32_t);
int GetSymbol(uint32_t);
void GetXref(uint32_t);
void InsertLabel(int32_t);
void InsertReloc(uint32_t, uint32_t, int32_t, uint32_t);
void InsertXref(uint32_t);
void SearchRomTag(ira_t *);
void WriteTarget(void *, uint32_t);

#endif /* IRA_2_H_ */
