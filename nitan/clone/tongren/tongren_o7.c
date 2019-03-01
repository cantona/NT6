#include <ansi.h>

inherit ITEM;

int is_tongren() { return 1; }
void create()
{
        set_name(YEL "沖穴銅人﹒手少陽脈﹒關沖穴" NOR, ({ "tongren o7", "tongren" }));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("long", NOR + YEL "這是一個沖穴銅人，上面繪制了一些經絡穴位圖案，以及沖穴使用方法。\n" NOR);
                set("value", 10000);
                set("material", "steal");
        }
        set("jingmai_name", "手少陽脈");
        set("xuewei_name", "關沖穴");
        set("chongxue_xiaoguo", "JING:50:JIALI:30");
        set("neili_cost", "1000");
        setup();
}

