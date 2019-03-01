#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(HIM "龍涎香" NOR, ({"longxian xiang", "longxian", "xiang"}));
        set("unit", "塊");
        set("long", HIM "這是一塊黑紅色的東西，散發出奇異香氣。\n" NOR);
        set("value", 1000);
        set_weight(50);
        setup();
}