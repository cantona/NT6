// shanzheng.c 單正

#include <ansi.h>
#include <quest.h>

inherit NPC;

void create()
{
        set_name("單正", ({ "shan zheng", "shan" }));

        set("gender", "男性");
        set("age", 62);
        set("long", "他體態魁梧，相貌威嚴，長的一副童顏鶴髮。\n");
        set("attitude", "peaceful");
        
        set("nickname", HIR "鐵面判官" NOR);

        set("str", 35);
        set("int", 36);
        set("con", 31);
        set("dex", 30);

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "blade.duan" :),
                (: perform_action, "unarmed.zhen" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set("inquiry", ([
                "鐵面判官" : "這是江湖好友給在下的稱號，見笑了。",
                "單正" : "沒錯，就是我了，怎麼，找我有事？",
                "審案" : "哪裏的案子？",
                "判案" : "哪裏的案子？",
        ]));

        set("shen_type", 1);

        set("qi", 3000);
        set("max_qi", 3000);
        set("jing", 1500);
        set("max_jing", 1500);
        set("neili", 4500);
        set("max_neili", 4500);
        set("jiali", 50);

        set("combat_exp", 800000);
        set("score", 5000000);

        set_skill("force", 150);
        set_skill("huntian-qigong", 150);
        set_skill("dodge", 160);
        set_skill("feiyan-zoubi", 150);
        set_skill("parry", 150);
        set_skill("blade", 150);
        set_skill("unarmed", 150);
        set_skill("taiji-quan", 150);
        set_skill("wuhu-duanmendao", 150);

        map_skill("force", "huntian-qigong");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("parry", "taiji-quan");
        map_skill("blade", "wuhu-duanmendao");

        set_temp("apply/attack", 100);
        set_temp("apply/defense", 100);
        set_temp("apply/damage", 80);
        set_temp("apply/unarmed_damage", 80);

        setup();
        carry_object("/clone/weapon/gangdao")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}

varargs int move(mixed dest, int raw)
{
        int r;

        // 執行原本的MOVE函數
        r = ::move(dest, raw);

        if (objectp(query_temp("run_ob")))
        {
                // 正在執行任務，察看是否到了地點
                remove_call_out("give_intercession");
                call_out("give_intercession", 2);
        }

        return r;
}

mixed accept_ask(object who, string topic)
{
        object *obs;
        object follow;
        object run_ob;

        obs = filter_array(children("/clone/quest/judge"),
                           (: $1->name() == $(topic) :));
        if (sizeof(obs) > 0)
        {
                if( query("weiwang", who)<5000 )
                        return "你算哪一號人物，居然也管起江湖上的事情來了？";

                follow = query_leader();
                if (objectp(follow) && environment(follow) == environment())
                {
                        // 正在跟隨另外一個人，察看當前執行
                        // 的任務。
                        run_ob = query_temp("run_ob");

                        if (follow == who)
                        {
                                // 跟隨的就是目前發問的人
                                if (! objectp(run_ob))
                                {
                                        // 由於原先的事情取消了，所以
                                        // 可以更換一件事情
                                        set_temp("run_ob", obs[0]);

                                        // 取消返回或是調解的定時呼叫
                                        remove_call_out("do_back");
                                        remove_call_out("give_intersession");

                                        // 四分鐘以後解除跟隨狀態
                                        remove_call_out("cancel_follow");
                                        call_out("cancel_follow", 240);
                                        return "好吧，剛才那件事情聽説也了了，咱們就換換吧！";
                                }

                                // 跟隨的就是發話的人
                                return "咱們快走吧！不是要辦" +
                                       run_ob->name() + "麼？別磨蹭了。";
                        }

                        if (run_ob == obs[0])
                                // 其他人詢問相同的事情
                                return "我現在正是和" + follow->name() +
                                       "去辦這件事的，不勞你費心了。";

                        if (objectp(run_ob))
                                // 其他人詢問不同的事情
                                return "我現在要和" + follow->name() +
                                       "去辦" + run_ob->name() + "，你先等等吧。";

                        message_vision("$N回頭對$n道：“我聽説你那件事情"
                                       "已經了了，我先走了。”\n",
                                       this_object(), follow);
                }

                // 我現在沒有跟誰人
                message_vision("$N點點頭，對$n道：“這事我也"
                               "略有耳聞，就和你走一趟吧！”\n",
                               this_object(), who);
                set_temp("run_ob", obs[0]);
                command("follow"+query("id", who));

                // 取消返回或是調解的定時呼叫
                remove_call_out("do_back");
                remove_call_out("give_intersession");

                // 四分鐘以後解除跟隨狀態
                remove_call_out("cancel_follow");
                call_out("cancel_follow", 240);
                return 1;
        }

        switch (random(3))
        {
        case 0:
                return "要是聽説哪兒有不公之事，儘可以告訴我，"
                       "不過你説的這個我實在不太清楚。";
        case 1:
                return RANK_D->query_respect(who) + "，你説的"
                       "這個事我不太清楚啊。";
        default:
                return "我只幫人斷案排憂，你説的這個究竟是啥事情？";
        }
}

