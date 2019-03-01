#include <ansi.h>; 
inherit ITEM;

void create()
{
        set_name(WHT "「九陰真經」拓本" NOR, ({ "zhenjing taben", "taben",
                                                "zhenjing", "jing" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "張");
                set("no_sell", "你想錢想瘋了？這也拿來賣錢？");
                set("long", WHT "這是一張拓片，上面拓滿了密密麻麻的小字。\n" NOR);
                set("material", "paper");
                set("skill", ([
                        "name":        "force",
                        "exp_required" : 100000,
                        "jing_cost"    : 80,
                        "difficulty"   : 50,
                        "max_skill"    : 199,
                        "min_skill"    : 100
                ]));
        }
}