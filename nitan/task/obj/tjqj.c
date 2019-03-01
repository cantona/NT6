#include <ansi.h>  
inherit TASK;  
void create()  
{
    set_name(HIW"太極拳經"NOR, ({ "tjqj" }) );  
    set_weight(1); 
    if( clonep() )
            destruct(this_object());  
    else {  
            set("unit", "本"); 
            set("material", "book");  
            set("long", "張三豐自創武功太極拳的心法。\n");  
      } 
      set("owner", "張三豐");  
        setup();  
}
