/*
 * Copyright (C) 2018 Microchip Technology Inc.  All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "egt/detail/alignment.h"
#include "egt/detail/imagecache.h"
#include "egt/frame.h"
#include "egt/label.h"
#include "egt/painter.h"

using namespace std;

namespace egt
{
inline namespace v1
{
static const auto DEFAULT_LABEL_SIZE = Size(100, 50);

Label::Label(const std::string& text, alignmask align, const Font& font) noexcept
    : Label(text, Rect(), align, font)
{
}

Label::Label(const std::string& text, const Rect& rect, alignmask align, const Font& font) noexcept
    : TextWidget(text, rect, align, font)
{
    set_name("Label" + std::to_string(m_widgetid));

    set_boxtype(Theme::boxtype::fill);
}

Label::Label(Frame& parent, const std::string& text, alignmask align, const Font& font) noexcept
    : Label(text, align, font)
{
    parent.add(*this);
}

Label::Label(Frame& parent, const std::string& text, const Rect& rect,
             alignmask align, const Font& font) noexcept
    : Label(text, rect, align, font)
{
    parent.add(*this);
}

void Label::set_text(const std::string& str)
{
    if (m_text != str)
    {
        bool doresize = m_text.empty();
        m_text = str;
        if (doresize)
        {
            first_resize();
        }
        damage();
    }
}

void Label::draw(Painter& painter, const Rect& rect)
{
    Drawer<Label>::draw(*this, painter, rect);
}

void Label::default_draw(Label& widget, Painter& painter, const Rect& rect)
{
    ignoreparam(rect);

    widget.draw_box(painter);

    // text
    painter.set(widget.palette().color(Palette::ColorId::text,
                                       widget.active() ? Palette::GroupId::active : Palette::GroupId::normal));
    painter.set(widget.font());

    auto text_size = widget.text_size(widget.text());
    Rect target = detail::align_algorithm(text_size,
                                          widget.box(),
                                          widget.text_align(),
                                          5);
    painter.draw(target.point());
    painter.draw(widget.text());
}

void Label::set_parent(Frame* parent)
{
    TextWidget::set_parent(parent);
    first_resize();
}

void Label::first_resize()
{
    if (box().size().empty())
    {
        if (!m_text.empty())
        {
            auto s = text_size(m_text);
            s += Size(5, 5);
            resize(s);
        }
        else
        {
            resize(DEFAULT_LABEL_SIZE);
        }
    }
}

ImageLabel::ImageLabel(const Image& image,
                       const std::string& text,
                       alignmask align,
                       const Font& font) noexcept
    : ImageLabel(image, text, Rect(), align, font)
{
}

ImageLabel::ImageLabel(const Image& image,
                       const std::string& text,
                       const Rect& rect,
                       alignmask align,
                       const Font& font) noexcept
    : Label(text, rect, align, font),
      m_image(image)
{
    set_name("ImageLabel" + std::to_string(m_widgetid));

    set_boxtype(Theme::boxtype::none);

    if (rect.empty())
        m_box.size(image.size());

    if (text.empty())
        m_image_align = alignmask::center;
}

ImageLabel::ImageLabel(Frame& parent,
                       const Image& image,
                       const std::string& text,
                       alignmask align,
                       const Font& font) noexcept
    : ImageLabel(image, text, align, font)
{
    parent.add(*this);
}

ImageLabel::ImageLabel(Frame& parent,
                       const Image& image,
                       const std::string& text,
                       const Rect& rect,
                       alignmask align,
                       const Font& font) noexcept
    : ImageLabel(image, text, rect, align, font)
{
    parent.add(*this);
}

void ImageLabel::scale_image(double hscale, double vscale,
                             bool approximate)
{
    m_image.scale(hscale, vscale, approximate);
    m_box = Rect(m_box.point(), m_image.size());
}

void ImageLabel::scale_image(double s, bool approximate)
{
    scale_image(s, s, approximate);
}

#if 0
void ImageLabel::resize(const Size& size) override
{
    if (m_text.empty())
    {
        if (this->size() != size)
        {
            double hs = (double)size.w / (double)m_image.size_orig().w;
            double vs = (double)size.h / (double)m_image.size_orig().h;
            scale_image(hs, vs);
        }
    }
    else
    {
        Widget::resize(size);
    }
}
#endif

void ImageLabel::draw(Painter& painter, const Rect& rect)
{
    Drawer<ImageLabel>::draw(*this, painter, rect);
}

void ImageLabel::default_draw(ImageLabel& widget, Painter& painter, const Rect& rect)
{
    ignoreparam(rect);

    widget.draw_box(painter);

    if (!widget.text().empty())
    {
        auto text_size = widget.text_size(widget.text());

        Rect tbox;
        Rect ibox;

        if (widget.m_position_image_first)
            detail::double_align(widget.box(),
                                 widget.m_image.size(), widget.m_image_align, ibox,
                                 text_size, widget.m_text_align, tbox, 5);
        else
            detail::double_align(widget.box(),
                                 text_size, widget.text_align(), tbox,
                                 widget.m_image.size(), widget.m_image_align, ibox, 5);

        painter.draw(ibox.point());
        painter.draw(widget.m_image);

        if (widget.m_show_label)
        {
            painter.set(widget.palette().color(Palette::ColorId::text));
            painter.set(widget.font());
            painter.draw(tbox.point());
            painter.draw(widget.m_text);
        }
    }
    else
    {
        Rect target = detail::align_algorithm(widget.m_image.size(),
                                              widget.box(), widget.m_image_align, 0);
        painter.draw(target.point());
        painter.draw(widget.m_image);
    }
}

void ImageLabel::set_image(const Image& image)
{
    if (!image.empty())
    {
        m_image = image;
#if 0
        auto width = cairo_image_surface_get_width(m_image.get());
        auto height = cairo_image_surface_get_height(m_image.get());
        m_box.w = width;
        m_box.h = height;
#endif
        damage();
    }
}

void ImageLabel::label_enabled(bool value)
{
    if (m_show_label != value)
    {
        m_show_label = value;
        damage();
    }
}

void ImageLabel::first_resize()
{
    if (box().size().empty())
    {
        if (!m_text.empty())
        {
            auto text_size = this->text_size(m_text);

            Rect tbox;
            Rect ibox;

            if (m_position_image_first)
                detail::double_align(box(),
                                     m_image.size(), m_image_align, ibox,
                                     text_size, m_text_align, tbox, 5);
            else
                detail::double_align(box(),
                                     text_size, m_text_align, tbox,
                                     m_image.size(), m_image_align, ibox, 5);

            auto s = Rect::merge(tbox, ibox);
            resize(s.size() + Size(10, 10));
        }
        else
        {
            resize(m_image.size());
        }
    }
}

}
}
