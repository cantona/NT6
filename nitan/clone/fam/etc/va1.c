#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(NOR + YEL "金塊" NOR, ({ "jin kuai", "jin", "kuai" }));
        set_weight(2000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", NOR + YEL "這是一錠黃澄澄的金塊，相信"
                            "可以賣個好價錢。\n");
                set("value", 150000);
                set("unit", "錠");
        }
}