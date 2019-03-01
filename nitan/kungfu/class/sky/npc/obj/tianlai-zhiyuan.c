#include <ansi.h>
#include <music.h>

inherit ITEM;
inherit MI_QIN;

void create()
{
        set_name(HIY "天籟之源" NOR, ({ "tianlai zhiyuan", "tianlai", "zhiyuan" }));
        set_weight(1);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", HIY "此琴通體泛出七彩之光，耀眼奪目，乃天下第一琴。上刻「" HIC "天籟之源" HIY "」。\n" NOR);
                set("value", 5000000);
                set("material", "gold");
        }
        setup();
}

void init()
{
        add_action("play_qin", "play");
}
