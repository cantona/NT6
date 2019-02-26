#include <ansi.h>   
inherit TASK;  
void create()   
{ 
    set_name(HIW"太極劍經"NOR, ({ "tjjj" }) );   
    set_weight(1);  
         if( clonep() ) 
            destruct(this_object());   
    else { 
        set("unit", "本");  
        set("material", "book"); 
        set("long", "張三丰自創武功太極劍的心法。\n");   
     } 
     set("owner", "張三丰"); 
        setup();  
}
