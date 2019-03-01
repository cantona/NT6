#include <ansi.h>
inherit NPC;
void create()
{
        string *names = ({"灰毛惡狼","黃毛惡狼","白毛惡狼"});
        set_name( names[random(sizeof(names))], ({ "wolf"}));
        set("vendetta_mark","wolf");
        set("race", "野獸");
        set("gender", "雄性");
        set("age", 20);
        set("long", "這是一只殘忍的惡狼。\n");

        set("str", 40);
        set("cor", 100);
        set("cps", 22);
        set("max_qi", 2000);
        set("max_jing", 1000);
        set("max_neili", 2000);
        set("attitude", "peaceful");
        set("chat_chance", 2);

        set("limbs", ({ "頭部", "身體", "前腳", "後腳", "尾巴" }) );
        set("verbs", ({ "bite", "claw" }) );
        set("combat_exp", 100000);
        set("bellicosity", 5 );

        set_temp("apply/attack", 20);
        set_temp("apply/dodge", 20);
        set_temp("apply/parry", 20);
        set_temp("apply/unarmed_damage", 10);
        setup();
        carry_object(__DIR__"obj/wolf_skin");
}

mixed hit_ob(object me, object victim, int damage_bonus)
{
        victim->receive_damage("qi",30+random(30), me);
        victim->receive_wound("qi",10+random(10), me);
        message_combatd(HIW"\n$N"+HIW"鋒利的爪子在$n"+HIW"身上留下一道血淋淋的傷口！"NOR,me,victim);
        return;
}