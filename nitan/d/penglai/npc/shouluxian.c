// 
// Create By Rcwiz 09/2003

#include <ansi.h>

inherit NPC;

void create()
{
        set_name(HIY "守路仙人" NOR, ({ "shoulu xian", "shoulu", "xian" }));

        set("long", HIY "這是守護南山路口的仙人，要進入南山非得守路仙人的指引不可。\n" NOR);

        set("gender", "男性");
        set("age", 9999);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 100);
        set("int", 100);
        set("con", 100);
        set("dex", 100);

        set("max_qi", 200000);
        set("max_jing", 50000);
        set("max_neili", 30000);
        set("neili", 30000);
        set("jiali", 200);
        set("combat_exp", 90000000);

        set_skill("dodge", 550);
        set_skill("parry",550);
        set_skill("sword", 550);
        set_skill("yinyang-shiertian", 550);
        set_skill("force", 550);
        set_skill("martial-cognize", 550);
        set_skill("literate", 550);
        set_skill("medical", 2500);

        map_skill("force", "yinyang-shiertian");
        map_skill("dodge", "yinyang-shiertian");
        map_skill("parry", "yinyang-shiertian");
        map_skill("unarmed", "yinyang-shiertian");
        
        set("inquiry", ([
                "蓬萊仙島"               :   "這不是你該來的地方，我看你還是快走吧。\n",
                "南山入口"               :   "呵呵，如果你能給我一瓶青梅酒，我便指引你入口所在。\n",
                "青梅酒"                 :   "你不知道麼，這島上仙人都愛喝，不過釀製方法只有酒劍仙知道，哈哈　……",
        ]));
        
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
        }) );
        setup();

        carry_object("/kungfu/class/sky/npc/obj/xianpao")->wear();
}

void init()
{
        object me = this_player();
        
        if (objectp(present("penglai qingmeijiu", me)))
                command("say 好香~~，是誰的青梅酒快快拿出來讓本仙人品嚐品嚐。");
}

void unconcious()
{
        die();
}

int accept_object(object me, object obj)
{                        
        
        if (me->query("penglai/nanshan_quest/ok"))
        {
                command("hehe");
                return 0;
        }
        
        if (obj->query("id") == "penglai qingmeijiu" &&
            base_name(obj) == "/d/penglai/obj/qingmeijiu")
        {
                command("wa");
                message_vision(HIC "$N" HIC "接過" + obj->name() + HIC "，一口便喝了個精光 ……\n" NOR, this_object());
                command("haha");
                command("say 好，實在是好~~~~");
                command("say 既然你解了本仙人的酒癮，進入南山的方法我自然會教給你 ……");
                message_vision("\n$N" NOR "對着$n" NOR "竊竊私語，似乎在傳授什麼口訣。\n\n" NOR, this_object(), me);
                tell_object(me, HIG "守路仙人在你耳邊説道：#%&$#%@%&%$&#$%@#@$\n" NOR);
                command("say 你可記好了，這入山的方法就在這裏面。");
                me->set("penglai/nanshan_quest/ok", 1);
                destruct(obj);
                return 1;
        }
        else
        {
                command("say 本仙人只要青梅酒，其他什麼都不要。");
                return 0;
        }        

}