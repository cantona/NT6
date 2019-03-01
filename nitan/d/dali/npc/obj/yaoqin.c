// tiepipa.c

#include <weapon.h>
#include <ansi.h>
#include <music.h>

inherit HAMMER;
inherit MI_QIN;

void create()
{
        set_name("瑤琴", ({ "yao qin" }) );
        set_weight(5000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("long", "這是一把歌女用的瑤琴，製做得相當精巧細膩。\n");
                set("value", 300);
                set("material", "iron");
                set("wield_msg", "$N從背上解下一把$n，然後橫在手中。\n");
                set("unwield_msg", "$N放下手中的$n。\n");
        }
        init_hammer(5);
        setup();
}

void init()
{
        add_action("play_qin", "play");
}
