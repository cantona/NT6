#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIY "炎黃商城九折卡" NOR, ({"yhshop vipcard9"}));
        set_weight(1);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIY "這是一張黃金打造而成的卡片，炎黃商城購買九折優惠。「謝謝您的參與」\n" NOR);
                set("unit", "張");
                                set("no_drop", 1);
                                set("no_sell", 1);
                                set("no_give", 1);
                                //set("no_get", 1);
                                set("no_put", 1);
                                set("no_steal", 1);
                                set("no_store", 1);
                                set("no_hand", 1);
        }
}

int query_autoload()
{
        return 1;
}

