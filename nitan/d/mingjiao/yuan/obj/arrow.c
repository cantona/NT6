// arrow.c

#include <weapon.h>
#include <ansi.h>

inherit THROWING; 

int is_arrow() { return 1; }

void create()
{
        set_name(HIC "鳳尾箭" NOR, ({ "fengwei jian", "arrow" }) );
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "束");
                set("value", 0);
                set("base_unit", "支");
                set("base_weight", 300);
                set("base_value", 0);
                set("wound_percent", 100); 
                set("material", "iron");
                set("long", "這是鳳尾箭，可以連珠箭發，勢道十分兇猛。\n");
        }
        set_amount(20);
        init_throwing(300); 
        set("no_wield", "這不是用來裝備的。\n"); 
        setup();
}