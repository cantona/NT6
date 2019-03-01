#include <ansi.h>
#include "zhenyuan.h"

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("戴永明", ({ "dai yongming","dai", "yongming"}));
          set("long", "鎮遠鏢局的鏢師中以他為首，也以他武功最\n"
                    "高，根基最好。他身形修長，相貌端正，白\n"
                    "衣飄飄，氣度不凡。雖然已四十多歲，但依\n"
                    "然形象瀟洒。\n");
        set("title", "鎮遠鏢局鏢師");
          set("gender", "男性");
          set("age", 35);
        set("class", "fighter");
        set("attitude", "peaceful");
        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 25);

        set("max_qi", 2000);
        set("max_jing", 2000);
        set("neili", 2000);
        set("max_neili", 2000);
        set("jiali", 40);
        set("combat_exp", 200000);

          set_skill("parry", 80);
          set_skill("force", 80);
          set_skill("bagua-xinfa", 80);
          set_skill("dodge", 80);
          set_skill("bagua-bu", 80);
          set_skill("strike", 80);
          set_skill("bagua-zhang", 80);
          set_skill("cuff", 80);
          set_skill("bagua-quan", 80);
          set_skill("literate", 50);
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

          create_family("八卦門", 3, "弟子");
          setup();

          carry_object("/clone/misc/cloth")->wear();
}

void attempt_apprentice(object me)
{
        if (! permit_recruit(me))
                return;

        command("en");
        command("say 既然這樣，那你就留下吧。");
        command("recruit "+query("id", me));
        if( query("class", me) != "fighter" )
                set("class", "fighter", me);
}
