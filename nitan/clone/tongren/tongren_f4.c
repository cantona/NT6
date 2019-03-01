#include <ansi.h>

inherit ITEM;

int is_tongren() { return 1; }
void create()
{
        set_name(YEL "沖穴銅人﹒沖脈﹒橫骨穴" NOR, ({ "tongren f4", "tongren" }));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("long", NOR + YEL "這是一個沖穴銅人，上面繪制了一些經絡穴位圖案，以及沖穴使用方法。\n" NOR);
                set("value", 10000);
                set("material", "steal");
        }
        set("jingmai_name", "沖脈");
        set("xuewei_name", "橫骨穴");
        set("chongxue_xiaoguo", "ATK:20");
        set("neili_cost", "1000");
        setup();
}
