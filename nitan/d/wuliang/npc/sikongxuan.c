// sikongxuan.c
// Date: Oct.18 1999 by Winder
#include <ansi.h>;
inherit NPC;

void create()
{
        set_name("司空玄", ({ "sikong xuan", "sikong", "xuan" }));
        set("title", HIY"神農幫幫主"NOR);
        set("age", 52);
        set("gender", "男性");
        set("long", "這是一個瘦小的老者，高出旁人，頦下一把山羊鬍子，神態
甚是倨傲，原來他就是區區神農幫的幫主。\n");
        set("attitude", "peaceful");

        set("shen_type", -1);
        set("str", 24);
        set("per", 20);
        set("dex", 16);
        set("neili", 1000);
        set("max_neili", 1000);
        set("combat_exp", 150000);
        set("shen_type", -1);
        set_temp("apply/armor", 60);

        set_skill("dodge", 80);
        set_skill("parry", 80);
        set_skill("force", 80);
        set_skill("strike", 80);
        set_skill("chousui-zhang", 80);
        set_skill("claw", 80);
        set_skill("sanyin-wugongzhao", 80);
        map_skill("dodge", "zhaixinggong");
        map_skill("strike", "chousui-zhang");
        map_skill("claw", "sanyin-wugongzhao");
        map_skill("parry", "chousui-zhang");
        prepare_skill("strike", "chousui-zhang");
        prepare_skill("claw", "sanyin-wugongzhao");

        setup();
        carry_object("/d/xingxiu/npc/obj/yaochu")->wield();
        carry_object("/clone/cloth/cloth")->wear();
}
