#include <weapon.h>
#include <ansi.h>
inherit BLADE;

void create()
{
        set_name(CYN "井中月" NOR, ({ "jingzhong yue" , "blade" ,"dao", "yue", "jingzhong" }) );
        set_weight(20000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "柄");
                set("long", CYN "一柄四尺來長的單刀，重達百斤，刀身散發着烏黑的光澤。\n" NOR);
                set("value", 100000);
                set("rigidity", 8000);   
                set("material", "steel");
                set("wield_msg", HIY "$N" HIY "一聲狂笑，從背後抽出井中月高高舉起。\n" NOR);
                set("unwield_msg", HIY "$N" HIY "哈哈一笑，將井中月插回背後。\n"NOR);
        }
        init_blade(200);
        setup();
}
mixed hit_ob(object me, object victim, int damage_bonus)
{
        int pro;
        int dam;
        dam = (int) me->query("str");
        victim->receive_damage("jing", dam);
        return HIY "井中月劃出一道熾熱的黃芒，$n" HIY "只感到心神俱碎。\n" NOR;
}

