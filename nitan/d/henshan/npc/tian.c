#include <ansi.h>
inherit NPC;
void greeting(object ob);
int accept_fight(object ob);
void create()
{
        seteuid(getuid());
        set_name("田伯光", ({ "tian boguang", "tian","boguang" }));
        set("long", "他一身飄逸的白色長衫，風流儒雅。\n");
        set("nickname", HIM "萬里獨行" NOR);
        set("gender", "男性");
        set("age", 37);
        set("attitude", "friendly");
        set("shen_type", -1);

       set("per", 23);
        set("str", 25);
        set("int", 24);
        set("con", 25);
        set("dex", 26);

        set("qi", 1000);
        set("max_qi", 1000);        
        set("combat_exp", 800000);
        set("score", 40000);

        set_skill("blade", 100);
        set_skill("dodge", 150);
        set("jing", 800);
        set("max_jing", 800);
        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 100);

        set_skill("blade",150);
        set_skill("parry", 120);
        set_skill("force", 120);
        set_skill("lingxu-bu", 150);
        set_skill("kuangfeng-blade", 150);

        map_skill("dodge", "lingxu-bu");
        map_skill("parry", "kuangfeng-blade");
        map_skill("blade", "kuangfeng-blade");

        set("chat_msg_combat", ({
                (: perform_action, "blade.kuang" :),
        }) );
        set("chat_chance", 10);
        set("chat_msg", ({
                CYN "田伯光笑道：尼姑也沒關係嘛，蓄起頭髮，兩個月就是小美人了。\n" NOR,
        }) );

        setup();
        carry_object("/d/baituo/obj/baipao")->wear();
        carry_object("/clone/weapon/gangdao")->wield();
        add_money("silver",40);
}

void init()
{
        object ob;

        ::init();

        if( interactive(ob = this_player()) && !is_fighting() ) 
       {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
}
void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        if( query("gender", ob) == "女性" )
        {
        if( query("age", ob)<26 )
                say(CYN "田伯光笑道：妙極，妙極，又來了一個小姑娘。\n" NOR);     
        else 
                say(CYN "田伯光笑道：妙極，妙極，可惜太老了點，我可沒胃口。\n" NOR);     
        }
        else 
                say(CYN "田伯光笑着招招手：這位"+RANK_D->query_respect(ob) + "來喝"
                    "兩杯，這個小尼姑嘛，反正也沒什麼事，就讓她坐着就是。\n" NOR);
        return;
}

int accept_fight(object ob)
{
        if( query("gender", ob) == "女性" )
        {
                write(CYN "田伯光笑道：花姑娘？殺了太可惜了的。\n" NOR);
                return 0;
        }
        return 1;
}
 