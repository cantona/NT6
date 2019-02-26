 //tulongdao.c
 //屠龍刀
 //PLZW 2003-12-22
 
#include <weapon.h>
#include <ansi.h>

inherit BLADE;

void create()
{
        set_name(NOR + CYN "屠龍刀" NOR, ({ "tulong dao", "tulong", "dao", "blade" }) );
        set_weight(32000);
        if (clonep())
                destruct(this_object());
        else {
                set("long", NOR + CYN "這便是號稱武林至尊的屠龍寶刀，四尺來長"
                            "的單刀，竟達一百多斤之重。\n相傳其中藏有曠世的大"
                            "祕密。\n" NOR);
                set("unit", "柄");
                set("value", 800000);
                set("no_sell", "我的天…你…你知道這是啥麼？這你也敢拿來賣？");
                set("material", "steel");
                set("wield_msg", HIY "$N" HIY "一聲狂笑，從背後抽出那柄號稱「"
                                 HIR "武林至尊" HIY "」的屠龍寶刀高高舉起。\n" NOR);
                set("unwield_msg", HIY "$N" HIY "哈哈一笑，將屠龍寶刀插回背後。\n" NOR);
                set("stable", 100);
        }
        init_blade(250);
        setup();
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        victim->receive_damage("jing",query("str", me)*2,me);
        victim->receive_wound("jing",query("str", me)*2,me);
        return HIM "屠龍刀夾帶着刺耳的破空聲劃出一道道長虹，霎時間$n"
               HIM "只感到心神意亂。\n" NOR;
}

