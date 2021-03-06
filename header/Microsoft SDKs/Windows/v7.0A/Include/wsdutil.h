//+-------------------------------------------------------------------------
//
//  Microsoft Windows
//  Copyright (c) Microsoft Corporation. All rights reserved.
//
//  Component: WSDAPI - Microsoft Web Services for Devices API
// 
//  File: wsdutil.h
//
//  Abstract: WSDAPI Utilities
//
//--------------------------------------------------------------------------
#pragma once

//
// Helpful macros
//
#define WSD_DEFAULT_HOSTING_ADDRESS L"http://*:5357/"
#define WSD_DEFAULT_SECURE_HOSTING_ADDRESS L"https://*:5358/"
#define WSD_DEFAULT_EVENTING_ADDRESS L"http://*:5357/"

#ifdef __cplusplus
extern "C" {
#endif

//
// Configuration
//

// MessageSize: DWORD value between 32768 and 1048576
#define WSDAPI_OPTION_MAX_INBOUND_MESSAGE_SIZE 0x0001

#if (WINVER >= _WIN32_WINNT_WIN7)
// XMLDebug: Send XML strings to debugger session
#define WSDAPI_OPTION_TRACE_XML_TO_DEBUGGER 0x0002

// XMLFile: Send XML strings to file
#define WSDAPI_OPTION_TRACE_XML_TO_FILE 0x0003
#endif
    
HRESULT WINAPI
WSDSetConfigurationOption(
    DWORD dwOption,
    __in_bcount(cbInBuffer) LPVOID pVoid,
    DWORD cbInBuffer);

HRESULT WINAPI
WSDGetConfigurationOption(
    DWORD dwOption,
    __out_bcount(cbOutBuffer) LPVOID pVoid,
    DWORD cbOutBuffer);
    
//
// Linked memory
//

void * WINAPI 
WSDAllocateLinkedMemory(
    void* pParent, 
    size_t cbSize);

void WINAPI
WSDFreeLinkedMemory(
    void *pVoid);

void WINAPI
WSDAttachLinkedMemory(
    void* pParent,
    void* pChild);

void WINAPI
WSDDetachLinkedMemory(
    void* pVoid);

//
// XML helpers 
//

typedef struct _WSDXML_ELEMENT WSDXML_ELEMENT; 

HRESULT WINAPI
WSDXMLBuildAnyForSingleElement(
    WSDXML_NAME* pElementName, 
    __in_opt LPCWSTR pszText, 
    WSDXML_ELEMENT** ppAny);

HRESULT WINAPI
WSDXMLGetValueFromAny(
    __in LPCWSTR pszNamespace,
    __in LPCWSTR pszName, 
    WSDXML_ELEMENT* pAny, 
    LPCWSTR* ppszValue);

HRESULT WINAPI
WSDXMLAddSibling(
    WSDXML_ELEMENT* pFirst,
    WSDXML_ELEMENT* pSecond);

HRESULT WINAPI
WSDXMLAddChild(
    WSDXML_ELEMENT* pParent,
    WSDXML_ELEMENT* pChild);

HRESULT WINAPI
WSDXMLCleanupElement(
    WSDXML_ELEMENT* pAny);    

HRESULT WINAPI
WSDGenerateFault(
    __in LPCWSTR pszCode,
    __in_opt LPCWSTR pszSubCode,
    __in LPCWSTR pszReason,
    __in_opt LPCWSTR pszDetail,
    __in IWSDXMLContext* pContext,
    __deref_out WSD_SOAP_FAULT** ppFault);

HRESULT WINAPI
WSDGenerateFaultEx(
    __in WSDXML_NAME* pCode, 
    __in_opt WSDXML_NAME* pSubCode, 
    __in WSD_LOCALIZED_STRING_LIST* pReasons, 
    __in_opt LPCWSTR pszDetail, 
    __deref_out WSD_SOAP_FAULT** ppFault);

#if (WINVER >= _WIN32_WINNT_WIN7)
HRESULT WINAPI
WSDUriEncode(
    __in_ecount(cchSource) LPCWSTR source,
    __in DWORD cchSource,
    __out_ecount(*cchDestOut) LPWSTR *destOut,
    __out_opt DWORD *cchDestOut);

HRESULT WINAPI
WSDUriDecode(
    __in_ecount(cchSource) LPCWSTR source,
    __in DWORD cchSource,
    __out_ecount(*cchDestOut) LPWSTR *destOut,
    __out_opt DWORD *cchDestOut);
#endif

#ifdef __cplusplus
};
#endif

