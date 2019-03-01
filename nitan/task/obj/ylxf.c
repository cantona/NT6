#include <ansi.h>  
inherit TASK;  
void create()  
{
    set_name(HIG"雲龍心法"NOR, ({ "ylxf" }) );  
    set_weight(1); 
    if( clonep() ) 
            destruct(this_object());  
    else {
            set("unit", "本");  
            set("material", "paper");  
            set("long", "雲龍門的內功心法。\n");  
      } 
      set("owner", "陳近南"); 
        setup();
}
