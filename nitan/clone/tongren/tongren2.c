#include <ansi.h>

#include "tr.h"

int query_tongren() { return 2; }
void create()
{
        set_name(YEL "無名大銅人" NOR, ({ "wuming tongren", "wuming", "tongren" }));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("base_unit", "個"); 
                set("long", YEL "這是一個破舊的銅人，上面繪制了一些圖案，但是已經無法辯識。\n" NOR);
                //set("long", NOR + YEL "這裡是一個沖穴銅人，上面刻有經絡穴位圖，可習得經絡學。\n" NOR);
                set("value", 10000);
                set("material", "steal");
                set("no_identify", 1);

                set("skill", ([
                        "name"         : "jingluo-xue",
                        "exp_required" : 500000,
                        "jing_cost"    : 150,
                        "difficulty"   : 30,
                        "max_skill"    : 99,
                        "min_skill"    : 0
                ]));
        }
        setup();
}

