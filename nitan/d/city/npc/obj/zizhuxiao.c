// zizhuxiao.c 紫竹簫

#include <ansi.h>
#include <weapon.h>
inherit SWORD;

void create()
{
        set_name(MAG "紫竹簫" NOR, ({"zizhu xiao", "xiao"}) );
        set_weight(1000);
        if ( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "此簫用紫竹製成，長約三尺有餘。。\n");
                set("value", 600);
                set("unit", "支");
                 set("wield_msg","$N漫不經心的把$n握在手上。\n");
                set("unwield_msg", "$N放下手裏的$n。\n");
        }
        init_sword(3);
        setup();
}