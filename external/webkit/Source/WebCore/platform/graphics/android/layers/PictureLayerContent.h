/*
 * Copyright 2012, The Android Open Source Project
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *  * Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 *  * Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef PictureLayerContent_h
#define PictureLayerContent_h

#include "LayerContent.h"
//AndroidJB4.3 Merge  - START
#include "SkStream.h" 
//AndroidJB4.3 Merge  - END
namespace WebCore {

class PictureLayerContent : public LayerContent {
public:
    PictureLayerContent(SkPicture* picture);
    PictureLayerContent(const PictureLayerContent& content);
    ~PictureLayerContent();

    virtual int width();
    virtual int height();
//    virtual bool isEmpty();//4.2 Merge : removed in 4.2
    virtual void setCheckForOptimisations(bool check) { m_checkedContent = !check; }
    virtual void checkForOptimisations();
    virtual float maxZoomScale();//4.2 Merge
    virtual void draw(SkCanvas* canvas);
    virtual void serialize(SkWStream* stream);

private:
    SkPicture* m_picture;
    bool m_checkedContent;
    bool m_hasText;
};
//AndroidJB4.3 Merge  - START
class LegacyPictureLayerContent : public LayerContent {
public:
    LegacyPictureLayerContent(SkMemoryStream* pictureStream);
    ~LegacyPictureLayerContent();

    virtual int width() { return m_width; }
    virtual int height() { return m_height; }
    virtual void setCheckForOptimisations(bool check) {}
    virtual void checkForOptimisations() {}
    virtual float maxZoomScale() { return 1e6; }
    virtual void draw(SkCanvas* canvas);
    virtual void serialize(SkWStream* stream) { }

private:
    void* m_legacyLib;
    void* m_legacyPicture;
    int m_width;
    int m_height;

    typedef int  (*legacy_skia_create_picture_proc)(const void*, int, void**, int*, int*);
    typedef void (*legacy_skia_delete_picture_proc)(void*);
    typedef void (*legacy_skia_draw_picture_proc)(void*, void*, void*, int, int, int, int, void*);

    legacy_skia_create_picture_proc m_createPictureProc;
    legacy_skia_delete_picture_proc m_deletePictureProc;
    legacy_skia_draw_picture_proc m_drawPictureProc;
};
//AndroidJB4.3 Merge  - END

} // WebCore

#endif // PictureLayerContent_h
