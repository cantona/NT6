// ZhuangZheng.c
// pal 1997.05.11

#include <ansi.h>
#include "mingjiao_job.h"

inherit NPC;
inherit F_MASTER;
inherit F_UNIQUE;

string ask_job();

void create()
{
        set_name("莊錚", ({ "zhuang zheng", "zhuang", "zheng", }));
        set("long",
        "他是一位高大魁偉的中年男子，身穿一件白布長袍。\n"
        "他天生神力，手中的兩頭狼牙棒有萬夫不當之勇，真是一條威風凜凜的漢子。\n"
        );

        set("title", HIG "明教" HIW "銳金旗" NOR "掌旗使");
        set("gender", "男性");
        set("attitude", "friendly");
        set("class", "fighter");

        set("age", 42);
        set("shen_type", 1);
        set("str", 25);
        set("int", 25);
        set("con", 25);
        set("dex", 25);
        set("max_qi", 1000);
        set("max_jing", 1000);
        set("neili", 1000);
        set("max_neili", 1000);
        set("jiali", 100);
        set("combat_exp", 100000);
        set("score", 5000);

        set_skill("force", 120);
        set_skill("dodge", 120);
        set_skill("parry", 120);
        set_skill("sword", 120);
        set_skill("cuff", 120);
        set_skill("strike", 120);
        set_skill("throwing", 200);
        set_skill("literate", 100);

        set_skill("shenghuo-xinfa", 120);
        set_skill("shenghuo-bu", 120);
        set_skill("shenghuo-quan", 120);
        set_skill("guangming-zhang", 120);
        set_skill("liehuo-jian", 120);
        set_skill("wuxing-jueji", 200);

        map_skill("force", "shenghuo-xinfa");
        map_skill("dodge", "shenghuo-bu");
        map_skill("strike", "guangming-zhang");
        map_skill("sword", "liehuo-jian");
        map_skill("parry", "liehuo-jian");
        map_skill("cuff", "shenghuo-quan");
        map_skill("throwing", "wuxing-jueji");

        prepare_skill("cuff", "shenghuo-quan");
        prepare_skill("strike", "guangming-zhang");

        create_family("明教", 37, "銳金旗掌旗使");
        set("inherit_title",HIG"明教"NOR"銳金旗教眾"NOR);

        set("inquiry", ([
                "name" : "在下就是明教銳金旗掌旗使莊錚，不知閣下有何指教。",
                "任務" : (: ask_job :),
                "job"  : (: ask_job :),
                "放棄" : (: ask_abandon :),
                "abandon" : (: ask_abandon :),
        ]));

        setup();

        carry_object("/d/mingjiao/obj/langyabang")->wield();
        carry_object("/d/mingjiao/obj/baipao")->wear();
}

#include "zhangqishi.h"

string ask_job()
{
     object player=this_player();
     mapping fam ;
     object ling,qiao;

        if( !(fam=query("family", this_player())) || fam["family_name"] != "明教" )
                return "這位"+RANK_D->query_respect(player)+"並非我教弟兄，在下哪敢分派閣下什麼任務呢？\n";

        if( query("combat_exp", player)>400000 )
                 return "這位"+RANK_D->query_respect(player)+"實戰經驗已經頗高，豈敢勞煩大架。\n";

        if (fam["generation"] <37)
                 return "這位"+RANK_D->query_respect(player)+"在我明教中地位頗高，豈敢勞煩大架。\n";

        if( query("mingjiao/job", player) )
                return judge_jobmsg(player,0);

        command("nod"+query("id", player));

        set("mingjiao/job", "jin_caikuang", player);

        qiao=new(OBJ_PATH"/qiao");
        qiao->move(player);
        tell_object(player,"莊錚給你一把鐵鍬。\n");

        return "我銳金旗在教內負責採礦煉鐵，最近上等精鐵快用完了，你去\n"
                "附近的山上找些鐵礦，然後到精練場將礦石煉制成精鐵。\n"
                "附近山上常有猛獸出沒，你自己多加小心。\n";
}
