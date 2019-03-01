#include <ansi.h>
#include <music.h>

inherit ITEM;
inherit MI_QIN;

void create()
{
        set_name(YEL "十玄古琴﹒戰國" NOR, ({ "shixuan qin", "shixuan", "qin" }));
        set_weight(700);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", YEL "這是迄今能看到的中國最早的琴類樂器，此\n"
                                "琴埋于戰國曾候乙墓之中，琴長67公分，琴\n" 
                                "面起伏有致。\n" NOR);
                set("value", 100000);
                set("material", "wood");
        }
        setup();
}

void init()
{
        add_action("play_qin", "play");
}