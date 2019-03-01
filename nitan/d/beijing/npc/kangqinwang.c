#include <ansi.h>

inherit NPC;

void create()
{
        set_name("康親王", ({ "kang qinwang", "kang"}));
        set("title", HIY "當朝親王" NOR);
        set("gender", "男性" );
        set("age", 42);
        set("long", "\n只見他一身錦衣，笑容滿面，任誰見了他都生不起氣來。\n"+
                      "此人深諳為官之道，極善察言觀色、溜須拍馬，頗得皇帝\n歡心。\n");
        set("shen_type", 1);
        set("combat_exp", 50000);
        set("str", 17);
        set("dex", 20);
        set("con", 17);
        set("int", 22);
        set("attitude", "peaceful");
        set_skill("dodge", 50);
        set_skill("unarmed", 50);

        setup();
        carry_object("/d/beijing/npc/obj/goldcloth2")->wear();
}

void init()
{
        object ob = this_player();

        ::init();
        remove_call_out("greeting");
        call_out("greeting", 1, ob);
}

void greeting(object ob)
{
        object man;

        if (! ob || environment(ob) != environment())
                return;

        if( query("meili", ob)<20 )
        {
                if (userp(ob))
                        message_vision("\n康親王一見$N, 頓時勃然大怒，叫道：“來人啊！將這廝給我拿下！”\n", ob);

                if(! present("shi", environment(ob)))
                {
                        message_vision("登時門外沖進幾個侍衛，揮刀向$N直撲過來。\n",ob);
                        man = new("/d/beijing/npc/shiwei2.c");
                        man->move(environment(ob));
                        man = new("/d/beijing/npc/shiwei2.c");
                        man->move(environment(ob));
                        man = new("/d/beijing/npc/shiwei2.c");
                        man->move(environment(ob));
                }
                return ;
        }

        switch (random(5))
        {
                case 0:
                        message_vision("\n$N剛一進門, 康親王便搶著迎了出來，笑道：“這位" +
                                       RANK_D->query_respect(ob) + "，請進請進。\n", ob);
                        if( query("meili", ob)<100 )
                        {
                                addn("meili", 10, ob);
                                message_vision(HIC "$N的魅力值提高了！\n" NOR, ob);
                                command("tell"+query("id", ob)+"你現在的魅力值是"+
                                        chinese_number(query("meili", ob))+"點");
                        }
                        break;
                default:
                        say("康親王笑道：不知這位" + RANK_D->query_respect(ob) +
                            "，光臨寒舍有何貴幹？\n");
                        break;
        }
}

