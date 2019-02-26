#include <ansi.h>

#define MEMBER_D "/adm/daemons/memberd"
#define MAX_POINT 100

inherit NPC;

void check_weapon();
void check_environment();
void check_time();

void create()
{
        set_name(HIR "火麒麟" NOR, ({ "huo qilin", "huo", "qilin" }) );
        set("title", HIY "上古神獸" NOR);
        set("long", HIR "這是一隻傳説中的上古神獸—火麒麟，只見它渾身似火，散射着令人窒息的熾熱。\n"
                        "仔細一看，這隻火麒麟經過千萬年修煉，已經化為人形，威風無比，令人敬畏。\n" NOR);

        set("gender", "男性");
        set("age", 999);

        set("str", 120);
        set("int", 120);
        set("con", 120);
        set("dex", 120);

        set("shen", 8000000);

        set_temp("apply/attack", 30000);
        set_temp("apply/unarmed_damage", 20000);
        set_temp("apply/damage", 20000);
        set_temp("apply/armor", 20000);
        set_temp("apply/qy", 20);  // 氣運
        set_temp("apply/fy", 20);  // 福緣

        set("scborn/ok", 1);

        set("max_qi", 15000000000);
        set("eff_qi", 15000000000);
        set("qi", 15000000000);

        set("max_jing", 10000000000);
        set("jing", 10000000000);
        set("eff_jing", 10000000000);
        set("max_jingli", 10000000000);
        set("jingli", 10000000000);

        set("neili", 2000000000);
        set("max_neili", 30000000);
        set("jiali", 20000);
        set("combat_exp", 2100000000);

        set_skill("unarmed", 2500);
        set_skill("finger", 2500);
        set_skill("claw", 2500);
        set_skill("strike", 2500);
        set_skill("hand", 2500);
        set_skill("cuff", 2500);
        set_skill("parry", 2500);
        set_skill("dodge", 2500);
        set_skill("force", 2500);
        set_skill("sword", 2500);
        set_skill("blade", 2500);
        set_skill("zuoyou-hubo", 2500);

        set_skill("badao", 2500);
        set_skill("jiuyang-shengong", 2500);
        set_skill("taiji-jian", 2500);
        set_skill("liumai-shenjian", 2500);
        set_skill("martial-cognize", 2500);
        set_skill("literate", 2500);
        set_skill("tianwei-zhengqi", 500);

        set_skill("jingluo-xue", 2000);

         set("no_nuoyi", 1); // 不被挪移影響

        map_skill("parry", "jiuyang-shengong");
        map_skill("force", "jiuyang-shengong");
        map_skill("dodge", "jiuyang-shengong");
        map_skill("unarmed", "jiuyang-shengong");
        map_skill("finger", "liumai-shenjian");
        map_skill("strike", "jiuyang-shengong");
        map_skill("hand", "jiuyang-shengong");
        map_skill("cuff", "jiuyang-shengong");
        map_skill("claw", "jiuyang-shengong");
        map_skill("sword", "taiji-jian");

        prepare_skill("claw", "jiuyin-shengong");
        prepare_skill("cuff", "jiuyin-shengong");
        prepare_skill("finger", "liumai-shenjian");

        // yun perform
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
              // 太極劍
              (: command("perform sword.sui and sword.chan") :),
              (: command("perform sword.jian and sword.zhuan") :),
              (: command("perform sword.zhenwu and sword.jian") :),
              (: command("perform sword.jian twice") :),
              (: command("perform sword.jian and finger.tian") :),
              // 六脈神劍
              (: command("perform finger.six twice") :),
              (: command("perform finger.qi twice") :),
              (: command("perform finger.zong and finger.tian") :),
              (: command("perform finger.tian twice") :),

              (: exert_function, "roar" :),
              (: exert_function, "powerup" :),
              (: exert_function, "shield" :),
              (: exert_function, "roar" :),
              (: exert_function, "recover" :),
              (: exert_function, "recover" :),
              (: exert_function, "dispel" :),
              (: check_weapon :),
              (: check_time :),
        }));

        set("my_life", 1); // 當氣血低於10%的時候補滿一次，設置該參數為0

        setup();

        // 衣服需要更改，不穿衣服？
        //carry_object("/clone/cloth/cloth")->wear();

        // 武器
        carry_object("/clone/weapon/chi-jian")->wield();

        // 設置地點
        set("startroom", "/d/shenlong/huodong1");

}

void heart_beat()
{
        keep_heart_beat();

        if( !environment(this_object()) )
                return ::heart_beat();

        // 檢查出現時間
        if (random(2))check_time();

        if (random(5) == 1)check_weapon();

        return ::heart_beat();
}

