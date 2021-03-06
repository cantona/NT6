#include <ansi.h>

#define MAX_POINT 100

inherit BOSS;

void damage_all();
void check_weapon();

void create()
{
        set_name(HIG "劍靈" NOR, ({ "jian ling", "jian", "ling" }) );
        set("title", HIC "虛空之痕" NOR);
        set("long", HIG "在你的面前站立着一位高大的青年，他雙手交叉於胸前，雪\n"
                        "白的長髮隨風飄灑。背上揹負着一柄巨大的寶劍，散發着藍\n"
                        "色的劍芒。這位青年看上去十分憂傷，空洞的眼神中似乎藏\n"
                        "着世俗人間永遠無法看透的悲傷。\n" NOR);

        set("gender", "男性");
        set("age", 35);

        set("str", 800);
        set("int", 800);
        set("con", 800);
        set("dex", 800);

        set("shen", 0);

        set_temp("apply/attack", 10000000);
        set_temp("apply/unarmed_damage", 400000); 
        set_temp("apply/damage", 200000); 
        set_temp("apply/armor", 100000);
        set_temp("apply/reduce_busy", 100);
        set_temp("apply/avoid_forget", 100);

        set("reborn/times", 2);

        set("max_qi", 2100000000);
        set("eff_qi", 2100000000);
        set("qi", 2100000000);

        set("max_jing", 1000000000);
        set("jing", 1000000000);
        set("eff_jing", 1000000000);
        set("max_jingli", 1000000000); 
        set("jingli", 1000000000);  

        set("neili", 200000000);
        set("max_neili", 1000000);
        set("jiali", 50000);
        set("combat_exp", 2100000000);

        set_skill("unarmed", 5000);
        set_skill("finger", 5000);
        set_skill("claw", 5000);
        set_skill("strike", 5000);
        set_skill("hand", 5000);
        set_skill("cuff", 5000);
        set_skill("parry", 5000);
        set_skill("dodge", 5000);
        set_skill("force", 5000);
        set_skill("sword", 5000);
        set_skill("blade", 5000);
        set_skill("zuoyou-hubo", 2500);

        set_skill("lonely-sword", 5000);
        set_skill("jiuyang-shengong", 5000);
        set_skill("yinyang-shiertian", 5000);
        set_skill("qiankun-danuoyi", 5000);
        set_skill("martial-cognize", 5000);
        set_skill("lingbo-weibu", 5000);
        set_skill("literate", 5000);
        set_skill("huajia-su", 800);

        set_skill("jingluo-xue", 5000);

        set("no_nuoyi", 1); // 不被挪移影響
        set("lonely-sword/nothing", 1); //無招
        set("can_learn/lonely-sword/xukong", 1); //特殊絕招，虛空之痕
        
        set("yinyang-shiertian/shier", 12);
        set("yinyang-shiertian/yinyang", 12);
        set("yinyang-shiertian/qiankun", 12);

        map_skill("parry", "lonely-sword");
        map_skill("force", "yinyang-shiertian");
        map_skill("dodge", "lingbo-weibu");
        map_skill("unarmed", "yinyang-shiertian");
        map_skill("finger", "yinyang-shiertian");
        map_skill("strike", "yinyang-shiertian");
        map_skill("hand", "yinyang-shiertian");
        map_skill("cuff", "yinyang-shiertian");
        map_skill("claw", "yinyang-shiertian");
        map_skill("sword", "lonely-sword");

        prepare_skill("finger", "yinyang-shiertian");
        prepare_skill("unarmed", "yinyang-shiertian");

        // yun perform
        set("chat_chance_combat", 120); 
        set("chat_msg_combat", ({ 
              // 獨孤九劍
              (: command("perform sword.jian") :), 
              (: command("perform sword.xukong") :),         // 虛空之痕   
              (: command("perform sword.po twice") :), 
              (: command("perform sword.qi and sword.yi") :), 
              (: command("perform sword.po and finger.tian") :),    
              (: command("perform sword.xukong") :),         // 虛空之痕                
              (: command("perform sword.po and sword.yi") :),    
              (: command("perform sword.xukong") :),         // 虛空之痕                   
               (: command("perform finger.tian twice") :),                                                                                    
              // 陰陽12t
              (: command("perform finger.tian twice") :), 
              (: command("perform finger.zhen and finger.jiu") :), 

              //(: exert_function, "roar" :),
              (: exert_function, "powerup" :), 
              (: exert_function, "shield" :), 
              //(: exert_function, "roar" :), 
              (: exert_function, "recover" :),   
              (: exert_function, "recover" :), 
              (: exert_function, "dispel" :), 
        }));
 

        set("my_life", 1); // 當氣血低於10%的時候補滿一次，設置該參數為0
        set("end_time", 1800);
        set("clear_fuben", 1);

        setup();

        // 衣服
        carry_object("/clone/cloth/bupao")->wear();

        // 武器
        carry_object("/clone/weapon/landie-jian")->wield();

        // 設置地點
        //set("startroom", "/d/shenlong/huodong1");
}

