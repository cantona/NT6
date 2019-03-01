#include <weapon.h>
#include <ansi.h>
inherit THROWING;
void create()
{
        set_name("鐵蒺藜", ({ "tie jili", "jili" }) );
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("value",1000);
                set("base_unit", "顆");
                set("base_weight", 100);
                set("base_value", 40);
                set("material", "steel");
                set("long", "一顆有芒刺的鐵球。\n");
                
        }
       set_amount(25);
       init_throwing(10);
       setup();
}