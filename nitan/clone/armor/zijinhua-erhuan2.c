
#include <armor.h>
#include <ansi.h>

inherit EARRING;

void create()
{
        set_name(HIR "紫金花耳環" NOR, ({ "zijinhua erhuan2", "zijinhua", "erhuan2" }));
        set_weight(100);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "副");
                set("value", 200000);
                set("material", "silver");
                set("armor_prop/armor", 1);
                set("armor_prop/dex", 8);
                set("limit", ([
                        "sex" : 1, // 1 為女性
                ]));
        }
        setup();
}        

int query_autoload()
{
        return 1;
}