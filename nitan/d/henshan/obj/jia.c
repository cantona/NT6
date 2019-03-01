#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIR "捕獸夾" NOR, ({ "bushou jia","jia", "bushou" }));
        set_weight(1000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("long", "這是專門用來捕捉各種禽獸的，夾齒鋒利無比。 \n");
                set("value", 1000);
                set("material", "iron");
        }

        setup();
}
