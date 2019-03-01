#include <ansi.h>
#include <armor.h>

inherit CLOTH;

void create()
{
        set_name(NOR + CYN "軟□甲" NOR, ({ "ruanwei jia", "ruanwei", "jia" }));
        set_weight(8000);
        if (clonep())
                destruct(this_object());
        else {
                set("unit", "件");
                set("long", NOR + CYN "
這是一件黑黝黝的軟甲，粗看下毫不起眼。這便是桃花島至寶
軟□甲，只見整個甲身烏黑亮澤，著手柔軟，卻又是堅硬勝鐵，
寶甲外圍還生滿了倒刺，尖利無比。\n" NOR);
                set("value", 100000);
                set("no_sell", "這是啥？黑不溜秋的。");
                set("material", "cloth");
                set("armor_prop/armor", 150);
                set("stable", 100);
        }
        setup();
}

mixed valid_damage(object ob, object me, int damage)
{
        if( !query_temp("weapon", ob )
            && !query_temp("secondary_weapon", ob )
            && !random(query("score", ob))<100000
           && random(50) == 1)
        {
                ob->receive_damage("qi", damage, me);
                ob->receive_wound("qi", damage * 2 / 3, me);

                return ([ "damage" : -damage,
                          "msg" : HIR "$N" HIR "一招剛觸及$n" HIR "身體，忽覺"
                                  "掌心一陣刺痛，大驚之下連忙縮手。\n" NOR ]);
        }
}