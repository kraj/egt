/*
 * Copyright (C) 2018 Microchip Technology Inc.  All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#ifndef EGT_DETAIL_SCREEN_FRAMEBUFFER_H
#define EGT_DETAIL_SCREEN_FRAMEBUFFER_H

/**
 * @file
 * @brief Working with framebuffers.
 */

#include <egt/detail/meta.h>
#include <egt/screen.h>
#include <string>

namespace egt
{
inline namespace v1
{
namespace detail
{

/**
 * Screen on a fbdev framebuffer.
 *
 * The framebuffer is internally mmap()'ed and directly accessible.  The
 * framebuffer does not manage multiple buffers.
 */
class EGT_API FrameBuffer : public Screen
{
public:

    explicit FrameBuffer(const std::string& path = "/dev/fb0");

    virtual void schedule_flip() override {}

    virtual ~FrameBuffer();

protected:
    int m_fd{-1};
    void* m_fb{nullptr};
};

}
}
}

#endif
