// rumor.c

#include <ansi.h>

inherit ITEM;
inherit F_AUTOLOAD;

void setup()
{}

void create()
{
        set_name(HIM "謠言生成器" NOR, ({"rumor generator", "rumor"}));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "架");
                set("long", "這是一架看起來怪怪的儀器，塗得五顏六色，專供各類長舌人士造謠使用。\n");
                set("value", 1);
                set("no_sell", 1);
        }
        setup();
}

int query_autoload()
{
        return 1;
}