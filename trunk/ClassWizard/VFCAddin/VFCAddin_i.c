/* this file contains the actual definitions of */
/* the IIDs and CLSIDs */

/* link this file in with the server and any clients */


/* File created by MIDL compiler version 5.01.0164 */
/* at Mon Mar 23 13:42:31 2009
 */
/* Compiler settings for D:\VFC_Projects\ClsWizard\VFCAddin\VFCAddin.odl:
    Os (OptLev=s), W1, Zp8, env=Win32, ms_ext, c_ext
    error checks: allocation ref bounds_check enum stub_data 
*/
//@@MIDL_FILE_HEADING(  )
#ifdef __cplusplus
extern "C"{
#endif 


#ifndef __IID_DEFINED__
#define __IID_DEFINED__

typedef struct _IID
{
    unsigned long x;
    unsigned short s1;
    unsigned short s2;
    unsigned char  c[8];
} IID;

#endif // __IID_DEFINED__

#ifndef CLSID_DEFINED
#define CLSID_DEFINED
typedef IID CLSID;
#endif // CLSID_DEFINED

const IID LIBID_VFCAddin = {0xA89A86CB,0xD1A8,0x449E,{0xAF,0x05,0x8E,0x14,0xD1,0xAE,0x84,0x30}};


const IID IID_ICommands = {0x390E5A7E,0xD80C,0x4C7B,{0x91,0x7A,0x92,0x3D,0xAD,0xC8,0x75,0x2F}};


const CLSID CLSID_Commands = {0xA95A358E,0xC3A7,0x4515,{0x81,0xE5,0xEE,0xFB,0x88,0x60,0x9D,0x76}};


const CLSID CLSID_ApplicationEvents = {0xFA844F9D,0xF74D,0x4FE5,{0x92,0x1F,0xA5,0xB6,0xA2,0x1E,0x3E,0xAE}};


const CLSID CLSID_DebuggerEvents = {0x12057C1C,0x026F,0x4231,{0xBE,0x2E,0x31,0x31,0xB6,0x8B,0x00,0xDE}};


#ifdef __cplusplus
}
#endif

