// Npc: /kungfu/class/shaolin/xuan-nan.c
// Date: YZC 96/01/19

inherit NPC;
inherit F_MASTER;

string ask_me();

#include "xuan-nan.h"

void create()
{
        set_name("玄難大師", ({
                "xuannan dashi",
                "xuannan",
                "dashi",
        }));
        set("long",
                "他是一位白須白眉的老僧，身穿一襲銀絲棕黃袈裟。他身材極瘦，\n"
                "兩手更象雞爪一樣。他雙目微閉，一副沒精打採的模樣。\n"
        );


        set("nickname", "般若堂首座");
        set("gender", "男性");
        set("attitude", "friendly");
        set("class", "bonze");

        set("age", 70);
        set("shen_type", 1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("max_qi", 2800);
        set("max_jing", 1000);
        set("neili", 3800);
        set("max_neili", 3800);
        set("jiali", 50);
        set("combat_exp", 1100000);

        set_skill("force", 125);
        set_skill("hunyuan-yiqi", 125);
        set_skill("shaolin-xinfa", 125);
        set_skill("dodge", 125);
        set_skill("shaolin-shenfa", 125);
        set_skill("parry", 125);
        set_skill("cuff", 125);
        set_skill("club", 125);
        set_skill("finger", 125);
        set_skill("strike", 125);
        set_skill("jingang-quan", 125);
        set_skill("wuchang-zhang", 125);
        set_skill("yizhi-chan", 125);
        set_skill("banruo-zhang", 125);
        set_skill("buddhism", 125);
        set_skill("literate", 125);
        set_skill("medical", 180);
        set_skill("shaolin-yishu", 180);

        map_skill("force", "hunyuan-yiqi");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("cuff", "jingang-quan");
        map_skill("finger", "yizhi-chan");
        map_skill("strike", "banruo-zhang");
        map_skill("club", "wuchang-zhang");
        map_skill("parry", "wuchang-zhang");

        prepare_skill("finger", "yizhi-chan");
        prepare_skill("strike", "banruo-zhang");

        create_family("少林派", 36, "弟子");

        set("inquiry", ([
                "十八羅漢陣"       : (: ask_me :),
                "羅漢大陣"           : (: ask_me :)
        ]));

        set("master_ob",4);
        setup();

        carry_object("/d/shaolin/obj/chanzhang")->wield();
        carry_object("/d/shaolin/obj/xuan-cloth")->wear();
}
