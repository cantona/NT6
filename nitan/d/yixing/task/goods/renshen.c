// /d/yixing/task/goods/renshen.c 人蔘
// Last Modified by winder on Jul. 12 2002

inherit ITEM;
#include <ansi.h>

void create()
{
        set_name("長白山人蔘", ({"renshen", "shen"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "株");
                set("long", "這是一株沾滿山泥的長白山人蔘。\n");
                set("value", 10000);
                set("medicine", 1);
        }
        setup();
}