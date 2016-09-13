//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;

#include <nb30.h>
#include <stdio.h>
#include <fstream>
using namespace std;

typedef struct _Adapter_
{
    ADAPTER_STATUS adapt;
    NAME_BUFFER NameBuff [30];
} Adapter, *PAdapter;

extern "C" _declspec(dllimport) void _stdcall str2md5(char *mac, char *output);

//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
    : TForm(Owner)
{
    mHasGetMac = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
    if (!mHasGetMac)
    {
        NCB Ncb;
        LANA_ENUM lenum;
        Adapter adapter;

        memset(&Ncb, 0, sizeof(Ncb));
        Ncb.ncb_command = NCBENUM;
        Ncb.ncb_buffer = (UCHAR *)&lenum;
        Ncb.ncb_length = sizeof(lenum);
        Netbios(&Ncb);
        ofstream file("sn.txt", ios::out|ios::trunc);

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

                char sMac[33];
                str2md5(mac, sMac);
                file << sMac << endl;
            }
        }

        mHasGetMac = true;
        file.close();
        Label1->Caption = "Success! have save to sn.txt";
        Button1->Caption = "Exit";
    }
    else
    {
        Application->Terminate();
    }
}
//---------------------------------------------------------------------------

