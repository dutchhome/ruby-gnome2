/* -*- c-file-style: "ruby"; indent-tabs-mode: nil -*- */
/************************************************

  rbgtkvpaned.c -

  $Author: mutoh $
  $Date: 2003/02/01 16:46:24 $

  Copyright (C) 2002,2003 Ruby-GNOME2 Project Team
  Copyright (C) 1998-2000 Yukihiro Matsumoto,
                          Daisuke Kanda,
                          Hiroshi Igarashi
************************************************/

#include "global.h"

static VALUE
vpaned_initialize(self)
    VALUE self;
{
    RBGTK_INITIALIZE(self, gtk_vpaned_new());
    return Qnil;
}

void 
Init_gtk_vpaned()
{
    VALUE gVPaned = G_DEF_CLASS(GTK_TYPE_VPANED, "VPaned", mGtk);

    rb_define_method(gVPaned, "initialize", vpaned_initialize, 0);
}
