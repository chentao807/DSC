//
//  Deformabel Simplicial Complex (DSC) method
//  Copyright (C) 2013  Technical University of Denmark
//
//  This program is free software: you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation, either version 3 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  See licence.txt for a copy of the GNU General Public License.

#pragma once

#include "velocity_function.h"


/**
 A rotating velocity function.
 */
class RotateFunc: public DSC::VelocityFunc<>
{
    
    
public:
    /**
     Creates a rotating velocity function.
     */
    RotateFunc(DSC::real velocity, DSC::real accuracy, int max_time_steps = 500):
        VelocityFunc<>(M_PI*velocity/(5.*180.), accuracy, max_time_steps)
    {
        
    }
    
    /**
     Returns the name of the velocity function.
     */
    virtual std::string get_name() const
    {
        return std::string("ROTATE MOTION");
    }
    
    /**
     Computes the motion of each interface vertex and stores the new position in new_pos in the simplicial complex class.
     */
    virtual void deform(DSC::DeformableSimplicialComplex<>& dsc)
    {
        auto init_time = std::chrono::system_clock::now();
        
        DSC::vec3 center = dsc.get_center();
        DSC::mat3 mrot = rotation_Mat3x3d(CGLA::Axis::ZAXIS, VELOCITY);
        DSC::vec3 new_pos;
        for(auto nit = dsc.nodes_begin(); nit != dsc.nodes_end(); nit++)
        {
            if(nit->is_interface() && !nit->is_crossing())
            {
                DSC::vec3 new_pos = center + mrot * (dsc.get_pos(nit.key()) - center);
                dsc.set_destination(nit.key(), new_pos);
            }
        }
        update_compute_time(init_time);
        init_time = std::chrono::system_clock::now();
        
        dsc.deform();
        
        update_deform_time(init_time);
    }
    
    /**
     Returns wether the motion has finished.
     */
    virtual bool is_motion_finished()
    {
        return false;
    }
    
};
