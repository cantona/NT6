#include <ansi.h>

inherit NPC;

void create()
{
        set_name("李尋歡", ({ "li xunhuan", "li", "xunhuan"}));
        set("long", "    一個身著白衫的中年男子，俊俏的面龐\n" 
                    "毫無血色，似乎因酒色過度而蒼白。他手中\n"
                    "握著一柄小刀，靜靜雕刻著一個木人。周圍\n"
                    "發生的一切他仿佛都看不見。\n"); 
        set("nickname", HIR "小李探花" NOR);
        set("title", HIY "大宗師" NOR);
        set("gender", "男性");
        set("age", 34);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 35);
        set("int", 35);
        set("con", 35);
        set("dex", 35);

        set("max_qi", 30000);
        set("max_jing", 30000);
        set("max_neili", 35000);
        set("neili", 35000);
        set("jiali", 250);
        set("combat_exp", 900000000);

        set("chat_chance", 1);
        set("chat_msg",({
                CYN "李尋歡深深的嘆了口氣。\n" NOR,
                CYN "李尋歡靜靜地雕刻著手中的木偶。\n" NOR,
                CYN "李尋歡咳嗽了幾聲。\n" NOR,
                CYN "李尋歡：“咳…咳…”\n" NOR,
        }));

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "throwing.fei" :),
                (: perform_action, "dodge.guiyuan" :),
                (: perform_action, "dodge.guiyuan" :),
                (: perform_action, "dodge.guiyuan" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),                
                (: exert_function, "heal" :),
                (: exert_function, "dispel" :),
                (: exert_function, "regenerate" :),             
        }) );

        set_skill("dodge", 350);
        set_skill("parry", 350);
        set_skill("unarmed", 350);
        set_skill("throwing", 350);
        set_skill("xiaoli-feidao", 350);
        set_skill("changquan", 350);
        set_skill("shexing-lifan", 350);
        set_skill("force", 350);
        set_skill("yijinjing", 350);
        set_skill("literate", 250);
        set_skill("martial-cognize", 400);

        map_skill("force", "yijinjing");
        map_skill("dodge", "shexing-lifan");
        map_skill("parry", "changquan");
        map_skill("throwing", "xiaoli-feidao");
        map_skill("unarmed", "changquan");

        set_temp("apply/damage", 800);
        set_temp("apply/armor", 1200);
                set_temp("apply/attack", 1000);
        set_temp("apply/dodge", 800);
                set_temp("apply/parry", 600);

        setup();

        carry_object(__DIR__"obj/cloth1")->wear();
        carry_object(__DIR__"obj/renou");
        //carry_object("/kungfu/class/sky/obj/tianxiadan");
        set_temp("handing", carry_object(__DIR__"obj/feidao"));
        add_money("gold", 20);
}

void unconcious()
{
        die();
}

void die()
{
        object ob;

        ob = query_last_damage_from();

        if (objectp(ob) && ob->is_fighting(this_object()))
        {
                         if (arrayp(ob->query_team()))
                         {
                                 command("heng");
                                 command("say 勝之不武！");
                                 set("qi", 30000);
                                 set("jing", 30000);
                                 set("neili", 35000);
                                 set("eff_qi", 30000);
                         set("max_jing", 30000);
                 set("max_neili", 35000);
                             this_object()->clear_condition();

                                 return;
                         }

             this_object()->remove_enemy(ob);
             ob->remove_enemy(this_object());

             if (! ob->query("sky12/floor"))
             {
                      ob->set("sky12/floor", 1);
                 command("say 好了，過了我這關，你可以進入天界了！");
             }
        }

        set("qi", 30000);
        set("jing", 30000);
        set("neili", 35000);
        set("eff_qi", 30000);
        set("max_jing", 30000);
        set("max_neili", 35000);

        this_object()->clear_condition();

                if (! query_temp("handing") && random(5) == 1)                
                        set_temp("handing", carry_object(__DIR__"obj/feidao"));

        return;
}


// 氣血小于1000則死亡，避免他人協助幫忙轉世
void heart_beat()
{
        if (this_object()->query("qi") < 1000 || this_object()->query("eff_qi") < 1000)
        {
                die();
        }
        ::heart_beat(); 
        keep_heart_beat(); 
}
