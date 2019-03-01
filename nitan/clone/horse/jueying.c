inherit "/clone/horse/horse.c";
#include <ansi.h>

void create()
{
        set_name(HIM "絕影無影" NOR, ({ "jueying wuying"}));
        set("long", HIM "絕影據說是大宛名馬，熬得痛，身上中了三箭竟然仍能奮蹄"
                        "疾馳，而且速度極快（絕影之名或許就是因為其速度快而得"
                        "的，意為其速度快的連影子都跟不上了），最後被流矢射中"
                        "眼睛才倒了下去。曹操再轉乘長子曹昂的馬逃跑，而絕影馬"
                        "便在這一戰中完成了其所有的使命。 \n" NOR);

        set("tili", 3000);
        set("max_tili", 3000);
        set("level", 3);

        setup();
}
