/**
* Project: VSXu: Realtime modular visual programming engine.
*
* This file is part of Vovoid VSXu.
*
* @author Jonatan Wallmander, Robert Wenzel, Vovoid Media Technologies AB Copyright (C) 2003-2013
* @see The GNU Lesser General Public License (LGPL)
*
* VSXu Engine is free software; you can redistribute it and/or modify
* it under the terms of the GNU Lesser General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful, but
* WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
* or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License
* for more details.
*
* You should have received a copy of the GNU Lesser General Public License along
* with this program; if not, write to the Free Software Foundation, Inc.,
* 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/


class module_quaternion_mul : public vsx_module {
  // in
  vsx_module_param_quaternion* quat_a;
  vsx_module_param_quaternion* quat_b;

  // out
  vsx_module_param_quaternion* result_quat;

  // internal
  vsx_quaternion q1,q2,q_out;

public:

  void module_info(vsx_module_info* info)
  {
    info->identifier =
      "maths;arithmetics;quaternion;quat_mul";

    info->description =
      "Rotate quaternion a by quaternion b";

    info->out_param_spec =
      "result_quat:quaternion";

    info->in_param_spec =
      "quat_a:quaternion,"
      "quat_b:quaternion"
    ;

    info->component_class = "parameters";
  }


  void declare_params(vsx_module_param_list& in_parameters, vsx_module_param_list& out_parameters)
  {
    loading_done = true;
    q_out.x = q_out.y = q_out.z = 0.0f;
    q_out.w = 1.0f;

    //--------------------------------------------------------------------------------------------------

    quat_a = (vsx_module_param_quaternion*)in_parameters.create(VSX_MODULE_PARAM_ID_QUATERNION, "quat_a");
    quat_a->set(0.0f, 0);
    quat_a->set(0.0f, 1);
    quat_a->set(0.0f, 2);
    quat_a->set(1.0f, 3);

    quat_b = (vsx_module_param_quaternion*)in_parameters.create(VSX_MODULE_PARAM_ID_QUATERNION, "quat_b");
    quat_b->set(0.0f, 0);
    quat_b->set(0.0f, 1);
    quat_b->set(0.0f, 2);
    quat_b->set(1.0f, 3);

    //--------------------------------------------------------------------------------------------------

    result_quat = (vsx_module_param_quaternion*)out_parameters.create(VSX_MODULE_PARAM_ID_QUATERNION,"result_quat");
    result_quat->set(0.0f,0);
    result_quat->set(0.0f,1);
    result_quat->set(0.0f,2);
    result_quat->set(1.0f,3);
  }

  void run()
  {
    q1.x = quat_a->get(0);
    q1.y = quat_a->get(1);
    q1.z = quat_a->get(2);
    q1.w = quat_a->get(3);
    q1.normalize();

    q2.x = quat_b->get(0);
    q2.y = quat_b->get(1);
    q2.z = quat_b->get(2);
    q2.w = quat_b->get(3);
    q2.normalize();

    q_out.mul(q1, q2);

    result_quat->set(q_out.x,0);
    result_quat->set(q_out.y,1);
    result_quat->set(q_out.z,2);
    result_quat->set(q_out.w,3);
  }

};
