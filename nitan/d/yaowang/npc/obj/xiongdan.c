#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(BLU"熊膽"NOR, ({"xiong dan", "xiong"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "顆");
                set("long", "這是一顆黑熊膽。\n");
                set("yaowang", 1);
                set("value", 1000);
                set("weight", 1000);
        }
        setup();
}
