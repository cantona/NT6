#include <armor.h>
#include <ansi.h>

inherit HEAD;
 
void create()
{
        set_name(HIG "劍靈之怒" NOR, ({ "jianling zhinu", "zhinu", }) );
        set_weight(1);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "頂");
                set("long", HIG "這是由黑曜石和劍靈的怒氣結晶而成的頭箍，陣陣光芒令人生畏。\n" NOR);
                set("value", 1500000);
                set("armor_prop/dex", 45);
                set("armor_prop/str", 45);
                set("armor_prop/con", 45);
                set("armor_prop/damage", 4300);
                set("armor_prop/sword", 200);
                set("armor_prop/T_jianling", 1);
                set("special/desc", "【劍靈套裝】部件之一（劍靈之怒、劍靈之痕、劍靈之力、劍靈之魂）。\n"
                                    "                  關于劍靈套裝的傳說參見 help boss\n"
                                    "                  有效劍法提高300級。\n");
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
