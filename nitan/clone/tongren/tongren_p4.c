#include <ansi.h>

inherit ITEM;

int is_tongren() { return 1; }
void create()
{
        set_name(YEL "衝穴銅人·足少陰脈·湧泉穴" NOR, ({ "tongren p4", "tongren" }));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("long", NOR + YEL "這是一個衝穴銅人，上面繪製了一些經絡穴位圖案，以及衝穴使用方法。\n" NOR);
                set("value", 10000);
                set("material", "steal");
        }
        set("jingmai_name", "足少陰脈");
        set("xuewei_name", "湧泉穴");
        set("chongxue_xiaoguo", "POT:20:JIALI:10");
        set("neili_cost", "4000");
        setup();
}

