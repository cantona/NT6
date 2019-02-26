inherit NPC;
inherit F_MASTER;

#include <command.h>
#include <ansi.h>
#include "emei.h"
mixed ask_skill1();
mixed ask_skill2();

void create()
{
        set_name("周芷若", ({ "zhou zhiruo","zhiruo","zhou"}));
        set("long", "她是峨嵋派的第四代掌門弟子。只見她一張\n"
                    "臉秀麗絕俗。身着一身淡黃衣裳。略顯清減\n"
                    "的巧笑中帶了些許無奈。\n");
        set("gender", "女性");
        set("age", 20);
        set("attitude", "peaceful");
        set("shen_type", 1);

        set("inquiry",([
                "剃度"     : "找我剃度？不對吧。",
                "出家"     : "要出家找我的師姐們去。",
                "還俗"     : "無聊。還俗也找我！",
                "張無忌"   : "這個狠心短命的傢伙，我再也不要見他！",
                "趙敏"     : "不要問這個賤婢子！",
                "倚天劍"   : "倚天不出，誰與爭鋒？唉！",
                "屠龍刀"   : "你想武林稱雄？別做夢了。",
                "滅絕師太" : "師父待我恩重如山，我今生難以回報。",
                "九陰真經" : "那是什麼東西？我這可是第一次聽説。",
                "天誅龍蛟訣" : (: ask_skill1 :),
                "奪命連環爪" : (: ask_skill2 :),
        ]));

        set("str", 22);
        set("int", 32);
        set("con", 26);
        set("dex", 24);

        set("max_qi", 5000);
        set("max_jing", 3000);
        set("neili", 6000);
        set("max_neili", 6000);
        set("jingli", 2000);
        set("max_jingli", 2000);
        set("jiali", 200);
        set("combat_exp", 2500000);

        set_skill("force", 260);
        set_skill("emei-xinfa", 260);
        set_skill("yijin-duangu", 260);      // 易筋鍛骨
        set_skill("linji-zhuang", 200);
        set_skill("dodge", 260);
        set_skill("shexing-lifan", 260);     // 蛇行狸翻
        set_skill("zhutian-bu", 180);
        set_skill("finger", 180);
        set_skill("tiangang-zhi", 180);
        set_skill("hand", 180);
        set_skill("jieshou-jiushi", 180);
        set_skill("strike", 260);
        set_skill("jinding-zhang", 180);
        // set_skill("sixiang-zhang", 180);
        set_skill("cuixin-zhang", 260);      // 催心掌
        set_skill("claw", 260);
        set_skill("jiuyin-baiguzhao", 260);  // 九陰白骨爪
        set_skill("whip", 260);
        set_skill("yinlong-bian", 260);      // 銀龍鞭法
        set_skill("sword", 180);
        set_skill("emei-jian", 180);
        set_skill("yitian-jian", 180);
        set_skill("blade", 180);
        set_skill("yanxing-dao", 180);
        set_skill("parry", 260);
        set_skill("martial-cognize", 200);
        set_skill("literate", 200);
        set_skill("mahayana", 100);
        set_skill("buddhism", 100);

        map_skill("force", "yijin-duangu");
        map_skill("dodge", "shexing-lifan");
        map_skill("finger", "tiangang-zhi");
        map_skill("hand", "jieshou-jiushi");
        map_skill("strike", "cuixin-zhang");
        map_skill("claw", "jiuyin-baiguzhao");
        map_skill("whip", "yinlong-bian");
        map_skill("sword", "yitian-jian");
        map_skill("blade", "yanxing-dao");
        map_skill("parry", "yinlong-bian");

        prepare_skill("strike", "cuixin-zhang");
        prepare_skill("claw", "jiuyin-baiguzhao");

        create_family("峨嵋派", 4, "掌門弟子");

        set("no_teach", ([
                "linji-zhuang"     : "想學臨濟十二莊找我師父去。",
                "shexing-lifan"    : "蛇行狸翻？這也是種武功嗎？聽名字倒是蠻有意思的。",
                "yijin-duangu"     : "你説的那是什麼啊？我這可是頭一次聽説。",
                "cuixin-zhang"     : "催心掌？聽名字怪嚇人的，這樣的武功我可不會。",
                //"jiuyin-baiguzhao" : "九陰白骨爪？這是什麼武功啊？光聽名字我就毛骨悚然。",
                "yinlong-bian"     : "我只會劍法和刀法，鞭法師父從來沒教過我。",
                "yitian-jian"      : "這門功夫是家師獨門絕學需找她親自傳授。",
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "claw.duo" :),       // 奪命連環
                (: perform_action, "claw.jie" :),       // 九陰剎神抓
                (: perform_action, "strike.cuixin" :),  // 催心破元訣
                (: perform_action, "whip.jiao" :),      // 天誅龍蛟訣
                (: perform_action, "dodge.guiyuan" :),  // 九陰歸元勁
                (: perform_action, "sword.yitian" :),
                (: perform_action, "sword.fumo" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
                (: exert_function, "shield" :),
        }));

        set("master_ob", 4);
        setup();
        carry_object("/clone/weapon/changjian")->wield();
        carry_object("/d/emei/obj/ycloth.c")->wear();
}

