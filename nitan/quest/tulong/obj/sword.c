#include <weapon.h>
#include <ansi.h> 
inherit SWORD;

void create()
{
        set_name(HIC"精靈長劍"NOR, ({ "spirit sword", "sword" })); 
        set("long", "精靈的寶物，其中包含著精靈之王"+HIY"夜"+HIG"辰"NOR+"的力量。\n");
        set("no_get",1);
        set("no_give",1);
        set("no_steal",1);
        set("no_sell",1);
        set("no_put",1);
        set_weight(10);
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("value", 0);
                set("material", "iron");
                set("wield_msg", HIC"$N右手結印，垂目默念咒語。一點光芒在$N掌中逐漸亮起，$n"NOR+HIC"漸漸成形。\n"NOR);
                set("unwield_msg", "$n"+HIC"從$N手中一躍而起，化為一片明亮的光芒。\n"NOR); 
        }
        init_sword(300);
        setup();
}

void owner_is_killed()
{
        write(HIY"只覺金光一閃，有什麼東西不見了。\n"NOR);
       destruct(this_object());
}
/*
int query_autoload()
{
        write(HIG"一陣清風拂過身側，仿佛在呢喃什麼咒語。\n"NOR);
       return 1;
}
*/ 
mixed hit_ob(object me, object victim, int damage_bonus)
{
        int may, dam;
        may = random(5);
        if(may >3)
        { 
        dam = random(10)+10;
        victim->receive_wound("qi",dam);
        return HIC "精靈長劍發出一道閃光，正好擊中了$n。\n" NOR;
        }
}
