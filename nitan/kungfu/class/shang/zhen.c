#include <ansi.h>
#include "shang.h"

inherit NPC;
inherit F_GUARDER;

void create()
{
        set_name("商寶震", ({"shang baozhen", "shang", "baozhen"}));
        set("gender", "男性");
        set("title", "商家堡少主");
        set("age", 17);
        set("long", @LONG
這便是商家堡的少主商寶震，只見他衣著華麗，
宛然一副富家公子的模樣。
LONG);
        set("attitude", "peaceful");
        set("shen_type", -1);
        set("str", 25);
        set("int", 20);
        set("con", 20);
        set("dex", 20);

        set("qi", 4000);
        set("max_qi", 4000);
        set("jing", 3000);
        set("max_jing", 3000);
        set("neili", 2000);
        set("max_neili", 2000);
        set("jiali", 120);
        set("combat_exp", 500000);
        set("score", 10000);

        set_skill("force", 120);
        set_skill("shangjia-neigong", 120);
        set_skill("parry", 100);
        set_skill("wai-bagua", 100);
        set_skill("dodge", 100);
        set_skill("bagua-bu", 100);
        set_skill("unarmed", 100);
        set_skill("tan-tui", 100);
        set_skill("strike", 100);
        set_skill("bagua-zhang", 100);
        set_skill("cuff", 100);
        set_skill("bagua-quan", 100);
        set_skill("blade", 120);
        set_skill("bagua-dao", 120);
        set_skill("shangjia-dao", 120);
        set_skill("throwing", 100);
        set_skill("jinbiao-jue", 100);
        set_skill("literate", 100);
        set_skill("martial-cognize", 80);

        map_skill("unarmed", "tan-tui");
        map_skill("dodge", "bagua-bu");
        map_skill("force", "shangjia-neigong");
        map_skill("strike", "bagua-zhang");
        map_skill("sword", "quemen-jian");
        map_skill("blade", "bagua-dao");
        map_skill("cuff", "bagua-quan");
        map_skill("parry", "wai-bagua");
        map_skill("throwing", "jinbiao-jue");

        prepare_skill("cuff", "bagua-quan");
        prepare_skill("strike", "bagua-zhang");

        set("class", "fighter");

        set("coagents", ({
                ([ "startroom" : "/d/shaolin/shang_dating",
                   "id"        : "shang jianming" ]),
        }));

        set("guarder", ([
                "refuse_other": CYN "$N" CYN "對$n" CYN "冷喝道："
                                "你給我站住！我們商家堡豈是由得外"
                                "人隨便走動地方？" NOR,
                "refuse_carry": CYN "$N" CYN "對$n" CYN "喝道：你"
                                "背上背的是什麼人？給我放下來！" NOR,
        ]));

        create_family("商家堡", 4, "少主");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "blade.mang" :),
                (: perform_action, "strike.ding" :),
                (: perform_action, "cuff.gua" :),
                (: perform_action, "parry.zhen" :),
                (: perform_action, "throwing.huan" :),
                (: exert_function, "recover" :),
        }) );
        setup();

        carry_object("/clone/weapon/gangdao")->wield();
        carry_object("/clone/misc/cloth")->wear();
        set_temp("handing", carry_object("/d/beijing/npc/obj/jinbiao"));
}

void attempt_apprentice(object ob)
{
        command("shake");
        command("say 你去找我爹爹或是娘親好了，我自己的武功都沒練好呢。");
}