// 全屏傷害 毀滅一擊
/*
東方不敗具備毀滅一擊，隨機發動，全場100%命中，傷血及上限80%
-- 套裝對其具備剋制作用，如下：$HIG$
   -= 通玄套裝: 50%機率抵禦毀滅一擊，同時毀滅一擊若抵禦失敗，傷血及上限50%$HIM$
   -= 鴻鈞套裝: 具備通玄套裝的特性。同時，命中東方不敗後對其追加一次傷害和
                忙亂效果。
                例如本次命中東方不敗傷害為10萬，則再追加10萬傷害，同時令其
                忙亂5至10秒。$HIR$
   -= 造化套裝:90%機率抵禦毀滅一擊，同時毀滅一擊若抵禦失敗，傷血及上限30%
               命中東方不敗後對其追加二次傷害和忙亂效果。例如本次命中東方不
               敗傷害為10萬，則再追加20萬傷害，同時令其忙亂5至10秒。
               命中東方不敗後70%追加封招10秒。$NOR$
*/
void damage_all()
{
        string msg;
        object *obs;
        int i, tzlv;
        
        if( !environment() )
        {
                set_heart_beat(0);
                return;
        }
        msg = HIM "$N" HIM "一聲長歎，手中的藍蝶寶劍化作萬千藍色光芒的彩蝶，鋪天蓋地般捲來，剎那間，"
                  "萬千光芒迸發出刺眼的光芒，竟變成道道劍芒從四面八方激射而來 ……\n" NOR;
        
        message_vision(sort_msg(msg), this_object());
        
        obs = all_inventory(environment(this_object()));
        for (i = 0; i < sizeof(obs); i++)
        {
                reset_eval_cost();
                
                if (! obs[i]->is_character() || obs[i] == this_object())
                        continue;
                        
                // 特殊標誌的ID不會被受招
                if( query("jianling-summon", obs[i]))continue;
                
                tzlv = to_int(query_temp("modequip_itemmake_level", obs[i]));
                // 套裝等級在2以下的100%收到80%的氣血上限傷害
                // 非玩家生物肯定沒有套裝，也是100%受傷
                if ( tzlv < 2 || ! playerp(obs[i]))
                {
                        set("last_damage_from", this_object(), obs[i]);
                        obs[i]->receive_wound("qi",query("max_qi", obs[i])/5*4,this_object());
                        message_vision("$N" HIY "驚恐萬分，已經毫無招架之力，數道劍芒穿胸而過，"
                                           "猛然噴出一口鮮血，倒退幾步，經脈盡傷，無法動彈！\n" NOR, obs[i]);
                        obs[i]->start_busy(10);
                }
                else if (tzlv == 2)
                {
                        // 50%抵禦，若未成功，則傷害為50%
                        if (random(2))
                        {
                                message_vision("$N" HIG "驚恐萬分，已經毫無招架之力，突然全身一道欄光籠罩，其"
                                                   "身穿的【通玄套裝】將所有傷害全部抵禦！\n" NOR, obs[i]);
                        }
                        else
                        {
                                set("last_damage_from", this_object(), obs[i]);
                                obs[i]->receive_wound("qi",query("max_qi", obs[i])/2,this_object());
                                message_vision(HIY "$N" HIY "驚恐萬分，已經毫無招架之力，數道藍芒穿胸而過，"
                                                   "猛然噴出一口鮮血！\n" NOR, obs[i]);
                                obs[i]->start_busy(5);
                        }
                }
                else if (tzlv == 3)
                {
                        if (random(2))
                        {
                                message_vision("$N" HIC "驚恐萬分，已經毫無招架之力，突然全身一道青光籠罩，其"
                                                   "身穿的【鴻鈞套裝】將所有傷害全部抵禦！\n" NOR, obs[i]);
                        }
                        else
                        {
                                set("last_damage_from", this_object(), obs[i]);
                                obs[i]->receive_wound("qi",query("max_qi", obs[i])/2,this_object());
                                message_vision(HIY "$N" HIY "驚恐萬分，已經毫無招架之力，數道藍芒穿胸而過，"
                                                   "猛然噴出一口鮮血！\n" NOR, obs[i]);
                                obs[i]->start_busy(5);
                        }                       
                }
                else if (tzlv == 4)
                {
                        if (1)
                        {
                                message_vision(HIM "$N" HIM "凝神抵禦，一道紫色的光芒纏繞在其周圍，【造化套裝】"
                                                    "叮叮作響，竟將所有傷害化解於無形！\n" NOR, obs[i]);
                        }
                }
        }
}

