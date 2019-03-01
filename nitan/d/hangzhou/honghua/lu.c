// lu.c 陸菲青

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("陸菲青", ({ "lu feiqing", "lu","feiqing" }));
        set("long", 
"陸菲青，乃武當派大俠，壯年時在大江南北行俠仗義，端的名
震江湖，原是屠龍幫中一位響當當的人物。屠龍幫是反清的秘
幫，雍正年間聲勢十分浩大，後來雍正、乾隆兩朝厲行鎮壓，
到乾隆七八年時，屠龍幫終于落得瓦解冰消。陸菲青遠走邊疆。
當時清廷曾四下派人追拿，但他為人機警，兼之武功高強，得
脫大難，但清廷繼續嚴加查緝。陸菲青想到“大隱隱于朝、中
隱隱于市、小隱隱于野”之理，混到李可秀府中設帳教讀。\n");
        set("nickname", HIC"綿裡針"NOR);
        set("gender", "男性");
        set("class", "scholar");
        set("age", 62);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("per", 23);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        
        set("max_qi", 3000);
        set("max_jing", 1000);
        set("neili", 2000);
        set("max_neili", 2000);
        set("jiali", 100);
        set("combat_exp", 1000000);

        set_skill("literate", 100);
        set_skill("force", 200);
        set_skill("dodge", 200);
        set_skill("unarmed", 200);
        set_skill("parry", 200);
        set_skill("blade", 200);
        set_skill("sword", 200);
        set_skill("taiji-quan", 150);
        set_skill("taiji-shengong", 200);
        set_skill("taiji-dao", 200);
        set_skill("taiji-jian", 200);
        set_skill("liangyi-jian", 150);
        set_skill("tiyunzong", 200);

        map_skill("dodge", "tiyunzong");
        map_skill("force", "taiji-shengong");
        map_skill("unarmed", "taiji-quan");
        map_skill("blade", "taiji-dao");
        map_skill("parry", "taiji-jian");
        map_skill("sword", "liangyi-jian");
        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
                (: perform_action, "sword.ren" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }) );
        set("env/wimpy", 60);
        create_family("武當派", 17, "掌門");

         setup();
        carry_object("/d/wudang/obj/greyrobe")->wear();
        carry_object("/clone/weapon/changjian")->wield();
}
