#include <ansi.h>
 
inherit ITEM;

void create()
{
        set_name(HIR "「血刀經」" NOR, ({ "xuedao jing", "xuedao", "jing", "book" }));
        set_weight(500);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "本");
                set("long", HIR "這是一本薄薄的書冊，封面上豁然寫著「血"
                            "刀經」三個大字。\n" NOR);
                set("value", 1);
                set("no_sell", "血…血刀…經？這…該不會是血刀門的東西吧？");
                set("material", "paper");
                set("skill", ([
                        "name" : "xuedao-dafa",
                        "exp_required" : 300000,
                        "jing_cost"  : 100,
                        "difficulty" : 80,
                        "max_skill"  : 179,
                        "min_skill"  : 10
                ]));
        }
}