void heart_beat()
{
        object ob;
        
        keep_heart_beat();

        // 解除不能perform yun的限制
        if (random(3) == 1)
        {
                delete_temp("no_perform");
                delete_temp("no_exert");
        }
/*
        // 檢查武器
        if (! query_temp("weapon"))
        {
                ob = new("/clone/weapon/xuantie-jian");
                ob->move(this_object());
                "/cmds/std/wield"->main(this_object(), "xuantie-jian");
        }
        */
        if (random(5) == 1)check_weapon();
        
        // 5%的機會全屏攻擊，100%命中，傷血及上限80%
        if (random(100) < 5)
        {
                damage_all();
        }
        
        return ::heart_beat();
}

// 檢查武器
void check_weapon()
{
        object me, ob;
        
        me = this_object();

        // 同時補充內力
        set("neili", query("max_neili"));

        if (me->is_busy())me->interrupt_busy(me, 1000); 

        if (me->is_busy())me->interrupt_me(me);

        if( !query_temp("weapon", me) )
        {
                ob = new("/clone/weapon/landie-jian");
                ob->move(me);
                "/cmds/std/wield"->main(me, "landie jian");
        }
/*
        if (random(5) == 1)
        {
                delete_temp("no_perform", me);
                delete_temp("no_exert", me);
                
                addn_temp("apply/damage", 50000, me);
                if (random(10) == 1)
                        command("perform sword.tian twice");
                else            
                        command("perform sword.po and finger.tian");
                addn_temp("apply/damage", -50000, me);

                if (random(2))
                {
                        delete_temp("eff/jiuyin-shengong/xin", me);
                }
        }
*/
        if (random(10) == 1)
        {
                me->clear_condition();
        }

        // 很小几率恢復氣血
        if (random(800) == 1)
        {
                //log_file("qilin", ctime(time()) + " 成功恢復氣血。\n");
                if( query("eff_qi", me)<query("max_qi", me)/3)addn("eff_qi",query("max_qi",  me)/5, me);
                if( query("qi", me)<query("max_qi", me)/3)addn("qi",query("max_qi",  me)/5, me);
        }

        if (me->is_busy())me->interrupt_busy(me); 
/*
        if (! me->is_fighting() || random(5) == 1)
        {
                command("yun roar");
        }
*/
        return;
}

void init()
{
        object me;

        me = this_player();
        
        set("env/combatd", 4, me);
        //if (! wizardp(me))this_object()->kill_ob(me);
}

int accept_hit(object me)
{
        this_object()->kill_ob(me);
        return 1;
}

int accept_fight(object me)
{
        this_object()->kill_ob(me);
        return 1;
}

int accept_kill(object me)
{
        this_object()->kill_ob(me);
        return 1;
}

