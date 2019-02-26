#include <ansi.h>
#include <music.h>

inherit ITEM;
inherit MI_QIN;

void create()
{
        set_name(RED "紅木胡琴·五玄" NOR, ({ "hongmu huqin", "qin", "huqin", "hongmu" }));
        set_weight(800);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", RED "一把精緻的紅木胡琴，琴身光滑，微泛紅光。\n" NOR);
                set("value", 2000);
                set("material", "wood");
        }
        setup();
}

void init()
{
        add_action("play_qin", "play");
}