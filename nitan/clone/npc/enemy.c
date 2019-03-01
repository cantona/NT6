// 守衛任務 NPC。

#include <ansi.h>

inherit CLASS_D("generate") + "/chinese"; 

#include <defend.h>

int is_stay_in_room()  { return 1; }

int do_nod(string arg);
void leave_here();
void move_enemy(object enemy, string family);

void create()
{
        NPC_D->generate_cn_name(this_object());
        set("long", "這人是前來攻打" + query("is_attacking")?query("is_attacking") : "別的門派"
                + "的一名" + query("family/family_name")?query("family/family_name") : "未知門派" +"弟子。\n");

        set("combat_exp", 100000 + random(500000));
        set("attitude", "peaceful");
        set("age", 18 + random(30));
        set("str", 20 + random(20));
        set("con", 20 + random(20));
        set("dex", 20 + random(20));
        set("int", 20 + random(20));
        
        set("chat_chance", 5);
        set("chat_msg", ({
                (: leave_here :), 
                (: random_move :), 
                (: random_move :), 
        }));

        set_temp("quest_ob", 1);
        
        setup();

        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        object me = this_player();

        ::init();

        if( interactive(me) && visible(me) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, me);
        }
        add_action("do_nod", "nod"); 
}

void greeting(object me)
{
        if (! me || ! present(me, environment())) 
                return;

        if (interactive(me) && 
            query_temp("defend_quest/start", me) && 
            me->query_family() == query("is_attacking") &&
            !query_temp("defend_quest/finish", me) )
        {
                // 這裡的描寫似乎需要調整（正派說這種話不合身份）
                command("grin");
                message_sort(HIW "只見$N" HIW "獰笑著對$n" HIW "道：“嘿嘿，不知死活的" +
                        RANK_D->query_rude(me) +"，竟然敢和我們" + this_object()->query_family() +"做對？！"
                        "看我來教訓教訓你！”\n", this_object(), me );
                        
                kill_ob(me);
                return;
        }
        message_vision(HIW "$N" HIW "冷冷地掃了$n" HIW "一眼。\n", this_object(), me );
}

void kill_ob(object me)
{
        object ob = this_object();

        if( !query_temp("defend_quest", me) || query_temp("defend_quest/finish", me) )
                return ::kill_ob(me);
        else
        {
                // 復制狀態，需要調整。
                NPC_D->set_from_me(ob, me, 100 + random(20));
                NPC_D->init_npc_skill(ob, NPC_D->check_level(me) + (1 + random(2)));
                ::kill_ob(me);
                return;
        }
}

// 如果接受了賄賂
int do_nod(string arg)
{
        object me = this_player();
        object ob = this_object();
        int amount;

        if( !query_temp("defend_quest/waiting", me) || 
            query_temp("defend_quest/finish", me) || 
            !arg || arg != query("id", ob) )
                return 0;

        else 
        {
                me->command("nod");
                if( intp(query_temp("defend_quest/waiting", me)) )
                {
                        amount=query_temp("defend_quest/waiting", me);

                        message_sort(HIW "只見$N" HIW "長笑三聲：“哈哈哈，識時務者為俊傑，" +
                                     RANK_D->query_respect(me) + "果然是明白人，嘿嘿，這區區" +
                                     chinese_number(amount) + "兩白銀就歸你了，哈哈。”\n\n" NOR,
                                     ob, me);

                        MONEY_D->pay_player(me, amount * 100);
                        set_temp("defend_quest/accepted", 1, me);
                        tell_object(me, HIR + ob->name() + "遞給了你" + chinese_number(amount) + 
                                        "兩白銀以後，吐出一口鮮血，揚長而去。\n" NOR );
                        return 1;
                }
                else return  0;
        }
}

void die()
{
        int percent;
        object me, ob = this_object();
        string *pills, pill;
        int amount = 300 + random(300);
        string *condition = ({
                "氣喘吁吁，就要不支", "頭重腳輕，馬上就倒", 
                "嘔血成升，眼冒金星", "傷痕累累，無力招架", 
        });

        if (objectp(me = ob->query_last_damage_from()) 
        &&  environment(ob) == environment(me) 
         && query_temp("defend_quest/start", me )
         && !query_temp("defend_quest/finish", me )
         && !query_temp("defend_quest/waiting", me) )
        {
                switch (random(15)) 
                {
                        case 1: {
                                message_sort(HIR "眼見$N" HIR + condition[random(sizeof(condition))]
                                                +"，突然$N大喝一聲，急退幾步，\n“撲通”給$n跪了下來。"
                                                "\n" NOR, ob, me);
                                tell_object(me, HIW + ob->name()+"突然從懷裡掏出一堆白花花的銀子，小聲"
                                                "對你道：“這位" + RANK_D->query_respect(me) + "，\n你"
                                                "就網開一面（nod）如何，這" + chinese_number(amount) +
                                                "兩白銀就歸你了！”\n" NOR);
                                ob->clean_up_enemy();
                                ob->remove_all_enemy(0);
                                ob->clear_condition(0);
                                set("jing", 1, ob);
                                set("qi", 1, ob);
                                set_temp("defend_quest/waiting", amount, me);
                                return;
                        }
                        default: {
                                // 獎勵
                                if( query("family/family_name", me) == query("is_attacking", ob) )
                                        addn_temp("defend_quest/killed", 1, me);
                                
                                set_temp("die", 1, ob);
                                
                                QUEST_D->bonus(me, ([ "exp" : 10 + random(30),
                                                      "pot" : 3 + random(20),
                                                      "score" : 3 + random(20) ]));
                                return ::die(me);
                        }
                }
                return;
        }
        if( objectp(me) && query("family/family_name", me) == query("is_attacking", ob) )
        {
                addn_temp("defend_quest/killed", 1, me);

                QUEST_D->bonus(me, ([ "exp" : 10 + random(30),
                                      "pot" : 3 + random(20),
                                      "score" : 3 + random(20) ]));
        }
        return ::die();
}


void leave_here()
{
        object ob = this_object();

        if( ob->is_fighting() || ob->is_busy() || query("qi", ob)<40
         || !query("is_attacking", ob) || ob->is_unconcious() )
                return;
                
        move_enemy(ob,query("is_attacking", ob));
        return;
}

// 送走敵人（在 ENEMY 的 chat_msg 中也有呼叫）
void move_enemy(object enemy, string family)
{
        string *places = familys[family]["place"];
        string place = places[random(sizeof(places))];
        object room;

        if (objectp(room = environment(enemy)))
        {
                tell_room(room, enemy->name() + "一閃身就不見了。\n");
        }
#ifdef DEBUG        
        CHANNEL_D->do_channel(this_object(), "sys",
                sprintf("%s : %O", enemy->short(), place)); 
#endif
        enemy->move(place);
        tell_room(place, "只見一名" + enemy->query_family() + "弟子不知什麼時候鑽了出來。\n");

        return;
}
