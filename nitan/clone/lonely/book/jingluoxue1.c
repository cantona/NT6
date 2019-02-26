#include <ansi.h>
 
inherit ITEM;

void create()
{
        set_name(HIY "「王叔和脈經」" NOR, ({ "mai jing", "mai", "jing", "book" }));
        set_weight(500);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "本");
                set("long", HIY "這是一本精裝書冊，書頁已然發黃，書"
                            "皮上寫着「王叔和脈經」五個字。\n" NOR);
                set("value", 1);
                set("no_sell", "奶奶的，這本破書也能賣錢？");
                set("material", "paper");
                set("skill", ([
                        "name" : "jingluo-xue",
                        "exp_required" : 10000,
                        "jing_cost"  : 80,
                        "difficulty" : 50,
                        "max_skill"  : 149,
                        "min_skill"  : 0
                ]));
        }
}