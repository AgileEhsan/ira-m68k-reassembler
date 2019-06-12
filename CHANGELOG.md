# IRA changelog


## 2.09

### Bug fixes

- Fixed possible crash with low memory.
- Fixed CINV and CPUSH (only "LINE" operations were recognized).
- Fixed input file names with deep paths.
- Fixed negative values on 64-bit systems.
- Fixed MOVE16 (only MOVE16 (Ax)+,(Ay)+ were recognized).
- Fixed MOVEC (incorrect control register).
- Fixed MOVES (extension word were ignored).
- Fixed BFINS (swapped operands).

### New features

- Support for extended memory attributes in Amiga executables.
- Improve CPU choice on command line.
- New general documentation file (ira2.doc).
- New documentation file about config file's directives (ira_config.doc).
- New directives for config file: COMMENTS, BANNER, EQU and LABEL (see
  ira_config.doc).
- Improve error messages.
- Also support '0x' to denote hexadecimal addresses on the command line.
- New option -AW enforces 8-digit address output, when printing address
  and data in the comment field.
- Support for 68060 instructions (except FPU).
- Support for MMU instructions.


## 2.08

## Bug fixes

- Fixed problems with printf output formats for 64-bit compilers.
- $083c is illegal and was erroneously disassembled to BTST #n,CCR.
- Fixed CMP2, CHK2, CAS, CAS2.

## New features

- Do not overwrite an existing config file, when -preproc is specified.
- Make it work on Mac OSX 64-bit systems.


## 2.07

## Bug fixes

- A lot more fixes to make IRA clean for 64-bit compilers. Seems to work
  much better now.
- A base address of 0 should be allowed with binary files.

## New features

- Allow comments ';' and empty lines in the config file.


## 2.06

## Bug fixes

- Make IRA compile and work on 64-bit systems (using a 64-bit compiler).
- An empty register list is now written as #0 instead of (NOREG!). This
  makes it assemble (with vasm at least).
- Fixed label-generation for references into the middle of a data relocation
  (e.g. use "label+2" instead of making a new label, which caused trouble).
- Put both sides of the subtract operation into parentheses, when generating
  code for a jump table (to avoid problems with "label1-label2+2").
- Fixed some possible crashes.


## 2.05

## Bug fixes

- Fixed a possible crash when a config file defines a SYMBOL where the
  assigned value is not within the reassembled address range.
- Fixed a crash on encountering relocations at an odd address. This cannot
  easily be supported at the moment, so IRA will just quit when it happens.
- Reverted some stupid changes of the last release. Always prefer a label
  from the referring section in case both have the same address.

## New features

- Config file directive NOPTRS. Syntax is like PTRS, but it will prevent IRA
  from taking any address in this region as a program pointer (which would
  generate a label). Only works with binary input files!


## 2.04

## Bug fixes

- Fixed automatic ROM tag detection routine. Handling of absolute 32-bit
  function tables did not work when a relative 16-bit one was found before.
- Function names from ROM tag function tables were sometimes missing, when
  the input file is a raw binary.
- Fixed SECSTRT_n symbol recognition with BASEREG directive and small data
  addressing modes.
- Do not forget .W extension for word-sized LINK, MOVEA and MOVEP.
- Recognize BTST Dn,#x.

## New features

- Report about misplaced relocations in code (usually caused by a bad PTRS
  directive).
- Print a warning when a symbol from HUNK_SYMBOL is not inside the current
  section limits, and ignore this symbol.
- Base-relative symbols outside the small-data section's bounds are
  referenced via SECTSTRT_n and a warning is printed (because the
  instruction could be data, or the base register contains something
  else at this point).


## 2.03

## Bug fixes

- Make sure that CODE areas, when read from a config file, are split at
  section boundaries. Otherwise IRA cannot detect the start of a new section
  during source generation.
- BASEADR didn't work correctly for raw binary files.

## New features

- Config file directive TEXT. To define a region in data as printable text.
  This overrides the automatic text recognition.
  Syntax: `TEXT $<start> - $<end>`.
- Config file directives JMPB, JMPW and JMPL for generating jump-tables
  (or other offset-tables used to reference a program address).
  Syntax: `JMP<s> $<start> - $<end> [@ $<base>]`. `<s>` may be B, W or L and
  defines the width of the table entries (8, 16, 32 bit). The `<base>` is
  optional and same as `<start>`, when missing. It defines the base address
  where the table-offsets are added to.
- Option -BITRANGE, which was introduced in V2.00, was replaced by
  `-COMPAT=<flags>` to allow multiple compatibility flags. Currently known:
  * `b` : Recognize immediate values of 8-15 for bit-instructions accessing
          memory (former -BITRANGE option).
  * `i` : Recognize immediate byte addressing modes with an MSB of 0xff. Some
          assemblers generated 0xffff instead of 0x00ff for #-1.


## 2.02

## Bug fixes

- Fixed NBAS config directive. Only the entry with the highest address worked.
- File buffers for binary and config file name were too small. Extended from
  32 to 128 bytes (as source and target file name buffer already were).
