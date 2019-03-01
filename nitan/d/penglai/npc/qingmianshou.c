inherit NPC;
#include <ansi.h>

#define MEMBER_D "/adm/daemons/memberd"
#define MAX_POINT 300

void create()
{
        set_name(HIG "青面獸" NOR, ({ "qingmian shou", "qingmian", "shou" }));
        set("long", HIG "這是一只青面獠牙的巨獸，乃酒劍仙的坐騎，看樣子是從蓬萊仙島逃出來的。\n" NOR);

        set("age", 190);
        set("str", 40);
        set("dex", 30);
        set("max_qi", 4000000);
        set("max_jing", 4000000);
        set("max_jingli", 4000000);
        set("max_neili", 200000);
        set("neili", 200000);                
        set("combat_exp", 200000000);
        set("no_nuoyi", 1);


        set_skill("force", 500);
        set_skill("dodge", 500);
        set_skill("unarmed", 600);
        set_skill("sword", 500);
        set_skill("parry", 500);
        set_skill("claw", 500);
        
        setup();
        add_money("gold", 1000 + random(2000));
}


int accept_fight(object ob)
{
        kill_ob(ob);
        return -1;
}

int accept_kill(object ob)
{
        return 1;
}

int accept_hit(object ob)
{
        kill_ob(ob);
        return -1;        
        return 1;
}

mixed hit_ob(object me, object ob, int damage_bouns)
{
        ob->start_busy(2 + random(3));
        me->receive_wound("qi", 200 + random(100), ob);
        return HIY "$N" HIY "大喝一聲，拼死反抗，竟逼得$n" HIY "手忙腳亂。\n" NOR;
}

void heart_beat()
{
        if (query("neili") < 1 && random(50) == 1)                                                
                set("neili", query("max_neili"));

        ::heart_beat();
}

void unconcious()
{
        
        // 防止直接call_die()
        if (query("qi") > 300000)
        {
                revive();
                return;
        }
        
        die(query_last_damage_from());
}

void die(object killer)
{
        object dob;             // 打暈這個NPC的人
        int n;                  // 可以獎勵的人的數目
        int exp;                // 需要瓜分的經驗
        int pot;                // 需要瓜分的潛能
        int weiwang;            // 需要瓜分的威望
        int gongxian;           // 貢獻
        int tihui;              // 體會
        int score;              // 需要瓜分的閱歷
        object *t;              // 殺死我的人的隊伍列表
        object tob;
        int ysg;
        int i;
        object *inv;
        
        // 定義獎勵物品列表
        // 幾率  MAX_POINT 分之 X
        mixed oblist = ([
                "/clone/fam/gift/str4" :1,
                "/clone/fam/gift/con4" :1,                        
                "/clone/armor/moling-zhiyi2" : 3,                        
                "/clone/armor/zhanhun-xue3":20,
                "/clone/armor/xingyue-erhuan3":20,
                "/clone/fam/item/wushi-pifeng3":30,
                "/clone/fam/max/naobaijin":50,        
        ]);

                object gift_ob;
                string s_gift, *key_s_gift;
                int gift_point;
                /*
                // 防止直接call_die()
                if (query("qi") > 100000)
                {
                        revive();
                        return;
                }
*/
                // 找到殺了我(NPC)或是打暈我的人
                if (! objectp(dob = killer))
                dob = query_last_damage_from();

                if (! dob)
                {
                        //MAP_D->update_boss(BOSS_FILE,UPDATE_PLACE,UPDATE_TIME);
                        destruct(this_object());
                        return;
                }

                t = dob->query_team();

                if (objectp(dob) && environment(dob) == environment(this_object()))
                {
                        exp = 20000 + random(20000);
                        pot = 30000 + random(20001);
                        tihui = 2500 + random(3000);
                        n = 0;
                        n = sizeof(t);
                        
                        if (! n || n < 3)
                        {
                               exp /= 3;
                               pot /= 3;
                               tihui /= 3;                               
                        }

                        if (n >= 3)
                        {
                                exp /= 2;
                                pot /= 2;        
                                tihui /= 2;                
                        }
        
                        if (n)
                        {                                
                                foreach(tob in t)
                                {
                                        
                                        if (objectp(tob) && living(tob))
                                        {
                                                if (environment(tob) == environment(dob))
                                                        GIFT_D->delay_bonus(tob,
                                                                ([ "exp"      : exp + ((tob == dob) ? 5000 : 0),
                                                                   "pot"      : pot + ((tob == dob) ? 5000 : 0),
                                                                   "mar"      : tihui + ((tob == dob) ? 1000 : 0),
                                                                   "prompt"   : "你的隊伍打敗" + name() + "之後"]), 999);
        
                                        }
                                }
                        }
                        else
                        {
                                if (1)
                                        GIFT_D->delay_bonus(dob,
                                                 ([ "exp"      : exp,
                                                        "pot"      : pot,
                                                        "mar"    : tihui,
                                                        "prompt"   : "你在打敗" + name() + "之後"]), 999);
                        }
        
                }
                
                message_vision(HIG "\n青面獸一聲怪叫，癱倒在地，化作一灘綠色的液體 ...\n" NOR, this_object());

                // 一定幾率掉物品在殺我的人身上dob
                if (objectp(dob) && environment(dob) == environment(this_object()))
                {
                        key_s_gift = keys(oblist);
                        s_gift = key_s_gift[random(sizeof(key_s_gift))];
                        gift_point = oblist[s_gift];
        
                        // 判斷幾率
                        if (MEMBER_D->is_valib_member(dob->query("id")) 
                            && random(MAX_POINT / ITEM_D->gift_point()) < gift_point)
                        {
                                // 獲得物品--爆出物品直接放在dob身上
                                gift_ob = new(s_gift);
                                if (objectp(gift_ob))
                                {
                                        message_vision(HIR "叮~~一聲，從$N" HIR "掉出一樣東西，$n" HIR 
                                                       "趕緊揀了起來。\n" NOR, this_object(), dob);
                                        tell_object(dob, BLINK + HIG "你得到了" + gift_ob->name() + BLINK + HIG "。\n" NOR);
                                        gift_ob->move(dob, 1);
                                }
                                else // 紀錄之 
                                {
                                        log_file("killed-gift-none", s_gift + "\n");
                                }
                        }
                }

                // 掉出金錢及其他物品
                if (1)
                {
                        inv = all_inventory(this_object());
                        inv -= ({ 0 });
                           i = sizeof(inv);
                        while (i--)
                            {
                                if (objectp(dob))
                                {
                                            inv[i]->set("who_get/id", dob->query("id"));
                                            inv[i]->set("who_get/time", time() + 60);
                                }
                                 inv[i]->move(environment(this_object()));
                        }
                }

                destruct(this_object());
        
                return;
}