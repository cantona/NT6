//huangyi.c

inherit NPC;

#include <ansi.h>

void create()
{
        set_name(HIY "黃衣" NOR, ({ "huang yi" }) );
        set("title", CYN "群玉八嬌" NOR);
        set("gender", "女性" );
        set("age", 22);
        set("str", 30);
        set("per", 40);
        set("long", @LONG
一個全身上下穿著黃裝，領露酥胸的美女．
LONG
        );
        set("combat_exp", 10);
        set("attitude", "friendly");
        setup();
        set("chat_chance", 15);
        set("chat_msg", ({
                "黃衣說道：我說湘湘妹子，你就從了吧！幹我們這行有什麼不好的，吃好的，穿好的，要什麼有什麼！\n",
                "黃衣嘆道：唉！已經勸了這丫頭三天了，我這張嘴都磨破了，她就是不出去接客！\n",
                "黃衣對湘湘說道：你就乖乖兒的聽我的話吧！別指望有誰會來救你出去了！\n",
        }) );

        setup();
        carry_object("/d/changan/npc/obj/skirt")->wear();
}

int accept_fight(object me)
{
        command("say 小女子哪裡是您的對手？");
        return 0;
}

int accept_kill(object me)
{       
        object ob;
        if (is_fighting()) return 1;
        if (query("called")) return 1;
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
                       "找死嗎？\n\n" NOR, me);
        ob->kill_ob(me);
        ob->set_leader(me);
        me->kill_ob(ob);
        set("called", 1);
        call_out("regenerate", 200);
        return 0;
}

int regenerate()
{
        set("called", 0);
        return 1;
}