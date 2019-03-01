#include <ansi.h> 
inherit ITEM;

void create()
{
        set_name(YEL "「毒經中篇」" NOR, ({ "du jing2", "jing2", "book2" }));
        set_weight(50);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", YEL "這是一本薄薄的小冊，上面密密麻麻的記滿"
                            "了各種用毒的法門。\n" NOR);
                set("value", 100);
                set("no_sell", "我…我的天…連五毒教的東西你都敢拿來賣？");
                set("material", "silk");
                set("skill", ([
                        "name"         : "poison",
                        "exp_required" : 100000,
                        "jing_cost"    : 40,
                        "difficulty"   : 40,
                        "min_skill"    : 50,
                        "max_skill"    : 99,
                ]));
        }
}