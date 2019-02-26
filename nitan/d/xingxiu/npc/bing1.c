// Room: /d/xingxiu/npc/bing.c
// Last Modified by Winder on Apr. 25 2001

#include <ansi.h>
inherit NPC;
void create()
{
        set_name("邊防官兵", ({ "guan bing", "bing" }));
        set("age", 32);
        set("gender", "男性");
        set("long", "他是個長年駐守這裏的邊防兵。\n");
        set("attitude", "peaceful");
        set("str", 33);
        set("int", 16);
        set("con", 25);
        set("dex", 20);
        set("no_get",1);
        set("combat_exp", 30000);
        set_skill("unarmed", 40);
        set_skill("dodge", 40);
        set_skill("parry", 40);
        set_skill("blade", 40);
        set_skill("force", 40);
        set_temp("apply/attack", 40);
        set_temp("apply/defense", 40);
        set_temp("apply/damage", 20);
        set_temp("apply/armor", 40);        
        setup();
        carry_object("/clone/weapon/gangdao")->wield();
        carry_object("/d/city/obj/junfu")->wear();
}

int accept_fight(object me)
{
        command("say 大爺我守邊關累得要死，沒空和"+RANK_D->query_respect(me)+"過招玩。\n");
        return 0;
}

void init()
{
        object ob, me, money;

        ::init();
        ob = this_player();
        if (!interactive(ob)) return;
        if (!living(ob)) return;
        if( query_temp("ride_horse", ob))return ;
        if( ob->query_condition("killer") || query_temp("xx_rob", ob) )
        {
                remove_call_out("kill_ob");
                call_out("kill_ob", 0, ob);
        }
/*
        else if(random(50)<=1)
                {
                        me=this_object();         
                        command("say 這個"+RANK_D->query_rude(ob)+"給我站住，例行檢查！");
                        if( query("guanbing", ob) )
                        {
                                addn("guanbing", -1, ob);
                                message_vision(HIY"$n對着$N看了半天，最後招了招手讓$N快走。\n"NOR, ob, me);
                                return;
                        }
                        message_vision(HIY"$n將$N攔住，在$N身上摸索了半天。\n"NOR, ob, me);
                        ob->start_busy(5);
                        if(money = present("gold_money", ob))
                        {
                                money->move(me);
                                addn("guanbing", 2, ob);
                                tell_object(ob, HIR "結果你發現邊防官兵將你身上的黃金拿走了！\n"NOR);
                        }
                        else if(money = present("silver_money", ob))
                                {
                                        money->move(me);
                                        addn("guanbing", 1, ob);
                                        tell_object(ob, HIR "結果你發現邊防官兵將你身上的白銀拿走了！\n"NOR);
                                }
                        else command("say 你這個窮光蛋，連點油水都沒有，給我滾！");
                        command("kick"+query("id", ob));
                }
*/
}