# IRA: 680x0 Interactive ReAssembler

IRA is a CLI _ReAssembler_ which translates any 68xxxx machine code executable or
binary file into an assembler sourcecode that might immediately be translated
back by an assembler.

                      ________________
                     /___/_________/_/\----- - -  -   -   -
                    /   /         /  \ \
                   /   /  ____   /    \ \
                  /   /  / / /  /  /\  \ \----- - -  -   -   -
                 /   /  / / /  /  / /\  \ \
                 \   \  \ \/  /  / /  \  \ \
                  \   \  \/  /  /  ¯¯¯¯\  \ \----- - -  -  -   -
                   \   \     \  ¯¯¯¯¯¯¯¯   \ \
                    \   \     \    ______   \ \ :
                    /   /  /\  \   \ \  :\   \ \|/--- - -  -  -   -
                   /   /  / /\  \   \ \ ° \   \ *--
                  /   /  / /  \  \   \/    \   \|\
                  ¯¯¯¯¯¯¯¯¯    ¯¯¯¯¯¯¯      ¯¯¯¯:



## Usage

    $ ./ira [OPTIONS] <SOURCE> [TARGET]


* Refer to [ira.doc](ira.doc) for the original IRA V1.xx documentation.
* Refer to [ira2.doc](ira2.doc) for IRA V2.xx documentation.
* Refer to [ira_config.doc](ira_config.doc) for a description of config directives.

### Example

Using the following commands to reassemble AmigaBASIC and to assemble an
identical binary with `vasm`. The config file was manually adjusted to reflect
all valid code regions (create a config file with `-preproc` first), then
duplicated as `NewAmigaBASIC.cnf`. The diff test reports no differences!

    $ ira -a -compat=bi -config -keepzh AmigaBASIC
    $ vasmm68k_mot -no-opt -Fhunkexe -nosym -o NewAmigaBASIC AmigaBASIC.asm
    $ ira -a -compat=bi -config -keepzh NewAmigaBASIC
    $ diff -s AmigaBASIC.asm NewAmigaBASIC.asm

The option `-compat=bi` is needed to allow bad btst instructions which access a
bit number > 7 in a byte (b) and to recognize immediate byte addressing modes
with an MSB of 0xff (i), which both appear frequently in the program. The
`-keepzh` option preserves empty sections, so that the number of sections stays
the same as before.

### Command-line args (default values are in brackets)