void new_life()
{
        object me = this_object();
        
        // 補滿氣血
        set("eff_qi",query("max_qi",  me), me);
        set("qi",query("max_qi",  me), me);
        set("eff_jing",query("max_jing",  me), me);
        set("jing",query("max_jing",  me), me);
        set("jingli",query("max_jingli",  me), me);

        me->clear_condition();

        me->interrupt_me(this_object());

        delete_temp("no_perform", me);
        delete_temp("no_exert", me);

        set_temp("apply/attack", 10000000);
        set_temp("apply/unarmed_damage", 400000); 
        set_temp("apply/damage", 200000); 
        set_temp("apply/armor", 100000);
        set_temp("apply/qy", 70);  // 氣運
        set_temp("apply/fy", 70);  // 福緣              
        delete("my_life", me);

        message_vision(HIG "\n$N" HIG "長歎一聲，一隻藍色光芒的蝴蝶從身體內升起！\n\n" NOR, me);
        
        return; 
}

int receive_wound(string type, int damage, object who)
{
        object ob, landie;

        object me = this_object();

        if (! who)return 0;

        // 藍蝶仙子在，不受任何傷害
        landie=query("mylandie", me);
        if (objectp(landie))
        {
                message_vision(HIC "$N" HIC "輕歎一聲，對$n" HIC "的攻勢毫無理會。\n" NOR, me, who);
                return 0;
        }
        
        return ::receive_wound(type, damage, who);
        
}

int receive_damage(string type, int damage, object who)
{
        object ob, landie;
        int tzlv;

        object me = this_object();

        if (! who)return 0;

        // 藍蝶仙子在，不受任何傷害
        landie=query("mylandie", me);
        if (objectp(landie))
        {
                message_vision(HIC "$N" HIC "輕歎一聲，對$n" HIC "的攻勢毫無理會。\n" NOR, me, who);
                return 0;
        }

        // 套裝的追加傷害
        if (objectp(who))
        {
                tzlv = to_int(query_temp("modequip_itemmake_level", who));
                
                if (tzlv == 3)// 
                {
                        damage *= 2;
                        this_object()->start_busy(5+random(6));
                        tell_object(HIM "「鴻鈞套裝」追加傷害及附加忙亂！\n" NOR);
                }
                else if (tzlv == 4)
                {
                        damage *= 3;
                        start_busy(5+random(6));
                        tell_object(HIM "「造化套裝」追加傷害及附加忙亂！\n" NOR);
                        if (random(10) < 7)
                        {
                                set_temp("no_perform", 1);
                                call_out("remove_no_perform", 10);
                                tell_object(HIC "「造化套裝」追加封招10秒！\n" NOR);
                        }
                }
        }
        
        if( !query("my_life", me))return ::receive_damage(type,damage,who);

        if( query("qi", me)<query("max_qi", me)/10 )
        {
                new_life(); // 重生一次
                return 0;
        }

        return ::receive_damage(type, damage, who);
}


void remove_no_perform()
{
        delete_temp("no_perform");
}

// 檢查生命
void check_life()
{
        object env;
        
        // 如果life<=1則死亡
        if (1)
        {
                message_vision(HIR "\n$N" HIR "一聲悲涼的長歎，竟化作一直藍蝶飛走了。\n" NOR, this_object());

                destruct(this_object());
        }
}

