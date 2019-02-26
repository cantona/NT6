#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("阿三", ({ "a san", "a", "san" }));
        set("long", "一個五十來歲的男子，上身裸露，右嘴角處\n"
                    "生有一個大痣，雙臂肌肉結實無比，一看便\n"
                    "知是外家好手。\n");
        set("title", HIR "西域少林派高手" NOR);
        set("gender", "男性");
        set("age", 55);
        set("attitude", "peaceful");
        set("shen_type", -1);

        set("per", 30);
        set("str", 60);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        
        set("max_qi", 4400);
        set("max_jing", 1400);
        set("neili", 5000);
        set("max_neili", 5000);
        set("jiali", 200);
        set("combat_exp", 1600000);

        set("chat_chance_combat", 200);
        set("chat_msg_combat", ({
                (: perform_action, "finger.fumo" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }) );

        set_skill("literate", 100);
        set_skill("buddhism", 150);
        set_skill("sanscrit", 150);
        set_skill("force", 250);
        set_skill("dodge", 250);
        set_skill("unarmed", 250);
        set_skill("parry", 250);
        set_skill("finger", 250);
        set_skill("shaolin-shenfa", 250);
        set_skill("yijinjing", 250);
        set_skill("jingang-zhi", 250);

        map_skill("dodge", "shaolin-shenfa");
        map_skill("force", "yijinjing");
        map_skill("finger", "jingang-zhi");
        map_skill("parry", "jingang-zhi");

        prepare_skill("finger", "jingang-zhi");

        setup();
        carry_object("/clone/cloth/cloth")->wear();
}

void init()
{
        add_action("begin","bi");
}
int accept_fight(object who)
{
        command("say 沒郡主的吩咐我不會出手。");
        return 0;
}

int accept_hit(object who)
{
        command("say 沒郡主的吩咐我不會出手。");
        return 0;
}

int accept_kill(object who)
{
        command("say 他奶奶的，郡主娘娘面前居然敢動手殺人。");
        return notify_fail("剎那間你只覺得不敢貿然下手。\n");
}

int accept_ansuan(object who)
{
        return notify_fail("你剛想暗算，可是隻見樓上人影晃動，根本看不清楚。\n");
}

int begin()
{
        object weapon;
        object me=this_player();
        object obj=this_object();

        if (objectp(present("he taichong", environment())))
        return 0;

        if( !query_temp("win_he", me) )
        {
                command("heng");
                command("say 閣下是誰？為何剛才不出戰，現在來趁機揀便宜。");
                return notify_fail("看起來阿三並不想跟你較量。\n");
        }

        if( objectp(weapon=query_temp("weapon", me)) )
        {
                command("say 我和你比空手，請將" + weapon->name() + "放下。");
                return notify_fail("看起來阿三並不想跟你較量。\n");
        }

        command("grin");
        command("say 好！");
        message_vision(HIY "$N突然大喝一聲，手作半爪，食指微曲，向$n" HIY
                           "直撲而來，架勢正是少林正宗的大力金剛指！\n" NOR,
                           obj,this_player());

        set_temp("bi", 1, me);
        set("anti",me);
        obj->kill_ob(this_player());
        this_player()->kill_ob(obj);
        return 1;
}

void die()
{
        if (objectp(query("anti")))
        {
                message_vision(HIR "\n只聽阿三幾聲慘嚎，全身各處關節竟然已被$n" HIR
                                   "一一用重手摺斷，大叫一聲，癱倒在地。\n" NOR,
                                   this_object(),query("anti"));

                message_vision(CYN "\n阿三倦縮在地，一張臉痛得全無血色，掙扎着説"
                                   "道：“郡主，小的無能。”，話未説完，已暈了過去。\n" NOR,
                                   this_object());

                message_vision(CYN "趙敏看了倒在地上的阿三一眼，面無表情地説道："
                                   "“來人，給我抬下去。”\n" NOR,
                                   this_object());

                message_vision(CYN "趙敏轉過頭對$n" CYN
                                   "微笑道：“不錯呀，現在讓阿二和你比。”\n" NOR,
                                   this_object(),query("anti"));

                set_temp("win_asan", 1, query("anti"));
                delete_temp("bi", query("anti"));
                delete_temp("win_he", query("anti"));
                destruct(this_object());
        }
}

