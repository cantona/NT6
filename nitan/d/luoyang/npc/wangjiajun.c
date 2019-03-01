// wangjiajun.c

#include <ansi.h>

inherit NPC;
void create()
{
        set_name("王家俊", ({ "wang jiajun", "wang", "jiajun" }) );
        set("title", HIY"金刀門"NOR"第五代弟子");
        set("gender", "男性" );
        set("shen_type", 1);
        set("age", 16);
        set("per", 15);
        set("str", 25);
        set("con", 25);
        set("dex", 25);
        set("int", 25);
        set("long",
"他是王仲強的大兒子，武功不過爾爾。不過在洛陽城中，教訓起地痞流氓
來，那倒是夠了。\n" );
        set("combat_exp", 60000);
        set("attitude", "friendly");
        set_skill("blade", 30);
        set_skill("dodge", 30);
        set_skill("unarmed", 30);
        set_skill("jinwu-blade", 30);
        set_skill("yanfly", 30);
        set_skill("parry", 30);
        map_skill("blade", "jinwu-blade");
        map_skill("parry", "jinwu-blade");
        map_skill("dodge", "yanfly");

        setup();
        carry_object(WEAPON_DIR"gangdao")->wield();
        carry_object(CLOTH_DIR"jinduan")->wear();
        add_money("gold", 2);
}
