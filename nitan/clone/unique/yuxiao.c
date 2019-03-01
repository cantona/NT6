#include <ansi.h>
#include <music.h>
#include <weapon.h> 

inherit XSWORD; 
inherit F_UNIQUE;

void create()
{
        set_name(HIG"玉簫"NOR,({ "yu xiao", "xiao" }) );
        set_weight(3000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("value", 7000000);
                set("unique", 1);
                set("rigidity", 300);
                set("no_put", 1);
                set("no_steal", 1);
                set("replica_ob","/clone/weapon/zhuxiao");
                set("material", "steel");
                set("shape", "flute");
                set("long", 
                        "一柄翠玉制玉簫，通體晶瑩碧綠，近吹口處幾點朱斑，殷紅如血，顯然都是\n"
                        "數百年乃至上千年的古物。\n");
                set("wield_msg", 
                    HIG "$N從腰間抽出一支玉簫，吹出優雅的簫聲。簫聲入耳，眾人激盪的心情便即平\n"
                        "復。$N隨即和道：“蒼生笑，不再寂聊，豪情仍在痴痴笑笑。”\n"NOR);
                set("unwield_msg", CYN "$N將$n插到領後。\n" NOR);
                set("unequip_msg", CYN "$N將$n插到領後。\n" NOR);
        }

        init_xsword(90); 
        setup();
}

void init()
{
        add_action("play_xiao", "play");
}
