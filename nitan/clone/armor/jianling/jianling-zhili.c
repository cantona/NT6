#include <armor.h>
#include <ansi.h>

inherit MYHEART2;

void create()
{
        set_name(HIG "劍靈之力" NOR, ({ "jianling zhili", "zhili"}) );
        set_weight(1);
        if( clonep())
                set_default_object(__FILE__);
        else {
                set("material", "paper");
                set("unit", "張");
                set("long", HIG "這是一張淡藍色的護符，其外形有如蝴蝶翅膀一般。\n" NOR);
                set("value", 10000000);
                set("limit", ([
                        "exp"    :   50000000,
                ]));
                set("armor_prop/int", 50);              
                set("armor_prop/qy", 3);
                set("armor_prop/fy", 3);

                set("armor_prop/T_jianling", 1);
                set("special/desc", "【劍靈套裝】部件之一（劍靈之怒、劍靈之痕、劍靈之力、劍靈之魂）。\n"
                                    "                  關于劍靈套裝的傳說參見 help boss\n");

                set("limit", ([
                         "exp" : 100000000,
                         "thborn" : 1,
                         "jianling": 1, // equip.c裡限制，必須要調整成功劍靈1次後才能裝備
                ]));
        }
        setup();
}

int query_autoload()
{
        return 1;
}
