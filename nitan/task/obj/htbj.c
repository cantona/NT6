#include <ansi.h> 
inherit TASK; 
void create() 
{ 
    set_name(HIR"渾天寶鑑"NOR, ({ "book", "book" }) ); 
    set_weight(1); 
    if( clonep() ) 
            destruct(this_object()); 
    else { 
            set("unit", "本"); 
            set("material", "book"); 
            set("long", "一本寫着渾天寶鑑內功的祕籍。\n"); 
         }
    set("owner", "南賢"); 
    setup();
}
