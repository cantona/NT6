#include <ansi.h>
#include "honghua.h"

inherit NPC;
inherit F_MASTER;

void create()
{
        set_name("石雙英", ({ "shi shuangying", "shi", "shuangying" }));
        set("title", "紅花會十二當家");
        set("nickname", HIR "鬼見愁" NOR);
        set("long", "鬼見愁石雙英在會中坐第十二把交椅，執掌刑\n"
                    "堂，鐵面無私，心狠手辣，犯了規條的就是逃\n"
                    "到天涯海角，他也必派人抓來處刑，原來依據\n"
                    "紅花會規條，會中兄弟犯了大罪，若是一時胡\n"
                    "塗，此後誠心悔悟，可在開香堂執法之前，自\n"
                    "行用尖刀在大腿上連戳三刀，這三刀須對穿而\n"
                    "過，即所謂“三刀六洞”，然後向該管舵主和\n"
                    "執法香主求恕，有望從輕發落，但若真正罪重\n"
                    "出自不能饒恕。是以紅花會數萬兄弟，提到鬼\n"
                    "見愁時無不悚然。\n");
        set("gender", "男性");
        set("age", 28);
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("per", 21);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("qi", 3500);
        set("max_qi", 3500);
        set("jing", 2500);
        set("max_jing", 2500);
        set("neili", 1500);
        set("max_neili", 1500);
        set("jiali", 50);
        set("combat_exp", 500000);
        set("score", 10000);

        set_skill("force", 100);
        set_skill("honghua-xinfa", 100);
        set_skill("unarmed", 100);
        set_skill("changquan", 100);
        set_skill("dodge", 100);
        set_skill("yanzi-chuanyun", 100);
        set_skill("staff", 120);
        set_skill("fengmo-zhang", 120);
        set_skill("parry", 100);
        set_skill("martial-cognize", 60);
        set_skill("literate", 100);

        map_skill("force"  , "honghua-xinfa");
        map_skill("staff"  , "fengmo-zhang");
        map_skill("unarmed" , "changquan");
        map_skill("dodge"  , "yanzi-chuanyun");
        map_skill("parry"  , "fengmo-zhang");

        prepare_skill("unarmed", "changquan");

        create_family("紅花會", 4, "當家");

        set("chat_chance_combat", 100);
        set("chat_msg_combat", ({
                (: perform_action, "staff.lun" :),
                (: exert_function, "powerup" :),
                (: exert_function, "recover" :),
        }) );
        setup();

        carry_object("/clone/misc/cloth")->wear();
}

void attempt_apprentice(object ob)
{
        command("hmm");
        command("say 你不收徒，你找其餘當家的吧。");
}
