#include <ansi.h>

inherit ITEM;

int is_tongren() { return 1; }
void create()
{
        set_name(YEL "銅人NAME" NOR, ({ "銅人ID", "tongren" }));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("long", NOR + YEL "這是一個衝穴銅人，上面繪製了一些經絡穴位圖案，以及衝穴使用方法。\n" NOR);
                set("value", 10000);
                set("material", "steal");
        }
        set("jingmai_name", "JINGMAI_NAME");
        set("xuewei_name", "XUEWEI_NAME");
        set("chongxue_xiaoguo", "CHONGXUE_XIAOGUO");
        set("neili_cost", "NEILI_COST");
        setup();
}

