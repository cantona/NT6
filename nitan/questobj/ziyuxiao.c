// Last Modified by winder on Nov. 17 2000
// ziyuxiao.c 紫玉簫
#include <weapon.h>
#include <ansi.h>

inherit SWORD;

void create()
{
        set_name(MAG"紫玉簫"NOR,({"ziyu xiao","xiao"}));
        set_weight(1000);
        set("taskobj", 1);
        if (clonep())
                set_default_object(__FILE__);
        else{
                set("unit","支");
                set("value",0);
                set("material","gem");
                set("unique", 3);
                set("wield_neili", 50);
                set("wield_maxneili", 500);
                set("long","這是一支晶瑩剔透的用罕見的"MAG"紫玉"NOR"做的簫，看起來十分珍貴。\n");
                set("wield_msg","$N伸手輕輕一招，一支$n已出現在$N手中。\n");
                set("unwield_msg","$N一聲清嘯，將$n插回腰間。\n");
        }
        setup();
}