/*
 * Copyright (C) 2018 Microchip Technology Inc.  All rights reserved.
 * Joshua Henderson <joshua.henderson@microchip.com>
 */
#include "mui/image.h"
#include "mui/imagecache.h"
#include "mui/painter.h"

using namespace std;

namespace mui
{

    Image::Image(const string& filename, const Point& point)
        : m_filename(filename),
          m_hscale(1.0),
          m_vscale(1.0)
    {
        m_image = image_cache.get(filename, 1.0);
        assert(m_image.get());

        m_box = Rect(point.x, point.y,
                     cairo_image_surface_get_width(m_image.get()),
                     cairo_image_surface_get_height(m_image.get()));
    }

    void Image::scale(double hscale, double vscale, bool approximate)
    {
        if (m_hscale != hscale || m_vscale != vscale)
        {
            m_image = image_cache.get(m_filename, hscale, vscale, approximate);

            Widget::resize(Size(cairo_image_surface_get_width(m_image.get()),
                                cairo_image_surface_get_height(m_image.get())));
            m_hscale = hscale;
            m_vscale = vscale;
        }
    }

    void Image::draw(Painter& painter, const Rect& rect)
    {
        painter.draw_image(Rect(rect.point() - box().point(), rect.size()),
                           rect.point(), m_image);
    }

    Image::~Image()
    {}

    ImageText::ImageText(const std::string& image,
                         const std::string& text,
                         const Point& point,
                         const Font& font)
        : Image(image, point),
          m_text(text),
          m_font(font),
          m_label(true)
    {

    }

    void ImageText::draw(Painter& painter, const Rect& rect)
    {
        Image::draw(painter, rect);

        if (m_label)
            painter.draw_text(m_text, box(), palette().color(Palette::TEXT),
                              ALIGN_BOTTOM | ALIGN_CENTER, 0, m_font);

    }

    void ImageText::label_enabled(bool value)
    {
        if (m_label != value)
        {
            m_label = value;
            damage();
        }
    }

    ImageText::~ImageText()
    {
    }
}