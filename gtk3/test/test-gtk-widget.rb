# Copyright (C) 2008-2015  Ruby-GNOME2 Project Team
#
# This library is free software; you can redistribute it and/or
# modify it under the terms of the GNU Lesser General Public
# License as published by the Free Software Foundation; either
# version 2.1 of the License, or (at your option) any later version.
#
# This library is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
# Lesser General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public
# License along with this library; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

class TestGtkWidget < Test::Unit::TestCase
  include GtkTestUtils

  def setup
    @widget = Gtk::Invisible.new
  end

  sub_test_case "class methods" do
    test ".style_properties" do
      assert_equal("cursor-aspect-ratio",
                   Gtk::Label.style_properties.collect(&:name).sort.first)
    end
  end

  def test_set_window
    attrs = Gdk::WindowAttr.new(100, 100, :input_only, :temp)
    window = Gdk::Window.new(nil, attrs, 0)
    @widget.window = window
    assert_equal(window, @widget.window)
  end

  def test_modify_color_component_with_nil_color
    assert_nothing_raised do
      @widget.override_color(:normal, nil)
    end

    assert_nothing_raised do
      @widget.override_background_color(:normal, nil)
    end
  end

  sub_test_case "#drag_source_set" do
    def setup
      only_gtk_version(3, 9, 16)
      super
    end

    test "targets - TargetEntry" do
      target = "text/uri-list"
      info = 0
      @widget.drag_source_set([:shift_mask, :control_mask],
                              [Gtk::TargetEntry.new(target, 0, info)],
                              :copy)
      list = @widget.drag_source_get_target_list
      assert_equal(info, list.find(target))
    end

    test "targets - Array" do
      target = "text/uri-list"
      info = 0
      @widget.drag_source_set([:shift_mask, :control_mask],
                              [[target, 0, info]],
                              :copy)
      list = @widget.drag_source_get_target_list
      assert_equal(info, list.find(target))
    end
  end

  sub_test_case "#drag_dest_set" do
    def setup
      only_gtk_version(3, 9, 16)
      super
    end

    test "targets - TargetEntry" do
      target = "text/uri-list"
      info = 0
      @widget.drag_dest_set(:all,
                            [Gtk::TargetEntry.new(target, 0, info)],
                            :copy)
      list = @widget.drag_dest_get_target_list
      assert_equal(info, list.find(target))
    end

    test "targets - Array" do
      target = "text/uri-list"
      info = 0
      @widget.drag_dest_set(:all,
                            [[target, 0, info]],
                            :copy)
      list = @widget.drag_dest_get_target_list
      assert_equal(info, list.find(target))
    end
  end

  sub_test_case "events" do
    def setup
      @widget = Gtk::EventBox.new
    end

    test "get" do
      assert_equal(Gdk::EventMask.new(0), @widget.events)
    end

    test "add" do
      @widget.add_events([:exposure_mask, :pointer_motion_mask])
      assert_equal(Gdk::EventMask::EXPOSURE_MASK |
                   Gdk::EventMask::POINTER_MOTION_MASK,
                   @widget.events)
    end

    test "set" do
      @widget.set_events([:exposure_mask, :pointer_motion_mask])
      assert_equal(Gdk::EventMask::EXPOSURE_MASK |
                   Gdk::EventMask::POINTER_MOTION_MASK,
                   @widget.events)
    end

    test "assign" do
      @widget.events = [:exposure_mask, :pointer_motion_mask]
      assert_equal(Gdk::EventMask::EXPOSURE_MASK |
                   Gdk::EventMask::POINTER_MOTION_MASK,
                   @widget.events)
    end
  end

  test "#style_get_property" do
    entry = Gtk::Entry.new
    assert do
      entry.style_get_property("focus-padding").is_a?(Integer)
    end
  end

  sub_test_case "predicates" do
    test "#in_destruction?" do
      entry = Gtk::Entry.new
      assert do
        not entry.in_destruction?
      end
    end
  end

  sub_test_case "#render_icon_pixbuf" do
    test "size: symbol" do
      window = Gtk::Window.new
      window.render_icon_pixbuf(:directory, :menu)
    end
  end

  sub_test_case ".bind_template_child" do
    setup do
      only_gtk_version(3, 10, 0)
      @resource_data = File.read(fixture_path("simple_window.ui"))
    end

    test "nothing" do
      data = @resource_data
      widget_class = Class.new(Gtk::Window) do
        type_register "BindTemplateChildNothing"

        singleton_class.send(:define_method, :init) do
          set_template(:data => data)
        end
      end
      widget = widget_class.new
      assert_nil(widget.get_template_child(widget_class, :label))
    end

    test "bind" do
      data = @resource_data
      widget_class = Class.new(Gtk::Window) do
        type_register "BindTemplateChildBind"

        singleton_class.send(:define_method, :init) do
          set_template(:data => data)
          bind_template_child(:label)
        end
      end
      widget = widget_class.new
      assert_equal(Gtk::Label,
                   widget.get_template_child(widget_class, :label).class)
    end
  end
end
