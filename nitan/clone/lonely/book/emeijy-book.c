#include <ansi.h>
 
inherit ITEM;

void create()
{
        set_name(HIY "「峨嵋九陽功」" NOR, ({ "emei jiuyang", "emei", "jiuyang", "book" }));
        set_weight(500);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "本");
                set("long", HIG "這是一本薄薄的冊子，書面已經有點開始腐爛。\n" NOR);
                set("value", 1);
                set("no_sell", "這本破書你自己留著吧。");
                set("material", "paper");
                set("skill", ([
                        "name"       : "emei-jiuyang",
                        "jing_cost"  : 100,
                        "difficulty" : 200,
                        "max_skill"  : 180,
                        "min_skill"  : 0
                ]));
        }
}