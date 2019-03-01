
#include <armor.h>
#include <ansi.h>

inherit MYHEART2;

void create()
{
        set_name(HIM "淺草觀音" NOR, ({ "qiancao guanyin", "qiancao", "guanyin" }) );
        set_weight(1);
        if( clonep())
                set_default_object(__FILE__);
        else {
                set("material", "paper");
                set("unit", "個");
                set("long", HIM "這是一個產自扶桑淺草寺的護身人偶，上面繡有「淺草觀音」的字樣。\n" NOR);
                set("value", 1000000);
                set("limit", ([
                        "exp"    :   2000000,
                ]));                
                set("armor_prop/qy", 4);

        }
        setup();
}

int query_autoload()
{
        return 1;
}