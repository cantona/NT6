#include <ansi.h> 
inherit TASK; 
void create() 
{ 
    set_name(MAG"道德經"NOR, ({ "daode jing" }) ); 
    set_weight(10); 
    if( clonep() ) 
            destruct(this_object()); 
    else { 
            set("unit", "本"); 
            set("material", "book"); 
            set("long", "一本道德經書。\n"); 
        }
    set("owner", "谷虛道長"); 
    setup(); 
}
