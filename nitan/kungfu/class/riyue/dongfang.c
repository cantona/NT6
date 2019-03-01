// dongfang.c
//Updated by haiyan

#include <ansi.h>
#include "riyue.h"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;
inherit F_QUESTER;

string ask_book();
mixed ask_pfm();

void create()
{
    object ob;
    set_name("東方不敗", ({"dongfang bubai", "dongfang", "bubai"}));
    set("nickname", HIY "天下無敵" NOR);
    set("title", HIM "日月神教教主" NOR);
    set("gender", "無性");
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

    set("inquiry", ([
        "楊蓮亭"   : "你敢直稱我愛人的名字，想找死呀？ \n",
        "辟邪劍譜" : "這是研讀葵花寶典的基礎，只有讀通了寶典，武功才算大成。\n",
        "辟邪劍影" : (: ask_book :),
/*
        "絕招"     : (: ask_pfm :),
        "鬼影"     : (: ask_pfm :),
*/
    ]));

    set("kuihua_count", 1);

    set("qi", 5000);
    set("max_qi", 5000);
    set("jing", 1000);
    set("max_jing", 1000);
    set("neili", 4500);
    set("max_neili", 4500);
    set("jiali", 400);

    set("combat_exp", 3000000);
    set("score", 0);

    set_skill("force", 600);
    set_skill("unarmed", 600);
    set_skill("riyue-xinfa", 600);
    set_skill("riyue-guanghua", 600);
        set_skill("kuihua-xinfa", 600);
    set_skill("sword", 600);
    set_skill("riyue-jian", 600);
    set_skill("pixie-jian", 600);
    set_skill("dodge", 600);
    set_skill("piaomiao-shenfa", 600);
    set_skill("parry", 600);
    set_skill("cuff", 600);
    set_skill("xuwu-piaomiao", 600);
    set_skill("hand", 600);
    set_skill("huanmo-longtianwu", 600);
    set_skill("literate", 600);
        set_skill("richu-dongfang", 600);
        set_skill("martial-cognize", 600);

    map_skill("force", "riyue-guanghua");
    map_skill("sword", "pixie-jian");
    map_skill("dodge", "pixie-jian");
    map_skill("parry", "pixie-jian");
    map_skill("cuff", "xuwu-piaomiao");
    map_skill("hand", "huanmo-longtianwu");

    prepare_skill("cuff", "xuwu-piaomiao");
    prepare_skill("hand", "huanmo-longtianwu");

    create_family("日月神教", 2, "教主");

    set("no_teach", ([
        "pixie-jian" : "辟邪劍法只能靠自己研讀《葵花寶典》。他日待你小成，我自會指點于你。",
    ]));


    set("master_ob",5);
        setup();
/*
        if (clonep())
        {
                     ob = find_object("/clone/lonely/book/kuihua-jianpu"); 
                     if (! ob) ob = load_object("/clone/lonely/book/kuihua-jianpu");
      
                     if (! environment(ob) && random(20) == 1) 
                             ob->move(this_object()); 
        }
*/

    carry_object("/d/fuzhou/obj/xiuhua")->wield();
    carry_object("/d/wanjiegu/npc/obj/qi-dress")->wear();
    carry_object("/d/heimuya/obj/yuxiao");
}

void attempt_apprentice(object ob)
{
     if(! permit_recruit(ob))  return;

     if( query("family/master_name", ob) == "任我行" )
     {
          command("say 我越看你越不順眼，快給我滾！");
          return;
     }

     if( query("combat_exp", ob)<250000 )
     {
          command("say 就你這點微末功夫，還是先跟我屬下各長老多練練吧！");
          return;
     }

     if((int)ob->query_skill("riyue-xinfa", 1) < 140)
     {
          command("say 本教的內功心法你還沒練好，還要多下苦功才行！");
          return;
     }

     command("xixi");
     command("recruit "+query("id", ob));
     command("say 好！好！我日月神教真是人才輩出，一統江湖，指日可待！");
     set("title", HIR"日月神教大護法"NOR, ob);
}

string ask_book()
{
     mapping fam;
     object me, ob;
        int cost;

     me = this_player();
     if( query("family/family_name", me) != query("family/family_name") )
            return "你這個" + RANK_D->query_rude(this_player()) +
                   "，打聽本教秘笈有何圖謀？";

     if( query("family/master_id", me) != query("id") )
            return "你又非我親傳弟子，打聽寶典做什麼？";

     if (me->query_skill("riyue-guanghua", 1) < 100)
            return "你的日月光華學得還不到家，貿然修煉寶典，有害無益。";

        if( query("reborn/times", me) < 1 )
                return "你境界不夠，給你也是無益，你還是等轉世後再找我吧。";

        if( query("family/first", me) ) cost = 2500; 
        else cost = 5000; 
        if( query("family/gongji", me) < cost ) 
                return "你為我教效力還不夠，等你擁有足夠的師門功績再來兌換辟邪劍影秘笈吧。";

     if (query("kuihua_count") < 1)
            return "你來晚了，寶典我已經借出去了。";

     addn("kuihua_count", -1);
        addn("family/gongji", -cost, me); 
      //ob = new("/clone/book/kuihua");
      ob = new("/clone/lonely/book/kuihua-jianpu");
     ob->move(me);
     return "這本寶典你可要收好，弄丟了我找你算帳。";
}

void reset()
{
     set("kuihua_count", 1);
}

mixed ask_pfm()
{
     object me = this_player();

     if( query("can_perform/pixie-jian/ying", me) )
           return "我已指點于你，還多問什麼？自己多練練去！";

     if( query("family/family_name", me) != query("family/family_name") )
           return "本教武功獨步武林，這位" + RANK_D->query_respect(me) +
                  "既然想學，不如入我日月神教如何？";

     if (me->query_skill("pixie-jian", 1) < 90)
           return "寶典所載武功博大精深，你連一半都沒看完，多問什麼？快給我用功去！";

     if (me->query_skill("pixie-jian", 1) < 200)
           return "你的辟邪劍法尚欠火候，再多去鑽研一下寶典！";

     message_vision(HIC "$n" HIC "對$N" HIC "點了點頭：“很好，我來教你一招，看仔細了。”\n" HIR
                    "只見$n" HIR "身形微晃，霎時不見蹤影，$N" HIR
                    "只覺無數黑影在身邊飄過，數道寒氣逼向周身，全身一陣刺痛。\n" NOR,
                    me, this_object());
     command("say 明白了沒有？”"NOR);
     tell_object(me, HIW "你學會了「鬼影」這一招。\n" NOR);
     if (me->can_improve_skill("sword"))
             me->improve_skill("sword", 160000);
     set("can_perform/pixie-jian/ying", 1, me);
     return 1;
}

