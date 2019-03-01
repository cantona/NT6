#include <ansi.h>
inherit BOOK;

void create()
{
        set_name(YEL "「千金方」" NOR, ({ "medical book4", "medical", "book4" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", YEL "孫思邈所著的醫書，囊括了許多名家學說。\n" NOR);
                set("value", 50000);
                set("material", "paper");
                set("skill",
                ([
                        "name" : "medical",
                        "jing_cost"  : 55,
                        "difficulty" : 45,
                        "max_skill"  : 119,
                        "min_skill"  : 80,
                ]));
        }
}