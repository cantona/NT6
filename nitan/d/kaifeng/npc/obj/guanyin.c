#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(YEL "千手觀音神像" NOR, ({ "xiang" }) );
        set_weight(500000);
        set_max_encumbrance(800);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "座");
                set("long", "從身上伸出一千隻手，每隻手掌上都有一隻眼睛。\n");
                set("value", 50);
        }
}