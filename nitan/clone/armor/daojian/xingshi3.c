
#include <armor.h>
#include <ansi.h>

inherit RINGS;

void create()
{
        set_name(HIY "天降﹒醒世環" NOR, ({ "xingshi huan3" }));
        set_weight(30);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "枚");
                set("long", HIY "傳說中狐仙所佩帶的指環。\n" NOR);
                set("value", 200000);
                set("material", "gold");
                set("armor_prop/con", 30);
                set("armor_prop/damage", 3000);
                set("armor_prop/unarmed", 150);
                set("armor_prop/magic_find", 10);
                set("special/desc", "有效拳法等級提高150級。\n"+
                                    "有效拳腳等級提高150級。\n"+
                                    "有效掌法等級提高150級。\n"+
                                    "有效指法等級提高150級。\n"
                );
                set("limit", ([ 
                         "exp" : 100000000,
                         "scborn" : 1,
                ]));

        }
        setup();
}

int query_autoload()
{
        return 1;
}
