#include <ansi.h>
 
inherit ITEM;

void create()
{
        set_name(HIR "「多羅葉指」" NOR, ({ "duoluoye zhi", "duoluoye", "zhi", "book" }));
        set_weight(500);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "本");
                set("long", HIY "這是一本薄薄的書冊，書皮看上去很新，像是"
                            "重新抄寫的，封面上寫著「多羅葉指」四個字。\n" NOR);
                set("value", 1);
                set("no_sell", 1);
                set("material", "paper");
                set("skill", ([
                        "name":       "duoluoye-zhi",
                        "exp_required" : 100000,
                        "jing_cost":  60,
                        "difficulty": 50,
                        "max_skill":  1,
                        "min_skill":  0
                ]));
        }
}