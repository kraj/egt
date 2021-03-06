/*
 * Copyright (C) 2018 Microchip Technology Inc.  All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 */
#include "egt/button.h"
#include "egt/checkbox.h"
#include "egt/detail/alignment.h"
#include "egt/detail/layout.h"
#include "egt/frame.h"
#include "egt/painter.h"
#include "egt/theme.h"

namespace egt
{
inline namespace v1
{

static const auto DEFAULT_CHECKBOX_SIZE = Size(100, 30);

CheckBox::CheckBox(const std::string& text,
                   const Rect& rect) noexcept
    : Button(text, rect)
{
    set_name("CheckBox" + std::to_string(m_widgetid));

    set_boxtype(Theme::boxtype::none);
    set_padding(5);
    set_text_align(alignmask::left | alignmask::center);

    flags().set(Widget::flag::grab_mouse);
}

CheckBox::CheckBox(Frame& parent,
                   const std::string& text,
                   const Rect& rect) noexcept
    : CheckBox(text, rect)
{
    parent.add(*this);
}

void CheckBox::handle(Event& event)
{
    Widget::handle(event);

    switch (event.id())
    {
    case eventid::pointer_click:
        set_checked(!checked());
    default:
        break;
    }
}

void CheckBox::draw(Painter& painter, const Rect& rect)
{
    Drawer<CheckBox>::draw(*this, painter, rect);
}

void CheckBox::default_draw(CheckBox& widget, Painter& painter, const Rect& /*rect*/)
{
    widget.draw_box(painter, Palette::ColorId::label_bg, Palette::ColorId::border);

    auto b = widget.content_area();

    painter.set(widget.font());
    auto text_size = painter.text_size(widget.text());

    std::vector<detail::LayoutRect> rects;

    rects.emplace_back(0,
                       Rect(0, 0,
                            std::min(b.width() - text_size.width() - widget.padding(), b.height()),
                            std::min(b.width() - text_size.width() - widget.padding(), b.height())),
                       0, 0, widget.padding() / 2);
    rects.emplace_back(0,
                       Rect(0, 0, text_size.width(), text_size.height()),
                       widget.padding() / 2);

    detail::flex_layout(b, rects, justification::start, orientation::horizontal);

    auto handle = rects[0].rect + b.point();
    auto text = rects[1].rect + b.point();
    auto border = widget.theme().default_border();

    widget.theme().draw_box(painter, Theme::boxtype::fill, handle,
                            widget.color(Palette::ColorId::button_fg),
                            Palette::transparent,
                            border);

    if (widget.checked())
    {
        // draw an "X"
        auto cr = painter.context().get();
        cairo_set_line_cap(cr, CAIRO_LINE_CAP_ROUND);
        painter.set(widget.color(Palette::ColorId::button_fg).color());
        painter.draw(handle.top_left() + Point(border, border),
                     handle.bottom_right() - Point(border, border));
        painter.draw(handle.top_right() + Point(-border, border),
                     handle.bottom_left() + Point(border, -border));
        painter.set_line_width(border);
        painter.stroke();
    }

    // text
    painter.set(widget.color(Palette::ColorId::label_text).color());
    auto size = painter.text_size(widget.text());
    Rect target = detail::align_algorithm(size,
                                          text,
                                          widget.text_align());
    painter.draw(target.point());
    painter.draw(widget.text());
}

Size CheckBox::min_size_hint() const
{
    const auto default_size = DEFAULT_CHECKBOX_SIZE + Widget::min_size_hint();

    if (!m_text.empty())
    {
        auto s = text_size(m_text);
        s += Size(s.width() / 2 + 5, 0);
        s += Widget::min_size_hint();
        if (s.width() < default_size.width())
            s.set_width(default_size.width());
        if (s.height() < default_size.height())
            s.set_height(default_size.height());
        return s;
    }

    return default_size;
}

ToggleBox::ToggleBox(const Rect& rect) noexcept
    : CheckBox( {}, rect)
{
    set_name("ToggleBox" + std::to_string(m_widgetid));

    set_boxtype(Theme::boxtype::fill_rounded);
    set_border(theme().default_border());
}

ToggleBox::ToggleBox(Frame& parent, const Rect& rect) noexcept
    : ToggleBox(rect)
{
    parent.add(*this);
}

void ToggleBox::draw(Painter& painter, const Rect& rect)
{
    Drawer<ToggleBox>::draw(*this, painter, rect);
}

void ToggleBox::default_draw(ToggleBox& widget, Painter& painter, const Rect& rect)
{
    widget.draw_box(painter, Palette::ColorId::bg, Palette::ColorId::border);

    auto b = widget.content_area();

    if (widget.checked())
    {
        Rect rect = b;
        rect.set_width(rect.width() / 2);
        rect.set_x(rect.x() + rect.width());
        widget.theme().draw_box(painter,
                                Theme::boxtype::fill_rounded,
                                rect,
                                widget.color(Palette::ColorId::border),
                                widget.color(Palette::ColorId::button_bg));
    }
    else
    {
        Rect rect = b;
        rect.set_width(rect.width() / 2);

        if (widget.enable_disable())
        {
            widget.theme().draw_box(painter,
                                    Theme::boxtype::fill_rounded,
                                    rect,
                                    widget.color(Palette::ColorId::border, Palette::GroupId::disabled),
                                    widget.color(Palette::ColorId::button_bg, Palette::GroupId::disabled));
        }
        else
        {
            widget.theme().draw_box(painter,
                                    Theme::boxtype::fill_rounded,
                                    rect,
                                    widget.color(Palette::ColorId::border),
                                    widget.color(Palette::ColorId::button_bg));
        }
    }

    if (!widget.on_text().empty())
    {
        Rect rect = b;
        rect.set_width(rect.width() / 2);
        rect.set_x(rect.x() + rect.width());

        if (widget.checked())
            painter.set(widget.color(Palette::ColorId::button_text).color());
        else
            painter.set(widget.color(Palette::ColorId::button_text, Palette::GroupId::disabled).color());
        painter.set(widget.font());
        auto size = painter.text_size(widget.on_text());
        Rect target = detail::align_algorithm(size,
                                              rect,
                                              alignmask::center);
        painter.draw(target.point());
        painter.draw(widget.on_text());
    }

    if (!widget.off_text().empty())
    {
        Rect rect = b;
        rect.set_width(rect.width() / 2);

        if (widget.checked())
            painter.set(widget.color(Palette::ColorId::button_text, Palette::GroupId::disabled).color());
        else
            painter.set(widget.color(Palette::ColorId::button_text, Palette::GroupId::disabled).color());
        painter.set(widget.font());
        auto size = painter.text_size(widget.off_text());
        Rect target = detail::align_algorithm(size,
                                              rect,
                                              alignmask::center);
        painter.draw(target.point());
        painter.draw(widget.off_text());
    }

}

Size ToggleBox::min_size_hint() const
{
    return Size(100, 30) + Widget::min_size_hint();
}

}
}
