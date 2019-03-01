// yuzhenzi.c

#include <ansi.h>

inherit NPC;
inherit F_UNIQUE;

void create()
{
        set_name("玉真子", ({ "yuzhen zi", "yuzhen" }));
        set("gender", "男性");
        set("title", "鐵劍門掌門人");
        set("nickname", HIC"護國真人"NOR);
        set("age", 44);
        set("long", "這是一位頗有仙風道骨的瀟洒全真，手握長劍，目視前方。\n");

        set("str", 25);
        set("int", 27);
        set("con", 23);
        set("dex", 28);

        set("qi", 3000);
        set("max_qi", 3000);
        set("jing", 1500);
        set("max_jing", 1500);
        set("neili", 3500); 
        set("max_neili", 3500);
        set("jiali", 60);
        set("combat_exp", 600000);
        set("shen_type", -1);
        set("attitude", "peaceful");

        set_skill("sword", 150);
        set_skill("force", 150);
        set_skill("mizong-neigong", 150);
        set_skill("unarmed", 150);
        set_skill("dodge", 150);
        set_skill("parry", 150);
        set_skill("huashan-sword", 150);
        set_skill("shenxing-baibian", 150);
        map_skill("whip",  "huashan-sword");
        map_skill("parry", "huashan-sword");
        map_skill("dodge", "shenxing-baibian");

        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver", 1);
}
