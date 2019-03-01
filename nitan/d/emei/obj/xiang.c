#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(YEL "普賢菩薩像" NOR, ({ "xiang" }));
        set_weight(500000);
        set_max_encumbrance(800);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "座");
                set("long", YEL "這是一尊普賢菩薩像，坐八寶蓮花，神聖莊嚴。"
                            "不過這尊菩薩\n像看起來似乎曾有被移動(move)過的"
                            "痕跡。\n" NOR);
                set("value", 50);
        }
}
