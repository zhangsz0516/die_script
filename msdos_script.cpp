// copyright (c) 2019-2020 hors<horsicq@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
#include "msdos_script.h"

MSDOS_Script::MSDOS_Script(XMSDOS *pMSDOS) : Binary_Script(pMSDOS)
{
    this->pMSDOS=pMSDOS;

    bIsLE=pMSDOS->isLE();
    bIsLX=pMSDOS->isLX();
    bIsNE=pMSDOS->isNE();
    bIsPE=pMSDOS->isPE();

    nNumberOfRich=0;
    bIisRichSignaturePresent=false;

    if(bIsLE||bIsPE)
    {
        bIisRichSignaturePresent=pMSDOS->isRichSignaturePresent();

        if(bIisRichSignaturePresent)
        {
            listRich=pMSDOS->getRichSignatureRecords();

            nNumberOfRich=listRich.count();
        }
    }

    nDosStubOffset=0;
    nDosStubSize=0;
    bIsDosStubPresent=false;

    if(bIsLE||bIsLX||bIsNE||bIsPE)
    {
        bIsDosStubPresent=pMSDOS->isDosStubPresent();

        if(bIsDosStubPresent)
        {
            nDosStubOffset=pMSDOS->getDosStubOffset();
            nDosStubSize=pMSDOS->getDosStubSize();
        }
    }
}

MSDOS_Script::~MSDOS_Script()
{

}

bool MSDOS_Script::isLE()
{
    return bIsLE;
}

bool MSDOS_Script::isLX()
{
    return bIsLX;
}

bool MSDOS_Script::isNE()
{
    return bIsNE;
}

bool MSDOS_Script::isPE()
{
    return bIsPE;
}

qint64 MSDOS_Script::getDosStubOffset()
{
    return nDosStubOffset;
}

qint64 MSDOS_Script::getDosStubSize()
{
    return nDosStubSize;
}

bool MSDOS_Script::isDosStubPresent()
{
    return bIsDosStubPresent;
}

qint32 MSDOS_Script::getNumberOfRichIDs()
{
    return nNumberOfRich;
}

bool MSDOS_Script::isRichVersionPresent(quint32 nVersion)
{
    return pMSDOS->isRichVersionPresent(nVersion,&listRich);
}

bool MSDOS_Script::isRichSignaturePresent()
{
    return bIisRichSignaturePresent;
}
