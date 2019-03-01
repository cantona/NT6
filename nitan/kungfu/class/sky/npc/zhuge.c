#include <ansi.h>

inherit NPC;

void create()
{
        set_name("諸葛亮", ({ "zhuge liang", "zhuge", "liang"}));
        set("long", "    此人便是傳說中有通天徹底的三國時代蜀國\n"
                    "軍師諸葛亮，據說他上知天文，下通地理，無一\n"
                    "不精，無一不曉，真乃神人也。\n");

        set("nickname", HIG "智囊" NOR);
        set("title", HIY "蜀國軍師" NOR);
        set("gender", "男性");
        set("age", 30);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("str", 35);
        set("int", 99);
        set("con", 35);
        set("dex", 45);

        set("max_qi", 500000);
        set("max_jing", 500000);
        set("max_neili", 35000);
        set("neili", 35000);
        set("jiali", 500);
        set("combat_exp", 900000000);

        set_skill("dodge", 500);
        set_skill("parry", 500);
        set_skill("unarmed", 500);
        set_skill("bagua-shengong", 500);
        set_skill("force", 500);
        set_skill("martial-cognize", 500);
        set_skill("literate", 500);

        map_skill("force", "bagua-shengong");
        map_skill("dodge", "bagua-shengong");
        map_skill("parry", "bagua-shengong");
        map_skill("unarmed", "bagua-shengong");

        add_temp("apply/attack", 9000);

        setup();

        carry_object(__DIR__"obj/clothY")->wear();
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
                                 set("qi", 500000);
                                 set("jing", 500000);
                                 set("neili", 35000);
                                 set("eff_qi", 500000);
                                 set("max_jing", 50000);
                                 set("max_neili", 35000);
                             this_object()->clear_condition();

                                 return;
                         }

             this_object()->remove_enemy(ob);
             ob->remove_enemy(this_object());
             command("shake");
             if (ob->query("sky12/floor") == 9)
             {
                      ob->set("sky12/floor", 10);
                 command("say 閣下請便吧！");
             }
        }

        set("qi", 500000);
        set("jing", 500000);
        set("neili", 35000);
        set("eff_qi", 500000);
        set("max_jing", 50000);
        set("max_neili", 35000);

        this_object()->clear_condition();

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
