// dongfang.c

#include <ansi.h>

inherit NPC;
inherit F_MASTER;

void create()
{
    set_name("東方不敗", ({"dongfang bubai", "dongfang", "bubai"}));
    set("nickname", HIY "天下無敵" NOR);
    set("title", HIM "日月神教教主" NOR);
    set("gender", "男性");
    set("shen_type", -1);
    set("age", 42);
    set("long",
        "他就是日月神教教主。號稱無人可敵，因此有一稱號為「東方不敗」。\n");
    set("attitude", "peaceful");

    set("per", 21);
    set("str", 21);
    set("int", 30);
    set("con", 26);
    set("dex", 30);

    set("chat_chance", 1);
    set("chat_msg", ({
          "東方不敗嘆了口氣道：“唉 …… 我的楊大哥....他怎麼還不回來,我好\n"
         "掛念他 ……東方不敗眼中流露無限迷茫。\n",
    }));
    set("inquiry", ([
        "楊蓮亭"   : "你敢直稱我愛人的名字,想找死呀？ \n",
        "葵花寶典" : "如果你能幫我取得葵花寶典上冊，我一定重重謝你。\n",
    ]));

    set("qi", 4000);
    set("max_qi", 4000);
    set("jing", 1000);
    set("max_jing", 1000);
    set("neili", 4500);
    set("max_neili", 4500);
    set("jiali", 400);

    set("combat_exp", 2500000);
    set("score", 0);

    set_skill("force", 290);             // 基本內功
    set_skill("finger", 290);            // 基本指法
    set_skill("unarmed", 290);           // 基本拳腳
    set_skill("dodge", 300);             // 基本躲閃
    set_skill("parry", 290);             // 基本招架
    set_skill("sword", 290);             // 基本劍法
    set_skill("pixie-jian", 300);        // 辟邪劍法
    set_skill("changquan", 280);         // 太祖長拳
    set_skill("literate", 120);          // 讀書識字
    set_skill("kuihua-xinfa", 290);      // 葵花心法

    map_skill("force", "kuihua-xinfa");
    map_skill("sword", "pixie-jian");
    map_skill("unarmed", "changquan");
    map_skill("dodge", "pixie-jian");
    map_skill("parry", "pixie-jian");

    create_family("日月神教", 2, "教主");

    setup();
    carry_object("/d/fuzhou/obj/xiuhua")->wield();
    carry_object("/d/wanjiegu/npc/obj/qi-dress")->wear();
    carry_object("/d/heimuya/obj/yuxiao");
}
