// nanhai.c

#include <ansi.h>

inherit NPC;

void create()
{
        set_name(NOR + YEL "黃金" + HIW "白玉" + HIY "虎" NOR, ({ "gold tiger" }) );
        set("title", HIM "萬獸之王" NOR);
        set("gender", "男性");
        set("age", 2000);
        set("long", @LONG
這是一隻巨大的老虎，渾身金黃色，頭為白色，猶如白玉。
LONG );
        set("combat_exp", 1000000000);
        set("shen_type", 0);
        set("attitude", "heroism");
        set("max_neili", 300000);
        set("neili", 300000);
        set("max_jing", 300000);
        set("jing", 300000);
        set("max_qi", 1200000);
        set("qi", 1200000);
        set("jingli", 1200000);
        set("max_jingli", 1200000);

        set("str", 200);
        set("int", 100);
        set("con", 100);
        set("dex", 100);

        set_skill("unarmed", 2000);
        set_skill("sword", 1200);
        set_skill("parry", 1000);
        set_skill("dodge", 1000);
        set_skill("force", 1000);
        set_skill("martial-cognize", 1000);

        set("jiali", 300);

        set_temp("apply/attack", 1000);
        set_temp("apply/unarmed_damage", 1000);
        set_temp("apply/armor", 2000);

        if (clonep(this_object()))
        {
                set("chat_chance", 30);
                set("chat_msg", ({ (: random_move :) }));
                set("born_time", time());
                keep_heart_beat();
        }

        setup();
}

void fight_ob(object ob)
{
        if (is_fighting(ob))
                return;

        message_vision(HIW "$N一聲長嘯，張牙舞爪，面目猙獰。\n" NOR, this_object(), ob);

        ::fight_ob(ob);
        if( !is_killing(query("id", ob)) )
                kill_ob(ob);
}

int accept_fight(object ob)
{
        message_vision(HIW "$N" HIW "一聲長嘯，撲向$n" HIW "上來。\n" NOR,
                       this_object(), ob);
        kill_ob(ob);
        return -1;
}

int accept_kill(object ob)
{
        return 1;
}

int accept_hit(object ob)
{
        return 1;
}

mixed hit_ob(object me, object ob, int damage_bouns)
{
        ob->receive_wound("qi", 1000 + random(1000), me);
        set("neili",query("max_neili",  me), me);
        return HIW "$N" HIW "周圍紫氣大盛，面目猙獰，狂嘯一聲，登時令$n"
               HIW "迷惑不已，難以自拔。\n" NOR;
}

varargs void unconcious(object defeater)
{
        object ob;

        //if( query("end_boss") || query("fight_boss") )
        if( objectp(ob = previous_object(0)) && sscanf(base_name(ob), "/kungfu/skill/%*s") ) {
                full_self();
                return;
        }
        die(defeater);
        return;
}

varargs void die(object killer)
{
        object ob;

        if( objectp(ob = previous_object(0)) && sscanf(base_name(ob), "/kungfu/skill/%*s") )
        {
                full_self();
                return;
        }

        if (! objectp(killer))
                killer = query_last_damage_from();
        if (! objectp(killer))return;

        if( query("lunhui-sword_quest/chushengdao/give_quest", killer) )
        {
                tell_object(killer, BLINK + HIG "你已經殺死了黃金白玉虎，任務完成。\n" NOR);
                set("lunhui-sword_quest/chushengdao/killed", 1, killer);
                killer->save();
        }
        destruct(this_object());
}


void random_move()
{
        if (time() - query("born_time") > 1800)
        {
                message_vision("$N竄入叢林，消失了。\n", this_object());
                destruct(this_object());
                return;
        }
}
