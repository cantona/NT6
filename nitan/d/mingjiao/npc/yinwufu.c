// YinWuFu.c
// pal 1997.05.11

inherit NPC;
inherit F_UNIQUE;
#include <ansi.h>

void create()
{
        set_name("殷無福", ({ "yin wufu", "yin", "wufu", }));
        set("long",
        "他是一位老者，身穿一件白布長袍。\n"
        "他是白眉鷹王殷天正的僕從。一雙三角眼陰光四射，讓人膽寒。\n"
        );

        set("title", HIG "明教" HIB "天微堂" NOR "屬下");
        set("gender", "男性");
        set("attitude", "friendly");
        set("class", "fighter");

        set("age", 58);
        set("shen_type", 1);
        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 25);
        set("max_qi", 1000);
        set("max_jing", 1000);
        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 100);
        set("combat_exp", 100000);
        set("score", 5000);

        set_skill("force", 85);
        set_skill("hunyuan-yiqi", 85);
        set_skill("dodge", 85);
        set_skill("shaolin-shenfa", 85);
        set_skill("cuff", 95);
        set_skill("jingang-quan", 95);
        set_skill("parry", 85);
        set_skill("buddhism", 85);
        set_skill("literate", 85);

        map_skill("force", "hunyuan-yiqi");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("cuff", "jingang-quan");
        map_skill("parry", "jingang-quan");

        prepare_skill("cuff", "jingang-quan");

        create_family("明教", 4, "天微堂屬下");

        setup();

        carry_object("/d/mingjiao/obj/baipao")->wear();
}