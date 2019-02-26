#include <weapon.h>
#include <ansi.h>
inherit SWORD;

void create()
{
        set_name(HIR "赤劍" NOR, ({ "chi jian" , "jian" , "sword", "chi", "chijian" }) );
        set_weight(12000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", HIR "一柄四尺來長的長劍，整個劍身呈紅色。\n" NOR);
                set("value", 200000);
                set("rigidity", 8000);   
                set("material", "steel");
                set("wield_msg", HIR "$N" HIR "從背後抽出赤劍，頓時騰起一股凜冽的殺氣。\n" NOR);
                set("unwield_msg", HIR "$N" HIR "歎了口氣，將赤劍插回背後。\n" NOR);
        }
        init_sword(250);
        setup();
}

