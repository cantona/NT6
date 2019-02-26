 // walker.c
 // Updated By Plzw for walker quest 2004-08-17


#include <ansi.h>

//#define ONEDAY (86400 / 365)
#define ONEDAY 480


inherit NPC;

int do_walk();
int ask_quest();

void create()
{
        set_name("拾荒者", ({ "walker" }));
        set("gender", "男性");
        set("age", 53 + random(20));
        set("long", @LONG
這是一個拾荒者，看上去老實巴交的。不過聽
説他和官府有交情，最好別去招惹。
LONG);
        set("attitude", "heroism");
        set("str", 35);
        set("int", 15);
        set("con", 19);
        set("dex", 17);
        
        set_skill("gleaning", 600);

        set("chat_chance", 30);
        set("chat_msg", ({
                (: do_walk :),
        }));

        set("inquiry", ([
                "拾荒" : (: ask_quest :),
                "help" : (: ask_quest :),
        ]));
        setup();
        if (clonep()) keep_heart_beat();

        set("check_time", time());
        carry_object("/clone/cloth/cloth")->wear();
}

int do_walk()
{
        string start_room;
        object room;
        object ob;
        mapping obmap;
        int n;

        if (! environment())
                return 0;

        if (time() - query("check_time") > 900)
        {
                if (! stringp(start_room = query("startroom")) ||
                    ! objectp(room = find_object(start_room)) ||
                    !mapp(obmap=query_temp("objects", room)) || 
                    member_array(this_object(), values(obmap)) == -1)
                {
                        message_vision(CYN "$N" CYN "歎了歎氣，走了。\n"
                                       NOR, this_object());
                        destruct(this_object());
                        return 0;
                }

                set("check_time", time());
        }

        n = 0;
        foreach (ob in all_inventory(environment()))
        {
                if (ob->is_character() ||
                    ob->is_head() ||
                    query("no_get", ob) )
                        continue;
                destruct(ob);
                n++;
        }

        if (n == 1)
                message_vision(HIC "$N" HIC "一彎腰，從地上撿起一樣"
                               "東西。\n" NOR, this_object());
        else
        if (n > 1)
                message_vision(HIC "$N" HIC "彎腰在地上摸摸索索找了"
                               "半天，撿起一堆東西。\n" NOR,
                               this_object());
                        
        random_move();
        return 1;
}

void unconcious()
{
        die();
}

int ask_quest()
{
        int t, count;
        object ob = this_player();
        // 閲歷不夠不能領取任務
        if( query("score", ob)<2000 )
        {
                command("say 你這點閲歷，恐怕地圖都還沒有跑熟吧，別在這裏給我添亂了！\n");
                return 1;
        }
        // 拾荒技能不夠不能領取任務
        if (ob->query_skill("gleaning", 1) < 30)
        {
                command("say 你估計連什麼是垃圾都不知道，還是和我學學再説吧！\n");
                return 1;
        }
        // 不能連續領任務
        if( query("walker_quest/finish_time", ob) )
        {
                if( time()-query("walker_quest/finsh_time", ob)<ONEDAY )
                {
                        command("say 你幫我也要注意身體，還是休息休息，改天再做吧！\n");
                        return 1;
                }
            }
        // 已經領過任務尚未完成
        if( query("walker_quest/count", ob) )
        {
                command("say 你不是答應我幫我拾荒了嗎？還站在這裏羅嗦什麼？\n");
                return 1;
        }
        // 領取任務
        t = time();
        set("walker_quest/time", t, ob);
        // 任務個數
        count = random(9) + 1;
        set("walker_quest/count", count, ob);
        if (count > 5)
                t += 3 * ONEDAY;
        else
                t += 2 * ONEDAY;
        set("walker_quest/limit", t, ob);

        message("vision", WHT + name() + WHT "小聲的對" + ob->name() +
                          WHT "吩咐着什麼，" + ob->name() +
                          WHT "一邊聽，一邊不住的點頭。\n" NOR,
                          environment(ob), ({ ob }));
        message("vision", WHT + name() + WHT "在你耳邊悄聲説道：你就去幫我"
                                          NOR + HIY + CHINESE_D->chinese_number(count) + NOR + WHT
                                          "件垃圾來吧！\n你務必要在" NOR + HIY + CHINESE_D->chinese_monthday(t) + NOR + WHT
                          "之前完成！\n" NOR, ob);
        ob->start_busy(1);
        return 1;
}

int accept_object(object who, object ob)
{
        int count, intime, amount, pot, score, weiwang, exp;
        object gold, silver;
        // 沒有領過任務
        if( !query("walker_quest/count", who) )
        {
                command("say 你給我這個東西幹嗎？\n");
                return -1;
        }
        // 非任務物品
        if( !query("walker_item", ob) )
        {
                command("say 這些東西別人還有用，你怎麼就給揀來了？\n");
                return -1;
        }
        count=query("walker_quest/count", who);
        set("walker_quest/count", count-1, who);
        if( query("walker_quest/limit", who)>time() )
                intime = 1;
        else
                intime = 0;
        if (intime)
                command("say 恩，做得不錯，這是給你的獎勵。\n");
        else
                command("say 恩，雖然晚了點，但也還不錯，這是給你的獎勵。\n");
        amount = random(2) + 1;
        exp = random(30) + 10;
        pot = exp / 3;
        score = random(5) + 2;
        weiwang = random(2) + 1;
        if (intime)
        {
                // 1/4的機率獲得額外的獎勵
                if (random(4)==0)
                        amount++;
                gold = new("/clone/money/gold");
                gold->set_amount(amount);
                gold->move(this_object());
                command("give gold to "+query("id", who));
                // 如果及時完成的話，得到的獎勵加倍
                pot *= 2;
                score *= 2;
                exp *= 2;
        }
        else
        {        
                amount = amount * 50;
                silver = new("/clone/money/silver");
                silver->set_amount(amount);
                silver->move(this_object());
        }
                
                // 如果拾荒技能超過60級則獎勵加倍
                if (who->query_skill("gleaning", 1) >= 60)
                {
                        pot *= 1.5;
                        score *= 2.5;
                        exp *= 2;
                }
        GIFT_D->work_bonus(who, ([ "exp" : exp, "pot" : pot, "score" : score ]));
        addn("weiwang", -weiwang, who);
        if( query("weiwang", who)<0 )
                set("weiwang", 0, who);
        // 全部完成
        if( query("walker_quest/count", who) == 0 )
        {
            set("walker_quest/finish_time", time(), who);
            command("say 好了，你也累了，去休息休息吧！\n");
        }
        else
                       message("vision", WHT + name() + WHT "在你耳邊悄聲説道：你還需要幫我揀"
                                          NOR+HIY+CHINESE_D->chinese_number(query("walker_quest/count", who))+NOR+WHT
                                          "件垃圾。\n" NOR, who);
        destruct(ob);
        return 1;
}

int recognize_apprentice(object me, string skill)
{

        if (skill != "gleaning")
        {
                command("say 我除了拾荒在行，其他可什麼都不會啊。\n");
                return -1;
        }

        return 1;
}
