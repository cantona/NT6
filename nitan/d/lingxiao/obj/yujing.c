// Obj: /d/lingxiao/obj/yujing.c
// Last Modified by winder on Jul. 15 2001

inherit ITEM;
#include <ansi.h>

void create()
{
        set_name(HIW"冰魄玉精"NOR, ({"bingpo yujing", "yujing"}));
        set_weight(80);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long","這是萬年寒玉所凝結而成的冰魄玉精，看上去潔白剔透，散發出綠幽幽的光芒。\n");
                set("unit", "塊");
                set("value", 70000);
        }
}

