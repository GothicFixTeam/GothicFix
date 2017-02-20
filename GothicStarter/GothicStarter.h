#ifndef _GOTHICSTARTER_H_
#define _GOTHICSTARTER_H_

/*//////////////////////////////////////////////////////////////////////////////
//
//  Conditional Compilation (might be defined in your project file or makefile)
*/

#define MOD_VERSION

/*//////////////////////////////////////////////////////////////////////////////
//
//  Application Version
*/

#define APP_VERSION_MAJOR 2
#define APP_VERSION_MINOR 8
#define APP_VERSION_PATCH 0
#ifndef MOD_VERSION
#define APP_VERSION_STRING "2.8\0"
#else
#define APP_VERSION_STRING "2.8 (mod)\0"
#endif
#define APP_VERSION_FILEDESCRIPTION "Gothic - Modification Starter\0"
#define APP_VERSION_COPYRIGHT       "Copyright (c) 2002-2007 Pluto 13 GmbH\0"

#define _APP_VERSION_TONUMBER(a, b, c, d) a,b,c,d
#define APP_VERSION_NUMBER _APP_VERSION_TONUMBER(APP_VERSION_MAJOR, APP_VERSION_MINOR, APP_VERSION_PATCH, 0)

/*//////////////////////////////////////////////////////////////////////////////
//
//  Windows Versions
*/

#ifndef WINVER
#define WINVER 0x0400
/* This program requires shell version 4.71! (IE >= 4.0) */
#endif
#ifndef _WIN32_IE
#define _WIN32_IE 0x0400
/* This program requires shell version 4.71! (IE >= 4.0) */
#endif
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
/* This program requires Windows 2000! (NT-based system) */
#endif

/*//////////////////////////////////////////////////////////////////////////////
//
//  Product Version
*/

#define APP_PRODUCT_MAJOR 2
#define APP_PRODUCT_MINOR 6
#define APP_PRODUCT_PATCH 0
#define APP_PRODUCT_PRODUCT "Gothic\0"
#define APP_PRODUCT_COMPANY "Piranha Bytes\0"
#define APP_PRODUCT_NUMBER _APP_VERSION_TONUMBER(APP_PRODUCT_MAJOR, APP_PRODUCT_MINOR, APP_PRODUCT_PATCH, 0)

#endif