mixed ask_skill1()
{
        object me = this_player();
        if( query("can_perform/yinlong-bian/zhu", me) )
               return "這招我不是已經教過你了嗎？自己下去多練吧！";

        if( query("family/family_name", me) != query("family/family_name") )
               return "你是哪裏來的？快給我滾開！";

        if (me->query_skill("yinlong-bian", 1) <130 )
               return "你的銀龍鞭法練的還不夠純熟，無發領悟此精妙絕技！";

        if (me->query_skill("yinlong-bian", 1) < 1)
               return "你連銀龍鞭法都沒學，還談什麼絕招可言？";

        command("say 看好了，以後對那些妖人不要手軟，一上來就用這招！");
        command("grin");
        message_vision(HIG "周芷若抽出鞭子，隨意揮舞着，將銀龍鞭法奧義展現無疑。\n不一會兒，周芷若已是大汗淋漓。\n" NOR,me);
        command("say 這就是銀龍鞭法的「天誅龍蛟訣」了，你要認真領悟其奧妙。");
        command("hehe");
        tell_object(me, HIC "你學會了「天誅龍蛟訣」。\n" NOR);
        if (me->can_improve_skill("whip"))
               me->improve_skill("whip", 1500000);
        if (me->can_improve_skill("yinlong-bian"))
               me->improve_skill("yinlong-bian", 1500000);
        set("can_perform/yinlong-bian/zhu", 1, me);
        return 1;
}

mixed ask_skill2()
{
        object me = this_player();
        if( query("can_perform/jiuyin-baiguzhao/duo", me) )
               return "這招我不是已經教過你了嗎？自己下去多練吧！";

        //if (me->query("family/family_name") != query("family/family_name"))
               //return "你是哪裏來的？快給我滾開！";

        if (me->query_skill("jiuyin-baiguzhao", 1) <120 )
               return "你的九陰白骨爪練的還不夠純熟，無發領悟此精妙絕技！";

         command("say 看好了，以後對那些妖人不要手軟，一上來就用這招！");
         command("grin");
       tell_object(me, HIC "你學會了「奪命連環爪」。\n" NOR);
        if (me->can_improve_skill("jiuyin-baiguzhao"))
               me->improve_skill("jiuyin-baiguzhao", 1500000);
        set("can_perform/jiuyin-baiguzhao/duo", 1, me);
        return 1;
}


void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if ((int)ob->query_int() < 45)
        {
                command("say 這位" + RANK_D->query_respect(ob) + "恐怕資質差了一點。");
                command("say 不過尚大有潛力，還是先回去磨練磨練。");
                return;
        }

        if( !query_temp("marks/宋夫人", ob) )
        {
                command("say "+query("name", this_player())+"你沒事就可以走了。\n\n");
                return;
        }

        delete_temp("marks/宋夫人", ob);
        command("say "+query("name", ob)+"看你這麼可憐，勉為其難收下你吧。\n");
        command("recruit "+query("id", ob));
}
