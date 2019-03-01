// Room: /d/kunlun/obj/pao1.c
// Last Modified by winder on Nov. 14 2000

#include <armor.h>
#include <ansi.h>

inherit CLOTH;

void create()
{
        set_name(WHT "黑邊白色長袍" NOR, ({ "chang pao", "cloth","changpao","pao"}));
        set_weight(6000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long","這是一件黑色滾邊的白色長袍，華貴異常，看不出是什麼質料做的。\n");
                set("unit", "件");
                set("material", "cloth");
                set("armor_prop/armor", 65);
                set("value", 100);
                set("wear_msg","$N迎風一展，[唰]的一聲，披上一件$n。\n");
                set("remove_msg","$N解開$n,把$n從身上脫了下來。\n");
        }
        setup();
}