// king-blade.c 闖王寶刀
// Last Modified by winder on Sep. 7 2001

#include <weapon.h>;
inherit BLADE;
inherit F_UNIQUE;

void create()
{
        set_name("闖王寶刀", ({ "chuangwang baodao", "blade", "dao" }) );
        set_weight(12000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("value", 0);
                set("material", "iron");
                set("long", "這是闖王所使用過的刀，上面刻有幾行小字。\n" );
                set("wield_msg", "一道白光，$n已在$N手中，只覺青光四射，寒氣透骨，不禁機伶伶的打個冷戰。\n");
                set("unwield_msg", "$N將$n插回腰間，華光頓斂，天地間只聞龍鳴。\n");
        }
        init_blade(250);
        setup();
}