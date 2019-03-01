// This program is a part of NT MudLIB

#include <ansi.h>
#include <command.h>

inherit BOSS;

void random_move();
void death_msg();
int big_blowing();

void create()
{
        set_name(HIC "神魔皇" NOR, ({ "shen mo huang", "shenmo", "huang" }) );
        set("title", HIY "魔族至尊" NOR);
        set("gender", "男性");
        set("age", 8888);
        set("long", @LONG
這是一隻代表月（Moon），掌管着Vampire Land，其能力為吸入垂耳兔獸並分解他們的資料使自己擁有不死之身的魔族。
不受任何挪移、致命一擊、致暈攻擊、忙亂的效果影響。
LONG );
        set("combat_exp", 500000);
        set("shen_type", 0);
        set("attitude", "heroism");
        set("max_neili", 2000000000);
        set("neili", 5000000000);
        set("max_jing", 1000000000);
        set("jing", 1000000000);
        set("max_qi", 2000000000);
        set("eff_qi", 2000000000);
        set("qi", 200000000);
        set("jingli", 1500000000);
        set("max_jingli", 1500000000);
        set("level", 140);

        set("no_nuoyi", 1); // 不被挪移影響

        set("str", 700);
        set("int", 400);
        set("con", 400);
        set("dex", 700);

        set_skill("unarmed", 2500);
        set_skill("sword", 2500);
        set_skill("parry", 2500);
        set_skill("dodge", 2500);
        set_skill("force", 2500);

        set("jiali", 1000);

        set_temp("apply/attack", 5000);
        set_temp("apply/unarmed_damage", 5000);
        set_temp("apply/damage", 5000);
        set_temp("apply/armor", 5000);

        set("chat_chance", 30);
        set("chat_msg", ({ (: random_move :) }));
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: big_blowing :),
        }));
        set("end_time", 600);
        set("death_msg", (: death_msg :));

        set("rewards", ([
                "exp"   : 40000,
                "pot"   : 12000,
                "mar"   : 3000,
                "score" : 600,
                "gold"  : 100,
        ]));

        set("drops", ([
                "RA&RANDOM20"    :       100,   // 低級普通裝備
                "RA&RANDOM30"    :       40,    // 低級普通裝備
                "FI&/clone/armor/fenghuang-chai2"           :           20,
                "FI&/clone/armor/haizhi-xin2"               :           20,
                "FI&/clone/armor/hong-feihun2"              :           15,
                "FI&/clone/armor/lan-feihun2"               :           10,
                "FI&/clone/armor/zi-feihun2"                :           10,
                "FI&/clone/armor/moling-zhiyi2"             :           15,
                "FI&/clone/armor/tiankong-zhiyi2"           :           10,
                "FI&/clone/armor/piaoxue2"                  :           10,
                "FI&/clone/armor/suomai2"                   :           15,
                "FI&/clone/armor/tianming2"                 :           15,
                "FI&/clone/armor/wuwei2"                    :           15,
                "FI&/clone/armor/zhanhun-xue2"              :           15,
                "FI&/clone/armor/fenghuang-chai3"           :           10,
                "FI&/clone/fam/max/naobaijin"               :           5,
                "FI&/clone/armor/feima-xue2"                :           20,
                "FI&/clone/armor/shengling-yaodai2"         :           30,
                "FI&/clone/armor/shangu-zhixing2"           :           45,
                "FI&/clone/armor/fenghuang-chai"            :           30,
                "FI&/clone/armor/haizhi-xin"                :           30,
                "FI&/clone/armor/hong-feihun"               :           35,
                "FI&/clone/armor/lan-feihun"                :           30,
                "FI&/clone/armor/zi-feihun"                 :           30,
                "FI&/clone/armor/moling-zhiyi"              :           35,
                "FI&/clone/armor/tiankong-zhiyi"            :           30,
                "FI&/clone/armor/piaoxue"                   :           30,
                "FI&/clone/armor/suomai"                    :           35,
                "FI&/clone/armor/tianming"                  :           35,
                "FI&/clone/armor/wuwei"                     :           35,
                "FI&/clone/armor/zhanhun-xue"               :           35,
                "FI&/clone/armor/fenghuang-chai"            :           30,
                "FI&/clone/armor/feima-xue"                 :           40,
                "FI&/clone/armor/shengling-yaodai"          :           50,
                "FI&/clone/armor/shangu-zhixing"            :           65,
                "FI&/clone/armor/fenghuang-chai3"           :           40,
                "FI&/clone/armor/haizhi-xin3"               :           3,
                "FI&/clone/armor/hong-feihun3"              :           3,
                "FI&/clone/armor/lan-feihun3"               :           3,
                "FI&/clone/armor/zi-feihun3"                :           3,
                "FI&/clone/armor/moling-zhiyi3"             :           3,
                "FI&/clone/armor/tiankong-zhiyi3"           :           3,
                "FI&/clone/armor/piaoxue3"                  :           3,
                "FI&/clone/armor/suomai3"                   :           3,
                "FI&/clone/armor/tianming3"                 :           3,
                "FI&/clone/armor/wuwei3"                    :           3,
                "FI&/clone/armor/zhanhun-xue3"              :           3,
                "FI&/clone/armor/fenghuang-chai3"           :           3,
                "FI&/clone/armor/feima-xue3"                :           3,
                "FI&/clone/armor/shengling-yaodai3"         :           2,
                "FI&/clone/armor/shangu-zhixing3"           :           4,
                "FI&/clone/fam/enchase/shenglong-zhiyan"    :           1,
                "FI&/clone/fam/enchase/shenglong-zhihun"    :           1,
                "FI&/clone/tuteng/diwang-suipian35"         :           5,
                "FI&/clone/tuteng/diwang-suipian"+(12+random(7)) :      10,
                "FI&/clone/tongren/tongren"+(1+random(2))   :           1,
        ]));
        set_temp("apply/reduce_damage", 80);
        set_temp("apply/reduce_busy", 36);
        set_temp("apply/add_weak", 60);
        set_temp("apply/add_busy", 15);
        set_temp("apply/add_poison", 80);

        setup();
        set_temp("born_time", time());
        if (clonep()) keep_heart_beat();
}

