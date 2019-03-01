// feecard.c 免費卡
//
// 使用免費卡建房不需要花費任何銀兩

#include <ansi.h>

inherit ITEM;

void create()
{
        set_name(CYN "免費卡" NOR, ({ "card", "fee free card" }));
        set_weight(10);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "張");
                set("material", "paper");
                set("fee free", 25000000);
                set("value", 1);
                set("no_sell", 1);
        }
}

string long()
{
        string msg;

        msg = "這是一張住房免費卡，憑這張卡可以免費購買一套價格";
        msg += MONEY_D->price_str(query("fee free"));
        msg += "以下的住房一套。\n";
        return msg;
}

int query_autoload() { return 1; }