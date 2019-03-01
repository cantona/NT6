#include <ansi.h> 
inherit TASK; 
void create() 
{ 
    set_name(HIW"倚天屠龍秘籍"NOR, ({ "mi ji", "miji" }) ); 
    set_weight(1); 
    if( clonep() ) 
            destruct(this_object()); 
    else { 
            set("unit", "本"); 
            set("material", "book"); 
            set("long", "一本倚天劍和屠龍刀裡的秘籍。\n"); 
         }
    set("owner", "周芷若"); 
    setup();
}
