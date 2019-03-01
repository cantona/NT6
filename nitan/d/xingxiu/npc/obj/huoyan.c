// Room: /d/xingxiu/npc/obj/huoyan.c
// Last Modified by winder on Feb. 17 2001

#include <ansi.h>;
inherit ITEM;
void create()
{
        set_name(HIR"火燄"NOR, ({ "huo yan"}) );
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long",HIR"火燄高約尺，色作純碧，鬼氣森森，和尋常火燄大異。\n"NOR );
                set("no_get", 1);
                set("value", 1);
                set("unit", "堆");
                set("fire_name", "火燄");
                set("weight", 30000);
                set("location", 1);
        }
        setup();
}

void init()
{
        if(base_name(environment(this_object()))!="/d/xingxiu/riyuedong")
        call_out("dest", 300);   
        remove_call_out("change");
        call_out("change", 50); 
}

string *fire_msg = ({BLU"火燄"NOR,RED"火燄"NOR,WHT"火燄"NOR,GRN"火燄"NOR,MAG"火燄"NOR});

void change()
{
        string msg = fire_msg[random(sizeof(fire_msg))];
        tell_room(environment(this_object()),this_object()->name()+ HIR"豁然一暗，接著火光爆長，竟然變了顏色，看起來怪異無比！\n"NOR);    
        set("name", msg, this_object());
        remove_call_out("change");
        call_out("change", 50);  
}
 
void dest()
{
        tell_room(environment(this_object()),HIR"火燄漸漸地熄滅了。\n"NOR);
        destruct(this_object());
}