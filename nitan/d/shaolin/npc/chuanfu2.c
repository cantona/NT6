// Npc: /d/shaolin/npc/chuanfu2.c

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("船夫", ({ "chuan fu", }));
        set("long", "這是常年在漢水專門管貨運的一位船夫。\n");

        set("gender", "男性");
        set("attitude", "peaceful");
        set("class", "bonze");

        set("age", 42);

        set("inquiry", ([
                "擺渡" : "不論貨多貨少，一船十兩紋銀，不二價。",
                "過河" : "不論貨多貨少，一船十兩紋銀，不二價。",
        ]));

        setup();
}

int accept_object(object who, object ob)
{
        object *obs;

        obs = filter_array(all_inventory(environment(who)),
                           (:query_temp("owner", $1) == $(who):));

        if (sizeof(filter_array(obs, (: ! $1->is_character() :))) < 1)
        {
                message_vision("船夫哼了一聲對$N道：“看清楚了，我這兒"
                               "只管貨運，沒有貨你添什麼亂？”\n", who);
                return 0;
        }

            if( query("money_id", ob) && ob->value() >= 1000 )
        {
                message_vision("船夫掂了掂" + ob->name() + "，對$N說：好！這就上船吧！\n" , who);
                message_vision("船夫叫來幾個年輕船夫，幫$N將貨拖上船，一聲「起錨」船就開走了。\n", who);
                who->move("/d/shaolin/hanshuim");
                if (sizeof(obs)) obs->move("/d/shaolin/hanshuim");
                tell_object(who, HIG "你悠閒的站在船頭，晃晃悠悠的過了漢水......\n" NOR);
                who->start_call_out((: call_other, __FILE__, "goto_peer", who, obs :), 10);
                destruct(ob);
                return -1;
        } else  
                message_vision("船夫白了$N一眼說：“這點錢？算了吧！”\n", who);

        return 0;
}

void goto_peer(object ob, object *obs)
{
        if (arrayp(obs) && sizeof(obs))
        {
                obs -= ({ 0 });
                if (sizeof(obs))
                        obs->move("/d/shaolin/hanshui1");
        }

        if (! objectp(ob) || environment(ob) != find_object("/d/shaolin/hanshuim"))
                return;

           tell_object(ob, "船終于到了對岸。你走下船來，船上的活計將你的貨都拉了下來。\n");
           ob->move("/d/shaolin/hanshui1");
}

void unconcious()
{
        ::die();
}