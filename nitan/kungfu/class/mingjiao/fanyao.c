// This program is a part of NT MudLIB

#include "ansi.h"

inherit NPC;
inherit F_COAGENT;
inherit F_GUARDER;

string ask_me();
string ask_me1();

void create()
{
        set_name("范遙", ({ "fan yao", "fan", "yao" }));
        set("long",
                "他是一位帶發修行的頭陀，身穿白布長袍。\n"
                "他的臉上七七八八的全是傷疤，簡直看不出本來面目了。\n"
        );

        set("title",HIG "明教" HIR "光明右使" NOR);
        set("level",11);
        set("gender", "男性");
        set("attitude", "peaceful");
        set("class", "bonze");

        set("age", 38);
        set("shen_type", 1);
        set("per", 12);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("max_qi", 3500);
        set("max_jing", 1500);
        set("neili", 3000);
        set("max_neili", 3000);
        set("jiali", 150);
        set("combat_exp", 1000000);
        set("score", 800000);

        set_skill("force", 220);
        set_skill("dodge", 220);
        set_skill("parry", 220);
        set_skill("sword", 220);
        set_skill("cuff", 220);
        set_skill("hand", 220);
        set_skill("claw", 220);
        set_skill("strike", 220);
        set_skill("literate", 150);

        set_skill("shenghuo-xinfa", 220);
        set_skill("lingxu-bu", 220);
        set_skill("shenghuo-quan", 220);
        set_skill("guangming-zhang", 220);
        set_skill("liehuo-jian", 220);
        set_skill("nianhua-zhi", 220);
        set_skill("sanhua-zhang", 220);
        set_skill("fengyun-shou", 220);
        set_skill("longzhua-gong", 220);
        set_skill("buddhism", 340);
        set_skill("martial-cognize", 220);

        map_skill("force", "shenghuo-xinfa");
        map_skill("dodge", "lingxu-bu");
        map_skill("strike", "guangming-zhang");
        map_skill("sword", "liehuo-jian");
        map_skill("parry", "liehuo-jian");
        map_skill("cuff", "shenghuo-quan");

        prepare_skill("cuff", "shenghuo-quan");
        prepare_skill("strike", "guangming-zhang");

        set("inquiry", ([
                "光明聖火陣"  : (: ask_me :),
                "明教聖火陣"  : (: ask_me :),
                "聖火陣"      : (: ask_me :),
                "黑玉斷續膏"  : (: ask_me1 :),
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: prepare_skill("finger", "nianhua-zhi") :),
                (: prepare_skill("strike", "sanhua-zhang") :),
        }) );
        set("inherit_title",HIG"明教"HIC"護教法王"NOR);
        create_family("明教", 34, "光明右使");

        set("master_ob",4);

        set("coagents", ({
                ([ "startroom" : "/d/mingjiao/dadian",
                   "id"        : "zhang wuji" ]),
        }));

        set_temp("apply/attack", 150);
        set_temp("apply/damage", 150);
        set_temp("apply/unarmed_damage", 150);
        set_temp("apply/armor", 150);
        set("heiyu", 1);
        setup();

        carry_object("/d/mingjiao/obj/baipao")->wear();
}

string ask_me1()
{
        mapping fam;
        object ob, *clone;
        int i, j;

        if( !(fam=query("family", this_player())) || fam["family_name"] != "明教" )
                return RANK_D->query_respect(this_player())+"與本派素無來往，不知此話從何談起？";

        if (this_player()->query_skill("shenghuo-shengong", 1) < 50)
                return "你在明教的時日尚短，這黑玉斷續膏你還不夠資格使用。\n";

        if( query_temp("marks/膏1", this_player()) )
                return "你不是剛拿了黑玉斷續膏了嗎，怎麼還要？";

        if (present("heiyu duanxugao", this_player()))
                return "你身上不是帶著黑玉斷續膏嗎，怎麼還要？";

        if( query("eff_qi", this_player()) == query("max_qi", this_player()) )
                return "你現在不需要用黑玉斷續膏。";

        if( query("heiyu", this_object())<1 )
                return "你來晚了，黑玉斷續膏已給全部發出去了。";

        ob = new("/d/mingjiao/obj/heiyu");
        ob->move(this_player());
        set_temp("marks/膏1", 1, this_player());
        addn("heiyu", -1, this_object());

        return "好吧，這盒黑玉斷續膏你就拿去用吧。";
}

void reset()
{
        set("heiyu", 1);
}

#include "fanyao.h"
