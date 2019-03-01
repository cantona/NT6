#include <ansi.h>

inherit BOOK;

void create()
{
        set_name(WHT "「孟子」" NOR, ({ "mengzi book", "shu", "mengzi", "book" }));
        set_weight(300);

        if (clonep())
                set_default_object(__FILE__);
        else
        {
                set("unit", "本");
                set("long", WHT "這本書記載了當年孟子許多言行哲論，是儒家經典書籍。\n" NOR);
                set("value", 100);
                set("no_sell", "這…這值什麼錢？\n");
                set("material", "paper");
                set("skill", ([
                        "name" : "literate",
                        "jing_cost"  :   100,
                        "difficulty" :   60,
                        "max_skill"  :   299,
                        "min_skill"  :   150,
                ]));
        }
}