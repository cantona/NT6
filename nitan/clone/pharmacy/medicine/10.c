#include <ansi.h>

inherit MEDICINE;

void create()
{
        set_name(RED"朱雀丹"NOR, ({"zhuque dan", "dan"}));
        set("unit", "顆");

        set("upgrade_stat", ([ "kee" : 20,
                               "sen" : 20 ]));
        set("apply_condition", ([ "drunk" : 20 ]));
        set("env_message", RED"$N取出一顆紅色的丸子，一仰頭吃了下去，頓時臉色變得紅火。");
        set("prv_message", HIR"你覺得腹內好象有火在燒，一股熱氣順著血行匯入了奇經百脈。");

        setup();
}
