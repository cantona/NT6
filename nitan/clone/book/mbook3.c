#include <ansi.h>
inherit BOOK;

void create()
{
        set_name(YEL "「華佗內昭圖」" NOR, ({ "medical book3", "medical", "book3" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", YEL "神醫華佗所著的醫書，內含許多醫學祕要。\n" NOR);
                set("value", 30000);
                set("material", "paper");
                set("skill",
                ([
                        "name" : "medical",
                        "jing_cost"  : 45,
                        "difficulty" : 40,
                        "max_skill"  : 79,
                        "min_skill"  : 50,
                ]) );
        }
}