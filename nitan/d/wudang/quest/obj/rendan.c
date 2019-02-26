// rendan.c
// Modified by haiyan

#include <ansi.h> 
inherit ITEM; 

void create() 
{ 
     set_name(HIG"仁丹"NOR, ({"ren dan", "dan"}));
     set("unit", "粒"); 
     set("long", "這是一顆泛着淡綠色光芒的藥丸，由妖魔的精氣凝聚而成。\n"); 
     set("no_drop", "這樣東西不能離開你。\n"); 
     set("no_sell", "這樣東西不能離開你。\n"); 
     set("no_put", "這樣東西不能放在那兒。\n"); 
     set("no_get", "這樣東西不能離開那兒。\n"); 
     set("no_steal", "這樣東西不能離開那兒。\n"); 
     set("no_beg", "這樣東西不能離開那兒。\n"); 
     set("only_do_effect", 1);
     setup(); 
} 

int do_effect(object me) 
{ 
    mapping my; 
    message_vision("$N一仰脖，吞下一粒" +HIG+ "仁丹。\n" NOR, me); 
    my = me->query_entire_dbase();
    switch (random(5))
    {  
         case 0:  
                write(HIY"你感覺全身一陣炙熱，一股內力流入丹田。\n"NOR); 
                addn("max_neili", 1+random(5), me);
                break;  
         case 1:  
                write(HIG"你感覺全身説不出的舒服受用。\n"NOR);
                my["eff_jing"] = my["max_jing"]; 
                my["jing"] = my["max_jing"]; 
                break;  
         case 2:  
                write(HIG"你感覺全身説不出的舒服受用。\n"NOR);
                my["eff_qi"] = my["max_qi"]; 
                my["qi"] = my["max_qi"]; 
                break;  
         case 3:
                write(HIC"你感覺味道還不錯。\n"NOR);
                my["food"] = me->max_food_capacity(); 
                my["water"] = me->max_water_capacity(); 
                break;  
         default: 
                write(HIC"你吞得太快，什麼味道也沒有嚐出來。\n"NOR);
                break;  
    } 
    destruct(this_object()); 
    return 1; 
} 