```
-M68xxx (-M68000)
        This specifies the type of processor or coprocessor for which the
        program should be reassembled. This doesn't have anything to do with
        the machine you're running IRA on.
        Most programs are written for 68000 CPUs.
        If anything other than -M68000 is specified, a MACHINE directive
        in the .ASM file is created. This works fine with PhxAss and vasm
        assemblers. For any other assembler this directive possibly has to be
        changed.

        Values accepted for xxx can be:

        - processor
          000,010,020,030,040,060
        - coprocessor
          851,881,882

-BINARY (off)
        IRA automatically recognises if the sourcefile is an executable,
        an object file or any other (binary). It may happen that some
        kind of binary data is recognised as an executable. To avoid this
        make use of the -BINARY option.

-A      (off)
        This option makes IRA append the address and data of an instruction
        to every line. That is pretty useful to me. E.g. when code and data
        is mixed, you can manually delete some instructions to replace them
        by DC.x directives.

-AW (off)
        Same as -A, but enforce 8-digit addresses.

-INFO   (off)
        Use this option to get some information about the hunk structure of
        your sourcefile.

-OFFSET=<OFFSET> (-OFFSET=0)
        When the sourcefile is relocated by IRA the offset value is added to
        the relocation. Why should I do that ?
        If you want to run an executable at a specific location in memory
        you specify the address of that location with the -OFFSET option
        in combination with the -KEEPBIN option. After running IRA you can
        load the .BIN file to the specific location and execute it. You just
        have to know what you're doing (e.g. contents of registers and so on).
        The second, more useful application is to write a part of memory to a
        file, then create a .ASM file with the -OFFSET option. You have to
        take the address of the memory location as offset. E.g. you can create
        your own kickfile with your own modifications (is it legal ?), of
        course some additional work on the .ASM file has to be done.
        OFFSET can be decimal or hexadecimal (e.g. -OFFSET=$4FF0).

-TEXT=1 (off)
        Since version 1.03 there is only one method for finding text left. The
        whole code and data sections are searched for text which is printed
        out to <stdout>. It may happen that some stupid text lines show up, so
        you have to decide yourself about every line to include into the .ASM
        file.

-KEEPZH (off)
        There are files that have hunks with a length of zero. By default
        these hunks don't appear in the .ASM file. If you want them preserved
        just use this option. There are executables where you have to use
        this option, because they work with their own SEGMENT structure.

-KEEPBIN (off)
        Before the first pass, an executable is relocated by IRA and written
        to a .BIN file. Normally, this file is deleted at some point, but if
        you want to keep it for some purpose, use the -KEEPBIN option.
        E.g. for a <type >x.hex x.bin opt h>.

-OLDSTYLE (depends on the -M68xxx option)
        This option forces IRA to use the old Motorola syntax like D16(PC)
        instead of (D16,PC). By default this option is used for 68000 and
        68010 processors.

-NEWSTYLE (depends on the -M68xxx option)
        This option forces IRA to use the new Motorola syntax like (D16,PC)
        instead of D16(PC). By default this option is used for 68020, 68030,
        68040 and 68060 processors.

-ESCCODES (off)
        Use escape character '\\' in strings.

-COMPAT=x (off)
        Various compatibility flags.

        b : Recognize immediate values of 8-15 for bit-instructions accessing
            memory (former -BITRANGE option).
        i : Recognize immediate byte addressing modes with an MSB of 0xff.
            Some assemblers generated 0xffff instead of 0x00ff for #-1.

-SPLITFILE (off)
        With this option the .ASM file is split up. Every section is put into
        its own file. One 'main' file is created to include these files via
        INCLUDE directives. What is it for ? I don't know. I was asked for
        this option.

-CONFIG (off)
        First, you can control the IRA settings with this option. That means
        you can specify the parameters that are otherways controlled via the
        command-line options. Second, you can specify addresses where to find
        code. This is useful for addresses where the -PREPROC option oversees
        code (for whatever reason). Third, you can specify symbols that are
        inserted instead using the 'LAB_xxxx' type.

        In combination with the -PREPROC option a new .cnf file is created.
        All the code areas found by PASS 0 are then written to this .cnf file.
        In addition, most of the command-line options are included, too.
        So, for the next calling of IRA you won't need to specify all of the
        command-line options you used to.

        If a .cnf file exists, a possible new one does not overwrite the old
        one. The name of the new one just get a '1' appended to its name.
        Look out for that.

        See ira_config.doc for details.

        Try the -CONFIG option out in combination with the -PREPROC option.
        IRA will create a .cnf file that you can look at for better
        understanding.

-PREPROC (off)
        This option will turn on PASS 0. That is to find data in code sections
        and even code in data sections (e.g some old compilers put their
        jumptables into data sections). Found data is checked for text.
        This option normally works very fine for compiled programs. But there
        may be problems like these:

        - parts of code may be seen as data. This comes for
          o code that is jumped to by (An), D16(An) or D8(PC,An)
            (jumptables, pointers to code, ...).
          o interrupt code that is only referenced by pointer (installation).
          o code that is never used.

        - parts of data may be seen as code. This comes for
          o crypted or crunched code.

-ENTRY=<OFFSET> (-ENTRY=0)
        If you know, that a file has data at the beginning (eg. bootblocks),
        you specify the (relative) adress where IRA should begin with
        code-scanning. For bootblocks: -ENTRY=$C .

-BASEREG[=n[,adr,sec]]
        n is the number of the base register, adr the address with that the
        base register is loaded and sec the section that n is related to.

        You can use this option if the program uses the smalldata model. It
        will provide you with a more readable .ASM file.
        Smalldata model means the access to data is made by D16(An), and the
        register An has to be preloaded by the SMALLDATABASE value. A lot of
        compilers use A4 as baseregister and the address of the datasection
        plus 32766 as the SMALLDATABASE.
        A good way to find out if a program makes use of the smalldata model
        is the following:
        1. Type "IRA >x -a -info -basereg test"
        2. Look at the file test.asm and x with an editor.
           If there are memory accesses by D16(An) (e.g. move.l -32754(A4),D0)
           look at the file x. There may be lines like BASEREG 00000008: A4.
           The first number is the hexadecimal address of an instruction that
           has A4 as destination register. Look at this address in the file
           test.asm. You may find a line like LEA SECSTRT_1,A4. Perhaps, A4
           is the base register and SECSTRT_1 the SMALLDATABASE. Now memo the
           address of SECSTRT_1 (=adr).
        3. Type "IRA -a -info -basereg=4,adr,1 test"
        4. Look at test.asm and you will see LAB_xxxx instead of D16(A4).
        5. The line NEAR A4,1 in test.asm tells the assembler to use the
           smalldata model. This directive may differ from assembler to
           assembler.

        As always, be careful when modifying a program. Often code and data
        is mixed or there are some program protection techniques that makes
        it hard to modify and run a program.

-BASEABS (off)
        When specified, a label in base-relative addressing mode is written as
        an absolute label, without the base register name (as with IRA V1.05).
        The default behaviour now is to write base-relative references
        as "(label,An)".
```



