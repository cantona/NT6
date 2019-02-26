// xiang.c
#include <ansi.h>
inherit ITEM;

void setup()
{}

void create()
{
        set_name(HIC"龍涎香"NOR, ({"longxian xiang","xiang" }));
        set("unit","塊");
        set("taskobj", 1);
        set("long","這是一塊黑紅色的東西，散發出奇異香氣,據説可以吸引毒蟲。\n");
        set("value", 0);
        set_weight(50);
        setup();
}
