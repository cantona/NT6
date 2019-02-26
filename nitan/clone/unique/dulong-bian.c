// dulong-bian.c 毒龍鞭 

#include <weapon.h>
#include <ansi.h>
inherit F_UNIQUE;
inherit WHIP;

void create()
{
        set_name("毒龍鞭",({ "dulong bian", "bian", "whip", "dulong" }) );
        set_weight(700);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("value", 7000000);
                set("rigidity", 100000);
                set("replica_ob","/clone/weapon/whip");
                set("poison_applied", 300);
                set("material", "leather");
                set("long", 
                "這是一條爛銀也似的銀色軟鞭，長達四丈有餘，鞭頭裝着十多隻明晃晃的尖利倒鈎。\n");
                set("wield_msg", "$N「唰」的一聲從腰後抽出一柄$n握在手中。\n");
                set("unwield_msg", "$N將手中的$n別回腰後。\n");
        }
        init_whip(50);
        setup();
}
