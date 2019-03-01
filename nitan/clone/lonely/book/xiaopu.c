#include <ansi.h>
 
inherit ITEM;

void create()
{
        set_name(HIG "「簫譜」" NOR, ({ "xiao pu", "xiao", "pu", "shu", "book" }));
        set_weight(500);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "本");
                set("long", HIG "這是一本薄薄的簫譜，記載了一些吹簫的方法。\n" NOR);
                set("value", 1);
                set("no_sell", "這本破書你自己留著吧。");
                set("material", "paper");
                set("skill", ([
                        "name"       : "chuixiao-jifa",
                        "jing_cost"  : 30,
                        "difficulty" : 30,
                        "max_skill"  : 149,
                        "min_skill"  : 0
                ]));
        }
}