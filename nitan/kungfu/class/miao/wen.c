#include <ansi.h>

inherit NPC;
inherit F_GUARDER;

void create()
{
        set_name("鍾兆文", ({ "zhong zhaowen", "zhong", "zhaowen", "wen" }));
        set("long", @LONG
這人是鍾氏三雄的老大鍾兆文。只見他身穿白
色粗麻布衣服，白帽白鞋，衣服邊上露著毛頭，
竟是剛死了父母的孝子服色，臉色慘白，鼻子
又扁又大，鼻孔朝天，留著灰白小胡子。
LONG );
        set("nickname", HIR "鍾氏三雄" NOR);
        set("title", "鄂北鍾氏兄弟");
        set("gender", "男性");
        set("age", 48);
        set("attitude", "peaceful");
        set("str", 23);
        set("int", 27);
        set("con", 25);
        set("dex", 24);

        set("qi", 4500);
        set("max_qi", 4500);
        set("jing", 3000);
        set("max_jing", 3000);
        set("neili", 3000);
        set("max_neili", 3000);
        set("jiali", 80);
        set("combat_exp", 800000);
        set("score", 3000);

        set_skill("force", 140);
        set_skill("mizong-neigong", 140);
        set_skill("dodge", 140);
        set_skill("feiyan-zoubi", 140);
        set_skill("parry", 140);
        set_skill("cuff", 140);
        set_skill("hujia-quan", 140);
        set_skill("staff", 140);
        set_skill("fengmo-zhang", 140);
        set_skill("literate", 100);
        set_skill("martial-cognize", 140);

        map_skill("force", "xueshan-neigong");
        map_skill("dodge", "feiyan-zoubi");
        map_skill("cuff", "hujia-quan");
        map_skill("staff", "fengmo-zhang");
        map_skill("parry", "fengmo-zhang");

        prepare_skill("cuff", "hujia-quan");

        set("coagents", ({
                ([ "startroom" : "/d/zhongzhou/miaojia_houting",
                   "id"        : "miao renfeng" ]),
        }));

        set("guarder", ([
                "refuse_other": CYN "$N" CYN "對$n" CYN "冷笑道："
                                "什麼人？居然連苗大俠的府邸都敢亂"
                                "闖！" NOR,
                "refuse_carry": CYN "$N" CYN "對$n" CYN "喝道：你"
                                "背上背負的是什麼人？還不快快給我"
                                "放下！" NOR,
        ]));

        create_family("中原苗家", 6, "助手");

        setup();

        carry_object("/clone/weapon/gangzhang")->wield();
        carry_object("/clone/misc/cloth")->wear();
        add_money("silver", 15);
}

void attempt_apprentice(object ob)
{
        command("hmm");
        command("say 走開，我不收徒。");
}
