// jiuzhang.c

#include <ansi.h>
 
inherit BOOK;

void create()
{
        set_name(HIY "「九章算術」" NOR, ({ "jiuzhang", "shu" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", "這是一本薄薄的小冊子，上面寫著"
                            "“九章算術”四個古篆小字。\n");
                set("value", 0);
                set("material", "paper");
                set("skill", ([
                        "name":       "mathematics",
                        "jing_cost":  100,
                        "difficulty": 30,
                        "max_skill":  149,
                        "min_skill":  80
                ]));
        }
}