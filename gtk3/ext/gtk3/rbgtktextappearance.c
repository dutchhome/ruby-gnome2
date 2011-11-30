/* -*- c-file-style: "ruby"; indent-tabs-mode: nil -*- */
/*
 *  Copyright (C) 2011  Ruby-GNOME2 Project Team
 *  Copyright (C) 2004  Masao Mutoh
 *
 *  This library is free software; you can redistribute it and/or
 *  modify it under the terms of the GNU Lesser General Public
 *  License as published by the Free Software Foundation; either
 *  version 2.1 of the License, or (at your option) any later version.
 *
 *  This library is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 *  Lesser General Public License for more details.
 *
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; if not, write to the Free Software
 *  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 *  MA  02110-1301  USA
 */

#include "global.h"

/*****************************************/
static GtkTextAppearance*
app_copy(const GtkTextAppearance* app)
{
  GtkTextAppearance* new_app;
  g_return_val_if_fail (app != NULL, NULL);
  new_app = g_new(GtkTextAppearance, 1);
  *new_app = *app;
  return new_app;
}

GType
gtk_text_appearance_get_type(void)
{
  static GType our_type = 0;
  if (our_type == 0)
    our_type = g_boxed_type_register_static ("GtkTextAppearance",
                    (GBoxedCopyFunc)app_copy,
                    (GBoxedFreeFunc)g_free);
  return our_type;
}
/*****************************************/

#define RG_TARGET_NAMESPACE cTextAppearance
#define _SELF(t) ((GtkTextAppearance*)RVAL2BOXED(t, GTK_TYPE_TEXT_APPEARANCE))

static VALUE
rg_initialize(VALUE self)
{
    GtkTextAppearance* app = ALLOC(GtkTextAppearance);
    memset(app, 0, sizeof(GtkTextAppearance));
    G_INITIALIZE(self, app);
    return Qnil;
}

static VALUE
txt_app_color_bg_color(VALUE self)
{
    VALUE val = BOXED2RVAL(&_SELF(self)->bg_color, GDK_TYPE_COLOR);
    G_CHILD_SET(self, rb_intern("bg_color"), val);
    return val;
}

static VALUE
txt_app_color_set_bg_color(VALUE self, VALUE val)
{
    G_CHILD_SET(self, rb_intern("bg_color"), val);
    _SELF(self)->bg_color = *RVAL2GDKCOLOR(val);
    return self;
}

static VALUE
txt_app_color_fg_color(VALUE self)
{
    VALUE val = BOXED2RVAL(&_SELF(self)->fg_color, GDK_TYPE_COLOR);
    G_CHILD_SET(self, rb_intern("fg_color"), val);
    return val;
}

static VALUE
txt_app_color_set_fg_color(VALUE self, VALUE val)
{
    G_CHILD_SET(self, rb_intern("fg_color"), val);
    _SELF(self)->fg_color = *RVAL2GDKCOLOR(val);
    return self;
}

/* deprecated
static VALUE
txt_app_gobj_bg_stipple(VALUE self)
{
    VALUE val;
    if (_SELF(self)->bg_stipple == NULL) return Qnil;
    val = GOBJ2RVAL(_SELF(self)->bg_stipple);
    G_CHILD_SET(self, rb_intern("bg_stipple"), val);
    return val;
}

static VALUE
txt_app_gobj_set_bg_stipple(VALUE self, VALUE val)
{
    _SELF(self)->bg_stipple = RVAL2GOBJ(val);
    G_CHILD_SET(self, rb_intern("bg_stipple"), val);
    return self;
}

static VALUE
txt_app_gobj_fg_stipple(VALUE self)
{
    VALUE val;
    if (_SELF(self)->fg_stipple == NULL) return Qnil;
    val = GOBJ2RVAL(_SELF(self)->fg_stipple);
    G_CHILD_SET(self, rb_intern("fg_stipple"), val);
    return val;
}

static VALUE
txt_app_gobj_set_fg_stipple(VALUE self, VALUE val)
{
    _SELF(self)->fg_stipple = RVAL2GOBJ(val);
    G_CHILD_SET(self, rb_intern("fg_stipple"), val);
    return self;
}
*/

static VALUE
txt_app_int_rise(VALUE self)
{
    return INT2NUM(_SELF(self)->rise);
}

static VALUE
txt_app_int_set_rise(VALUE self, VALUE val)
{
    _SELF(self)->rise = NUM2INT(val);
    return self;
}

