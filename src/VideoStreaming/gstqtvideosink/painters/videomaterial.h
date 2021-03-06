/*
    Copyright (C) 2013 Digia Plc and/or its subsidiary(-ies).
    Copyright (C) 2013 basysKom GmbH <info@basyskom.com>
    Copyright (C) 2013 Collabora Ltd. <info@collabora.com>

    This library is free software; you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License version 2.1
    as published by the Free Software Foundation.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/**
 * @file
 *   @brief Extracted from QtGstreamer to avoid overly complex dependency
 *   @author Gus Grubba <mavlink@grubba.com>
 */

#pragma once

#include "../utils/bufferformat.h"
#include <QSize>
#include <QMutex>
#include <QMatrix4x4>

#include <QtQuick/QSGMaterial>

class VideoMaterialShader;

class VideoMaterial : public QSGMaterial
{
public:
    static VideoMaterial *create(const BufferFormat & format);

    virtual ~VideoMaterial();

    virtual int compare(const QSGMaterial *other) const;

    void setCurrentFrame(GstBuffer *buffer);
    void updateColors(int brightness, int contrast, int hue, int saturation);

    void bind();

protected:
    VideoMaterial();
    void initRgbTextureInfo(GLenum internalFormat, GLuint format,
                            GLenum type, const GstVideoInfo& videoInfo);
    void initYuv420PTextureInfo(const GstVideoInfo& videoInfo);
    void updateYuv420PTextureInfo(const GstVideoInfo& videoInfo);
    void init(GstVideoColorMatrix colorMatrixType);

private:
    void bindTexture(int i, const quint8 *data);

    GstVideoInfo m_videoInfo;
    GstBufferPool* m_bufferPool;
    GstBuffer *m_frame;
    QMutex m_frameMutex;

    static const int Num_Texture_IDs = 3;
    int m_textureCount;
    GLuint m_textureIds[Num_Texture_IDs];
    int m_textureWidths[Num_Texture_IDs];
    int m_textureHeights[Num_Texture_IDs];
    int m_textureOffsets[Num_Texture_IDs];
    int m_textureStrides[Num_Texture_IDs];
    bool m_textureAllocated[Num_Texture_IDs];

    GLenum m_textureFormat;
    GLuint m_textureInternalFormat;
    GLenum m_textureType;

    QMatrix4x4 m_colorMatrix;
    GstVideoColorMatrix m_colorMatrixType;

    friend class VideoMaterialShader;
};

