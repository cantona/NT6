// shashou.c 殺手
#include <ansi.h>;
#include "init.h";
inherit NPC;

void create()
{
        mapping name;
        switch (random(3))
        {
                case 0:
                        name = NAMES_D->man_name();
                        set("gender", "男性");
                        break;
                case 1:
                        name = NAMES_D->woman_name();
                        set("gender", "女性");
                        break;
                default:
                        name = NAMES_D->jap_name();
                        set("gender", "男性");
                        break;
        }
        set_name(name["name"],({name["id"]}));
        set("title","一品堂殺手");
        set("long",
                "這是一位滿身黑衣的人，跟普通人完全沒什麼兩樣。\n");
        set("age", 20 + random(25) );
        set("attitude", "heroism");
        set("str", 20 + random(11));        // 膂力
        set("per", 20 + random(11));        // 容貌
        set("int", 20 + random(11));        // 悟性
        set("con", 20 + random(11));        // 根骨
        set("dex", 100 + random(11));         // 身法
        set("kar", 20 + random(11));        // 福緣
        set("shen", -10);
        set("demogorgon",1);
        set("no_suck",1);
        set( "max_qi", 1200 + random(400) );
        set( "max_jing", 300 + random(300) );
        set_temp("apply/attack", 40);
        set_temp("apply/defense", 40);
        set_temp("apply/damage", 60);
        set_temp("apply/armor", 40);
        set_temp("apply/dodge", 40);
        setup();
        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: perform_action, "sword.chan" :),
                (: perform_action, "sword.lian" :),
                (: perform_action, "sword.chan" :),
                (: perform_action, "parry.ren" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }) );
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
        add_money("silver", 20);
}