// 檢查時間 6 小時後消失
// 未戰鬥狀態下消失
void check_time()
{
        int t;
        object env;

        t = time() - query("life_time");

        if (t > 60 && ! is_fighting())
        {
                env = environment(this_object());
                env->move_all_player_out(1);
                destruct(this_object());
                return;
        }

        if (t > 6 * 3600)
        {
                message_vision(BLINK + HIG "\n此次對抗火麒麟已經超過6小時，挑戰失敗！\n" NOR, this_object());
                env = environment(this_object());
                env->move_all_player_out(1);
                destruct(this_object());
                return;
        }

        return;
}

// 檢查地點
void check_environment()
{        /*
        if (! environment(this_object()))return;

        if (base_name(environment(this_object())) != query("startroom"))
        {
                command("say 咦？我怎麼會在這裏，有人作弊，有人作弊，巫師快出來！");
                destruct(this_object());
        }
        */

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
                ob = new("/clone/weapon/chi-jian");
                ob->move(me);
                "/cmds/std/wield"->main(me, "chi jian");
        }

        if (random(5) == 1)
        {
                delete_temp("no_perform", me);
                delete_temp("no_exert", me);

                addn_temp("apply/damage", 20000, me);
                if (random(10) == 1)
                        command("perform sword.jian twice");
                else
                        command("perform sword.jian and finger.tian");
                addn_temp("apply/damage", -20000, me);

                if (random(2))
                {
                        delete_temp("eff/jiuyin-shengong/xin", me);
                }
        }

        if (random(20) == 1)
        {
                me->clear_condition();
        }

        // 很小几率恢復氣血
        if (random(50) == 1)
        {
                //log_file("qilin", "成功恢復氣血。\n");
                if( query("eff_qi", me)<query("max_qi", me)/3)addn("eff_qi",query("max_qi",  me)/5, me);
                if( query("qi", me)<query("max_qi", me)/3)addn("qi",query("max_qi",  me)/5, me);
        }

        if (me->is_busy())me->interrupt_busy(me);

        if (! me->is_fighting() || random(5) == 1)
        {
                command("yun roar");
        }

        return;
}

void init()
{
        object me;

        me = this_player();

        if (! wizardp(me))this_object()->kill_ob(me);
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
        set("eff_qi",query("max_qi", me), me);
        set("qi",query("max_qi", me), me);
        set("eff_jing",query("max_jing", me), me);
        set("jing",query("max_jing", me), me);
        set("jingli",query("max_jingli", me), me);

        me->clear_condition();

        me->interrupt_me(this_object());

        delete_temp("no_perform", me);
        me->delete_temp("no_exert");

        set_temp("apply/attack", 30000, me);
        set_temp("apply/unarmed_damage", 20000, me);
        set_temp("apply/damage", 20000, me);
        set_temp("apply/armor", 20000, me);
        set_temp("apply/qy", 30, me);//氣運
        set_temp("apply/kar", 30, me);//福緣

        delete("my_life", me);

        message_vision(HIG "\n$N" HIG "大叫一聲，渾身散發着火紅的金光，剎那間，如獲重生！\n\n" NOR, me);

        return;
}

int receive_damage(string type, int damage, object who)
{
        object ob;

        object me = this_object();

        if( !query("my_life", me))return ::receive_damage(type,damage,who);

        if( query("qi", me)<query("max_qi", me)/10 )
        {
                new_life(); // 重生一次
                return 0;
        }

        return ::receive_damage(type, damage, who);
}

void unconcious()
{
        object ob;

        if( objectp(ob = previous_object(0)) && sscanf(base_name(ob), "/kungfu/skill/%*s") )
        {
                full_self();
                return;
        }

        die(query_last_damage_from());
}

