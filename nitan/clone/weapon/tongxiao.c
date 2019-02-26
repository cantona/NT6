// Room Of Mxj
// have a good day

#include <weapon.h>
#include <ansi.h>
inherit SWORD;

void create()
{
        set_name(HIG "青銅簫" NOR,({ "tong xiao", "xiao" }) );
        set_weight(5000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "支");
                set("value", 400);
                set("material", "steel");
                set("shape", "flute");
                set("long", "一柄青銅打造的洞簫，通體銅綠斑斕，看起來有些年頭了。\n");
                set("wield_msg", "$N從懷裏掏出一支$n，握在手中。\n" NOR);
                set("unwield_msg", "$N小心翼翼的將$n放入懷裏。\n" NOR);
        }
        init_sword(40);
        setup();

}

#include "music.h"

