#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("阿二", ({ "a er", "a", "er" }));
        set("long", "阿二乃阿三的同門師兄，也是西域少林派一\n"
                    "等一的高手，被汝陽王一重金安置于麾下，\n"
                    "非常得汝陽王的賞識。\n");
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
        
        set("max_qi", 5000);
        set("max_jing", 1400);
        set("neili", 7000);
        set("max_neili", 7000);
        set("jiali", 240);
        set("combat_exp", 1800000);

        set("chat_chance_combat", 20);
        set("chat_msg_combat", ({
                (: perform_action, "strike.feng" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }) );

        set_skill("literate", 100);
        set_skill("buddhism", 150);
        set_skill("sanscrit", 150);
        set_skill("force", 270);
        set_skill("dodge", 270);
        set_skill("unarmed", 270);
        set_skill("parry", 270);
        set_skill("strike", 270);
        set_skill("shaolin-shenfa", 270);
        set_skill("yijinjing", 270);
        set_skill("banruo-zhang", 270);

        map_skill("dodge", "shaolin-shenfa");
        map_skill("force", "yijinjing");
        map_skill("strike", "banruo-zhang");
        map_skill("parry", "banruo-zhang");

        prepare_skill("strike", "banruo-zhang");

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
        command("say 沒郡主的吩咐我不會出手，殺了我也一樣。");
        return notify_fail("剎那間你只覺得下不了手。\n");
}

int accept_ansuan(object who)
{
        return notify_fail("你剛想暗算，可是只見樓上人影晃動，根本看不清楚。\n");
}

int begin()
{
        object weapon;
        object me=this_player();
        object obj=this_object();

        if (objectp(present("a san", environment())))
        return 0;

        if( !query_temp("win_asan", me) )
        {
                command("@@");
                command("say 閣下是誰？為何剛才不出戰，現在來趁機揀便宜。");
                return notify_fail("看起來阿二並不想跟你較量。\n");
        }

        if( objectp(weapon=query_temp("weapon", me)) )
        {
                command("shake");
                command("say 我也和你比空手，放下你的" + weapon->name() + "再說。");
                return notify_fail("看起來阿二並不想跟你較量。\n");
        }

        command("nod");
        command("say 我出招了。");
        message_vision( HIW "$N雙手合十，對著$n" HIW 
                            "微微一揖，雙掌平推，掌勁如巨浪般洶湧而出！\n" NOR,
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
                message_vision( HIR "\n只聽一聲轟響，阿二前胸被$n" HIR 
                                    "打中，胸骨盡斷，口中鮮血狂噴，身子如斷了線的風箏\n"
                                    "一樣直飛了出去，倒在地上動也不動一下。\n\n" NOR,
                                    this_object(),query("anti"));

                message_vision( CYN "趙敏頗為驚訝，可還是不露聲色，只是向親兵淡淡揮手說"
                                    "道：“抬下去。”\n" NOR,
                                    this_object());

                message_vision( CYN "趙敏又轉頭對$n" CYN 
                                    "微笑道：“很好，還剩下個阿大，你勝過了他倚天劍你就取走吧。”\n" NOR,
                                    this_object(), query("anti"));

                set_temp("win_aer", 1, query("anti"));
                delete_temp("bi", query("anti"));
                delete_temp("win_asan", query("anti"));
                destruct(this_object());
        }
}
