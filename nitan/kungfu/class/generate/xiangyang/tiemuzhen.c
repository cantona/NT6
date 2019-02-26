// person used in quest

#include <ansi.h>

inherit NPC;

void random_move();
int  is_stay_in_room()  { return 1; }
void shot_arrow();

void create()
{
        object arrow;

        set_name(HIR "鐵木真" NOR, ({"tie muzhen", "tie", "muzhen" }));
        set("gender", "男性");
        set("age", 40 + random(20));
        set("long", "這就是傳説中蒙古大汗，成吉思汗鐵木真，只見其身材高大魁梧，英氣逼人，令人生畏！");
        set("chat_chance", 130);
        set("chat_msg", ({ (: random_move :) }));
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({ 
                        (: perform_action, "blade.tian" :),
                        (: perform_action, "blade.po" :),
                        (: exert_function, "shield" :),
                        (: exert_function, "powerup" :),
                        (: exert_function, "recover" :),                        
                        (: shot_arrow :),
        }));
        set("no_get", 1);

        // 蒙古士兵標誌
        set("mgbing", 1);

        set_temp("apply/armor", 15000);
        set_temp("apply/damage",20000);
        set_temp("apply/attack", 100000); // 高命中

                set("str", 100);
                set("int", 90 + random(24));
                set("dex", 50);
                set("con", 50);

                set("combat_exp", 2000000000);

                set("max_qi", 40000000);
                set("eff_qi", 40000000);
                set("qi", 40000000);
                set("max_neili", 120000);
                set("neili", 100000000);
                set("max_jingli", 1800000);
                set("jingli", 1800000);

                set_skill("dodge", 2500);
                set_skill("blade", 2500);
                set_skill("daojian-guizhen", 2500);
                set_skill("lingxu-bu", 2500);
                set_skill("force", 2500);
                set_skill("jiuyang-shengong", 2500);
                set_skill("unarmed", 2500);
                set_skill("changquan", 2500);
                set_skill("sword", 2500);
                set_skill("taiji-jian", 2500);
                set_skill("martial-cognize", 2500);
                set_skill("daojian-xiaotianwai", 500);
                set_skill("jingluo-xue", 400);

                map_skill("dodge", "lingxu-bu");
                map_skill("blade", "daojian-guizhen");
                map_skill("parry", "taiji-jian");
                map_skill("force", "jiuyang-shengong");
                map_skill("unarmed", "changquan");
                map_skill("sword", "daojian-guizhen");

        set_temp("born_time", time());

        set_temp("dest_now", 0); // 撤退標記 0 為不撤退繼續戰鬥

        add_money("gold",4000 + random(1000));

        // 增加射擊命中
        set("special_skill/accuracy", 1);
        
        // 設置獎勵級別
        set("gift/level", "成吉思汗");
        set("gift/exp", 1000000);
        set("gift/pot", 1000000);
        set("gift/experience", 1000000);

        setup();

                if (random(5) == 1)
                {                
                        set_temp("handing", carry_object("/clone/weapon/longbow")); 
                }
                else
                {
                        set_temp("handing", carry_object("/clone/weapon/tianshen-gong")); 
                }

                arrow = new("/clone/weapon/arrow");
                arrow->set_amount(2000);
                arrow->move(this_object());

                carry_object(__DIR__"obj/tianzicloth")->wear(); 

                if (random(5) == 1)
                {
                        carry_object("/clone/weapon/shuangleng-dao")->wield();
                }
                else
                {
                        carry_object("/clone/weapon/ningyue-dao")->wield();
                }

                carry_object("/clone/weapon/qinggang-jian")->wield();

}

int accept_fight(object ob)
{
        command("say 我可沒興趣陪你玩，快給我滾開。");
        return 0;
}

int accept_hit(object ob)
{
        return 0;
}

int accept_ansuan(object ob)
{
        return notify_fail("那人警惕性好高，你難以下手。\n");
}

int accept_touxi(object ob)
{
        return notify_fail("那人警惕性好高，你難以下手。\n");
}

void me_die_msg()
{        
        command("chat* sigh");
        command("chat 枉我鐵木真征戰沙場多年，今日竟對一個小小的襄陽城束手無策。");
        command("chat 罷罷罷，全軍就此撤退，重新整頓，來日再戰。");

        XYWAR_D->war_win(); // 襄陽勝利
        set_temp("dest_now", 1);
        return;        
}

void me_die_msg2()
{
        command("chat* sigh");
        command("chat 枉我鐵木真征戰沙場多年，今日竟對一個小小的襄陽城束手無策。");
        command("chat 罷罷罷，全軍就此撤退，重新整頓，來日再戰。");

        set_temp("dest_now", 1);
        return;                
}

