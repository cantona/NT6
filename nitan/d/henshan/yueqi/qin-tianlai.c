#include <ansi.h>
#include <music.h>

inherit ITEM;
inherit MI_QIN;

void create()
{
        set_name(WHT "七玄流銀·天籟" NOR, ({ "tianlai qin", "tianlai", "qin" }));
        set_weight(1000);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", WHT "此琴通體泛出銀光，耀眼奪"
                                "目。上刻「" HIG "天籟" WHT "」。\n" NOR);
                set("value", 5000000);
                set("material", "wood");
        }
        setup();
}

void init()
{
        add_action("play_qin", "play");
}