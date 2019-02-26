// helper for user

#include <ansi.h>

inherit CLASS_D("generate") + "/chinese";

void create()
{
        ::create();
        set("gender", "男性" );
        set("age", 15 + random(20));
        set("long", "");
        set("attitude", "friendly");
        set("chat_chance_combat", 120);
        set_temp("apply/damage", 15);
}

void init_man(mapping p)
{
        mapping my;

        my = query_entire_dbase();
        my["qi"] = my["eff_qi"] = my["max_qi"] = p["life"];
        my["jing"] = my["eff_jing"] = my["max_jing"] = p["life"] / 2;
        my["neili"] = my["max_neili"] = p["neili"];
        my["jingli"] = my["max_jingli"] = p["neili"] / 4;
        my["jiali"] = query_skill("force") / 2;

        set_temp("apply/armor", 100);
}

void kill_ob(object ob)
{
        if( query("family/family_name", ob) == query("family/family_name") )
        {
                message_vision(HIC "$N" HIC "看了看對方，連忙往後一跳，"
                               "大聲喊道：“大家住手！有話好説！”\n" NOR,
                               this_object());
                return;
        }

        ::kill_ob(ob);
}

int accept_fight(object ob)
{
        message_vision("$N連連搖頭，道：“不必了，我沒有興趣。”\n",
                       this_object());
        return 0;
}

int accept_hit(object ob)
{
        message_vision("$N往後一退，道：“我可沒有興趣和你過招。”\n",
                       this_object());
        return 0;
}

int accept_kill(object ob)
{
        if (ob == query_temp("owner"))
        {
                message_vision("$N向後一退，大聲喊道：“所謂合則留，不合"
                               "則去，我是不能侍奉你了！”\n説罷，也不待"
                               "$n回話，自顧去了。\n", this_object(), ob);
                destruct(this_object());
                return -1;
        }

        message_vision("$N一聲冷笑，道：“豈有此理！接招吧！”\n",
                       this_object());
        return 1;
}

void destruct_by_owner()
{
        call_out("destruct_me", 1);
}

protected void destruct_me()
{
        destruct(this_object());
}

void scan()
{
        object ob;
        object env;
        object *obs;
        object enemy;

        if (objectp(query_temp("renter")))
                return;

        if (! objectp(ob = query_temp("owner")))
        {
                if (environment())
                        message_vision("$N急急忙忙的走了。\n", this_object());
                destruct(this_object());
                return;
        }

        if ((time() - query_temp("help_time")) >= 86400)
        {
                if (environment())
                {
                        command("tell"+query("id", ob)+"跟隨你一年，是"
                                "時候回俠客島啦，改日再會吧！\n");
                        message_vision("$N急急忙忙的走了。\n", this_object());
                }
                destruct(this_object());
        }

        ::scan();

        env = environment(ob);
        if (environment() == env || ob->is_ghost())
                // 和主人在的地點相同，或是主人處於鬼魂狀態
                return;

        if (is_busy() || is_fighting() || ! living(this_object()))
                // 現在忙
                return;

        if( !sizeof(query("exits", env)) || 
            ! sizeof(query("exits",environment())))
                return;

        message_vision("$N急急忙忙的走開了。\n", this_object());
        if (! move(env)) return;
        obs = filter_array(all_inventory(env),
                           (: $1->is_character() &&
                              $1->is_killing(query("id", $(ob))) &&
                              $1->query_competitor() != $(ob) :));
        if (sizeof(obs))
        {
                message_vision("$N急急忙忙的敢了過來，看見$n正"
                               "在苦鬥，當即大喝一聲，加入了$n的戰團！\n",
                               this_object(), ob);
                foreach (enemy in obs) kill_ob(enemy);
        } else
                message_vision("$N走了過來，站在$n的身後。\n",
                               this_object(), ob);
}
