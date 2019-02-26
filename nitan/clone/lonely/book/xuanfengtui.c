#include <ansi.h>
 
inherit ITEM;

void create()
{
        set_name(HIY "「旋風掃葉腿法」" NOR, ({ "xuanfeng paper", "xuanfeng", "paper", "shu", "book" }));
        set_weight(500);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "本");
                set("long", HIY "這是兩張紙片，上面寫的都是練功的口訣要旨，卻是\n"
                            "黃藥師的親筆，字跡遒勁挺拔，第一葉上右首寫着題\n目，"
                            "是「旋風掃葉腿法」六字。\n" NOR);
                set("value", 1);
                set("no_sell", "這本破書你自己留着吧。");
                set("material", "paper");
                set("skill", ([
                        "name"       : "xuanfeng-tui",
                        "jing_cost"  : 100,
                        "difficulty" : 30,
                        "max_skill"  : 119,
                        "min_skill"  : 0
                ]));
        }
}