#include "roomnpc.h"

inherit NPC;

void greeting(object ob);
void init();
int  accept_object(object who, object ob);

void create()
{
        set_name("丫鬟", ({"girl", "ya huan"}) );
        set("gender", "女性" );
        set("age", 12 + random(6));
        set("long", "這是個年齡不大的小姑娘，一臉聰明乖巧。");
        set("attitude", "friendly");

        setup();
}

void init()
{
        object ob;

        ::init();

        if (interactive(ob = this_player()) && !is_fighting())
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if (! ob || (environment(ob) != environment())) return;

        if (is_owner(ob))
        {
                message_vision(name() + "對$N盈盈道了一個萬福。\n", ob);
                command("say 有什麼吩咐嗎？");
                return;
        }
        message_vision(name() + "對$N道：“這位" + RANK_D->query_respect(ob) +
                "好。”\n", ob);
}

int accept_object(object who, object ob)
{
        object obn;

        if( !query("money_id", ob) )
                return 0;

        if (is_owner(who))
        {
                message_vision(name() + "對$N施了一禮。\n", who);
                destruct(ob);
                return 1;
        }

        if (ob->value() < 1000)
        {
                if (owner_is_present())
                {
                        say(name() + "不情願的接下了" + ob->name() + "。\n");
                        destruct(ob);
                        return 1;
                }
                message_vision(name() + "杏目園睜，喝道：“你以為是打"
                               "發叫花子啊？”\n", who);
                return 0;
        }

        destruct(ob);
        message_vision(name() + "對$N微微一笑，道：“多謝這位" +
                       RANK_D->query_respect(who) + "啦！”\n", who);
        return 1;
}
