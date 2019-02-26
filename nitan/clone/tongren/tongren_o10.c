#include <ansi.h>

inherit ITEM;

int is_tongren() { return 1; }
void create()
{
        set_name(YEL "衝穴銅人·手少陽脈·青冷淵穴" NOR, ({ "tongren o10", "tongren" }));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("long", NOR + YEL "這是一個衝穴銅人，上面繪製了一些經絡穴位圖案，以及衝穴使用方法。\n" NOR);
                set("value", 10000);
                set("material", "steal");
        }
        set("jingmai_name", "手少陽脈");
        set("xuewei_name", "青冷淵穴");
        set("chongxue_xiaoguo", "NEI:30:MAR:50");
        set("neili_cost", "4000");
        setup();
}

