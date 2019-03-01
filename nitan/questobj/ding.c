// ding.c 神木王鼎

inherit ITEM;
#include <ansi.h>;
void create()
{
        set_name(YEL"神木王鼎"NOR, ({ "shenmu wangding", "ding" }));
        set_weight(500);
        set("taskobj", 1);
        set("count", 50);
        set_max_encumbrance(1000);
        if (clonep())

                set_default_object(__FILE__);
        else {
                set("unit", "座");
                set("long", 
YEL"這是一座色作深黃的小小木鼎。木鼎雕琢甚是精細，木質堅潤似
似玉，木理之中隱隱約約的泛出"RED"紅絲"YEL"。鼎側有五個銅錢大的圓孔，
木鼎齊頸處有一道細縫，似乎分為兩截。\n"NOR);
                set("value", 0);
        }
}

int is_container() { return 1; }

void init()
{
}