// furen.c
inherit NPC;
#include <ansi.h>

void create()
{
        set_name("莊夫人", ({ "san furen", "san","furen"}));
        set("title", "莊家三少奶奶" );
        set("nickname", HIW "未亡人" NOR);
        set("long",  "\n只見她約莫二十六七年紀,全身縞素,不施脂粉,臉色蒼白.\n");
        set("gender", "女性");
        set("age", 25);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 30);
        
        set("max_qi", 1000);
        set("max_jing", 400);
        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 100);
        set("combat_exp", 100000);
        set("score", 50000);

        set_skill("force", 90);
        set_skill("dodge", 90);
        set_skill("unarmed", 90);
        set_skill("sword", 90);
        set_skill("taiji-jian", 80);
        set_skill("tiyunzong",90);
        map_skill("dodge", "tiyunzong");
        map_skill("parry", "tiaji-jian");
        map_skill("sword", "tiaji-jian");

        set_temp("apply/attack", 35);
        set_temp("apply/attack", 35);
        set_temp("apply/damage", 35);
        set("inquiry", ([
                "鰲拜"  : "鰲拜是我家的大仇人。",
                "吳之榮": "我一定要手刃了這個姦賊。",
                "禮物"  : "這樣禮物可不一般，她就是我的好丫環雙兒。",
                "雙兒"  : "這小丫頭跟隨我多年，做事也還妥當。",
        ]) );
        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
}

void init()
{
        object ob; 
        ob = this_player();

        if( interactive(ob) && !is_fighting() ) 
        {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}

void greeting(object ob)
{
        if (! ob || environment(ob) != environment() || ! living(ob))
                return;

        say( "莊夫人說道：很久沒有人來了，這位" + RANK_D->query_respect(ob) +
             "，可知道我相公的下落嗎？\n");
}

int accept_object(object me, object ob)
{
        int i;

        if ( userp(ob) ) return 0; 
        if( query("id", ob) == "wuzhirong" )
        {
                i=query("weiwang", me);

                message_vision("\n莊夫人大喜道：狗賊，死去吧！"
                               "想不到你也有今天！\n", me);
                ob->move(environment());
                ob->die();

                if ( i >= 50 && i < 70 )
                {
                        i += 10;
                        set("weiwang", i, me);
                        message_vision(HIC "\n$N的江湖威望提高了！\n" NOR, me);
                        return -1;
                }

              set_temp("zhuang_liwu", 1, me);
                 message_vision("\n莊夫人對$N說道：這位" +
                               RANK_D->query_respect(me) +
                               "，如此大恩大德，妾身實不知何以為報。\n"
                                "莊夫人微一沉思，道：我想送恩公一件禮物，"
                               "務請勿卻是幸。\n", me);
        } else
        if( query("name", ob) == "明史輯略" || 
             query("name", ob) == "莊允城" )
        {
                 message_vision("\n莊夫人說道：這位" +
                               RANK_D->query_respect(me)+"，多謝了！\n", me);

                 message_vision("莊夫人感嘆道：唉！你要能幫我找到吳之榮這"
                               "狗賊就好了。\n", me);
        }                
         return 1;
}
