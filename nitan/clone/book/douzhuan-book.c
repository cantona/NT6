// douzhuan-book.c 斗轉星移

#include <ansi.h>

inherit BOOK;

void create()
{
        set_name(CYN "斗轉星移" NOR, ({ "douzhuan book", "douzhuan", "book" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "本");
                set("no_sell", 1);
                set("long", "這是一本記載了慕容家斗轉星移的祕籍。\n");
                set("value", 1000);
                set("material", "paper");
                set("skill", ([
                        "name":         "douzhuan-xingyi",
                        "family_name" : "慕容世家",
                        "exp_required": 100000,
                        "jing_cost" :   50,
                        "difficulty":   40,
                        "max_skill":    179,
                        "min_skill":    100
                ]) );
        }
}
