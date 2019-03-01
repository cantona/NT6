// cart.c
//

#include <ansi.h>

inherit ITEM;
inherit F_TRANSPORT;

void create()
{
        set_name("大車", ({ "cart" }) );
        set_weight(200000);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("value", 1);
                set("long", "這是一輛普通的貨車。\n");
                set("no_sell", "你還是拿到別地去吧。\n");
                set("unit", "輛");
                set("material", "wood");
                set("no_get", "好家伙，車你也想扛在肩上？\n");
        }
        setup();
}

string long()
{
        mapping goods;
        string desc;

        desc = ::long();
        if (! mapp(goods = query_temp("goods")))
                return desc;

        desc += "裡面裝著" + chinese_number(goods["amount"]) +
                goods["unit"] + goods["name"] + "。\n";
        return desc;
}