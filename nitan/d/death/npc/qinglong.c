inherit NPC;
#include <ansi.h>

void create()
{

        set_name(GRN "青龍" NOR,({"qing long", "qing", "long", "dragon"}));

        set("race", "野獸");
        set("long", GRN "\n\n一條長達數十丈的神龍，乃四神獸之一。它騰\n"
                        "雲駕霧，張牙舞爪，口中噴著熊熊烈火。\n" NOR);
        set("age", 10000);
        set("attitude", "peaceful");

        set("limbs", ({ "頭部", "身體", "前爪", "後爪", "龍尾", "龍角" }) );
        set("verbs", ({ "bite" }) );
        set("title", HIY "神獸" NOR);

        set("combat_exp", 10000000);
        set("max_neili", 20000);
        set("neili", 20000);
        set("max_jing", 20000);
        set("jing", 20000);
        set("max_qi", 25000);
        set("qi", 25000);
        set("jingli", 20000);
        set("max_jingli", 20000);

        set("str", 50);
        set("int", 50);
        set("con", 50);
        set("dex", 50);

        set_skill("unarmed", 800);
        set_skill("sword", 800);
        set_skill("parry", 800);
        set_skill("dodge", 800);
        set_skill("force", 800);

        set("jiali", 100);

        set_temp("apply/attack", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 100);

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
        return HIR "青龍噴出一團烈火，青龍潭內頓時揚起一片火海，潭水沸騰，似"
               "乎整個大地都要被烤焦了一般。\n" NOR;
}

void die()
{
        object me;
        object jin, dan;

        int exp, pot;

        exp = 3000 + random(200);
        pot = 500 + random(50);

        jin = new("/d/death/obj/longjin");
        dan = new("/d/death/obj/longdan");

        if( objectp(me = query_last_damage_from()) &&
            query("wang_get/龍膽", me) && 
            query("wang_get/龍筋", me) && 
            userp(me) )
        {
                message_vision(HIC "$N" HIC "從青龍的屍體上除下了一根龍筋和"
                               "一只龍膽。\n", me);
                jin->move(me);
                dan->move(me);
                delete("wang_get/龍膽", me);
                delete("wang_get/龍筋", me);
                addn("combat_exp", exp, me);
                addn("potential", pot, me);
                if( query("potential", me)>me->query_potential_limit() )
                set("potential", me->query_potential_limit(), me);

                tell_object(me, HIC "由于你斬殺神獸青龍，你獲得了" + chinese_number(exp)
                                + "點經驗和" + chinese_number(pot) + "點潛能。\n" NOR);
        }

        if( objectp(me = query_last_damage_from()) &&
            query("wang_get/龍膽", me) && 
            userp(me) )
        {
                message_vision(HIC "$N" HIC "從青龍的屍體上除下了一只龍膽。\n", me);
                dan->move(me);
                delete("wang_get/龍膽", me);
                addn("combat_exp", exp, me);
                addn("potential", pot, me);

                tell_object(me, HIC "由于你斬殺神獸青龍，你獲得了" + chinese_number(exp)
                                + "點經驗和" + chinese_number(pot) + "點潛能。\n" NOR);
        }

        if( objectp(me = query_last_damage_from()) &&
            query("wang_get/龍筋", me) && 
            userp(me) )
        {
                message_vision(HIC "$N" HIC "從青龍的屍體上除下了一根龍筋。\n", me);
                jin->move(me);
                delete("wang_get/龍筋", me);
        }

        ::die();
}
