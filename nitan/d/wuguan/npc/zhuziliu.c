#include <ansi.h>
inherit NPC;

void create()
{
        set_name("朱子柳", ({"zhu ziliu", "zhu", "ziliu"}));
        set("gender", "男性");
        set("age", 55);
        set("title", HIY "南帝四大弟子" NOR);
        set("long", @LONG
朱子柳乃是一燈大師的四大弟子之一，現在正協助
郭靖、黃蓉鎮守襄陽城。
LONG );
        set("attitude", "peaceful");
        set("per", 17);
        set("str", 40);
        set("int", 20);
        set("con", 30);
        set("dex", 25);

        set("max_qi", 3200);
        set("max_jing", 2600);
        set("neili", 4200);
        set("max_neili", 4200);
        set("jiali", 150);
        set("combat_exp", 2500000);
        set("score", 5000);

        set_skill("force", 180);
        set_skill("duanshi-xinfa", 180);
        set_skill("dodge", 180);
        set_skill("tiannan-bu", 180);
        set_skill("cuff", 180);
        set_skill("jinyu-quan", 180);
        set_skill("strike", 180);
        set_skill("wuluo-zhang", 180);
        set_skill("dagger", 200);
        set_skill("qingliang-daxuefa", 200);
        set_skill("parry", 180);
        set_skill("literate", 400);
        set_skill("martial-cognize", 180);

        map_skill("force", "duanshi-xinfa");
        map_skill("dodge", "tiannan-bu");
        map_skill("cuff", "jinyu-quan");
        map_skill("strike", "wuluo-zhang");
        map_skill("dagger", "qingliang-daxuefa");
        map_skill("parry", "qingliang-daxuefa");

        prepare_skill("cuff", "jinyu-quan");
        prepare_skill("strike", "wuluo-zhang");

        create_family("段氏皇族", 6, "家臣");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "dagger.ding" :),
                (: perform_action, "cuff.man" :),
                (: perform_action, "strike.bian" :),
                (: exert_function, "recover" :),
        }));

        setup();
        carry_object("/d/dali/npc/obj/junfu")->wear();
        carry_object("/d/meizhuang/obj/panguanbi")->wield();
        add_money("silver", 10);
}

void init()
{
        object ob;

        ::init();
        if (interactive(ob = this_player()) && ! is_fighting())
	{
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

int recognize_apprentice(object ob, string skill)
{
        if( query("combat_exp", ob)>20000 )
        {
                command("say 你經驗也不低了，應該多出去鍛鍊，可別埋沒在這裏。");
                return -1;
        }

        if (skill != "literate")
        {
                command("shake");
                command("say 在這兒我最多傳授你一些讀書寫字的常識。");
                command("say 其它的還是等你將來拜師後找師父學吧。");
                return -1;
        }

        if (skill == "literate" && ob->query_skill("literate", 1) > 99)
        {
                command("haha");
                command("say 你的文學造詣已經非常不錯了，就到此為止吧。");
                return -1;
        }

        if( !query_temp("can_learn/zhuziliu", ob) )
        {
                command("smile");
                command("say 趁年輕多讀點書是好事，我就教你點讀書寫字的常識吧。");
                set_temp("can_learn/zhuziliu", 1, ob);
        }
        return 1;
}

void greeting(object ob)
{
       if (! ob || environment(ob) != environment()) return;

       if (ob->query_skill("literate") > 99) return;

       command("pat"+query("id", ob));
       command("say 這位" + RANK_D->query_respect(ob) + "，過來跟我學些知"
               "識(" HIY "xue zhu ziliu literate" NOR + CYN ")吧。" NOR);

}