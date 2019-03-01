#include <ansi.h>
inherit TASK; 
void create()
{
    set_name(HIR"淫穢圖"NOR, ({ "yinhui tu", "tu" }) ); 
    set_weight(1);
    if( clonep() ) 
            destruct(this_object()); 
    else { 
            set("unit", "張"); 
            set("material", "paper"); 
              set("long", "一張畫滿美女裸體的圖。\n"); 
       }
       set("owner", "血刀老祖"); 
       setup(); 
}
