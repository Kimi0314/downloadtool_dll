//---------------------------------------------------------------------------
#include <vcl.h>
#include <windows.h>
#pragma hdrstop
//---------------------------------------------------------------------------
//   Important note about DLL memory management when your DLL uses the
//   static version of the RunTime Library:
//
//   If your DLL exports any functions that pass String objects (or structs/
//   classes containing nested Strings) as parameter or function results,
//   you will need to add the library MEMMGR.LIB to both the DLL project and
//   any other projects that use the DLL.  You will also need to use MEMMGR.LIB
//   if any other projects which use the DLL will be performing new or delete
//   operations on any non-TObject-derived classes which are exported from the
//   DLL. Adding MEMMGR.LIB to your project will change the DLL and its calling
//   EXE's to use the BORLNDMM.DLL as their memory manager.  In these cases,
//   the file BORLNDMM.DLL should be deployed along with your DLL.
//
//   To avoid using BORLNDMM.DLL, pass string information using "char *" or
//   ShortString parameters.
//
//   If your DLL uses the dynamic version of the RTL, you do not need to
//   explicitly add MEMMGR.LIB as this will be done implicitly for you
//---------------------------------------------------------------------------

#pragma argsused
int WINAPI DllEntryPoint(HINSTANCE hinst, unsigned long reason, void* lpReserved)
{
    return 1;
}
//---------------------------------------------------------------------------

#include <nb30.h>
#include <stdio.h>
#include "md5.h"
#define SN_LEN 33

typedef struct _Adapter_
{
    ADAPTER_STATUS adapt;
    NAME_BUFFER NameBuff [30];
} Adapter, *PAdapter;

static const char white_list[][SN_LEN] =
{
    "84c5c568d4a83ad40501cb211e1d64f6",
    "5324dae524fa33ad5de8f1c973d83800",
    "7611f05b20fb21b56f8d77a5d07744b2",
    "07956d190f2b800088f2fcb27ebb5237",
    "5c5678cfc25d2099ba694d11f69e1642",
    "fa4075e98e78f17a3beb03bccd723591",
    "cba588711fe3a8b088e74e4a7533296d",
    "749f61fd9cefbedbff6c579131226410",
    "07f45587b7a6865db638c7190694e720",
    "8b35d542886219c8f00ec98d5637da43",
    "1f4c4fd50e5a9160244564a688b372fa",
    "4e793f2dc1d9913b4d136cce43abb64a",
    "69caccd6f182f0f85998e5ce8cfe5d65",
    "242ae243182c2d6b3727a52c1e28f8eb",
    "3deae4a5ac5a1b10fa7cbb1c3bff7ef5",
    "be498213ba94f039f78cdf8eeedd8c3f",
    "1d145275ae7b953866fd23ca298108c5",
    "592e4c3de0cb86ca98aa44b50dad42d5",
    "1efaf57881c51774993f6fdd4fa6cdd5",
    "d16442083ca52d4053542d7661ebbb5d",
    "e1242d394f05f70b923aabb30459fcf0",
    "3c943b82382e9be10f618541cbd4a856",
    "a3bd6ae9b6833e39a24129165e9e8370",
    "b1fc7545c83ffe4c32b8d40012409dbb",
    "9018752d245cc5be86f14bf7e1c3f65c",
    "e1af9fafc9f339bfdec2acc1ccb62828",
    "4080eebafe243444a396f3fb4a01e883",
    "7ac747fd6875ea2a75ba26b7db604232",
    "0fa060d529431c136920b2aadb661cf4",
    "0404b239c8077fdd523939dc446ae153",
	"71b88294233a5a2e81695cc18dd90e4f",
	"a583e8893938e58105a8d2aa6579e7c2",
	"497726ccc304c9fce068f2cf197116c3",
    "a583e8893938e58105a8d2aa6579e7c2",
    "497726ccc304c9fce068f2cf197116c3",
    "ea766e7d8fbd328462e0551b5a67ea95",
    "9835a5b963d0672418302270714f21da",
    "59b74301a875fb979f2b5fcbd99b3cfb",
    "667843d166bdeeaa395bf0d63a700dab",
    "5a93cf49a8cf5884b441efcaf5e214fa",
    "ab8a82b6dbd067cd0d0b011f1a4ff17e",
    "017fe9b77611f7899267e76b4ae29579",    "1dd38405d926bef9a4765675cba15dc4",    "9e87d1f37c6577002d2f388fdd45367c",
    "bacd23ae55a46a4c2cd517d59e27cb06",


    "1b889a2792795c9511c4ea7084adbe5b",
    "494badac66664feea09a5ad366373bff",
    "428e6a9ba86fc69a50c8dfb9cf2d2508",
    "12f1ca24102458729365a81c0c7d6a3c",

    "0ee8772557a75f900e27650ae14e844a",    "60416c5fd00f9f58ba65728ede711038",    "e69e0f92eb1679eee6e6d2f02f0c6377",    "07e6bcfc8fb081a9e03e3ccb1b0ed1fc",    "2b7ab989f087a87f54c4c9f727be924a",    "e8f78ac88333edcb46e26db61b1382ab",    "60cef1db1e4917b4f65a6ff467af24f5",    "b22870829d02e4d2b6f1d88931f87853",    "41e7be1d1f704933b560a80cd4104236",    "da728c571c9d715060298af330589251",    "31db9b4aeacf6dd5be315861dd9e5876",    "0fd3346e3a7a5a57966b01f4348c9a9e",    "56f7adf8c236c3ba82ed698e21cceac7",    "6fcb80e5efc9023ce72caae4c3ef0240",    "de38cfde910bd368a5bf180add514455",
    "db036bc616a85e120f18dc7c1a8723b8",};

