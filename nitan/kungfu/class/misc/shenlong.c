// nanhai.c

#include <ansi.h>

inherit NPC;

void create()
{
        set_name(HIG "碧海神龍" NOR, ({ "bihao shenlong", "bihai", "shenlong" }) );
        set("title", HIC "龍族" NOR);
        set("gender", "男性");
        set("age", 23);
        set("combat_exp", 10000000);
        set("shen_type", 0);
        set("attitude", "heroism");
        set("max_neili", 20000);
        set("neili", 20000);
        set("max_jing", 10000);
        set("jing", 10000);
        set("max_qi", 20000);
        set("qi", 20000);
        set("jingli", 10000);
        set("max_jingli", 10000);

        set("str", 30);
        set("int", 50);
        set("con", 50);
        set("dex", 50);

                set_skill("unarmed", 600);
                set_skill("sword", 600);
                set_skill("parry", 600);
                set_skill("dodge", 760);
                set_skill("force", 800);

        set("jiali", 300);

        set_temp("apply/attack", 500);
        set_temp("apply/unarmed_damage", 800);
        set_temp("apply/armor", 2400);

        if (clonep(this_object()))
        {
                set("chat_chance", 30);
                set("chat_msg", ({ (: random_move :) }));
                keep_heart_beat();
        }

        setup();
}

void fight_ob(object ob)
{
        if (is_fighting(ob))
                return;

        message_vision(HIC "$N" HIC "嘯叫一聲，渾身雲氣大盛，"
                       "霧氣彌漫。\n" NOR, this_object(), ob);

        ::fight_ob(ob);
        if (! is_killing(ob->query("id")))
                kill_ob(ob);
}

int accept_fight(object ob)
{
        message_vision("$N微一搖頭，略一擺尾，掃了上來。\n",
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
        ob->receive_wound("qi", 200 + random(200), me);

        return HIY "$N" HIY "周圍煙霧繚繞，光華四射，登時令$n"
               HIY "心力受損。\n" NOR;
}

void unconcious()
{
        die();
}

void random_move()
{
        if (! this_object()->is_fighting() && this_object()->query_temp("no_fighting_times") > 1)
        {
                message_vision(HIC "$N化作一道輕煙，消失了。\n" NOR, this_object());

                destruct(this_object());
                return;
        }

        if (! this_object()->is_fighting())this_object()->add_temp("no_fighting_times", 1);

    NPC_D->random_move(this_object());
}

