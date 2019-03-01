// baishou.c 白自在
#include <ansi.h>
inherit NPC;

void create()
{
        set_name("白自在", ({ "bai zizai", "bai" }));
        set("nickname", "雪山劍派掌門人");
        set("title", "鐵劍無敵");
        set("long",
                "他就是雪山劍派的掌門人，習武成性，自認為天下武功第一，\n"
                "他大約五十多歲，精明能幹，嫉惡如仇，性如烈火。\n");
        set("gender", "男性");
        set("age", 55);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 30);
        set("int", 30);
        set("con", 28);
        set("dex", 28);

        set("max_qi", 2000);
        set("qi", 2000);
        set("jing", 2000);
        set("max_jing", 2000);
        set("neili", 2000);
        set("max_neili", 2000);
        set("jiali", 100);
        set("combat_exp", 125000);
        set("score", 60000);

        set_skill("force", 100);
        set_skill("hand", 170);
        set_skill("dodge", 100);
        set_skill("staff", 170);
        set_skill("unarmed", 100);
        set_skill("hamagong", 200);
        set_skill("parry", 100);
        set_skill("sword", 100);
        set_skill("chanchu-bufa", 150);
        set_skill("shexing-diaoshou", 100);
        set_skill("literate", 80);
        set_skill("lingshe-zhangfa", 150);

        map_skill("force", "hamagong");
        map_skill("dodge", "chanchu-bufa");
        map_skill("unarmed", "shexing-diaoshou");
        map_skill("parry", "lingshe-zhangfa");
        map_skill("hand", "shexing-diaoshou");
        map_skill("staff", "lingshe-zhangfa");


        setup();
        carry_object("/clone/weapon/gangzhang")->wield();
        carry_object("/d/wudang/obj/whiterobe")->wear();
        add_money("gold",2);
}
void init()
{
        object ob;
        ob = this_player();
        ::init();
        remove_call_out("greeting");
        call_out("greeting", 1, ob);
}


void greeting(object ob)
{
        mapping fam;
        int i ;
        object me;
        object* obj;
        object obn;
        me = this_object();
        if (interactive(ob)
                 && !query("no_fight", environment(ob)) )
        {
                if( query("shen", ob)>0 )
                {
                        command("say 我輩練功學武，所為何事?");
                        command("say 行俠仗義，濟人困厄固然是本分，但卻是使之小者。");
                        command("say 為國為民，俠之大者，這八個字，日後名揚天下，成為萬民敬仰的大俠。");

                        obj = all_inventory(environment(me));
                        for(i=0; i<sizeof(obj); i++)
                        {
                                if(obj[i]==me)
                                        continue;
                                if( random(query("kar", ob))>28 )
                                {
command("say 既能到此，既為你我有緣，我這有樣東西，你拿去吧。\n");
                                        obn = new("/d/xiakedao/obj/shane-bu");
                                        obn->move(ob);
command("say 到俠客島來，想必是學武功吧，我在助你一臂之力。\n");
                                        ob->move("/d/xiakedao/neiting");
tell_object(ob,HIR"你只覺眼前一黑，什麼也不知道了，醒來卻神秘的出現在一個大廳內。\n"NOR);
                                }
command("say 既能到此，既為有緣，在後洞有一把劍，如有緣，你拿去吧。\n");
                        }
                }
                else
                {
                        command("say 年輕人應該走正路，你去吧。");
                }
        }
}
