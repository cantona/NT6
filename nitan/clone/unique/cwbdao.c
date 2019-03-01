//cwbdao.c
#include <weapon.h>

inherit BLADE;

void create()
{
        set_name("闖王寶刀", ({ "chuangwang baodao", "blade","baodao" }) );
        set_weight(6000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("value", 500000);
                set("unique", 1); 
                set("no_sell", 1);
                set("material", "iron");
                set("long", "這是闖王所使用過的刀，上面刻有幾行小字。\n" );
                set("wield_msg","一道白光，$n已在$N手中，只覺青光四射，寒氣透骨，不禁機伶伶的打個冷戰。\n");
                set("unwield_msg", "$N將$n插回腰間，華光頓斂，天地間只聞龍鳴。\n");
        }
        init_blade(150);
        setup();
}