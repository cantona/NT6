// lan.c 禮籃

inherit ITEM;
#include <ansi.h> 

void create()
{
        set_name(HIY"禮籃" NOR, ({ "li lan", "lan" }));
        set_weight(500);
        set_max_encumbrance(10000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "個");
                set("long", "一只裝禮物的竹籃子，細蔑精制而成，手藝可真不錯。\n");
                set("value", 1000);
        }
}

int is_container() { return 1; }