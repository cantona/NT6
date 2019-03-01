// zhang.c

#include <ansi.h>

inherit NPC;

void create()
{
        set_name("張召重", ({ "zhang zhaozhong", "zhang", "zhaozhong"}) );
        set("title", "御林軍驍騎營佐領");
        set("nickname", HIR"火手判官"NOR);
        set("gender", "男性");
        set("age", 43);
        set("long",
"張召重人稱“火手判官”，身材魁梧，留一叢短鬍子。江湖盛
言“寧挨一槍，莫遇一張”就是指他了。他熱衷功名利祿，投
身朝廷，此人辦事賣力，這些年來更是青雲直上。\n");
        set("combat_exp", 750000);
        set("shen_type", -1);
        set("attitude", "heroism");
        set("max_neili", 2000);
        set("neili", 2000);
        set("max_jing", 1000);
        set("jing", 1000);
        set("max_qi", 2000);
        set("qi", 2000);
        set("per", 20);
        set("int", 30);
        set("con", 30);
        set("str", 30);
        set("dex", 30);

        set_skill("unarmed", 100);
        set_skill("sword", 100);
        set_skill("parry", 100);
        set_skill("dodge", 100);
        set_skill("force", 100);
        set_skill("taiji-shengong", 100);
        set_skill("taiji-jian", 100);
        set_skill("taiji-quan", 100);
        set_skill("tiyunzong", 100);
        map_skill("dodge", "tiyunzong");
        map_skill("force", "taiji-shengong");
        map_skill("sword", "taiji-jian");
        map_skill("unarmed", "taiji-quan");
        map_skill("parry", "taiji-jian");

        create_family("武當派", 13, "弟子");
        setup();

        carry_object(WEAPON_DIR"treasure/green_sword")->wield();
        carry_object("/d/city/obj/tiejia")->wear();

        add_money("silver", 30);
}
