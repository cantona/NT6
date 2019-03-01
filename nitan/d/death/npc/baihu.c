inherit NPC;
#include <ansi.h>

void create()
{

        set_name(HIW "白虎" NOR,({"bai hu", "bai", "hu", "tiger"}));

        set("race", "野獸");
        set("long", HIW "\n\n一只長達丈許的巨型猛虎，乃四神獸之一的白虎。\n"
                        "它全身毛皮潔白無暇，很是高貴。\n" NOR);
        set("age", 10000);
        set("attitude", "peaceful");

        set("limbs", ({ "頭部", "身體", "前爪", "後爪", "虎尾" }) );
        set("verbs", ({ "bite" }) );
        set("title", HIY "神獸" NOR);

        set("combat_exp", 8000000);
        set("max_neili", 18000);
        set("neili", 18000);
        set("max_jing", 18000);
        set("jing", 18000);
        set("max_qi", 22000);
        set("qi", 22000);
        set("jingli", 18000);
        set("max_jingli", 18000);

        set("str", 45);
        set("int", 45);
        set("con", 45);
        set("dex", 45);

        set_skill("unarmed", 800);
        set_skill("sword", 800);
        set_skill("parry", 800);
        set_skill("dodge", 800);
        set_skill("force", 800);

        set("jiali", 100);

        set_temp("apply/attack", 150);
        set_temp("apply/unarmed_damage", 150);
        set_temp("apply/armor", 150);

        set_weight(500000000);

        setup();
}

void init()
{
        object me,ob;

        if (interactive(me = this_player()))
        {
                remove_call_out("kill_ob");
                call_out("kill_ob", 1, me);
        }
        ::init();
}

mixed hit_ob(object me, object ob, int damage_bouns)
{
        ob->receive_wound("qi", 200 + random(200), me);
        set("neili",query("max_neili",  me), me);
        return HIW "白虎噴出一團寒氣，剎時地面冰封九尺，四周冰雪"
               "紛飛，似乎連空氣都要被凍住一般。\n" NOR;
}

void die()
{
        object me;
        object gu, pi;

        int exp, pot;

        exp = 3000 + random(200);
        pot = 500 + random(50);

        gu = new("/d/death/obj/hugu");
        pi = new("/d/death/obj/hupi");

        if( objectp(me = query_last_damage_from()) &&
            query("wang_get/虎骨", me) && 
            query("wang_get/虎皮", me) && 
            userp(me) )
        {
                message_vision(HIC "$N" HIC "從白虎的屍體上除下了一張白虎"
                               "皮和一根虎骨。\n", me);
                gu->move(me);
                pi->move(me);
                delete("wang_get/虎骨", me);
                delete("wang_get/虎皮", me);
                addn("combat_exp", exp, me);
                addn("potential", pot, me);

                tell_object(me, HIC "由于你斬殺神獸白虎，你獲得了" + chinese_number(exp)
                                + "點經驗和" + chinese_number(pot) + "點潛能。\n" NOR);
        }

        if( objectp(me = query_last_damage_from()) &&
            query("wang_get/虎骨", me) && 
            userp(me) )
        {
                message_vision(HIC "$N" HIC "從白虎的屍體上除下了一根虎骨。\n", me);
                gu->move(me);
                delete("wang_get/虎骨", me);
                addn("combat_exp", exp, me);
                addn("potential", pot, me);
                if( query("potential", me)>me->query_potential_limit() )
                set("potential", me->query_potential_limit(), me);

                tell_object(me, HIC "由于你斬殺神獸白虎，你獲得了" + chinese_number(exp)
                                + "點經驗和" + chinese_number(pot) + "點潛能。\n" NOR);
        }

        if( objectp(me = query_last_damage_from()) &&
            query("wang_get/虎皮", me) && 
            userp(me) )
        {
                message_vision(HIC "$N" HIC "從白虎的屍體上除下了一張白虎皮。\n", me);
                pi->move(me);
                delete("wang_get/虎皮", me);
        }

        ::die();
}
