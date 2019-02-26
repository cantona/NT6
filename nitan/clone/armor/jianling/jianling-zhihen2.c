#include <ansi.h>
#include <armor.h>

inherit BOOTS;

void create()
{
        set_name(HIG "劍靈之痕" NOR, ({ "jianling zhihen2", "zhihen2" }) );
        set_weight(10);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "雙");
                set("long", HIG "這是由劍靈的真氣結晶而成的寶靴，看上去異常奇特。\n");
                set("value", 2000000);
                
                set("armor_prop/dex", 60);
                set("armor_prop/dodge", 300);
                set("armor_prop/T_jianling", 1);
                set("special/desc", "【劍靈套裝】部件之一（劍靈之怒、劍靈之痕、劍靈之力、劍靈之魂）。\n"
                                    "                  關於劍靈套裝的傳説參見 help boss\n"
                                    "                  有效輕功等級提高300級。\n");
                set("material", "boots");
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
