// Written by Lonely@chinamud.cn

#include <ansi.h>
inherit BOSS;

void do_summon();
int checking(object me);
void create()
{
        set_name( "殭屍道長", ({ "jiangshi daozhang", "jiangshi", "daozhang" }));
        set("long", "一個可以控制殭屍的道長，看起來好可怕。。。\n");

        set("gender", "男性");
        set("age", 45);
        set("attitude", "peaceful");
        set("shen_type", 0);
        set("str", 25);
        set("int", 30);
        set("con", 25);
        set("dex", 30);
        set("shen", 0);

        set("max_qi", 3000000);
        set("max_jing", 700000);
        set("neili", 3000000);
        set("max_neili", 2000);
        set("jiali", 300);
        set("no_suck", 1);
        set("combat_exp", 300000000);
        set("level", 30);
        set("fight_boss", 1);
        set("score", 5000);

        set_skill("force", 1200);
        set_skill("taiji-shengong", 780);
        set_skill("dodge", 1000);
        set_skill("tiyunzong", 780);
        set_skill("unarmed", 1000);
        set_skill("taiji-quan", 600);
        set_skill("parry", 1000);
        set_skill("sword", 1200);
        set_skill("taiji-jian", 600);
        set_skill("blade", 800);
        set_skill("taiji-dao", 600);
        set_skill("taoism", 850);
        set_skill("literate", 1000);
        map_skill("force", "taiji-shengong");
        map_skill("dodge", "tiyunzong");
        map_skill("unarmed", "taiji-quan");
        map_skill("parry", "taiji-jian");
        map_skill("sword", "taiji-jian");
        map_skill("blade", "taiji-dao");
        set("class", "taoist");
        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: perform_action, "sword.lian" :),
                (: perform_action, "sword.chan" :),
                (: perform_action, "sword.sui" :),
                (: exert_function, "recover" :),
        }) );

        set_temp("apply/defense", 500);
        set_temp("apply/armor", 1500);
        set_temp("apply/reduce_damage", 80);
        set_temp("apply/reduce_busy", 25);

        set("clear_fuben", 1);
        //set("auto_perform", 1);
        set("rewards", ([
                "exp"   : 35000,
                "pot"   : 20000,
                "score" : 500,
        ]));

        set("drops", ([
                "RA&RANDOM30"    :       100,   // 低級普通裝備
                "RA&RANDOM40"    :       40,    // 低級普通裝備
                "FI&/clone/item/pcrystal"   :   10,
                "FI&/d/item/obj/xuantie"    :   10,
                "FI&/clone/item/ycrystal"   :   10,
        ]));

        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/wudang/obj/greyrobe")->wear();
}

void do_summon()
{
        object zombie,me,enemy,*enemies;
        object *obs;
        me = this_object();

        obs = all_inventory(environment(me));
        obs=filter_array(obs,(:query("id", $1) == "zombie":));
        if( sizeof(obs) >= 4 ) return;
        message_vision(HIM "\n$N嗬嗬乾嚎，周圍的殭屍王應聲而來。\n" NOR, me);
        zombie = new(__DIR__"zombie");
        zombie->move(environment(me));
        enemies = me->query_enemy();
        foreach(enemy in enemies) {
                if( !userp(enemy) ) continue;
                zombie->kill_ob(enemy);
                enemy->kill_ob(zombie);
        }
        message_vision( "\n\n$N惡狠狠地撲了上來。\n" , zombie);
        call_out("leave",30+random(10),zombie);
        if( !this_object()->is_busy() )
                this_object()->start_busy(3);
}

void leave(object zombie){
        if( !zombie || zombie->is_fighting() ) return;
        message_vision("\n$N消失了。\n",zombie);
        destruct(zombie);
}

int accept_fight(object ob)
{
        command("say 我可沒興趣陪你玩，快給我滾開。");
        return 0;
}

int accept_hit(object ob)
{
        message_vision(HIW "$N" HIW "臉色一變，閃過一道殺氣。怒"
                       "喝道：好一個" + RANK_D->query_rude(ob) +
                       "，來吧！\n" NOR, this_object());
        kill_ob(ob);
        return 1;
}

int accept_kill(object ob)
{
        if (! living(this_object()))
                return 1;

        return accept_hit(ob);
}

int accept_ansuan(object ob)
{
        return notify_fail("那人警惕性好高，你難以下手。\n");
}

int accept_touxi(object ob)
{
        return notify_fail("那人警惕性好高，你難以下手。\n");
}

void kill_ob(object me)
{
        remove_call_out("checking");
        call_out("checking", 1, this_object());

        return ::kill_ob(me);
}

int checking(object me)
{
        if( !objectp(me) ) return 0;

        do_summon();
        remove_call_out("checking");
        call_out("checking", 20, me);
        return 1;
}