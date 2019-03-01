inherit "/clone/horse/horse.c";
#include <ansi.h>

void create()
{
        set_name(HIC "爪黃飛電" NOR, ({ "zhuahuang feidian"}));
        set("long", HIC "乃三國時曹操的愛馬，奔跑如電，乃世間罕有。\n" NOR);

        set("tili", 3000);
        set("max_tili", 3000);
        set("level", 3);

        setup();
}
