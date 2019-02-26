// 玄兵聖水用於開孔兵器

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIW "玄兵聖水" NOR, ({ "bored water", "water" }) );
        set_weight(30);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "一瓶瑩剔透聖水，散射出絢目的光彩。\n"
                            "他可以用來最大化開孔兵器或防具。\n" NOR);
                set("value", 1);
                set("no_sell", 1);
                set("unit", "瓶");
        }

        setup();
}

int query_autoload()
{
        return 1;
}
