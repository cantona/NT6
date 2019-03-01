// This program is a part of NT MudLIB

#include <ansi.h>
#include <command.h>

inherit BOSS;

void random_move();
void death_msg();

void create()
{
        set_name(HIY "七彩" HIM "琉璃獸" NOR, ({ "qicai liulishou", "qicai", "liulishou" }) );
        set("title", HIW "聖誕" HIR "怪獸" NOR);
        set("gender", "男性");
        set("age", 8888);
        set("long", @LONG
這是一只長相奇特怪獸，全身幻出七彩之色，頭大身小，一對渾圓的眼
珠閃爍出攝人的光芒。
LONG );
        set("combat_exp", 2000000000);
        set("shen_type", 0);
        set("attitude", "heroism");
        set("max_neili", 5000000);
        set("neili", 5000000);
        set("max_jing", 5000000);
        set("jing", 5000000);
        set("max_qi", 900000000);
        set("eff_qi", 900000000);
        set("qi", 900000000);
        set("jingli", 5000000);
        set("max_jingli", 5000000);

        set("no_nuoyi", 1); // 不被挪移影響

        set("str", 200);
        set("int", 100);
        set("con", 100);
        set("dex", 300);

        set_skill("unarmed", 4000);
        set_skill("sword", 4000);
        set_skill("parry", 4000);
        set_skill("dodge", 4000);
        set_skill("force", 4000);

        set("jiali", 1000);

        set("end_time", 300);
        set("death_msg", (: death_msg :));

        set("rewards", ([
                "exp"   : 10000,
                "pot"   : 3000,
                "mar"   : 15,
                "score" : 30,
                "gold"  : 5,
        ]));

        set("drops", ([
                "RA&RANDOM30"    :       100,   // 低級普通裝備
                "RA&RANDOM40"    :       40,    // 低級普通裝備
                "FI&/clone/goods/sun"    :   20,
                "FI&/clone/goods/moon"   :   20,
                "FI&/clone/armor/qicai-xue"      :   20,
        ]));

        set_temp("apply/attack", 150000);
        set_temp("apply/unarmed_damage", 100000);
        set_temp("apply/damage", 100000);
        set_temp("apply/armor", 10000);

        if (clonep(this_object()))
        {
                set("chat_chance", 30);
                set("chat_msg", ({ (: random_move :) }));
                set_temp("born_time", time());
                //keep_heart_beat();
        }

        setup();
}

int accept_fight(object ob)
{
        message_vision("$N一聲巨吼，撲了過來。\n",
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
        ob->start_busy(20 + random(10));
        me->receive_wound("qi", 5000 + random(3000), ob);
        return HIY "$N" HIY "周圍霧氣繚繞，直逼得$n" HIY "頭暈目眩。\n" NOR;
}

void heart_beat()
{
        if (query("neili") < 1)
                set("neili", query("max_neili"));

        ::heart_beat();
}

void random_move()
{
        object env;

        if (time() - query_temp("born_time") > 1800)
        {
                env = environment(this_object());
                message_vision("$N長嘯一聲，化作一團火燄，消失在天際。\n", this_object());
                
                CHANNEL_D->channel_broadcast("mess", "聽說"+
                        env->short() + HIW "(" + LOOK_CMD->locate(base_name(env)) + ")一帶出現的" +
                        HIR + this_object()->short() + HIG "消失了。\n" NOR);

                destruct(this_object());
                return;
        }
        //::random_move();
}

void death_msg()
{
        command("chat 看來這趟東方之行實在是自討沒趣！");
        message_vision("$N長嘯一聲，化作一團火燄，消失在天際。\n", this_object());
        CHANNEL_D->channel_broadcast("rumor",
                        "聽說" + name() + HIM "被一群武林異士打敗，敗興而歸。" NOR);
}
