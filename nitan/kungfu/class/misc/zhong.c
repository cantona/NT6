// zhong.c

#include <ansi.h>

inherit "/inherit/char/punisher";

void create()
{
        set_name("鐘志靈", ({ "pang toutuo", "pang" ,"toutuo"}));
        set("title", HIY "神龍教" NOR "左護法");
        set("nickname",HIR "遼東胖尊者" NOR);
        set("long", "這頭陀身材奇高，而且瘦得出奇；臉上皮包骨頭、雙\n"
                    "目深陷，當真便如僵屍一般。\n" );
        set("gender", "男性");
        set("age", 44);

        set("str", 32);
        set("int", 28);
        set("con", 31);
        set("dex", 25);

        set("max_qi", 47000);
        set("qi", 47000);
        set("max_jing", 24000);
        set("jing", 24000);
        set("neili", 58000); 
        set("max_neili", 58000);
        set("jiali", 120);
        set("score", 10000000);

        set("combat_exp", 50000000);
        set("shen_type", -1);
        set("attitude", "peaceful");

        set_skill("force", 2000);
        set_skill("hand", 2000);
        set_skill("strike", 2000);
        set_skill("staff", 2000);
        set_skill("parry", 2000);
        set_skill("dodge", 2000);
        set_skill("yixing-bufa", 2000);
        set_skill("shenlong-bashi", 2000);
        set_skill("huagu-mianzhang", 2000);
        set_skill("shenlong-xinfa", 2000);
        set_skill("shedao-qigong", 2000);

        map_skill("staff", "shedao-qigong");
        map_skill("force", "shenlong-xinfa");
        map_skill("hand", "shenlong-bashi");
        map_skill("strike", "huagu-mianzhang");
        map_skill("parry", "shedao-qigong");
        map_skill("dodge", "yixing-bufa");
        prepare_skill("hand", "shenlong-bashi");
        prepare_skill("strike", "huagu-mianzhang");

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "hand.xian" :),
                (: perform_action, "strike.hua" :),
                (: perform_action, "staff.fei" :),
                (: exert_function, "recover" :),
        }));

        create_family("神龍教", 0, "白龍使");

        setup();
        carry_object("/clone/misc/cloth")->wear();
        carry_object("/clone/weapon/gangzhang")->wield();
}
