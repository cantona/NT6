// 上古十大神器之 真龍石 
// Create by Rcwiz for Hero.cn 2003/09

#include <ansi.h>

inherit ITEM;

int is_magic_item() { return 1; }

void create()
{
        set_name(NOR + YEL + "真龍石" NOR, ({ "zhenlong shi", "zhenlong", "shi" }) );
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "塊");
                set("long", NOR + YEL "這是一塊泛著七彩光芒的石頭，傳說此石乃黃帝的"
                                      "護身符。\n"
                                      "只要帶在身上死亡後不會丟失經驗，潛能以及技能。\n"
                                      "此神器下線後不丟失。\n" NOR);

        }
        setup();
}
