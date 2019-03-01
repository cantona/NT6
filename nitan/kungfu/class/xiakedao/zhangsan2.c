// zhangsan.c

#include <ansi.h>

inherit NPC;
int give_ling();

void create()
{
        set_name("張三", ({ "zhang san", "zhang", "san" }));
        set("title", HIY "俠客島賞善使者" NOR);
        set("gender", "男性");
        set("age", 37);
        set("long",
              "這是個看起來三十來歲的漢子，身材肥胖，臉色紅潤。\n"
        );

        set("str", 36);
        set("int", 35);
        set("con", 34);
        set("dex", 37);

        set_temp("apply/attack", 600);
        set_temp("apply/armor", 1500);
        set_temp("apply/damage", 800);
        set_temp("apply/unarmed_damage", 800);
        set_temp("apply/dodge", 600);
        set_temp("apply/parry", 600);

        set("qi", 9000);
        set("max_qi", 9000);
        set("jing", 20000);
        set("max_jing", 20000);
        set("neili", 15000);
        set("max_neili", 15000);
        set("jiali", 250);
        set("combat_exp", 5000000);
        set("score", 20000000);

        set_skill("force", 340);
        set_skill("taixuan-gong", 340);
        set_skill("dodge", 340);
        set_skill("taixuan-gong", 340);
        set_skill("unarmed", 340);
        set_skill("taixuan-gong", 340);
        set_skill("parry", 340);

        map_skill("force", "taixuan-gong");
        map_skill("dodge", "taixuan-gong");
        map_skill("unarmed", "taixuan-gong");
        map_skill("parry", "taixuan-gong");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: perform_action, "unarmed.xuan" :),
                (: perform_action, "unarmed.hun" :),
        }) );
        create_family("俠客島", 0, "賞善使者");
        set("inquiry",  ([
            "賞善罰惡令" : (: give_ling :),
            "臘八粥"     : "拿了賞善罰惡令，上俠客島就可以喝臘八粥，你也想去？\n",
        ]));

        set("lingpai", 3);

        setup();

        carry_object("/clone/misc/cloth")->wear();
}


void unconcious()
{
        die();
}

int give_ling()
{
        object ling;
        object me;

        me = this_player();
      
        if( query("shen", me)<-100000 )
        {
             command("heng");
             command("say 爾等邪魔歪道，我正欲相除，你卻反找上門來了！\n");
             kill_ob(me);
             return 1;
        }
        
        if (me->query_skill("force", 1) < 200)
        {
             command("say 閣下內功不濟，這賞善罰惡令你還是要不得！\n");
             return 1;
        }  

        if( query("weiwang", me)<100000 )
        {
             command("say 閣下非江湖成名人士，還是請回吧！");
             return 1;
        }
       
        if (me->query_skill("martial-cognize", 1) < 200)
        {
             command("say 閣下武學修養實在有限，這賞善罰惡令你還是不要為好！\n");
             return 1;
        }  
       
        if (present("shangfa ling", me))
        {
             command("heng");
             command("say 閣下也太貪心了吧！");
             return 1;
        }

        if (query("lingpai") < 1)
        {
             command("shake"); 
             command("say 我手頭上的賞善罰惡令已經全送出去了。");
             return 1;
        }
        command("nod");
        command("say 拿去吧，記得上俠客島喝臘八粥！");

        "/clone/lonely/shangfaling"->move(me);
        return 1;
}

void reset()
{
        set("lingpai", 3);
}
