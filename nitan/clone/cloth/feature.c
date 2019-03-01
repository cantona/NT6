// feather.c

#include <armor.h>
#include <ansi.h>
#include <mudlib.h>

inherit CLOTH;

void create()
{
        set_name(HIW "孔雀羽衣" NOR, ({ "kongque yuyi", "kongque", "yuyi" }) ); 
        set_weight(600);

        if (clonep())
                set_default_object(__FILE__);
        else {
                set("long", HIW "這是一件出自天宮織女妙手神裁的羽"
                            "紗輕衣。款式新穎別致，\n輕柔飄逸的。"
                            "放在手中簡直輕若無物，真是一件服飾極品。\n" NOR);

                set("unit", "件");
                set("value", 100000);
                set("material", "feather");
                set("armor_prop/per", 10);
                set("armor_prop/armor", 10);
                set("armor_prop/armor_vs_force", 10);
                set("armor_prop/attack", -2); 
                set("wear_msg", HIW "$N" HIW "輕柔的展開一件潔白如雪的飄逸紗"
                                "衣輕輕披在身上，映襯的\n$P" HIW "肌膚如"
                                "雪一般，一張盈盈笑臉如出水芙蓉，"
                                "讓人意動魂搖。\n" NOR);

        }

        setup();
}