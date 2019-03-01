// punisher.c

#include <ansi.h>

inherit NPC;
int is_punisher() { return 1; }

void setup()
{
        addn_temp("apply/attack", 300);
        addn_temp("apply/defense", 300);
        addn_temp("apply/damage", 500);
        addn_temp("apply/unarmed_damage", 500);
        addn_temp("apply/armor", 2000);
        ::setup();
        set_heart_beat(1);
}

void init()
{
        add_action("do_halt", "halt");
}

int do_halt()
{
        object me;

        if (this_player() == query_temp("punish_ob"))
        {
                write(name() + "喝道：“逆徒！休走！”\n");
                return 1;
        }

        return 0;
}

void receive_damage(string type, int amount, object who)
{
        ::receive_damage(type, 1 + amount / 100, who);
}

void receive_wound(string type, int amount, object who)
{
        ::receive_wound(type, 1 + amount / 100, who);
}

mixed hit_ob(object me, object ob, int damage_bouns)
{
        ob->receive_wound("qi", 200 + random(200), me);
        set("neili", query("max_neili",me), me);
        return HIR "$N" HIR "一招突出，竟然是$n"
               HIR "聞所未聞，見所未見的招式，一驚之下，已然受創！\n" NOR;
}

void fight_ob(object ob)
{
        if (is_fighting(ob))
                return;

        if (ob != query_temp("punish_ob") &&
            ! is_fighting(ob))
        {
                message_vision("$N對$n冷笑道：“我在這裡清理門戶，你插手做甚？”\n",
                               this_object(), ob);
                if (! ob->is_busy())
                        ob->start_busy(2);
        }

        ::fight_ob(ob);
        if (! is_killing(query("id", ob)))
                kill_ob(ob);
}

int accept_fight(object ob)
{
        message_vision("$N不理$n。\n", this_object(), ob);
        return 0;
}

int accept_kill(object ob)
{
        return 1;
}

int accept_hit(object ob)
{
        command("say 嘿！且慢！");
        return 1;
}

void start_punish(object ob, string fam)
{
        set_temp("punish_ob", ob);
        set_temp("punishing_fam", fam);
        move(environment(ob));
        message_vision("$N走了過來，看到$n，冷笑一聲。\n", this_object(), ob);
        if (! this_object()->chat_punish())
        {
                // no chat for punish, use default
                command("chat " + ob->name(1) + "你背叛師門，今天我就替" + fam +
                        "清理你這個門戶敗類，留下武功，走你的路！");
        }
        command("follow " + query("id", ob));

        if (query("no_fight", environment(ob)))
        {
                tell_object(ob, "你看到" + name() + "，不由大吃一驚，慌忙轉身逃走。\n");
                message("vision", ob->name() + "看到" + name() +
                        "，臉色大變，慌裡慌張的轉身逃走。\n" +
                        name() + "冷笑一聲，喝道：“那裡走？”，緊隨其後追了上去。\n",
                        environment(ob), ({ ob }));
                ob->move("/d/city/guangchang");
                move("/d/city/guangchang");
                tell_object(ob, HIR "...這...這是哪裡？好熟悉啊？"
                            "你心底一橫，轉過身來，喝道：“不是魚"
                            "死，就是網破，來吧！”。\n" NOR);
                message("vision", ob->name() + "慌慌張張的跑了過來，只見有一人"
                        "緊隨其後而來。\n", environment(ob), ({ ob }));
        }

        command("yun powerup");
        kill_ob(ob);
}

void punish_ob(object ob)
{
        string fam;

        remove_enemy(ob);
        if (living(ob))
                ob->unconcious();

        message_vision("$N伸手粘在$n的後背，臉上煞氣一抹而過，喃喃"
                       "自語道：“你走吧！武功留下了！”\n",
                       this_object(), ob);

        fam = query_temp("punishing_fam");
        addn("detach/times", 1, ob);
        addn("detach/"+fam, 1, ob);
        if (addn("betrayer/times", -(int)query("betrayer/" + fam, ob), ob) < 1)
                delete("betrayer", ob);
        else
                delete("betrayer/"+fam, ob);

        ob->skill_expell_penalty();

        if (is_fighting())
        {
                // Am I in fighting now ?
                message_vision("$N冷冷道：“今天我走了，你們"
                               "幾個我改日再收拾！”\n",
                               this_object());
        }
        message_vision("$N撇下$n，揚長而去。\n", this_object(), ob);

        CHANNEL_D->do_channel(this_object(), "rumor", "聽說" +
                            ob->name(1) + HIM "因為背叛師門，被" +
                            name() + HIM "廢去一身武功。");
        destruct(this_object());
        return;
}

int attack()
{
        object ob;

        if (objectp(ob = query_temp("punish_ob")) &&
            ! living(ob) &&
            environment(ob) == environment())
        {
                punish_ob(ob);
                return 1;
        } else
                return ::attack();
}

void unconcious()
{
        die();
}

void die()
{
        command("chat 天哪！我" + name() + "難道...難道是不中用了？");
        ::die();
}

void scan()
{
        object ob;

        if (! environment())
        {
                destruct(this_object());
                return;
        }

        if (! objectp(ob = query_temp("punish_ob")) ||
            environment(ob) != environment() ||
            query("no_fight", environment(ob)))
        {
                message_vision("$N收住招式，悻悻道：“哼”，隨即轉身離去。\n",
                               this_object());
                destruct(this_object());
                return;
        }

        if (! living(ob))
        {
                punish_ob(ob);
                return;
        }

        if (! is_fighting(ob))
                fight_ob(ob);

        ::scan();
}

