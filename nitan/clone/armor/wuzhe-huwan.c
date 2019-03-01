#include <ansi.h>
#include <armor.h>

inherit WRISTS;

void create()
{
        set_name(HIM "武者護腕" NOR, ({ "wuzhe huwan", "wuzhe", "huwan" }));
        set_weight(800);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIM "一雙武士用的護腕。\n" NOR);;
                set("unit", "雙");
                set("value", 500000);
                set("armor_prop/armor", 200);
                set("limit", ([
                        "exp"    :    500000,
                        "str"    :    20,
                        "int"    :    20,
                ]));                
        }
        setup();
}

int query_autoload()
{
        return 1;
}
