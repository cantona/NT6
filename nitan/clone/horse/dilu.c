inherit "/clone/horse/horse.c";
#include <ansi.h>

void create()
{
        set_name(HIG "的盧馬" NOR, ({ "dilu ma"}));
        set("long", HIG "此馬極其雄俊，奔跑有力，通人性，忠心。眼下有淚槽，額"
                        "上有白點，乃三國劉備的愛馬，曾數次助其脱險。\n" NOR);

        set("tili", 3000);
        set("max_tili", 3000);
        set("level", 3);

        setup();
}
