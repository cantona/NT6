// popi1.c
// Last Modified by Winder on Jul. 15 2000

inherit NPC;

void create()
{
        set_name("張不四", ({"po pi","punk"}) );
        set("gender", "男性" );
        set("title","潑皮");
        set("age", 20);
        set("long", "這人是個潑皮，整天無所事事，到處閒逛。。\n");
        set_temp("apply/attack", 10);
        set_temp("apply/defense", 10);
        set_skill("unarmed", 20);
        set("combat_exp", 2000);
        set("str", 25);
        set("per", 20);
        set("inquiry", ([
                "here" : "掙大眼睛自己看看，沒看老子正忙著嗎？！",
        ]) );
        set("chat_chance", 20);
        set("chat_msg", ({
"潑皮罵罵咧咧的說道：賭場老板真他媽不是東西，老子欠債又不是不能還了，竟敢把老子轟出來？！\n",
"潑皮盯著自己的手看了半天，咕咕囔囔的叨嘮著：”真是怪事，這手盡抓癟十！？\n",
"媽的！潑皮不滿的嘟囔著：人都他媽死絕了，老子一沒錢了，連個鬼影都見不到了！\n",
"潑皮說道：去去，一邊去，大爺正煩著呢！\n",
"潑皮打量者你，不知道想做些什麼。\n",
"我知道個秘密，怎麼樣，咱最近手頭有點緊。\n",
                (:random_move:),
        }) );
        setup();
        carry_object(__DIR__"obj/poyi")->wear();
}

int accept_object(object me, object ob)
{
        int val;

        val = ob->value();
        if ( val < 5000  )
        {
                message_vision("張不四對$N一翻大眼，這麼一點錢就想打發大爺我？\n", me);
                command("kick"+query("id", me));
                return 0;
        }
        if (random(5) == 0)
                command("whisper"+query("id", me)+"據說楊府藏有不世奇珍，是件神物呢！");
        else 
        {
                command("look"+query("id", me));
                command( "say 現在真是怪事多，還到處硬塞錢的，那我就收下了。");
        }
        return 1;
}
