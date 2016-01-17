#ifndef VSX_WIDGET_SEQUENCE_TREE_H
#define VSX_WIDGET_SEQUENCE_TREE_H

#include <widgets/vsx_widget_base_edit.h>
#include <widgets/vsx_widget_popup_menu.h>
#include <dialogs/dialog_query_string.h>

class vsx_widget_sequence_tree :
    public vsx_widget_editor
{
  vsx_widget_sequence_editor* sequence_editor;
  vsx_widget* save_dialog;

public:

  void set_sequence_editor( vsx_widget_sequence_editor* editor )
  {
    sequence_editor = editor;
  }

  void extra_init()
  {
    editor->enable_syntax_highlighting = false;
    editor->mirror_mouse_double_click_object = this;
    coord_type = VSX_WIDGET_COORD_CORNER;
    set_pos(vsx_vector3<>(size.x/2,size.y/2)-dragborder*2);
    editor->set_font_size(0.008f);
    size_from_parent = true;
    editor->editing_enabled = false;
    editor->selected_line_highlight = true;
    editor->enable_syntax_highlighting = false;
    editor->enable_line_action_buttons = true;
    pos_from_parent = true;

    editor->menu = editor->add(new vsx_widget_popup_menu,".sequencer_list_menu");
    editor->menu->commands.adds(VSX_COMMAND_MENU, "save selected sequence to disk...", "menu_save","");
    editor->menu->size.x = 0.2;
    editor->menu->init();
  }

  void init_2d()
  {
    save_dialog = add
    (
      new dialog_query_string(
          "Perform Operation",
          "Filename"
      ),
      "save"
    );
    save_dialog->set_render_type( render_2d );
    save_dialog->init();
  }

  void event_mouse_double_click(vsx_widget_distance distance,vsx_widget_coords coords,int button)
  {
    VSX_UNUSED(distance);
    VSX_UNUSED(coords);
    VSX_UNUSED(button);

    sequence_editor->toggle_channel_visible(
      editor->get_line( editor->selected_line )
    );
  }

  vsx_string<> get_selected_component()
  {
    vsx_nw_vector< vsx_string<> > parts;
    vsx_string_helper::explode_single(editor->get_line( editor->selected_line ),':',parts);
    return parts[0];
  }

  vsx_string<> get_selected_parameter()
  {
    vsx_nw_vector< vsx_string<> > parts;
    vsx_string_helper::explode_single(editor->get_line( editor->selected_line ),':',parts);
    return parts[1];
  }

  void command_process_back_queue(vsx_command_s *t)
  {
    if (t->cmd == "menu_save")
      return (void)dynamic_cast<dialog_query_string*>(save_dialog)->show();
    vsx_widget::command_process_back_queue(t);
  }


};


#endif // VSX_WIDGET_SEQUENCE_TREE_H