// 判斷是否有人需要調解
void give_intercession()
{
        object run_ob;
        object npc1;
        object npc2;
        object me;
        int npc1_present, npc2_present;
        int percent;

        if (! objectp(run_ob = query_temp("run_ob")))
                // 現在沒有調解任務
                return;

        npc1=query("npc1", run_ob);
        npc2=query("npc2", run_ob);
        npc1_present =  (objectp(npc1) && environment(npc1) == environment());
        npc2_present =  (objectp(npc2) && environment(npc2) == environment());
                
        if (! npc1_present || ! npc2_present)
                // 這個場景沒有需要調解的人
                return;

        if (! npc1_present)
        {
                // 只有NPC2
                message_vision("$N看了看四周，搖頭道：“只有" +
                               npc2->name() +"一個人了，還調"
                               "解什麼？我還是走吧！”\n", this_object());
                set_leader(0);
                call_out("do_back", 1);
                return;
        }

        if (! npc2_present)
        {
                // 只有NPC1
                message_vision("$N看了看四周，搖頭道：“只有" +
                               npc1->name() +"一個人了，還調"
                               "解什麼？我還是走吧！”\n", this_object());
                set_leader(0);
                call_out("do_back", 1);
                return;
        }

        me = query_leader();
        message("vision", sort_msg(name() + "看了看" + npc1->name() +
                "和" + npc2->name() + "，搖搖頭，喝道：“大家"
                "都是武林人士，何苦為了一些小事爭執不休？沒得"
                "失了顏面！”\n"), environment());
        message("vision", HIG + name() + HIG "開始勸説調解二人，聽"
                "得兩人連連點頭，不敢放肆。\n" NOR, environment());
        if (objectp(me))
        {
                tell_object(me, CYN "你聽了" + name() + CYN
                            "調解二人的話語，甚是得理，眼見"
                            "二人心服口服，不由得暗自欣慰。\n" NOR);
                CHANNEL_D->do_channel(find_object(QUEST_D), "task",
                        "聽説"+me->name(1)+"("+query("id", me)+
                        ")請到鐵面判官" + name() + WHT "為" +
                        npc1->name() + WHT "和" + npc2->name() +
                        WHT "成功的調解了糾紛。");
                percent=30000*100/(random(query("weiwang", me)+1)+30000);
                QUEST_D->bonus(me, ([ "exp" : 100 + random(100),
                                      "pot" : 30 + random(50),
                                      "score" : 10 + random(10),
                                      "weiwang" : 10 + random(20),
                                      "percent" : percent,
                                      "prompt" : "通過這次為人調解糾紛" ]));

                if( query("quest/freequest", me)>0 )
                        GIFT_D->delay_freequest_bonus(me);
        }

        delete_temp("run_ob");
        set_leader(0);
        run_ob->change_status(QUEST_FINISH);
        remove_call_out("cancel_follow");
        call_out("do_back", 2);
}

// 停止跟蹤
void cancel_follow()
{
        object ob;

        // 去掉正在做的任務信息
        delete_temp("run_ob");

        // 現在沒有領路的？直接返回
        if (! objectp(ob = query_leader()))
        {
                call_out("do_back", 1);
                return;
        }

        // 不再跟隨
        set_leader(0);
        message_vision("$N歎道：“我看你也是迷迷糊糊的，算"
                       "了，我還是先走了吧！以後有事再説！”\n",
                       this_object());
        call_out("do_back", 1);
}

// 返回
void do_back()
{
        string startroom;

        if (! stringp(startroom = query("startroom")))
                return;

        if (! living(this_object()))
        {
                call_out("do_back", 10);
                return;
        }

        if (is_fighting())
        {
                message_vision("$N忽然罷手，道：“老夫不能奉陪了，走了！”\n"
                               "話音剛落，$N就急急忙忙的走了，你不由的一愣神。\n",
                               this_object());
        } else
                message_vision("$N歎了口氣，頭也不回的走了。\n",
                               this_object());

        // 返回故地
        move(startroom);
        message("vision", name() + "趕了過來。\n", environment());
}

void unconcious()
{
        message_vision("$N大叫一聲：“氣殺我也！”\n", this_object());
        die();
}

int return_home(object home)
{
        if (objectp(query_leader()))
                return 0;

        return ::return_home(home);
}