extern "C" _declspec(dllexport) void _stdcall str2md5(char *mac, char *output)
{
    if (output == NULL || mac == NULL)
    {
        return;
    }

    MD5 md5;
    md5.GenerateMD5(mac, strlen(mac));
    strcpy(output, md5.ToString().data());
}

extern "C" _declspec(dllexport) bool _stdcall hasAuthorizedHelper(char *info)
{
    boolean isAuthorized = false;
    NCB Ncb;
    LANA_ENUM lenum;
    Adapter adapter;
    const int LEN = sizeof(white_list) / SN_LEN;

    memset(&Ncb, 0, sizeof(Ncb));
    Ncb.ncb_command = NCBENUM;
    Ncb.ncb_buffer = (UCHAR *)&lenum;
    Ncb.ncb_length = sizeof(lenum);
    Netbios(&Ncb);

    for(int i=0; i < lenum.length ; i++)
    {
        memset(&Ncb, 0, sizeof(Ncb));
        Ncb.ncb_command = NCBRESET;
        Ncb.ncb_lana_num = lenum.lana[i];
        Netbios(&Ncb);

        memset(&Ncb, 0, sizeof(Ncb));
        Ncb.ncb_command = NCBASTAT;
        Ncb.ncb_lana_num = lenum.lana[i];
        strcpy((char *)Ncb.ncb_callname, "* ");
        Ncb.ncb_buffer = (unsigned char *)&adapter;
        Ncb.ncb_length = sizeof(adapter);
        UCHAR uRetCode = Netbios(&Ncb);
 
        if (uRetCode == 0)
        {
            char mac[20];
            sprintf(mac, "%02X%02X%02X%02X%02X%02X\n",
                    adapter.adapt.adapter_address[0],
                    adapter.adapt.adapter_address[1],
                    adapter.adapt.adapter_address[2],
                    adapter.adapt.adapter_address[3],
                    adapter.adapt.adapter_address[4],
                    adapter.adapt.adapter_address[5]
                   );

            // covert mac to md5 string at first
            char sMac[33];
            str2md5(mac, sMac);
            // for test
            if (info != NULL)
            {
                strcpy(info, sMac);
            }

            // check from white-list
            for (int j = 0; j < LEN; j++) {
                if (stricmp(sMac, white_list[j]) == 0)
                {
                    isAuthorized = true;
                    break;
                }
            }

            if (isAuthorized)
            {
                break;
            }
        }
    }

    return isAuthorized;
}

extern "C" _declspec(dllexport) bool _stdcall hasAuthorized(void)
{
    return hasAuthorizedHelper(NULL);
}
