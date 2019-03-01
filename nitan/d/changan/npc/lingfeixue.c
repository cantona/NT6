//lingfeixue.c

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("凌飛雪", ({ "ling feixue", "feixue", "ling" }) );
        set("gender", "女性" );
        set("title",HIY "千金一笑" NOR);
        set("age", 23);
        set("long", 
        "凌飛雪原是一個青樓名妓，後來被當朝一位大官看中，據說這個\n群玉樓也是那位官員給她開的。");
        set("str", 40);
        set("dex", 40);
        set("con", 40);
        set("int", 40);
        set("per", 40);
        set("shen_type", -1);
        set_skill("unarmed", 50);
        set_skill("force", 50);
        set_skill("dodge", 50);
        set("combat_exp", 25000);
        set("max_qi", 300);
        set("max_jing", 300);
        set("qi", 300);
        set("jing", 300);
        set("neili", 500);
        set("max_neili", 500);
        set("attitude", "friendly");
        set("inquiry", ([
        "name" : "我就是曾經“一笑博千金”的長安第一美女凌飛雪。",
        "here" : "這兒就是長安城裡最最有名的群玉樓。",
        ]) );

        setup();
        set("chat_chance", 15);
        set("chat_msg", ({
                "凌飛雪得意地說道：當初我嫵媚一笑，也不知有多少人曾經拜倒在我裙下。\n",
                "凌飛雪若有所思的道：也不知到湘湘今天肯不肯出來接客。\n",
                "凌飛雪對你說道：這位客官，你來我們群玉樓就算對了，您想要什麼樣的姑娘都有。\n",
        }) );

        carry_object("/d/changan/npc/obj/skirt")->wear();
}

void init()
{
        object ob;

        ::init();
        if (interactive(ob = this_player()) && !is_fighting()) 
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object me)
{
        if (! objectp(me) || environment(me) != environment())
                return;

        command("look"+query("id", me));

        if( query("class", me) == "bonze" )
        {
                command("say 呵！" + RANK_D->query_respect(me) +
                        "也來光顧我們群玉樓啊。");
                command("say 快請上樓吧！");
        }

        if( query("gender", me) == "女性" )
        {
                command("say 哎呀，這位" + RANK_D->query_respect(me) +
                        "也來逛窯子，成何體同。");
                command("sigh");
        }
        command("say 樓上的姑娘們，有客人來了！");
        return ;
}

void accept_kill(object me)
{       
        object ob;
        if (is_fighting()) return;
        if (query("called")) return;
        command("say 要殺人了，快來人救命啊！");
        ob = present("bao biao");
        if (! ob)
        {
                seteuid(getuid());
                ob=new("/d/changan/npc/baobiao");
                ob->move(environment());
        }
        message_vision(HIC "\n忽然從門外沖進來幾個保鏢，對$N"
                       HIC "大喊一聲“幹什麼？在這兒鬧事，想"
                       "找死嗎？\n\n"NOR, me);
        ob->kill_ob(me);
        ob->set_leader(me);
        me->kill_ob(ob);
        this_object()->kill_ob(me);
        me->kill_ob(this_object());
        set("called", 1);
        call_out("regenerate", 200);
}

int regenerate()
{
        set("called", 0);
        return 1;
}