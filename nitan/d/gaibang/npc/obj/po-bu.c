#include <ansi.h>
inherit ITEM;

string long();

void create()
{
        set_name(NOR + WHT "破布" NOR, ({ "po bu", "po", "bu", "piece" }));
        set_weight(80);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "塊");
                set("long", WHT "這是一塊破布，不知道有什麼用。\n" NOR);
                set("material", "cloth");
                set("no_sell", "什麼東西？快拿走。");
        }
}

string long()
{
        string msg;

        if (query("owner") && query("from"))
        {
                msg = WHT "這是一塊從" HIW + query("from") + NOR +
                      WHT "處得來的破布，散發著一陣油臭。憑此可直"
                      "接向簡長老要求升袋。只見破布上寫著「今日接"
                      "受" HIW + query("owner") + NOR + WHT "挑戰"
                      "技勝一籌，同意升袋」幾個歪歪斜斜的字。" NOR;
        } else
                msg = query("long");

        return sort_string(msg, 54);
}