// shi.c 石雙英

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("石雙英", ({ "shi shuangying", "shi","shuangying" }));
        set("title", HIR "紅花會"HIG"十二當家" NOR);
        set("nickname", HIG "鬼見愁" NOR);
        set("long", 
"鬼見愁石雙英在會中坐第十二把交椅，執掌刑堂，鐵面無私，心狠手
辣，犯了規條的就是逃到天涯海角，他也必派人抓來處刑，原來依據紅
花會規條，會中兄弟犯了大罪，若是一時胡塗，此後誠心悔悟，可在開
香堂執法之前，自行用尖刀在大腿上連戳三刀，這三刀須對穿而過，即
所謂“三刀六洞”，然後向該管舵主和執法香主求恕，有望從輕發落，
但若真正罪重出自不能饒恕。是以紅花會數萬兄弟，提到鬼見愁時無不
悚然。\n");
        set("gender", "男性");
        set("class", "scholar");
        set("age", 24);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("per", 26);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        
        set("max_qi", 1500);
        set("max_jing", 700);
        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 100);
        set("combat_exp", 200000);

        set_skill("force", 90);
        set_skill("dodge", 90);
        set_skill("unarmed", 90);
        set_skill("parry", 90);
        set_skill("sword", 90);
        set_skill("taiji-quan", 95);
        set_skill("taiji-shengong", 90);
        set_skill("taiji-jian", 90);
        set_skill("tiyunzong", 90);

        map_skill("dodge", "tiyunzong");
        map_skill("force", "taiji-shengong");
        map_skill("unarmed", "tianji-quan");
        map_skill("parry", "taiji-jian");
        map_skill("sword", "taiji-jian");

        set("env/wimpy", 20);
        create_family("太極門",8, "弟子");

         setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
}

