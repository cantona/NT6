#include <ansi.h> 
inherit TASK; 
void create() 
{ 
    set_name(HIR"渾天寶鑒"NOR, ({ "book", "book" }) ); 
    set_weight(1); 
    if( clonep() ) 
            destruct(this_object()); 
    else { 
            set("unit", "本"); 
            set("material", "book"); 
            set("long", "一本寫著渾天寶鑒內功的秘籍。\n"); 
         }
    set("owner", "南賢"); 
    setup();
}
