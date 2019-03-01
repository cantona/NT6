// nfeecard.c 無上免費卡
//
// 使用免費卡建房不需要花費任何銀兩

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(HIY "免費卡" NOR, ({ "card", "fee free card" }));
        set_weight(10);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "張");
                set("long", "這是一張無上住房免費卡，憑這張卡可以免費"
                            "購買任何住房。\n");
                set("material", "paper");
                set("fee free", 2000000000);
                set("value", 1);
                set("no_sell", 1);
        }
}

int query_autoload() { return 1; }