void die(object killer)
{
        object dob;             // 打暈這個NPC的人
        int n;                  // 組隊中隊員數目
        int exp;                // 需要瓜分的經驗
        int pot;                // 需要瓜分的潛能
        int tihui;              // 需要瓜分的體會
        int weiwang;            // 需要瓜分的威望
        int score;              // 需要瓜分的閲歷

        object *t;              // 殺死我的人的隊伍列表
        object tob;
        int i;

        // 防止直接call_die()
        if (query("qi") > 300000)
        {
                revive();
                return;
        }

        // 戰鬥進行時才有獎勵
        if (XYWAR_D->now_status() != 2)
        {
                me_die_msg2();
                destruct(this_object());
                return;
        }
        
        // 找到殺了我(NPC)或是打暈我的人
        if (! objectp(dob = killer))
                dob = query_defeated_by();

        if (! dob)
        {
                me_die_msg();
                destruct(this_object());
                return;
        }

        if (objectp(dob))
        {
                exp = query("gift/exp");
                pot = query("gift/pot");
                tihui = query("gift/experience");

                // 組隊
                t = dob->query_team();

                if (pointerp(t))n = sizeof(t);

                // 組隊後需要瓜分經驗
                if (n > 1)
                {
                       exp /= n;
                       pot /= n;
                       tihui /= n;
                }

                if (exp < 1)exp = 1;
                if (pot < 1)pot = 1;
                if (tihui < 1)tihui = 1;
                                
                if (pointerp(t))
                {                                                
                        /// 999 表明獲得的特殊獎勵不受上限限制
                        foreach(tob in t)
                        {
                                   if (objectp(tob) && living(tob))
                                   {
                                                     // 設置殺敵標誌，最為最終獎勵依據
                                                     tob->set("xywar/xy_" + sprintf("%d", XYWAR_D->get_ran_num()), pot);

                                                  GIFT_D->delay_bonus(tob,
                                                         ([ "exp"         : exp + ((tob == dob) ? exp : 0),
                                                              "pot"         : pot + ((tob == dob) ? pot : 0),
                                                               "mar"         : tihui + ((tob == dob) ? tihui : 0),
                                                              "prompt"      : "你的隊伍擊斃" + name() + "之後" ]), 999);
                                                                  
                                    }
                        }
                }
                else
                {
                        // 設置殺敵標誌，最為最終獎勵依據
                        dob->set("xywar/xy_" + sprintf("%d", XYWAR_D->get_ran_num()), pot);
                        
                        GIFT_D->delay_bonus(dob,
                            ([ "exp"         : exp,
                               "pot"         : pot,
                               "mar"         : tihui,
                               "prompt"      : "你在擊斃" + name() + "之後" ]), 999);
                }
        }

        // 正常死亡
        me_die_msg();
        destruct(this_object());

        return;
}

void uncoucious()
{
        die(query_last_damage_from());
}

// 弓箭手特有函數，用於使用弓箭攻擊敵人
void shot_arrow()
{
        object me = this_object();

        if (! me->is_fighting())return;

        if ( me->select_opponent())
        {                
                command("shot");
                command("shot");
        }
                
        // 同時補充內力
        set("neili", query("max_neili"));

        if (random(10) == 1)
        {
                me->delete_temp("no_perform");
                me->delete_temp("no_exert");
                me->interrupt_me(me);

                me->add_temp("apply/damage", 20000);
                command("perform sword.tian");
                me->add_temp("apply/damage", -20000);

                if (random(2))
                {
                        me->delete_temp("eff/jiuyin-shengong/xin");
                }
        }

        if (me->is_busy())me->interrupt_busy(this_object(),1000); 

        // 很小几率恢復氣血
        if (random(20) == 1)
        {
                if (me->query("eff_qi") < me->query("max_qi") / 3)me->add("eff_qi", me->query("max_qi") / 5);
                if (me->query("qi") < me->query("max_qi") / 3)me->add("qi", me->query("max_qi") / 5);
        }                
}

void random_move()
{
        string dir;
        string route;
        object master;
        object *listeners;
        object env;

        if (query_temp("dest_now"))
        {
                destruct(this_object());
                return;
        }

        if (XYWAR_D->dest_status() == 1)
        {
                set_temp("dest_now", 1);
        }
        
        // 檢查襄陽保衞戰是否勝利 1 == 勝利
        if (XYWAR_D->now_status() == 0 && XYWAR_D->get_who_win() == 1)
        {
                command("chat* sigh");
                command("chat 枉我鐵木真征戰沙場多年，今日居然對一個小小的襄陽城束手無策。");
                command("chat 罷罷罷，全軍就此撤退，重新整頓，來日再戰。");
                destruct(this_object());
                return;
        }
        // 檢查襄陽保衞戰是否失敗 2 == 失敗
        if (XYWAR_D->now_status() == 0 && XYWAR_D->get_who_win() == 2)
        {
                command("chat* haha");

                destruct(this_object());
                return;
        }        
        

} 

void init()
{
        object me = this_player();
        
        if (playerp(me))me->set("env/combatd",4);        
}
