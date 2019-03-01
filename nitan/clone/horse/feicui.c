inherit "/clone/horse/horse.c";
#include <ansi.h>

void create()
{
        set_name(HIG "翡翠駒" NOR, ({ "feicui ju"}));
        set("long", HIG "據說翡翠駒產自四川，腳力不錯　。\n" NOR);

        set("tili", 1000);
        set("max_tili", 1000);
        set("level", 1);

        setup();
}
