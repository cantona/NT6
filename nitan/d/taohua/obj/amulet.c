//Cracked by Kafei
// amulet.c 長命鎖
#include <ansi.h>
#include <armor.h>

inherit NECK;

void create()
{
        set_name("長命鎖", ({ "amulet" }));
        set("weight", 500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", "這是一串頗為精緻的長命鎖，不過已相當破舊，"+
                            "上面依稀刻了“長命百歲”幾個字，下面似乎有一個小小的“曲”字。\n");
                set("unit", "串");
                set("value", 1500);
                set("material", "gold");
                set("armor_prop/armor", 1);
        }
        setup();
}        