- An immediate width-field in bitfield instructions showed up as '0' when
  it should have been '32'.
- Multiple MACHINE directives in the config file confused IRA.
- Fixed DIVxL.L, DIVx.L and MULx.L.
- A new label is defined for the base-address, used in BASEREG. Using a
  SECSTRT_n-offset is unreliable when optimizing.

## New features

- New/improved BASEREG handling. The base-relative section specifier (BASESEC)
  has disappeared. It is sufficient to define base-relative addressing by
  a base-register and a base-address (e.g. -BASEREG=4,$12340).
- New config file directive BASEOFF (also as optional third argument in the
  -BASEREG option) defines an additional offset on the base-label (usually
  32766).
- (d8,An,Rn) addressing modes may also be used for base-relative addressing.
- Always create a SECSTRT_n symbol when starting a new section, even when
  this address is not referenced.
- After some modifications, Makefile.win32 was reported to work with VC6.


## 2.01

## Bug fixes

- Call fopen() in binary-mode where appropriate, for Windows support.

## New features

- `"` in strings are now encoded as `""` by default. To get the PhxAss-specific
  (and vasm-supported) `\"` encoding, use the new -ESCCODES option.
- The string length is limited to 60 bytes, before a new line is started.


## 2.00

## Bug fixes

- ENTRY and OFFSET directives from the config file have been ignored
- The BASEADR for base-relative addressing is always a real address now,
  which is loaded to the base address register, and not an offset. This
  caused some confusion when the binary's OFFSET is not 0.
- MACHINE directive in the config file was emitted multiple times.
- Fixed -M option to specifiy the CPU type.
- Fixed parsing of RELOC32SHORT hunks.
- Better support for raw binary input.
- Fixed illegal access when making a label from a ROMtag name, and another
  one when running with -preproc over code which is not ended by an RTS or
  similar.

## New features

- Use BASEREG instead of the PhxAss-specific NEAR directive for base-relative
  addressing modes. There are more assemblers (including vasm 1.4 and PhxAss)
  supporting it.
- Option -BASEABS. When specified, a label in base-relative addressing mode
  is written as an absolute label, without the base register name (as with
  IRA V1.05). The default behaviour now is to write base-relative references
  as "(label,An)".
- Option -BITRANGE. Also recognizes bit-test/manipulation instructions as
  valid when accessing bits 8-15 in memory (e.g. btst #14,DMACONR).
- Config file directive PTRS. Syntax: `PTRS <adr1> [<adr2>]`. It defines a
  single address or a range of addresses which contain 32-bit pointers to
  addresses from the reassembled binary. This directive is especially useful
  in data sections of a raw binary, which has no relocation information.
  IRA will create a label for all the pointers in that range.
- Config file directive NBAS. Syntax: `NBAS <adr1> <adr2>`. Defines that the
  area between `<adr1>` and `<adr2>` should not use base-relative addressing
  modes (e.g. because the base register is used in another way here).
  IRA will start this area with an "ENDB An", to disable basereg-mode, and
  reenables base-relative mode with a BASEREG directive afterwards.
- I made sure that there is always a valid size extension as instruction
  suffix and in indirect addressing modes. ".W" was mostly missing before.
- Output an ORG directive instead of SECTION when the -binary option had
  been specified.
- Switched from PhxAss specific MACHINE/FPU/PMMU directives to MC680x0/
  MC68881/MC68851, which is understood by more assemblers (e.g. vasm,
  phxass, barfly, snma, etc.).


## 1.05beta

- some bugs removed
- new command-line option added: -ENTRY (not much tested)
- HUNK_DREL32 (V37+) and HUNK_RELOC32SHORT (V39+) added.


## 1.04

- intern version for friends, eg special TJSeka version...


## 1.03beta

- Text in DATA hunks is now recognised.
- Much better -TEXT=1 option.
- Removed the -TEXT=2 option.
- A stand-alone postprocessor for symbolizing library calls is added.
  See irapost.doc.
- A new pass (PASS 0) is added for finding data in CODE hunks. It is
  switched on by the new -PREPROC option. See above for more.
- Symbol hunks are now processed and symbols inserted into the source.
- Resident structures are searched for and extra symbols set. That means
  .library and .device files are much better deassembled.
- The new command-line option -CONFIG is added. Coming up with this is
  a an edible .cnf file. See above.
- Much less memory intensive, especially when having large data parts.
- The -CACHE option no longer exists due to using buffered i/o now.
- Some (major) bugs with 020+ code fixed.
- Sometimes no labels were printed - fixed.
- Shortened the help-text. Now it fits on a 25 lines console window.


## 1.02

- CHIP and FAST hunks are now recognised.
- Addressing mode D8(PC,An) is now used with a label.
- Removed a never-ending-loop problem that came up with a special
  program protection (a hack in the hunk structure).
- Removed the multiple-label problem.
- The MACHINE directive is no longer used in 68000 programs.
- Some of the command-line options changed.


## 1.01

- First released version.
