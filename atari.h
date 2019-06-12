/*
 * atari.h
 *
 *  Created on: 2 may 2015
 *      Author   : Nicolas Bastien
 *      Project  : IRA  -  680x0 Interactive ReAssembler
 *      Part     : atari.h
 *      Purpose  : Atari's executable file definitions
 *      Copyright: (C)2015-2016 Nicolas Bastien
 */

#ifndef ATARI_H_
#define ATARI_H_

/* Atari's magic */
#define ATARI_MAGIC 0x601A

typedef struct {
    int16_t ph_branch; /* Branch to start of the program  */
                       /* (must be 0x601a!)               */

    int32_t ph_tlen;     /* Length of the TEXT segment      */
    int32_t ph_dlen;     /* Length of the DATA segment      */
    int32_t ph_blen;     /* Length of the BSS segment       */
    int32_t ph_slen;     /* Length of the symbol table      */
    int32_t ph_res1;     /* Reserved, should be 0;          */
                         /* Required by PureC               */
    int32_t ph_prgflags; /* Program flags                   */
    int16_t ph_absflag;  /* 0 = Relocation info present     */
} atari_header_t;

void ReadAtariExecutable(ira_t *);

#endif /* ATARI_H_ */
