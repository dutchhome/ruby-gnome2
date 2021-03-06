/* -*- c-file-style: "ruby"; indent-tabs-mode: nil -*- */
/*
 *  Copyright (C) 2014-2015  Ruby-GNOME2 Project Team
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

#include "rb-gio2.h"

#define RG_TARGET_NAMESPACE rb_mGio

static gboolean
name_equal(GIArgInfo *info, const gchar *target_name)
{
    GITypeInfo type_info;
    GIBaseInfo *interface_info;
    const gchar *namespace;
    const gchar *name;
    gboolean equal_name_p = FALSE;

    g_arg_info_load_type(info, &type_info);
    interface_info = g_type_info_get_interface(&type_info);
    namespace = g_base_info_get_namespace(interface_info);
    name = g_base_info_get_name(interface_info);
    if (strcmp(namespace, "Gio") == 0 && strcmp(name, target_name) == 0) {
        equal_name_p = TRUE;
    }
    g_base_info_unref(interface_info);

    return equal_name_p;
}

static void
rb_gio2_async_ready_callback_callback(GObject *source_object,
                                      GAsyncResult *result,
                                      gpointer user_data)
{
    RBGICallbackData *callback_data = user_data;
    ID id_call;

    CONST_ID(id_call, "call");
    rb_funcall(callback_data->rb_callback, id_call, 2,
               GOBJ2RVAL(source_object), GOBJ2RVAL(result));
}

static gpointer
rb_gio2_async_ready_callback_finder(GIArgInfo *info)
{
    if (!name_equal(info, "AsyncReadyCallback")) {
        return NULL;
    }
    return rb_gio2_async_ready_callback_callback;
}

void
Init_gio2 (void)
{
    VALUE RG_TARGET_NAMESPACE;

    RG_TARGET_NAMESPACE = rb_define_module("Gio");

    rb_gio2_init_application(RG_TARGET_NAMESPACE);
    rb_gio2_init_pollable_source(RG_TARGET_NAMESPACE);

    rb_gi_callback_register_finder(rb_gio2_async_ready_callback_finder);
}
