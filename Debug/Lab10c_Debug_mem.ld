/*
 * GENERATED FILE - DO NOT EDIT
 * (c) Code Red Technologies Ltd, 2008-2016
 * (c) NXP Semiconductors 2013-2016
 * Linker script memory definitions
 * Created from LinkMemoryTemplate
 * By LPCXpresso v7.3.0 [Build 186] [2014-07-09]  on Wed Mar 09 16:33:51 MST 2016)
*/

MEMORY
{
  /* Define each memory region */
  MFlash64 (rx) : ORIGIN = 0x0, LENGTH = 0x10000 /* 64K bytes */
  RamLoc8 (rwx) : ORIGIN = 0x10000000, LENGTH = 0x2000 /* 8K bytes */


}
  /* Define a symbol for the top of each memory region */
  __top_MFlash64 = 0x0 + 0x10000;
  __top_RamLoc8 = 0x10000000 + 0x2000;



