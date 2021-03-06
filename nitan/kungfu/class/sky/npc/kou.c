#include <ansi.h>

inherit NPC;

void create()
{
        set_name("寇仲", ({ "kou zhong", "kou", "zhong"}));
        set("long", "一個身着龍袍的魁梧少年，他就是少帥軍的統帥寇仲。\n"); 
        set("nickname", HIR "大唐雙龍" NOR);
        set("title", HIY "大宗師" NOR);
        set("gender", "男性");
        set("age", 27);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 35);
        set("int", 35);
        set("con", 35);
        set("dex", 35);
        set("per", 35);

        set("max_qi", 320000);
        set("max_jing", 220000);
        set("max_neili", 35000);
        set("neili", 35000);
        set("jiali", 250);
        set("combat_exp", 900000000);

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "blade.bafa" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
                (: exert_function, "recover" :),                
                (: exert_function, "heal" :),
                (: exert_function, "dispel" :),
                (: exert_function, "regenerate" :),               
        }) );

        set_skill("dodge", 620);
        set_skill("parry", 620);
        set_skill("hand", 640);
        set_skill("unarmed", 640);
        set_skill("shou-yin", 640);
        set_skill("wudu-shu", 620);
        set_skill("force", 600);
        set_skill("changsheng-jue", 600);
        set_skill("blade", 620);
        set_skill("jingzhong-bafa", 620);
        set_skill("literate", 600);
        set_skill("martial-cognize", 600);

        map_skill("force", "changsheng-jue");
        map_skill("blade", "jingzhong-bafa");
        map_skill("dodge", "wudu-shu");
        map_skill("parry", "jingzhong-bafa");
        map_skill("hand", "shou-yin");
        map_skill("unarmed", "shou-yin");

        prepare_skill("hand", "shou-yin");

        set_temp("apply/damage", 800);
        set_temp("apply/armor", 1200);
                set_temp("apply/attack", 1000);
        set_temp("apply/dodge", 800);
                set_temp("apply/parry", 600);

        setup();

        carry_object(__DIR__"obj/cloth2")->wear();
        carry_object(__DIR__"obj/jingzhongyue")->wield();
        //carry_object("/kungfu/class/sky/obj/heshibi");
        //carry_object("/kungfu/class/sky/obj/jue");
}

void kill_ob (object ob)
{
        object me = this_object();
        object where = environment (me);
        object guard = present ("xu ziling", where);

        set_temp("my_killer", ob);
        ::kill_ob(ob);
        if (guard && !guard->is_fighting())
         {
                 message_vision (CYN "$N淡笑：我們兩兄弟奉命在此守侯，閣下休怪我們無情！\n" NOR, guard);
                 guard->kill_ob(ob);
         }
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
                                 set("qi", 320000);
                                 set("jing", 120000);
                                 set("neili", 35000);
                                 set("eff_qi", 320000);
                                 set("max_jing", 120000);
                                 set("max_neili", 35000);
                             this_object()->clear_condition();

                                 return;
                         }

             this_object()->remove_enemy(ob);
             ob->remove_enemy(this_object());
             command("shake");
             if (ob->query("sky12/floor") == 4)
             {
                      ob->set("sky12/floor", 5);
                 command("say 閣下請便吧！");
             }
        }

        set("qi", 320000);
        set("jing", 120000);
        set("neili", 35000);
        set("eff_qi", 320000);
        set("max_jing", 120000);
        set("max_neili", 35000);

        this_object()->clear_condition();

        return;
}


// 氣血小於1000則死亡，避免他人協助幫忙轉世
void heart_beat()
{
        if (this_object()->query("qi") < 1000 || this_object()->query("eff_qi") < 1000)
        {
                die();
        }
        ::heart_beat(); 
        keep_heart_beat(); 
}
