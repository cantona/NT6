// hua.c 花劍影

#include <ansi.h>
inherit NPC;

void create()
{
        set_name("花劍影", ({ "hua  jianying"}));
        set("nickname", "流星趕月");
        set("long","他有著一個好聽的名字，中等身材，白凈臉皮，若不是一副牙齒向外突了一寸，一個鼻頭低陷了半寸，倒算是一位相貌英俊的人物，可惜功夫平平，還時常打劫一些路客。\n");
        set("gender", "男性");
        set("age", random(10) + 25);
        set("attitude", "peaceful");
        set("str", 25);
        set("int", 20);
        set("con", 25);
        set("dex", 27);
        set("max_qi", 1500);
        set("max_jing", 800);
        set("neili", 700);
        set("max_neili", 700);
        set("jiali", 50);
        set("combat_exp", 400000 + random(40000));
        set("chat_chance_combat", 60);
        set("chat_msg_combat", ({
               (: exert_function, "powerup" :),
               (: exert_function, "regenerate" :),
               (: exert_function, "recover" :),
        }));

        set_skill("force", 60);
        set_skill("dodge", 100 + random(50));
        set_skill("tie-zhang", 150 + random(50));
        set_skill("shuishangpiao",150 + random(50));
        set_skill("strike", 100 + random(50));
        set_skill("unarmed", 100 + random(50));
        set_skill("parry", 100 + random(50));
        set_skill("literate", 20);
        set_skill("sword",100 + random(50));
        set_skill("changge-jian",150 + random(50));
        map_skill("sword","changge-jian");
        map_skill("strike","tie-zhang");
        map_skill("parry","tie-zhang");
        map_skill("dodge","shuishangpiao");


        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/changjian")->wield();
          add_money("silver", 50);
}
#include "npc.h"
