// jlding.c 九龍鼎

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIY"九龍"NOR+RED"神火"NOR+YEL"爐" NOR, ({ "jiulong lu", "lu" }));
        set_weight(1200);
        set_max_encumbrance(200);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("long", "一個周邊鑲嵌九條龍的爐，頗為沉重，特殊質地，乃煉丹神器。\n");
                set("value", 20000);
                set("auto_load", 1);
                set("can_summon", 1); 
                set("item_prop/medical", 900);
                set("item_prop/liandan-shu", 300);
        }
        setup();
}

int is_container() { return 1; }

int can_make_medicine() { return 1; }
