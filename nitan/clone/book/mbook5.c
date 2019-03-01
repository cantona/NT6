#include <ansi.h>
inherit BOOK;

void create()
{
        set_name(YEL "「千斤翼」" NOR, ({ "medical book5", "medical", "book5" }));
        set_weight(500);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "本");
                set("long", YEL "千斤翼乃醫學寶典，介紹了各種疑難雜症的治療方法。\n" NOR);
                set("value", 3000);
                set("no_sell", "這…這值什麼錢？\n");
                set("material", "paper");
                set("skill",
                ([
                        "name" : "medical",
                        "jing_cost"  : 60,
                        "difficulty" : 50,
                        "max_skill"  : 149,
                        "min_skill"  : 120,
                ]) );
        }
}