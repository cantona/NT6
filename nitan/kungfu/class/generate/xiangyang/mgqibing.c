// person used in quest

#include <ansi.h>

inherit NPC;

#define GO_CMD                   "/cmds/std/go"

void random_move();
int  is_stay_in_room()  { return 1; }

void create()
{
        set_name(HIR "蒙古鐵騎" NOR, ({"menggu tieqi", "tieqi" }));
        set("gender", "男性");
        set("age", 20 + random(20));
        set("long", "這是一位蒙古鐵騎兵，是成吉思汗鐵木真旗下最勇猛的軍隊！");
        set("chat_chance", 120);
        set("chat_msg", ({ (: random_move :) }));
        set("no_get", 1);

        // 蒙古士兵標志
        set("mgbing", 1);

        set_temp("apply/armor", 400);
        set_temp("apply/damage", 600);
                set_temp("apply/attack", 100000); // 高命中

                set("str", 40);
                set("int", 10 + random(14));
                set("dex", 10);
                set("con", 15);

                set("combat_exp", 3000000);

                set("max_qi", 6000);
                set("eff_qi", 6000);
                set("qi", 6000);
                set("max_neili",6000);
                set("neili", 6000);
                set("max_jingli", 6000);
                set("jingli", 6000);
                
                set_skill("dodge", 50);
                set_skill("force", 30);
                set_skill("unarmed", 30);
                set_skill("blade", 200);
                
        set_temp("born_time", time());

        set_temp("dest_now", 0); // 撤退標記 0 為不撤退繼續戰鬥

        add_money("gold", 1 + random(2));

        // 設置獎勵級別
                set("gift/level", "騎兵");
                set("gift/exp", 1800 + random(1801));
                set("gift/pot", 1800 + random(1201));
                set("gift/experience", 800 + random(601));

                setup();

                carry_object(__DIR__"obj/menggucloth")->wear(); 
                carry_object("/clone/weapon/gangdao")->wield();
                        if (clonep()) keep_heart_beat();
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

void die(object killer)
{
        object dob;             // 打暈這個NPC的人
        int n;                  // 組隊中隊員數目
        int exp;                // 需要瓜分的經驗
        int pot;                // 需要瓜分的潛能
        int tihui;              // 需要瓜分的體會
        int weiwang;            // 需要瓜分的威望
        int score;              // 需要瓜分的閱歷

        object *t;              // 殺死我的人的隊伍列表
        object tob;
        int i;

        // 找到殺了我(NPC)或是打暈我的人
        if (! objectp(dob = killer))
                dob = query_defeated_by();

        if (! dob)
        {
                if (! query("no_total"))
                        XYWAR_D->soldier_die(this_object()->query("route"), 0);
                
                destruct(this_object());
                return;
        }

        // 戰鬥進行時才有獎勵
        if (XYWAR_D->now_status() != 2)
        {
                if (! query("no_total"))
                        XYWAR_D->soldier_die(this_object()->query("route"), 0);
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
                                                     // 設置殺敵標志，最為最終獎勵依據
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
                        // 設置殺敵標志，最為最終獎勵依據
                        dob->set("xywar/xy_" + sprintf("%d", XYWAR_D->get_ran_num()), pot);
                        
                        GIFT_D->delay_bonus(dob,
                            ([ "exp"         : exp,
                               "pot"         : pot,
                               "mar"         : tihui,
                               "prompt"      : "你在擊斃" + name() + "之後" ]), 999);
                }
        }

        // 正常死亡
        if (! query("no_total"))
                XYWAR_D->soldier_die(this_object()->query("route"), 0);
        destruct(this_object());

        return;
}

void uncoucious()
{
        die(query_last_damage_from());
}

void random_move()
{
        string dir;
        string route;
        object env;
                
        if (query_temp("dest_now"))
        {
                if (! query("no_total"))
                        XYWAR_D->soldier_die(this_object()->query("route"), 0);
                destruct(this_object());
                return;
        }

        if (XYWAR_D->dest_status() == 1)
        {
                set_temp("dest_now", 1);
        }

        // 行進路徑方向
        // 需要先設置
        route = query("route");

        env = environment(this_object());

        if (! objectp(env))return;
        
        // 如果到達中央廣場宣告襄陽保衛戰失敗
        if (base_name(env) == "/d/xiangyang/guangchang")
        {                        
               XYWAR_D->arrived_center();// 保衛戰失敗
               return;
        }

        // 按照路由列表移動
        if (stringp(route) && XYWAR_D->now_status() == 2)command("go " + route);
}

void init()
{
        object me = this_player();

        if (! living(me) || me->query_temp("apply/invisible"))
                 return;

        // 蒙古並不相互戰鬥
                if (me->query("mgbing"))return;                        

                // 延遲一定時間攻擊
                // 為了設置fighting標記也更真實
                if (! me->query("env/invisible"))call_out("do_kill", 1 + random(4), me);
        if (playerp(me))me->set("env/combatd",4);
}

void do_kill(object me)
{
        if (! objectp(me))return;
                        
        if (! living(me) || me->query_temp("apply/invisible"))
                 return;

        // 並不是每個對象都攻擊，這樣做是為了節約系統資源和更為真實
        if (me->is_fighting() && random(3) == 1)return;

        // 只能同時攻擊一個人
        if (this_object()->is_fighting())return;

        kill_ob(me);
        me->kill_ob(this_object());
}
