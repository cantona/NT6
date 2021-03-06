// wen.c 文泰來

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("文泰來", ({ "wen tailai", "wen","tailai" }));
        set("title", HIR "紅花會"HIG"四當家" NOR);
        set("nickname", HIW "奔雷手" NOR);
        set("long", "文泰來號稱“奔雷手”，十五歲起浪蕩江湖，手掌下不知擊斃
過多少神奸巨憝、兇徒惡霸。\n");
        set("gender", "男性");
        set("class", "fighter");
        set("age", 32);
        set("attitude", "friendly");
        set("shen_type", 1);
        set("per", 24);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        
        set("max_qi", 2000);
        set("max_jing", 1000);
        set("neili", 2000);
        set("max_neili", 2000);
        set("jiali", 100);
        set("combat_exp", 700000);

        set_skill("literate", 100);
        set_skill("force", 150);
        set_skill("dodge", 150);
        set_skill("parry", 150);
        set_skill("hand", 150);
        set_skill("claw", 150);
        set_skill("yunlong-shengong", 150);
        set_skill("yunlong-shenfa", 150);
        set_skill("yunlong-shou", 150);
        set_skill("yunlong-zhua", 150);

        map_skill("dodge", "yunlong-shenfa");
        map_skill("force", "yunlong-shengong");
        map_skill("hand", "yunlong-shou");
        map_skill("parry", "yunlong-shou");
        map_skill("claw", "yunlong-zhua");

        prepare_skill("hand","yunlong-shou");
        prepare_skill("claw","yunlong-zhua");
        set("env/wimpy", 20);

         setup();
        carry_object("/clone/misc/cloth")->wear();
}

