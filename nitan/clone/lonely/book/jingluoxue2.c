#include <ansi.h>
 
inherit ITEM;

void create()
{
        set_name(HIW "「玉顴神脈經」" NOR, ({ "yuquan jing", "yuquan", "jing", "book" }));
        set_weight(500);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "本");
                set("long", HIW "這是一本精裝書冊，書頁已然發黃，書"
                            "皮上寫著「玉顴神脈經」五個字。\n" NOR);
                set("value", 1);
                set("no_sell", "奶奶的，這本破書也能賣錢？");
                set("material", "paper");
                set("skill", ([
                        "name" : "jingluo-xue",
                        "exp_required" : 600000,
                        "jing_cost"  : 90,
                        "difficulty" : 65,
                        "max_skill"  : 200,
                        "min_skill"  : 149
                ]));
        }
}