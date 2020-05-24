#include "FatLib/FatVolume.h"
#include "FatLib/FatFile.h"

bool FatFile::ls(print_t* pr, uint8_t flags /*= 0*/, uint8_t indent /*= 0*/)
{
    printf("fatfile::ls\n");
    return true;
}
void FatFile::printFatDate(print_t* pr, uint16_t fatDate)
{
    printf("fatfile::printFatDate(%04x)\n", fatDate);
}
void FatFile::printFatTime(print_t* pr, uint16_t fatTime)
{
    printf("fatfile::printFatTime(%04x)\n", fatTime);
}
size_t FatFile::printName(print_t* pr)
{
    printf("fatfile::printName\n");
    return 0;
}
bool FatVolume::wipe(print_t* pr /*= 0*/)
{
    printf("fatfile::wipe\n");
    return true;
}

bool FatFile::close()
{
    printf("fatfile::close\n");
    return true;
}

FatFile* FatFile::m_cwd;

bool FatFile::open(FatFile*ff, char const*name, unsigned char mode)
{
    printf("fatfile::open('%s', %x)\n", name, mode);
    return true;
}

bool FatFile::openRoot(FatVolume*)
{
    printf("fatfile::openroot\n");
    return true;
}

bool FatVolume::init(unsigned char b)
{
    printf("fatfile::init(%d)\n", b);
    return true;
}

bool SdSpiCard::begin(SdSpiLibDriver* drv, unsigned char c, SPISettings s)
{
    printf("SdSpiCard::begin(%02x, ...)\n", c);
    return true;
}

bool SdSpiCard::readOCR(unsigned int*ocr)
{
    printf("SdSpiCard::readOCR\n");
    *ocr = 0x80FF8000;
    return true;
}

bool SdSpiCard::readRegister(unsigned char reg, void*data)
{
    printf("SdSpiCard::readRegister(%02x)\n", reg);

    return true;
}

bool SdSpiCard::readStatus(unsigned char*status)
{
    printf("SdSpiCard::readStatus\n");
    status[0] = 0;
    return true;
}