// 檢查生命
void check_life()
{
        object env;

        // 如果life<=1則死亡
        if (1)
        {
                message_vision(HIR "\n$N" HIR "長嘯一聲，身體化作一團火球，消失了！\n" NOR, this_object());

                message_vision(BLINK + HIY "\n此次對抗火麒麟已經結束，2分鐘後清場，請抓緊時間。\n\n" NOR, this_object());

                env = environment(this_object());
                env->move_all_player_out(120);
                set("doing", 1, env);
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
        int mar;                //  需要瓜分的體會
        int i;
        string prop, name;
        mapping data;
        object ob, where;
        string *apply = ({ "reduce_busy", "avoid_busy", "def_damage", "avoid_weak",
                "add_locked", "reduce_damage", "add_busy", "add_weak", "avoid_locked",
                "add_damage", "add_skill" });


        // 定義獎勵物品列表
        // 機率  X / 百分之
        mixed oblist = ([
                "/clone/armor/qilin/jixing"              :              20,
                "/clone/armor/qilin/jinghua"             :              20,
                "/clone/armor/qilin/yaoyan"              :              20,
                "/clone/armor/qilin/jinlinyi"            :              20,
                "/clone/armor/qilin/yanmie"              :              20,
        ]);

        object gift_ob, gift_huoyan;
        string s_gift, *key_s_gift;
        string huoyan = "/clone/armor/qilin/jiezhi";
        int gift_point;

        if( objectp(ob = previous_object(0)) && sscanf(base_name(ob), "/kungfu/skill/%*s") )
        {
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

        if (! dob)
        {
                // 調用生命檢查函數
                check_life();
                return;
        }

        t = dob->query_team();

        if (objectp(dob) && environment(dob) == environment(this_object()))
        {
                exp = 22000 + random(22000);
                pot = 22000 + random(28000);
                weiwang = 6000 + random(9000);
                score = 6000 + random(6000);
                mar = 6000 + random(6000);
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
                                        // 會員獎勵再提高10%
                                        /*
                                        if( MEMBER_D->is_valid_member(query("id", tob)) )
                                        {
                                                if (environment(tob) == environment(dob))
                                                        GIFT_D->delay_boss_bonus(tob,
                                                                     ([ "exp"      : exp + exp * 1 / 10 + ((tob == dob) ? 50000 : 0),
                                                                   "pot"      : pot + pot * 1 / 10 / 10 + ((tob == dob) ? 50000 : 0),
                                                                     "weiwang"  : weiwang + weiwang * 1 / 10 + ((tob == dob) ? 50000 : 0),
                                                                   "score"    : score + score * 1 / 10 + ((tob == dob) ? 50000 : 0),
                                                                   "mar"      : mar + mar * 1 / 10 + ((tob == dob) ? 50000 : 0),
                                                                   "prompt"   : "你的隊伍殺死" + name() + HIG "之後"]), 999);
                                        }
                                        else */
                                        {
                                                if (environment(tob) == environment(dob))
                                                        GIFT_D->delay_boss_bonus(tob,
                                                                     ([ "exp"      : exp + ((tob == dob) ? 50000 : 0),
                                                                   "pot"      : pot + ((tob == dob) ? 50000 : 0),
                                                                   "weiwang"  : weiwang + ((tob == dob) ? 50000 : 0),
                                                                   "score"    : score + ((tob == dob) ? 50000 : 0),
                                                                   "mar"      : mar + ((tob == dob) ? 50000 : 0),
                                                                   "prompt"   : "你的隊伍殺死" + name() + HIG "之後"]), 100);
                                        }

                                }
                        }
                }
                else
                {
                        /*
                        if( MEMBER_D->is_valid_member(query("id", dob)) )
                        {
                                GIFT_D->delay_boss_bonus(dob,
                                        ([ "exp"      : exp + exp * 3 / 10,
                                           "pot"      : pot + pot * 3 / 10,
                                           "weiwang"  : weiwang + weiwang * 3 / 10,
                                           "score"    : score + score * 3 / 10,
                                           "mar"      : mar + mar * 3 / 10,
                                           "prompt"   : "你在殺死" + name() + HIG "之後"]), 999);
                        }

                        else */
                        {
                                GIFT_D->delay_boss_bonus(dob,
                                        ([ "exp"      : exp,
                                           "pot"      : pot,
                                           "weiwang"  : weiwang,
                                           "score"    : score,
                                           "mar"      : mar,
                                           "prompt"   : "你在殺死" + name() + HIG "之後"]), 100);
                       }
                }
        }

        // 100%掉一件物品
        if (1)
        {
                key_s_gift = keys(oblist);
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
                        //log_file("qilin-gift-none", s_gift + "\n");
                }
        }

        // 20%機率掉出火眼之戒
        if (random(10) < 2)
        {
                gift_huoyan = new(huoyan);
                set("who_get/id", "NONE", gift_huoyan);
                set("who_get/time", time()+30, gift_huoyan);//30秒內都不能撿取
                gift_huoyan->move(environment(this_object()));
                message_vision(HIW "叮~~一聲，從$N" HIW "身上掉出" + gift_huoyan->name() +
                               HIW "，落在地上。\n" NOR, this_object());

                //log_file("qilin_gift", "火麒麟於 " + ctime(time()) + " 掉出火眼之戒。\n");
        }

        where = environment();

        prop = apply[random(sizeof(apply))];
        name = EQUIPMENT_D->chinese(prop)+"元素";

        data = ([]);
        data["element"] = prop;
        data["name"] = name;
        ob = TEMPLATE_D->create_object("/inherit/template/element/element", prop, data);
        ob->set_name(name, ({prop, "element"}));
        ob->move(where);
        message_vision(HIC "叮~~一聲，從$N" HIC "身上掉出" + ob->name() + NOR + HIC "，落在地上。\n" NOR, this_object());
        // 檢查生命
        check_life();

        return ;
}
