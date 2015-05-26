//
//  mjRandom.c
//  mjRandom
//
//  Created by Martin Jaroszewicz on 7/20/14.
//  Copyright (c) 2014 com.martinjaroszewicz. All rights reserved.
//

#include "m_pd.h"
#include <math.h>
#include <string.h>
#include <stdlib.h>

static t_class *mjRandom_class;

typedef struct _mjRandom {
	t_object x_obj;
	//local variables
	t_float i_num_points;
    t_float a_x[100];
	t_float a_y[100];
	t_float a_z[100];
	t_float f_seed;
    t_float f_input;
	t_outlet *l1_out, *l2_out, *l3_out,*l4_out;
} t_mjRandom;


void mjRandom_float(t_mjRandom *x, t_float f){
    
    int index = f*x->i_num_points;
    post("Incoming float %f with index %d",f, index);
    outlet_float(x->l1_out, x->a_x[index]);
    outlet_float(x->l2_out, x->a_y[index]);
    outlet_float(x->l3_out, x->a_z[index]);
    if (f == 0.999){ // a phasor never gets to 1 but this does not work
        outlet_bang(x->l4_out);//change seed here
    }
}

void mjRandom_bang(t_mjRandom *x){
    
    float seed = x->f_seed;
    int points = x->i_num_points;
    if (points > 100){
        post("Max number of points is 100");
        points = 100;
    }
    if (points < 0){
        post("Please provide a value between 0 and 100");
        points = 0;
    }
    int index;
    float m1[points];
    float m2[points];
    float m3[points];
    for (index = 0; index < points; index++){
        m1[index] = (float)rand() / (float)RAND_MAX;
        m2[index] = (float)rand() / (float)RAND_MAX;
        m3[index] = (float)rand() / (float)RAND_MAX;
        post("x[%d] = %f",index,m1[index]);
        post("y[%d] = %f",index,m2[index]);
        post("z[%d] = %f",index,m3[index]);
        x->a_x[index] = m1[index];
        x->a_y[index] = m2[index];
        x->a_z[index] = m3[index];
        
    }
}

void *mjRandom_new(t_floatarg f){
    
    t_mjRandom *x = (t_mjRandom *)pd_new(mjRandom_class);
    x->l1_out = outlet_new(&x->x_obj, &s_float);
    x->l2_out = outlet_new(&x->x_obj, &s_float);
    x->l3_out = outlet_new(&x->x_obj, &s_float);
    x->l4_out = outlet_new(&x->x_obj, &s_bang);
    floatinlet_new(&x->x_obj, &x->f_seed);
    floatinlet_new(&x->x_obj, &x->i_num_points);
    
    return (void *)x;
}

void mjRandom_setup(void) {
    mjRandom_class = class_new(gensym("mjRandom"),
    (t_newmethod)mjRandom_new,
            0, sizeof(t_mjRandom),
            CLASS_DEFAULT,
            A_DEFFLOAT, 0);
    class_addbang(mjRandom_class, mjRandom_bang);
    class_addfloat(mjRandom_class, mjRandom_float);
    
}
