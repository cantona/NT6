#include <ansi.h>

inherit ITEM;

int is_tongren() { return 1; }
void create()
{
        set_name(YEL "沖穴銅人﹒足太陽脈﹒玉枕穴" NOR, ({ "tongren m22", "tongren" }));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("long", NOR + YEL "這是一個沖穴銅人，上面繪制了一些經絡穴位圖案，以及沖穴使用方法。\n" NOR);
                set("value", 10000);
                set("material", "steal");
        }
        set("jingmai_name", "足太陽脈");
        set("xuewei_name", "玉枕穴");
        set("chongxue_xiaoguo", "POT:20");
        set("neili_cost", "12000");
        setup();
}
