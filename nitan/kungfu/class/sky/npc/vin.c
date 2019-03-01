#include <ansi.h>

inherit NPC;

mixed give_quest();

void create()
{
        set_name(HIY "軒轅行" NOR, ({ "vin" }));
        set("long", HIY "    此人身穿炎黃聖袍，氣宇軒昂，相貌不凡，乃「炎黃英雄史」開山祖師。\n" NOR);

        set("gender", "男性");
        set("age", 22);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 100);
        set("int", 100);
        set("con", 100);
        set("dex", 100);

        set("max_qi", 2000000);
        set("max_jing", 500000);
        set("max_neili", 300000);
        set("neili", 300000);
        set("jiali", 2000);
        set("combat_exp", 990000000);

        set_skill("dodge", 550);
        set_skill("parry",550);
        set_skill("unarmed", 550);
        set_skill("yinyang-shiertian", 550);
        set_skill("force", 550);
        set_skill("martial-cognize", 550);
        set_skill("literate", 550);

        map_skill("force", "yinyang-shiertian");
        map_skill("dodge", "yinyang-shiertian");
        map_skill("parry", "yinyang-shiertian");
        map_skill("unarmed", "yinyang-shiertian");
        
        set("inquiry", ([
                "軒轅行"     : "軒轅行也是你叫的嗎？放肆！",
                "望天涯"     : "他是炎黃英雄史的天神！",
                "周風"       : "他是炎黃英雄史服務器管理人員！",
                "心願"       : (: give_quest :),
                "上古神器"   :  "那是上古失落的神器，你有嗎？",
                "神器"       : "那是上古失落的神器，你有嗎？",
                "轉世"       : "要轉世先過我這關！",
                "炎黃英雄史"  : "呵呵，這個也用問？",
        ]));
        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
        }) );
        setup();

        carry_object(__DIR__"obj/yanhuangpao")->wear();
}

mixed give_quest()
{
        object me = this_player();
        string obj;
        
        if (me->query("sky12/floor") != 12)
        {
                command("say 哼，無恥狂徒，你是怎麼到這裡來的，滾回地上去吧！");
                me->move("/d/city/wumiao");
                me->unconcious();
                return "哼！\n";
        }

        if (stringp(me->query("sky12/quest/obj")))
             return "我不是讓你幫我尋找" + me->query("sky12/quest/obj") + 
                    "了嗎，在哪兒呢？\n";
        
        // 尋找一件上古神器     
        obj = ULTRA_QUEST_D->get_random_magic_item();
        
        command("smile");
        message_sort(HIW "\n$N" HIW "對$n" HIW "說道：多年前我遺失一件上古神"
                     "器，名曰：" + HIR + obj + HIW "，如果你能幫我把它找回來"
                     "給我，我便不再阻攔你！\n" NOR, this_object(), me);
        
        me->set("sky12/quest/obj", obj);
        
  return 1;
}

int accept_object(object me, object ob)
{        
        string obj;
        
        if (! me->query("sky12/quest/obj"))
             return 0;

        obj = filter_color(ob->name());
        
        if (me->query("sky12/quest/obj") == obj)
        {
                if (ob->is_item_make() ||
                    ! ob->is_magic_item())
                {
                        command("heng");
                        command("say 想拿這個來蒙我，找死！");
                        me->unconcious();
                        return 1;
                }
                command("smile");
                if (me->query("sky12/floor") == 12)
                {
                          me->set("sky12/floor", 13);
                     command("say 很好，很好，閣下可以請便了！");
                }                

                destruct(ob);
                
                me->delete("sky12/quest");

                return 1;
        }
        else return 0;
                   
}

void unconcious()
{
        die();
}
