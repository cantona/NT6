#include <ansi.h>
inherit NPC;

void create()
{
        set_name("守寺僧兵", ({ "seng bing", "seng", "bing" }));
        set("long", @LONG
這是一位身材高大的壯年僧人，兩臂粗壯，膀
闊腰圓。他手持僧棍，身穿一襲黑色袈裟，似
乎懷有一身武藝。
LONG);
        set("gender", "男性");
        set("attitude", "peaceful");
        set("class", "bonze");

        set("age", 40);
        set("shen_type", -1);
        set("str", 25);
        set("int", 20);
        set("con", 20);
        set("dex", 25);
        set("max_qi", 500);
        set("max_jing", 300);
        set("neili", 500);
        set("max_neili", 500);
        set("jiaji", 50);
        set("combat_exp", 10000);
        set("score", 1);

        set_skill("force", 50);
        set_skill("xiaowuxiang", 50);
        set_skill("dodge", 50);
        set_skill("shenkong-xing", 50);
        set_skill("unarmed", 50);
        set_skill("yujiamu-quan", 50);
        set_skill("parry", 50);
        set_skill("staff", 50);
        set_skill("xiangmo-chu", 50);

        map_skill("force", "xiaowuxiang");
        map_skill("dodge", "shenkong-xing");
        map_skill("unarmed", "yujiamu-quan");
        map_skill("parry", "xiangmo-chu");
        map_skill("staff", "xiangmo-chu");

        setup();

        carry_object("/d/xueshan/obj/senggun")->wield();
        carry_object("/d/xueshan/obj/b-jiasha")->wear();
}

void init()
{
        object me, ob;
        mapping fam;

        ::init();

        ob = this_player();
        me = this_object();
        
        if (interactive(ob) 
            && !query("no_fight", environment(ob) )
            && ((fam=query("family", ob) )
           && fam["family_name"] != "雪山寺"))
        {
                if( !query_temp("warned", ob) )
                {
                        command("say 你是誰？怎麼闖入雪山寺來了！");
                        command("say 快給我速速離開，下次再看到你決不輕饒。");
                        set_temp("warned", 1, ob);
                } else
                if( query_temp("stay", ob)<30 )
                {
                        command("say 喂，叫你離開，你怎麼還呆在這裡？");
                        addn_temp("stay", 1, ob);
                } else
                {
                        command("say 天堂有路你不走，地獄無門你闖進來，死吧！");
                        me->set_leader(ob);
                        remove_call_out("kill_ob");
                        call_out("kill_ob", 1, ob); 
                }
        }

}