void init()
{
        object me, ob;

        ::init();
        if (! interactive(me = this_player()))
                return;

        remove_call_out("kill_ob");
        call_out("kill_ob", 0, me);
}

int big_blowing()
{
        message_vision(HIB "$N" HIB "深深地吸入一口氣，全身發出耀眼的金色，"
                       "整個腹部脹大了幾倍！！\n" NOR, this_object());

        remove_call_out("hurting");
        call_out("hurting", random(2) + 1);
        return 1;
}

int hurting()
{
        int dam, i , num;
        object *inv;

        message_vision(HIB "$N" HIB "噴出一團巨大的火球．．．．．．整個天地都被火球吞沒！！！\n" NOR,
                       this_object());

        inv = all_inventory(environment(this_object()));

        num = sizeof(inv);
        if (num < 1) num = 1;
        if (num > 5) num = 5;

        dam = 160000 / num;

        for (i=sizeof(inv)-1; i>=0; i--)
        {
                if (living(inv[i]) && inv[i] != this_object())
                {
                        dam -= query_temp("apply/reduce_fire", inv[i]);
                        if (dam <0) dam = 0;

                        inv[i]->receive_wound("qi", dam, this_object());
                        inv[i]->receive_wound("jing", dam/2, this_object());
                        COMBAT_D->report_status(inv[i], 1);
                }
        }
        return 1;
}


int accept_fight(object ob)
{
        message_vision("$N一聲長嘯，撲了過來。\n",
                       this_object(), ob);
        kill_ob(ob);
        return -1;
}

int accept_kill(object ob)
{
        return 1;
}

int accept_hit(object ob)
{
        return 1;
}

mixed hit_ob(object me, object ob, int damage_bouns)
{
        ob->start_busy(5 + random(5));
        me->receive_wound("qi", 25000 + random(30000), ob);
        return HIY "$N" HIY "周圍霧氣繚繞，直逼得$n" HIY "頭暈目眩。\n" NOR;
}

void heart_beat()
{
        if (query("neili") < 1)
                set("neili", query("max_neili"));

        ::heart_beat();
}

void death_msg()
{
        command("chat 人間居然有如此厲害的角色，看來我魔族在人間無立身之地了！");
        message_vision("$N長嘯一聲，響徹天地，然後身體慢慢變得透明，消失在無盡魔氣之中。\n", this_object());
        CHANNEL_D->do_channel(this_object(), "rumor",
                        "聽説" + name() + HIM "在人間受辱後，回到了魔族，從此不再出沒人間。" NOR);
}

void random_move()
{
        if (time() - query_temp("born_time") > 1800)
        {
                message_vision("$N長嘯一聲，響徹天地，然後身體慢慢變得透明，消失在無盡魔氣之中。\n", this_object());
                CHANNEL_D->do_channel(this_object(), "rumor",
                        "聽説" + name() + HIM "在人間走了一遭後，百無聊奈，又返回了魔界。" NOR);
                destruct(this_object());
                return;
        }
        //::random_move();
}

varargs void start_busy(mixed new_busy, mixed new_interrupt)
{
        return;
}
