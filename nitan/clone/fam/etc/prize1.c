#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIW "□角□之角" NOR, ({ "unicorn horn", "unicorn", "horn" }));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "□角□的角，似乎可以□□好□□。\n" NOR);
                set("unit", "根");
                set("value", 700000);
        }
        setup();
}