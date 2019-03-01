#include <ansi.h>

inherit ITEM;

int is_tongren() { return 1; }
void create()
{
        set_name(YEL "沖穴銅人﹒足太陽脈﹒意舍穴" NOR, ({ "tongren m57", "tongren" }));
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
        set("xuewei_name", "意舍穴");
        set("chongxue_xiaoguo", "JING:60:_INT:2");
        set("neili_cost", "600");
        setup();
}

