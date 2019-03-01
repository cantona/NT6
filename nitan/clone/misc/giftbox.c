// giftbox.c 禮品盒

inherit ITEM;
#include <ansi.h>;
void create()
{
        set_name(HIR"禮品盒"NOR, ({ "giftbox", "box" }));
        set_weight(500);
        set_max_encumbrance(10000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "盒");
                set("long", "一盒禮品盒。盒裡裝著巫師的新年賀禮。\n\n    "HIR"新年快樂！！\n\n"NOR);
                set("value", 0);
        }
}

int is_container() { return 1; }
