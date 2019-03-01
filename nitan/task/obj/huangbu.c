#include <ansi.h> 
inherit TASK; 
void create()
{ 
    set_name(HIY"黃布" NOR, ({ "huangbu"}) ); 
    set_weight(1); 
    if( clonep() )
            destruct(this_object()); 
    else { 
            set("unit", "塊"); 
            set("material", "paper");
            set("long", "一塊黃色的布上面繡了幾個黑色的字。\n打遍天下無敵手。\n"); 
         } 
    set("owner", "苗人鳳"); 
    setup(); 
}
