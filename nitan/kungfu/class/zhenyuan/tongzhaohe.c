// tongzhaohe 童兆和

#include <ansi.h>
#include "zhenyuan.h"

inherit NPC;
inherit F_MASTER;
inherit F_GUARDER;

void create()
{
        set_name("童兆和", ({ "tong zhaohe", "tong", "zhaohe"}));
          set("long", "此人相貌猥瑣，身材瘦削，一副有氣沒力的樣子。"
                    "是鎮遠鏢局裡赫赫有名的混混。\n");
        set("title", "鎮遠鏢局鏢師");
          set("gender", "男性");
          set("age", 35);
        set("class", "fighter");
        set("attitude", "peaceful");
        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 25);

        set("max_qi", 3000);
        set("max_jing", 3000);
        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 20);
        set("combat_exp", 150000);

          set_skill("parry", 60);
          set_skill("force", 60);
          set_skill("bagua-xinfa", 60);
          set_skill("dodge", 60);
          set_skill("bagua-bu", 60);
          set_skill("strike", 60);
          set_skill("bagua-zhang", 60);
          set_skill("cuff", 60);
          set_skill("bagua-quan", 60);
          set_skill("literate", 40);
          set_skill("blade", 60);
          set_skill("kuimang-dao", 60);
          set_skill("martial-cognize", 40);

        map_skill("blade", "kuimang-dao");
        map_skill("dodge", "bagua-bu");
        map_skill("force", "bagua-xinfa");
        map_skill("strike", "bagua-zhang");
        map_skill("cuff", "bagua-quan");
        map_skill("parry", "bagua-quan");

        prepare_skill("cuff", "bagua-quan");
        prepare_skill("strike", "bagua-zhang");

        set("coagents", ({
                ([ "startroom" : "/d/beijing/shufang",
                   "id"        : "wang weiyang" ]),
        }));

        set("guarder", ([
                "refuse_other": CYN "$N" CYN "對$n" CYN "皺眉道："
                                "喂！你這倒是往哪裡走啊？" NOR,
                "refuse_carry": CYN "$N" CYN "對$n" CYN "嬉皮笑臉"
                                "地道：你背上背的是個啥？扔下來給"
                                "咱瞧瞧。" NOR,
        ]));

          create_family("八卦門", 3, "弟子");
          setup();

        carry_object("/clone/weapon/gangdao")->wield();
          carry_object("/clone/misc/cloth")->wear();
}

void attempt_apprentice(object me)
{
        if (! permit_recruit(me))
                return;

        command("@@");
        command("say 居然有人拜我為師？念在你有心，我就收下你好了。");
        command("recruit "+query("id", me));
        if( query("class", me) != "fighter" )
                set("class", "fighter", me);
}
