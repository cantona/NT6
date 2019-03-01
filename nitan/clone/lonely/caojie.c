#include <ansi.h>
#include <armor.h>

inherit BOOTS; 

void create()
{
        set_name(HIG "神草結" NOR, ({ "shen caojie", "shen", "caojie" }));
        set_weight(100);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "對");
                set("long", HIG "當年達摩祖師一葦渡江時所穿的草鞋。\n" NOR);
                set("wear_msg", HIG "$N" HIG "將一對神草結綁于足間。\n" NOR);
                set("remove_msg", HIG "$N" HIG "將神草結從足間取下，放回包"
                                  "囊。\n" NOR);
                set("no_sell", "這是啥？是烏拉草麼？");
                set("value", 100000);
                set("material", "silk");
                set("armor_type", "feet");
                set("armor_prop/dodge", 50);
                set("armor_prop/armor", 50);
                set("stable", 100);
        }
        setup();
}