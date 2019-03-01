// This program is a part of NT MudLIB

#include <ansi.h>
#include <command.h>

inherit BOSS;

void random_move();
void death_msg();

void create()
{
        set_name(HIW "扶桑武士" NOR, ({ "fusang wushi", "fusang", "wushi",}));
        set("title", HIR "來自扶桑劍氣道家的" NOR);
        set("gender", "男性");
        set("age", 22);
        set("long", @LONG
這是一位來自扶桑的武士，看上去異常冷漠。
LONG);
        set("attitude", "friendly");
        set("str", 31);
        set("int", 30);
        set("con", 30);
        set("dex", 46);
        set("per", 20);
        set("shen_type", 0);

        set("qi", 24000000);
        set("max_qi", 24000000);

        set("jing", 4000000);
        set("max_jing", 4000000);
        set("jingli", 4000000);
        set("max_jingli", 4000000);

        set("neili", 45000);
        set("max_neili", 45000);
        set("jiali", 2200);
        set("combat_exp", 40000000);

        set("special_skill/guimai", 1);

        set_skill("force", 1000);
        set_skill("pixie-jian", 1000);
        set_skill("surge-force", 1000);
        set_skill("liumai-shenjian", 1000);
        set_skill("sword", 1000);
        set_skill("finger", 1000);
        set_skill("whip", 1000);
        set_skill("dodge", 1000);
        set_skill("parry", 1000);
        set_skill("unarmed", 1000);
        set_skill("strike", 1000);
        set_skill("zuoyou-hubo", 500);
        set_skill("literate", 1000);
        set_skill("throwing", 1000);
        set_skill("taishang-wangqing", 500);
        set_skill("jingluo-xue", 500);
        set_skill("martial-cognize", 1000);

        map_skill("force", "surge-force");
        map_skill("sword", "pixie-jian");
        map_skill("dodge", "pixie-jian");
        map_skill("parry", "pixie-jian");
        map_skill("unarmed", "pixie-jian");
        map_skill("finger", "liumai-shenjian");

        prepare_skill("finger", "liumai-shenjian");

        set_temp("apply/attack",10000);
        set_temp("apply/defense", 10000);
        set_temp("apply/damage", 6000);
        set_temp("apply/unarmed_damage", 6000);
        set_temp("apply/armor", 6000);
        set_temp("apply/fy", 10);

        set("chat_chance", 30); 
        set("chat_msg", ({ (: random_move :) })); 
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: command("perform sword.duo and sword.gui") :),
                (: command("perform sword.pi and sword.po") :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: perform_action, "sword.jian twice" :),
                (: perform_action, "finger.tian twice" :),
        }) );

        set("end_time", 300);
        set("death_msg", (: death_msg :));

        set("rewards", ([
                "exp"   : 10000,
                "pot"   : 30000,
                "mar"   : 150,
                "score" : 30,
                "gold"  : 5,
        ]));

        set("drops", ([
                "RA&RANDOM60"    :       100,   // 低級普通裝備
                "RA&RANDOM70"    :       40,    // 低級普通裝備
                "FI&/clone/armor/fusang/heima-yi"       : 20,
                "FI&/clone/armor/qianshou-guanyin"      : 5,
                "FI&/clone/armor/mingwang-xiang"        : 10,
                "FI&/clone/armor/shougu"                : 10,
                "FI&/clone/armor/fusang/shenxing-xue"   : 20,
                "FI&/clone/armor/sanye-cao"             : 10,
                "FI&/clone/fam/enchase/guxuan-yu2"      : 8,
                "FI&/clone/armor/fudai"                 : 10,
                "FI&/clone/tessera/rune10"  :   1,
                "FI&/clone/fam/enchase/xuanbing-shi2"   : 8,
                "FI&/clone/armor/fusang/jiakang-toudai" : 20,
        ]));

        setup();

        set_temp("born_time", time()); 
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/cloth/baipao")->wear();
        set("startroom", "/d/xiakedao/xkroad4");
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
}

mixed hit_ob(object me, object ob, int damage_bouns)
{
        ob->start_busy(5 + random(6));
        me->receive_wound("qi", 1500 + random(1600), ob);
        return HIY "$N" HIY "怒喝一聲，奮力反抗，竟逼得$n" HIY "手忙腳亂。\n" NOR;
}

void heart_beat()
{
        if (query("neili") < 1 && random(50) == 1)
                set("neili", query("max_neili"));

        return ::heart_beat();
}

void random_move()
{
        object env;

        if (time() - query_temp("born_time") > 1800)
        {
                env = environment(this_object());
                message_vision("$N急急忙忙的走了。\n", this_object());

                CHANNEL_D->channel_broadcast("mess", env->short() + HIW "(" + LOOK_CMD->locate(base_name(env)) + ")一帶出現的" +
                        HIR + this_object()->short() + HIG "消失了。\n" NOR);

                destruct(this_object());
                return;
        }
        //::random_move();
}

void death_msg()
{
        command("chat 中原武學果然名不虛傳 ……");
        CHANNEL_D->channel_broadcast("rumor", "聽說" + name() + HIM "被江湖人士所殺。" NOR);
}


