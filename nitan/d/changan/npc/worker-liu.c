// worker-liu.c

inherit NPC;

#include <ansi.h>

// 接收的貨物
#define CHECK_GOODS     "cuprum_ore"

void create()
{
        set_name("劉工匠", ({ "liu gongjiang", "liu", "worker" }) );
        set("title", HIY "天國大匠" NOR);
        set("gender", "男性" );
        set("age", 52);
        set("str", 33);
        set("long", @LONG
一個毫不起眼的老匠人，但是卻有著難以言喻的威嚴。從旁邊學徒工
人們的眼神中你感覺他不是一般的人物。
LONG);
        set("attitude", "friendly");

        setup();

        carry_object("/clone/cloth/cloth")->wear();
}

void init()
{
        set_heart_beat(1);
}

int filter_ob(object ob)
{
        object owner;

        if (! ob->is_transport())
                return 0;

        owner = ob->query_owner();
        if (! objectp(owner))
                // 該車無主
                return 0;

        if (environment(owner) != environment())
                // 主人不在
                return 0;

        if( query_temp("goods/id", ob) != CHECK_GOODS )
                // 沒有裝載銅礦石
                return 0;

        if( query_temp("goods/amount", ob)<1 )
                // 沒有貨
                return 0;

        return 1;
}

void heart_beat()
{
        object *obs;
        object ob;
        object owner;
        string startroom;
        int amount;
        mapping job;
        mapping goods;
        object bonus;

        ::heart_beat();
        if (! environment())
                return;

        if (! stringp(startroom = query("startroom")) ||
            find_object(startroom) != environment())
                // 不在出生地點
                return;

        obs = all_inventory(environment());
        obs = filter_array(obs, (: filter_ob :));
        if (sizeof(obs) < 1)
        {
                // 沒有到達合適的車輛，停止心跳
                set_heart_beat(0);
                return;
        }

        // 到達了合適的車輛
        ob = obs[0];
        owner = ob->query_owner();
        message_vision("$N看到$n押貨而來，連連點頭道：“很"
                       "好！很好！就卸到這裡吧！”\n",
                       this_object(), owner);
        tell_object(owner,"你卸下"+query_temp("goods/name", ob)+
                    "，將" + ob->name() + "交給學徒拉走。\n");

        // 卸下銅礦石
        goods=query_temp("goods", ob);
        amount = goods["amount"];
        environment()->improve_product_amount(goods["id"], amount);

        // 給與獎勵
        MONEY_D->pay_player(owner, amount * 10);
        tell_object(owner, "你領到了一些工錢。\n");
        if( query_temp("job/owner", ob) == owner )
        {
                // 這個是本人領的工作，獲得獎勵
                GIFT_D->work_bonus(owner, ([ "exp" : 1000 + random(500),
                                        "pot" : 500 + random(300),
                                        "score" : 30 + random(50),
                                        "prompt" : "通過這次押送" + goods["name"] + HIG ]));

                // 去掉我做這個工作的信息
                delete("job/"+query_temp("job/info", ob), owner);
        }
        destruct(ob);

        if (sizeof(obs) < 2)
        {
                // 已經處理完畢，沒有新的車輛到達，停止心跳
                set_heart_beat(0);
        }
}
