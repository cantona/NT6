// zheng.c

#include <ansi.h>
#include <music.h>

inherit ITEM;
inherit MI_ZHENG;

void create()
{
        set_name("古箏", ({ "gu zheng", "gu", "zheng" }));
        set_weight(300);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "台");
                set("long", YEL "這是一台看上去有些陳舊的古箏。\n" NOR);
                set("value", 50);
                set("material", "wood");
        }
        setup();
}

void init()
{
        add_action("play_zheng", "play");
}