void die(object killer)
{
        object dob;             // 打暈這個NPC的人                                                                                       
        int n;                  // 可以獎勵的人的數目                                                                                    
        int exp;                // 需要瓜分的經驗
        int pot;                // 需要瓜分的潛能                                                                                        
        int weiwang;            // 需要瓜分的威望
        int score;              // 需要瓜分的閲歷
        object *t;              // 殺死我的人的隊伍列表                                                                                  
        object tob;       
        object ob;
        int mar;                //  需要瓜分的體會
        int i;

        // 定義獎勵物品列表
        // 機率  X / 百分之
        mixed oblist = ([
                "/clone/armor/jianling/jianling-zhili"   : 1,
                "/clone/armor/jianling/jianling-zhili2"  : 1,
                "/clone/armor/jianling/jianling-zhinu"   : 1,
                "/clone/armor/jianling/jianling-zhinu2"  : 1,
                "/clone/armor/jianling/jianling-zhihen"  : 1,
                "/clone/armor/jianling/jianling-zhihen2" : 1,
                "/clone/armor/jianling/jianling-zhihun"  : 1,   
                "/clone/armor/jianling/jianling-zhihun2" : 1,
        ]);

        object gift_ob, gift_ob2, gift_ob3, gift_ob4;
        string s_gift, *key_s_gift;
        int gift_point, ran;
                              
        if( objectp(ob = previous_object(0)) && sscanf(base_name(ob), "/kungfu/skill/%*s") ) { 
                full_self(); 
                return; 
        }

        // 如果還未重生，則重生一次
        if (query("my_life"))
        {
                new_life();
                return;
        }

        // 找到殺了我(NPC)或是打暈我的人
        if (! objectp(dob = killer))
                dob = query_last_damage_from();
        if (! objectp(dob))
                dob = query_defeated_by();
                
        if (! dob)
        {
                // 調用生命檢查函數
                check_life();
                return;
        }

        t = dob->query_team();
        
        if (objectp(dob) && environment(dob) == environment(this_object()))                                                              
        {
                exp = 40000 + random(40000);
                pot = 40000 + random(40000);
                weiwang = 6000 + random(9000);
                score = 6000 + random(6000);
                mar = 12000 + random(12000);
                n = 0;
                
                n = sizeof(t);
                if (! n || n < 3)                                                                                                        
                {
                       exp /= 5;                                                                                                         
                       pot /= 5;                                                                                                         
                       weiwang /= 3;
                       score /= 3;
                       mar /= 5;
                }

                if (n >= 3)
                {
                        exp /= n;
                        pot /= n;
                        weiwang /= n;
                        score /= n;
                        mar /= n;
                }

                
                if (n)
                {
                        foreach(tob in t)
                        {
                                if (objectp(tob) && living(tob))
                                {       
                                        
                                        // 設置戰勝過劍靈的標記
                                        if( !query("thborn/fuben/jianling/win", tob) )
                                        {
                                                tell_object(tob, HIG + BLINK + "恭喜你！已經成功戰勝劍靈，可以使用劍靈裝備了！\n" NOR);
                                                set("thborn/fuben/jianling/win", 1, tob);
                                        }
                                        
                                        // 會員獎勵再提高10%
                                        if( MEMBER_D->is_valib_member(query("id", tob)) )
                                        {
                                                if (environment(tob) == environment(dob))
                                                        GIFT_D->delay_bonus(tob,                                              
                                                                ([ "exp"      : exp + exp * 1 / 10 + ((tob == dob) ? 50000 : 0),              
                                                                   "pot"      : pot + pot * 1 / 10 / 10 + ((tob == dob) ? 50000 : 0),          
                                                                   "weiwang"  : weiwang + weiwang * 1 / 10 + ((tob == dob) ? 50000 : 0),  
                                                                   "score"    : score + score * 1 / 10 + ((tob == dob) ? 50000 : 0),
                                                                   "mar"      : mar + mar * 1 / 10 + ((tob == dob) ? 50000 : 0),
                                                                   "prompt"   : "你的隊伍殺死" + name() + HIG "之後"]), 999);          
                                        }
                                        else
                                        {
                                                if (environment(tob) == environment(dob))                                  
                                                        GIFT_D->delay_bonus(tob,                                              
                                                                ([ "exp"      : exp + ((tob == dob) ? 50000 : 0),              
                                                                   "pot"      : pot + ((tob == dob) ? 50000 : 0),          
                                                                   "weiwang"  : weiwang + ((tob == dob) ? 50000 : 0),  
                                                                   "score"    : score + ((tob == dob) ? 50000 : 0),
                                                                   "mar"      : mar + ((tob == dob) ? 50000 : 0),
                                                                   "prompt"   : "你的隊伍殺死" + name() + HIG "之後"]), 999);  
                                        }
                                }
                        }
                }
                else
                {
                        // 設置戰勝過劍靈的標記
                        if( !query("thborn/fuben/jianling/win", dob) )
                        {
                                tell_object(dob, HIG + BLINK + "恭喜你！已經成功戰勝劍靈，可以使用劍靈裝備了！\n" NOR);
                                set("thborn/fuben/jianling/win", 1, dob);
                        }
                        
                        if( MEMBER_D->is_valib_member(query("id", dob)) )
                        {
                                GIFT_D->delay_bonus(dob,
                                        ([ "exp"      : exp + exp * 3 / 10,                                           
                                           "pot"      : pot + pot * 3 / 10,                                       
                                           "weiwang"  : weiwang + weiwang * 3 / 10,                               
                                           "score"    : score + score * 3 / 10,  
                                           "mar"      : mar + mar * 3 / 10,                           
                                           "prompt"   : "你在戰勝" + name() + HIG "之後"]), 100);                                    
                        }                                                                                          

                        else
                        {
                                GIFT_D->delay_bonus(dob,                                              
                                        ([ "exp"      : exp,                                           
                                           "pot"      : pot,                                       
                                           "weiwang"  : weiwang,                               
                                           "score"    : score,  
                                           "mar"      : mar,                           
                                           "prompt"   : "你在戰勝" + name() + HIG "之後"]), 100); 
                       }     
                }
        }

        // 100%掉物品
        if (1)
        {
                
                key_s_gift = keys(oblist);

                // 5%至少爆一件
                if (random(100) < 5)
                {
                        s_gift = key_s_gift[random(sizeof(key_s_gift))];
                        gift_point = oblist[s_gift];
                        gift_ob = new(s_gift);
                        if (objectp(gift_ob))
                        {
                                message_vision(HIC "當~~一聲，從$N" HIC "身上掉出" + gift_ob->name() + HIC "，落在地上。\n" NOR, this_object());                                  
                                set("who_get/id", "NONE", gift_ob);
                                set("who_get/time", time()+30, gift_ob);//30秒內都不能撿取
                                gift_ob->move(environment(this_object()));                                                                           
                        }
                        else // 紀錄之
                        {
                                log_file("gift-none", s_gift + " from " + __FILE__ + "\n");
                        }
                }
                
                // 1%機率再追加一件物品
                if (random(100) < 1)
                {
                        s_gift = key_s_gift[random(sizeof(key_s_gift))];
                        gift_point = oblist[s_gift];
                        gift_ob2 = new(s_gift);
                        if (objectp(gift_ob2))
                        {
                                message_vision(HIC "當~~一聲，從$N" HIC "身上掉出" + gift_ob2->name() + HIC "，落在地上。\n" NOR, this_object());                                  
                                set("who_get/id", "NONE", gift_ob2);
                                set("who_get/time", time()+10, gift_ob2);//30秒內都不能撿取
                                gift_ob2->move(environment(this_object()));                                                                           
                        }
                        else // 紀錄之
                        {
                                log_file("gift-none", s_gift + " from " + __FILE__ + "\n");
                        }                       
                }
                // 0.01%機率再追加一件
                if (random(10000) == 1)
                {
                        s_gift = key_s_gift[random(sizeof(key_s_gift))];
                        gift_point = oblist[s_gift];
                        gift_ob3 = new(s_gift);
                        if (objectp(gift_ob3))
                        {
                                message_vision(HIC "當~~一聲，從$N" HIC "身上掉出" + gift_ob3->name() + HIC "，落在地上。\n" NOR, this_object());                                  
                                //gift_ob3->set("who_get/id", "NONE");
                                //gift_ob3->set("who_get/time", time() + 30); // 30秒內都不能撿取
                                gift_ob3->move(environment(this_object()));                                                                           
                        }
                        else // 紀錄之
                        {
                                log_file("gift-none", s_gift + " from " + __FILE__ + "\n");
                        }
                }
/*
                // 25%的機率掉東西
                if (random(4) == 1) 
                {
                        ran = random(100);

                        if (random(10) == 1)// 10%蟬翼披風
                        {
                                gift_ob = new("/clone/armor/dongfang/chanyi-pifeng");
                                
                                if (objectp(gift_ob))
                                {
                                        message_vision(HIC "當~~一聲，從$N" HIC "身上掉出" + gift_ob->name() + HIC "，落在地上。\n" NOR, this_object());                                  
                                        set("who_get/id", "NONE", gift_ob);
                                        set("who_get/time", time()+30, gift_ob);//30秒內都不能撿取
                                        gift_ob->move(environment(this_object()));                                                                           
                                }
                        }
                        
                        if (random(100) < 3)// 黑玉指環 3%
                        {
                                gift_ob2 = new("/clone/armor/dongfang/heiyu");
                                
                                if (objectp(gift_ob2))
                                {
                                        message_vision(HIC "當~~一聲，從$N" HIC "身上掉出" + gift_ob2->name() + HIC "，落在地上。\n" NOR, this_object());                                  
                                        set("who_get/id", "NONE", gift_ob2);
                                        set("who_get/time", time()+30, gift_ob2);//30秒內都不能撿取
                                        gift_ob2->move(environment(this_object()));                                                                           
                                }
                        }                       

                        if (random(100) < 3)// 紫血環
                        {
                                gift_ob3 = new("/clone/armor/dongfang/zixue");
                                
                                if (objectp(gift_ob3))
                                {
                                        message_vision(HIC "當~~一聲，從$N" HIC "身上掉出" + gift_ob3->name() + HIC "，落在地上。\n" NOR, this_object());                                  
                                        set("who_get/id", "NONE", gift_ob3);
                                        set("who_get/time", time()+30, gift_ob3);//30秒內都不能撿取
                                        gift_ob3->move(environment(this_object()));                                                                           
                                }
                        }

                        if (random(100) < 5)// 魅影劍法或天擎祕氣 5% 隨機一件
                        {
                                switch(random(3))
                                {
                                        case 0:
                                                gift_ob4 = new("/clone/book/meiying-jian1");
                                        break;
                                        
                                        case 1:
                                                gift_ob4 = new("/clone/book/meiying-jian2");
                                        break;
                                        
                                        default:
                                                gift_ob4 = new("/clone/book/tianqing-miqi");
                                        break;
                                }

                                if (objectp(gift_ob4))
                                {
                                        message_vision(HIC "當~~一聲，從$N" HIC "身上掉出" + gift_ob4->name() + HIC "，落在地上。\n" NOR, this_object());                                  
                                        set("who_get/id", "NONE", gift_ob4);
                                        set("who_get/time", time()+30, gift_ob4);//30秒內都不能撿取
                                        gift_ob4->move(environment(this_object()));                                                                           
                                }
                        }
                }
                */
        }
        
        // 5/100機率掉出無名銅人
        if (random(100) < (5+5*query_temp("apply/magic_find", dob)/100))
        {
                object ob_tongren;
                ob_tongren = new("/clone/tongren/tongren"+(1+random(2)));     
                message_vision(HIR "當~~一聲，從$N" HIR "身上掉出" + ob_tongren->name() + HIR "，落在地上。\n" NOR, this_object());
                set("who_get/id", "NONE", ob_tongren);
                set("who_get/time", time()+30, ob_tongren);//30秒內都不能撿取
                ob_tongren->move(environment(this_object()));
        }
                
        // 特殊活動爆物品，統一調用giftd接口
        GIFT_D->fuben_boss_gift(this_object()); 
                                
        // 20%機率掉出特殊物品
        // 同時有50%機率掉出2件
        if (random(100) < (2+2*query_temp("apply/magic_find", dob)/100))
        {       
                object gift_huoyan;
                gift_huoyan = new("/clone/tessera/rune31");
                set("who_get/id", "NONE", gift_huoyan);
                set("who_get/time", time()+30, gift_huoyan);//30秒內都不能撿取
                gift_huoyan->move(environment(this_object()));  
                message_vision(HIW "叮~~一聲，從$N" HIW "身上掉出" + gift_huoyan->name() + 
                               HIW "，落在地上。\n" NOR, this_object());

        }
        // 檢查生命
        check_life();

        return ;
}
