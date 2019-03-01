#include <ansi.h>
inherit ITEM;

void create()
{
        set_name(NOR + WHT "「率意帖」" NOR, ({ "shuaiyi tie", "tie", "shuaiyi" }));
        set_weight(600);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "冊");
                set("no_sell", "我的天，你…你知道這是啥麼？也拿來賣？\n");
                set("long", WHT @LONG
這便是唐朝張旭的率意帖，但見帖上的草書大開大
闔，便如一位武林高手展開輕功，竄高伏低，雖然
行動迅捷，卻不失高雅的風致。帖尾寫滿了題跋蓋
了不少圖章，料想此帖的是非同小可。
LONG NOR);
                set("value", 1);
                set("material", "paper");
                set("skill", ([
                        "name"         : "calligraphy",
                        "exp_required" : 10000,
                        "jing_cost"    : 60,
                        "difficulty"   : 30,
                        "max_skill"    : 199,
                        "max_skill"    : 599,
                        //"min_skill"    : 100,
                        "need"         : ([ "literate" : 200 ]),
                ]));
        }
}
