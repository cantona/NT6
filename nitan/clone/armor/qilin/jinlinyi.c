

#include <armor.h>
#include <ansi.h>

inherit CLOTH;


void create()
{
        set_name(HIR "火麒麟﹒金鱗衣" NOR, ({ "jinlin yi", "jinlin", "yi" }) );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("long", HIR "這是一件傳世寶衣，渾身閃耀著金色的火燄，絢麗無比。\n" NOR);
                set("material", "steel");
                set("value", 80000000);
                set("armor_prop/armor", 2000);
                set("limit", ([
                        "exp"  :  50000000,
                ]));
                
        }
        setup();
}

int query_autoload()
{
        return 1;
}
