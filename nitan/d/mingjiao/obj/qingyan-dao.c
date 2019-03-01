#include <weapon.h>
#include <ansi.h>
inherit BLADE;

void create()
{
        set_name(HIC"青燄刀"NOR, ({ "qingyan dao", "dao", "blade" }) );
          set_weight(20000);
        if( clonep() )
              set_default_object(__FILE__);
        else {
           set("value", 1000);
           set("rigidity", 3);
        set("long",HIC"這柄刀重約四十余斤，但見青光閃爍，背厚刃薄，刃鋒上刻有古樸花紋，顯是一件歷時已久的珍品。\n"NOR);
           set("sharpness", 3);
           set("unique", 1);
           set("treasure",1);
           set("weapon_prop/parry", 2);
           set("wield_neili", 500);
           set("wield_maxneili", 900);
           set("wield_str", 22);
           set("unit", "把");
        set("wield_msg", HIB"$N由背後取下寶刀，雙手一分，將青燄刀抽出刀鞘，四周頓時布滿凌厲的殺氣。\n"NOR);
        set("unwield_msg",HIB" 只聽見倉啷一聲響，$N將沉重的青燄刀插進刀鞘，背在背上。\n"NOR);
        }
        init_blade(80);
        setup();
}