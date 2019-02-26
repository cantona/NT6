#include <armor.h>
#include <ansi.h>

inherit CLOTH;


void create()
{
        set_name(HIG "劍靈之魂" NOR, ({ "jianling zhihun", "zhihun" }) );
        set_weight(10);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("long", HIG "這是一件由藍蝶仙子幻化而成並附身在愛人身上的寶衣，淡淡的藍色光芒中隱現一隻蝴蝶。\n" NOR);
                set("material", "steel");
                set("value", 80000000);
                set("armor_prop/parry", 200);
                set("armor_prop/T_jianling", 1);
                set("special/desc", "【劍靈套裝】部件之一（劍靈之怒、劍靈之痕、劍靈之力、劍靈之魂）。\n"
                                    "                  關於劍靈套裝的傳説參見 help boss\n"
                                    "                  有效招架提高200級。\n");
                set("limit", ([
                         "exp" : 100000000,
                         "thborn" : 1,
                         "jianling": 1, // equip.c裏限制，必須要調整成功劍靈1次後才能裝備
                ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}
