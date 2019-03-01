// wuchangyi.c

#include <ansi.h>
#include <armor.h>
inherit CLOTH;

void create()
{
        set_name(BLK"烏蠶衣"NOR, ({ "wucan yi", "cloth" }) );
        set_weight(5000);
        set("taskobj", 1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("material", "silk");
                set("value", 0);
                set("armor_prop/armor", 0);
                set("long",
"這一件刀槍不入的寶衣，是用大雪山的上烏蠶蠶絲織成的。整
件烏蠶衣只是兩塊料子，剪刀也剪不爛，只得前一塊、後一塊
的扣在一起。");
        }
        setup();
}
