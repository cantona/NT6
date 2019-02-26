#include <ansi.h>
inherit BOOK;

void create()
{
        set_name(YEL "「外台祕要」" NOR, ({ "medical book6", "medical", "book6" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", YEL "王燾所著的醫學寶典，介紹了各種疑難雜症的治療方法。\n" NOR);
                set("value", 5000);
                set("material", "paper");
                set("skill",
                ([
                        "name" : "medical",
                        "jing_cost"  : 80,
                        "difficulty" : 60,
                        "max_skill"  : 179,
                        "min_skill"  : 150,
                ]) );
        }
}