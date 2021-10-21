#pragma once

#include "ImageBuffer.h"
#include <stdio.h>
#include "Util.h"

void TestImageBuffer() {
    wprintf(L"==== TestImageBuffer() ====\n");
    
    std::wstring file0 = L"c:\\test\\8K Aqua.bmp";
    std::wstring file1 = L"c:\\test\\8K Aqua.png";
    std::wstring file2 = L"c:\\test\\8K Aqua.jpg";
    std::wstring file3 = L"c:\\test\\8K Aqua_deflate.tif";
    std::wstring file4 = L"c:\\test\\8K Aqua_lzw.tif";

    auto t0 = GetTimeMs();

    hims::ImageBuffer img0(file0);
    auto t1 = GetTimeMs();

    hims::ImageBuffer img1(file1);
    auto t2 = GetTimeMs();

    hims::ImageBuffer img2(file2);
    auto t3 = GetTimeMs();

    hims::ImageBuffer img3(file3);
    auto t4 = GetTimeMs();

    hims::ImageBuffer img4(file4);
    auto t5 = GetTimeMs();

    wprintf(L"file0 %s - width:%lld height:%lld buffer:%p / %.1f\n", file0.c_str(), img0.Width(), img0.Height(), img0.Buffer(), t1 - t0);
    wprintf(L"file1 %s - width:%lld height:%lld buffer:%p / %.1f\n", file1.c_str(), img1.Width(), img1.Height(), img1.Buffer(), t2 - t1);
    wprintf(L"file2 %s - width:%lld height:%lld buffer:%p / %.1f\n", file2.c_str(), img2.Width(), img2.Height(), img2.Buffer(), t3 - t2);
    wprintf(L"file3 %s - width:%lld height:%lld buffer:%p / %.1f\n", file3.c_str(), img3.Width(), img3.Height(), img3.Buffer(), t4 - t3);
    wprintf(L"file4 %s - width:%lld height:%lld buffer:%p / %.1f\n", file4.c_str(), img4.Width(), img4.Height(), img4.Buffer(), t5 - t4);

    wprintf(L"\n");
}