static VALUE
txt_app_enums_underline(VALUE self)
{
    return GENUM2RVAL(_SELF(self)->underline, PANGO_TYPE_UNDERLINE);
}

static VALUE
txt_app_enums_set_underline(VALUE self, VALUE val)
{
    _SELF(self)->underline = RVAL2GENUM(val, PANGO_TYPE_UNDERLINE);
    return self;
}

static VALUE
txt_app_bool_strikethrough(VALUE self)
{
    return CBOOL2RVAL(_SELF(self)->strikethrough);
}

static VALUE
txt_app_bool_set_strikethrough(VALUE self, VALUE val)
{
    _SELF(self)->strikethrough = RVAL2CBOOL(val);
    return self;
}

static VALUE
txt_app_bool_draw_bg(VALUE self)
{
    return CBOOL2RVAL(_SELF(self)->draw_bg);
}

static VALUE
txt_app_bool_set_draw_bg(VALUE self, VALUE val)
{
    _SELF(self)->draw_bg = RVAL2CBOOL(val);
    return self;
}

static VALUE
txt_app_bool_inside_selection(VALUE self)
{
    return CBOOL2RVAL(_SELF(self)->inside_selection);
}

static VALUE
txt_app_bool_set_inside_selection(VALUE self, VALUE val)
{
    _SELF(self)->inside_selection = RVAL2CBOOL(val);
    return self;
}

static VALUE
txt_app_bool_is_text(VALUE self)
{
    return CBOOL2RVAL(_SELF(self)->is_text);
}

static VALUE
txt_app_bool_set_is_text(VALUE self, VALUE val)
{
    _SELF(self)->is_text = RVAL2CBOOL(val);
    return self;
}

void
Init_gtk_text_appearance(VALUE mGtk)
{
    VALUE RG_TARGET_NAMESPACE = G_DEF_CLASS(GTK_TYPE_TEXT_APPEARANCE, "TextAppearance", mGtk);

    RG_DEF_METHOD(initialize, 0);
    rb_define_method(RG_TARGET_NAMESPACE, "bg_color", txt_app_color_bg_color, 0);
    rb_define_method(RG_TARGET_NAMESPACE, "set_bg_color", txt_app_color_set_bg_color, 1);
    rb_define_method(RG_TARGET_NAMESPACE, "fg_color", txt_app_color_fg_color, 0);
    rb_define_method(RG_TARGET_NAMESPACE, "set_fg_color", txt_app_color_set_fg_color, 1);
/* deprecated
    rb_define_method(RG_TARGET_NAMESPACE, "bg_stipple", txt_app_gobj_bg_stipple, 0);
    rb_define_method(RG_TARGET_NAMESPACE, "set_bg_stipple", txt_app_gobj_set_bg_stipple, 1);
    rb_define_method(RG_TARGET_NAMESPACE, "fg_stipple", txt_app_gobj_fg_stipple, 0);
    rb_define_method(RG_TARGET_NAMESPACE, "set_fg_stipple", txt_app_gobj_set_fg_stipple, 1);
*/
    rb_define_method(RG_TARGET_NAMESPACE, "rise", txt_app_int_rise, 0);
    rb_define_method(RG_TARGET_NAMESPACE, "set_rise", txt_app_int_set_rise, 1);
    rb_define_method(RG_TARGET_NAMESPACE, "underline", txt_app_enums_underline, 0);
    rb_define_method(RG_TARGET_NAMESPACE, "set_underline", txt_app_enums_set_underline, 1);

    rb_define_method(RG_TARGET_NAMESPACE, "strikethrough?", txt_app_bool_strikethrough, 0);
    rb_define_method(RG_TARGET_NAMESPACE, "set_strikethrough", txt_app_bool_set_strikethrough, 1);
    rb_define_method(RG_TARGET_NAMESPACE, "draw_bg?", txt_app_bool_draw_bg, 0);
    rb_define_method(RG_TARGET_NAMESPACE, "set_draw_bg", txt_app_bool_set_draw_bg, 1);
    rb_define_method(RG_TARGET_NAMESPACE, "inside_selection?", txt_app_bool_inside_selection, 0);
    rb_define_method(RG_TARGET_NAMESPACE, "set_inside_selection", txt_app_bool_set_inside_selection, 1);
    rb_define_method(RG_TARGET_NAMESPACE, "text?", txt_app_bool_is_text, 0);
    rb_define_method(RG_TARGET_NAMESPACE, "set_text", txt_app_bool_set_is_text, 1);

    G_DEF_SETTERS(RG_TARGET_NAMESPACE);
}