## Installation

Copy the binary for your architecture anywhere you want (e.g. C:) and rename
it into `ira`.

* ira_68k: IRA for AmigaOS2.x/3.x (680x0)
* ira_os4: IRA for AmigaOS4.x (PPC)
* ira_mos: IRA for MorphOS1.x/2.x (PPC)



## Compiling

Use `makefile` to compile the source with `gcc` on any architecture.

- Use `Makefile` to compile IRA for any GNU tools (including macOS).
- Use `Makefile.win32` to compile IRA for Windows (tested with VC6).
- Use `Makefile.os3` to compile a native binary with vbcc for AmigaOS 2.x/3.x.
- Use `Makefile.os4` to compile a native binary with vbcc for AmigaOS4.x.
- Use `Makefile.mos` to compile a native binary with vbcc for MorphOS.



## How to Reassemble a Program

First, you have to be sure that your Assembler, Linker and IRA work fine.

That goes like follows:

    (Let's assume the linker is called `ln`, the Assembler is called `as` and the
     program is called `test`.)

    $ ira -a test test1.s
    $ as -n test1.s           (assume -n to be the NO_OPTIMISE flag)
    $ ln test1.o
    $ ira -a test1 test2.s
    $ fdiff test1.s test2.s resync 1

If no error pops up until now it's very likely that `test1` will work. (Try it).

If `fdiff` tells you that there are differences between `test1.s` and `test2.s` you
have to be careful with running `test1` because there is at least one bug in
IRA or in your assembler.

If you got no problems with the five points above you can start with editing
`test1.s`. First, try to find all data that is hidden in code sections and
replace the instructions with `DC.W` directives. If you have done so try
assembling `test1.s` with an optimising assembler (should work).

To find parts of text use the `-TEXT` option. Or use the `-KEEPBIN` option and
type `<type >test.hex test.bin opt h>` and look at `test.hex` for text.

To collect some experience it'll be better to begin with short programs.

To reassemble bootblocks, disktracks or memory take a monitor program and put
these things into a file. Then invoke IRA.



## What Assembler Can I Use?

The original IRA was tuned for PhxAss, which might still work. The
recommended assembler is vasm/M68k V1.7 or greater though, which you
should call with the `-no-opt` option to avoid optimizations, for the
generation of an identical binary.

Other assemblers like DevPac, Barfly and SNMA can assemble IRA output
without error, but do not generate identical code. All of them convert
ADD/SUB/CMP/AND/etc. into their immediate form (ADDI/SUBI/CMPI/ANDI/etc.)
when possible, and DevPac additionally swaps registers in EXG.

You can use any assembler you want, but minor problems may occur:

  - There may be problems with the SECTION, MACHINE and NEAR directives.
    Change these lines by hand.
  - Some assemblers can't handle more than 2^16-1 (65535) lines. Get the
    GigaPhxAss from Frank Wille for the big programs.
  - If code and data is mixed in a code hunk you have to switch optimising
    off when you run the assembler. Else the chance of having a damaged
    program is very high. Some assemblers have problems with that.



## Notes

Reassembling programs for 68020+ processors may cause trouble with some
addressing modes.

For example: (0,A0) and (0,A0) seem to be the same, but the first may be
(d16,An) and the second (bd,An,Xn) with Xn suppressed (and bd might be 16
or 32 bit). There are other ambiguous addressing modes.
IRA has no problems with that, but assemblers can't know what the original
addressing mode was, so problems with running a reassembled file may occur.



## License

IRA is freeware.

There is no guarantee for the correct functioning of IRA.

Any responsibility will be explicitly rejected for any consequences from the
use of IRA whatsoever. This includes, but is not limited to, secondary
consequences, personal injuries or other kinds of side effects.

Note: IRA is no longer Shareware, but Freeware! The initial author,
Tim Ruehsen, should not be contacted, as he left the Amiga and stopped
working on IRA many years ago.
