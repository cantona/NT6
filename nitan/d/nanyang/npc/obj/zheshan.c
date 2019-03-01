// Room: /d/nanyang/npc/obj/zheshan.c
// Last Modified by winder on Nov. 20 2001

#include <weapon.h>
#include <ansi.h>
inherit DAGGER;

void create()
{
        set_name(CYN "紙折扇" NOR, ({ "zhe shan","fan"}) );
        set_weight(100);
        set("long","一把普普通通的折扇，扇面上畫著一幅山水畫。\n");
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("value", 200);
                set("material", "bamboo");
        }
        init_dagger(1);
        set("wield_msg", "$N將一把折扇拿在手中。\n");
        set("unwield_msg", "$N將手中的$n揣回長袖子裡。\n");
        setup();
}