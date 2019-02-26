// This program is a part of NITAN MudLIB
// hufei.c 胡斐

#include <ansi.h>
#include "hu.h"

#define LENGYUE  "/clone/unique/lengyue"
#define JUNDAO   "/clone/unique/cwbdao"
#define QUANJING "/clone/book/hujia1"
#define DAOPU    "/clone/book/hujia2"

inherit NPC;
inherit F_MASTER;
inherit F_COAGENT;
inherit F_QUESTER;
// inherit F_NOCLONE;

mixed ask_baodao();
mixed ask_jundao();
mixed ask_quanjing();
mixed ask_daopu();

mixed ask_skill1();
mixed ask_skill2();
mixed ask_skill3();
mixed ask_skill4();
mixed ask_skill5();
mixed ask_skill6();
mixed ask_skill7();
mixed ask_skill8();
mixed ask_skill9();
mixed ask_skill10();
mixed ask_skill11();

mixed  try_to_learn_baishengdao();
mixed  try_to_learn_hujiadao();
mixed  try_to_learn_sixiangbu();

string ask_book();

void create()
{
        object ob;
        set_name("胡斐", ({"hu fei", "hu", "fei"}));
        set("gender", "男性");
        set("nickname", HIW "雪山飛狐" NOR);
        set("age", 25);
        set("long", @LONG
他就是胡一刀之子胡斐，因其武功高強神出鬼
沒。在江湖上人送外號「雪山飛狐」。他身穿
一件白色長衫，腰間別着一把看起來很舊的刀。
滿腮虯髯，根根如鐵，一頭濃髮，卻不結辮。
LONG
        );
        set("attitude", "peaceful");
        set("shen_type", 1);
        set("str", 45);
        set("int", 30);
        set("con", 30);
        set("dex", 30);

        set("qi", 5200);
        set("max_qi", 5200);
        set("jing", 3500);
        set("max_jing", 3500);
        set("neili", 6500);
        set("max_neili", 6500);
        set("jiali", 180);
        set("combat_exp", 6000000);
        set("level", 50);
        set("score", 20000);

        set_skill("force", 640);
        set_skill("lengyue-shengong", 640);
        set_skill("blade", 660);
        set_skill("baisheng-daofa", 660);
        set_skill("hujia-daofa", 660);
        set_skill("dodge", 660);
        set_skill("sixiang-bufa", 660);
        set_skill("parry", 640);
        set_skill("throwing", 660);
        set_skill("mantian-xing", 660);
        set_skill("strike", 640);
        set_skill("tianchang-zhang", 640);
        set_skill("cuff", 640);
        set_skill("hujia-quan", 640);
        set_skill("literate", 480);
        set_skill("martial-cognize", 600);
        set_skill("daojian-xiaotianwai", 800);

        map_skill("force", "lengyue-shengong");
        map_skill("blade", "hujia-daofa");
        map_skill("dodge", "sixiang-bufa");
        map_skill("parry", "hujia-daofa");
        map_skill("throwing", "mantian-xing");
        map_skill("strike", "tianchang-zhang");
        map_skill("cuff", "hujia-quan");

        prepare_skill("strike", "tianchang-zhang");
        prepare_skill("cuff",   "hujia-quan");

        set("no_teach", ([
                "baisheng-daofa" : (: try_to_learn_baishengdao :),
                "hujia-daofa"    : (: try_to_learn_hujiadao :),
                "sixiang-bufa"   : (: try_to_learn_sixiangbu :),
        ]));

        create_family("關外胡家", 7, "傳人");

        set("inquiry", ([
                "冷月寶刀"   : (: ask_baodao :),
                "闖王寶刀"   : (: ask_jundao :),
                "胡家拳經"   : (: ask_quanjing :),
                "刀譜"       : (: ask_book :),
                "胡家刀譜"   : (: ask_daopu :),
                // "風捲霹靂"   : (: ask_skill1 :),
                // "風捲霹靂上九天" : (: ask_skill1 :),
                "奔拳快打"   : (: ask_skill2 :),
                // "烏龍探海"   : (: ask_skill3 :),
                // "作繭自縛"   : (: ask_skill4 :),
                "飛天神行"   : (: ask_skill5 :),
                "星光閃爍"   : (: ask_skill6 :),
                // "雄霸羣山"   : (: ask_skill7 :),
                // "閃刀訣"     : (: ask_skill8 :),
                "推天獻印勢" : (: ask_skill9 :),
                "卸甲錐心勢" : (: ask_skill10 :),
                "八方藏刀勢" : (: ask_skill11 :),
                "橫掃千軍"   : "咦？這是什麼招數，我沒聽説過。",
                "袁紫衣"     : "算了，別提這傷心事了。",
                "閻基"       : "閻基這個狗賊我非殺了他不可。",
                "趙半山"     : "我趙三哥啊！他剛來關外看我呢。 ",
                "苗若蘭"     : "不知什麼時候還能再見到若蘭姑娘。",
                "若蘭"       : "不知什麼時候還能再見到若蘭姑娘。",
                "胡一刀"     : "遼東大俠胡一刀是我爹。不過我從沒見過他。",
                "程靈素"     : "現在我也不知道她在哪裏，只是曾經聽她説過好像要去襄陽。",
                "苗人鳳"     : "苗人鳳和家父齊名，本可成為知交好友，然而家父卻死在他的劍下。"
        ]));

        set("chat_chance_combat", 120);
        set("chat_msg_combat", ({
                (: perform_action, "blade.xian" :),
                (: perform_action, "blade.zhui" :),
                (: perform_action, "blade.cang" :),
                (: perform_action, "cuff.kuai" :),
                (: perform_action, "strike.jian" :),
                (: perform_action, "dodge.fei" :),
                (: perform_action, "throwing.shan" :),
                (: perform_action, "throwing.xing" :),
                (: exert_function, "recover" :),
                (: exert_function, "powerup" :),
        }));

        set_temp("apply/damage", 100);
        set_temp("apply/unarmed_damage", 100);
        set_temp("apply/armor", 200);

        set("master_ob",5);
        setup();

        if (clonep())
        {
                ob = find_object(LENGYUE);
                if (! ob) ob = load_object(LENGYUE);
                if (! environment(ob))
                {
                        ob->move(this_object());
                        ob->wield();
                } else
                {
                        ob = find_object(JUNDAO);
                        if (! ob) ob = load_object(JUNDAO);
                        if (! environment(ob))
                        {
                                ob->move(this_object());
                                ob->wield();
                        } else
                        {
                                ob = new("/clone/weapon/gangdao");
                                ob->move(this_object());
                                ob->wield();
                        }
                }
        }

        carry_object("/clone/cloth/cloth")->wear();
        set("startroom", "/d/guanwai/xiaowu");
        // check_clone();
}

void attempt_apprentice(object ob)
{
        if (! permit_recruit(ob))
                return;

        if (ob->name(1) == "胡一刀")
        {
                command("say 我操！你想做我的老子啊？");
                return;
        }

        if (ob->name(1) == "胡斐")
        {
                command("say 他奶奶的！你咋也起這個名字？");
                return;
        }

        if (ob->name(1) == "鬍子" || ob->name(1) == "胡臭")
        {
                command("say 你給換起個名字，現在這個名字也太齷齪了。");
                return;
        }

        command("recruit "+query("id", ob));
        command("say 今日我便收下你，我們胡家還要靠你們來發揚光大！");
        return;
}

mixed try_to_learn_baishengdao()
{
        object ob = this_player();

        if( query("can_learn/hufei/baisheng-daofa", ob) )
                return 0;

        if( query("combat_exp", ob)>100000 )
        {
                command("say 不錯，不錯！今日我便傳授你百勝刀法。");
                set("can_learn/hufei/baisheng-daofa", 1, ob);
                return 0;
        }

        return "你此時功力太淺，我還是先傳授你一些簡單的刀法。";
}

mixed try_to_learn_hujiadao()
{
        object ob = this_player();

        if( query("can_learn/hufei/hujia-daofa", ob) )
                return 0;

        if( query("combat_exp", ob)>600000 )
        {
                command("say 既然你能有如此造詣，我今日便傳授你胡家刀法！");
                set("can_learn/hufei/hujia-daofa", 1, ob);
                return 0;
        }

        return "你的實戰經驗不足，尚難以領會這高深胡家刀法。";
}

mixed try_to_learn_sixiangbu()
{
        object ob = this_player();

        if( query("can_learn/hufei/sixiang-bufa", ob) )
                return 0;

        if( query("combat_exp", ob)>50000 )
        {
                command("say 看來你武功已經有了一定的基礎，今日我就傳你四象步法。");
                set("can_learn/hufei/sixiang-bufa", 1, ob);
                return 0;
        }

        return "四象步法對你來説過於艱深，你還是先奠定好基礎再説。";
}

/*
mixed ask_skill1()
{
        object me;

        me = this_player();

        if( query("can_perform/hua-quan/juan", me) )
                return "俺不是已經教過你了嗎？還多説什麼？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你又不是俺胡家的，還和我羅嗦什麼？";

        if (me->query_skill("hua-quan", 1) < 1)
                return "你連西嶽華拳都未曾學過，哪裏來絕招？";

        if( query("family/gongji", me)<350 )
                return "你在我胡家碌碌無為，這招我先不忙傳你。";

        if( query("shen", me)<5000 )
                return "你俠義正事做得不夠，這招我先不忙傳你。";

        if (me->query_skill("force") < 180)
                return "你的內功火候不足，學不成這招。";

        if (me->query_skill("hua-quan", 1) < 120)
                return "你的西嶽華拳火候未到，還得多練習練習。";

        message_vision(HIY "$n" HIY "點了點頭，説道：“我先將這華拳的總"
                       "訣傳授予你，需得慢慢\n領會。”説完便聽得$n" HIY
                       "朗誦道：“風捲霹靂上九天，曉星當頭即\n走拳。出"
                       "勢跨虎西嶽傳，金鵬展翅庭中站。韋陀獻抱在胸前，"
                       "把臂\n攔門橫鐵閂。魁鬼仰鬥撩綠欄，出勢跨虎西嶽"
                       "傳。白猿偷桃拜天庭，\n吳王試劍劈玉磚……”$N" HIY
                       "在一旁細細捉摸。如此這般，過了良久。\n" NOR, me,
                       this_object());
        command("nod");
        command("say 我曾以華拳門掌門的身份參加掌門人大會，那次……");
        command("sigh");
        command("say 這西嶽華拳創於唐朝，威力的確不凡，可得多花功夫練習。");
        tell_object(me, HIC "你學會了「風捲霹靂上九天」。\n" NOR);

        if (me->can_improve_skill("cuff"))
                me->improve_skill("cuff", 1500000);
        if (me->can_improve_skill("hua-quan"))
                me->improve_skill("hua-quan", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/hua-quan/juan", 1, me);
        addn("family/gongji", -350, me);
        return 1;
}
*/

mixed ask_skill2()
{
        object me;

        me = this_player();

        if( query("can_perform/hujia-quan/kuai", me) )
                return "俺不是已經教過你了嗎？還多説什麼？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你又不是俺胡家的，還和我羅嗦什麼？";

        if (me->query_skill("hujia-quan", 1) < 1)
                return "你連胡家拳法都未曾學過，哪裏來絕招？";

        if( query("family/gongji", me)<100 )
                return "你在我胡家碌碌無為，這招我先不忙傳你。";

        if( query("shen", me)<2000 )
                return "你俠義正事做得不夠，這招我先不忙傳你。";

        if (me->query_skill("force") < 100)
                return "你的內功火候不足，學不成這招。";

        if (me->query_skill("hujia-quan", 1) < 80)
                return "你的胡家拳法火候未到，還得多練習練習。";

        message_vision(HIY "$n" HIY "略微點了點頭，深深呼入一口氣，縱"
                       "步上前，拳招迭出，疾如\n奔雷，霎時已向$N" HIY
                       "攻出數拳，招式甚為精妙。\n" NOR, me,
                       this_object());
        command("nod");
        command("say 看懂了嗎？");
        tell_object(me, HIC "你學會了「奔拳快打」。\n" NOR);

        if (me->can_improve_skill("cuff"))
                me->improve_skill("cuff", 1500000);
        if (me->can_improve_skill("hujia-quan"))
                me->improve_skill("hujia-quan", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/hujia-quan/kuai", 1, me);
        addn("family/gongji", -100, me);
        return 1;
}

mixed ask_skill5()
{
        object me;

        me = this_player();

        if( query("can_perform/sixiang-bufa/fei", me) )
                return "俺不是已經教過你了嗎？還多説什麼？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你又不是俺胡家的，還和我羅嗦什麼？";

        if (me->query_skill("sixiang-bufa", 1) < 1)
                return "你連四象步法都未曾學過，還神行什麼？";

        if( query("family/gongji", me)<1000 )
                return "你在我胡家碌碌無為，這招我先不忙傳你。";

        if( query("shen", me)<12000 )
                return "你俠義正事做得不夠，這招我先不忙傳你。";

        if (me->query_skill("force", 1) < 150)
                return "你的內功火候不足，學不成這招。";

        if( query("max_neili", me)<1000 )
                return "你的內力修為不夠，修煉高了再來。";

        if (me->query_skill("dodge", 1) < 150)
                return "你的基本輕功有待提高，暫時還學不成這招。";

        if (me->query_dex() < 33)
                return "你的身法太差，還需多加練習。";

        if (me->query_skill("sixiang-bufa", 1) < 150)
                return "你的四象步法火候未到，還得多練習練習。";

        message_vision(HIY "$n" HIY "對$N" HIY "點了點頭，喝道：“看"
                       "好了。”話音剛落，只見$n" HIY "足尖\n輕點地面"
                       "，凌空一躍而起，身形頓時變得飄忽不定，難以捉"
                       "摸。$N" HIY "\n越看越覺精奇，不禁暗自感歎。\n"
                       NOR, me, this_object());

        command("haha");
        command("say 可看明白了？");
        tell_object(me, HIC "你學會了「飛天神行」。\n" NOR);

        if (me->can_improve_skill("dodge"))
                me->improve_skill("dodge", 1500000);
        if (me->can_improve_skill("sixiang-bufa"))
                me->improve_skill("sixiang-bufa", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/sixiang-bufa/fei", 1, me);
        addn("family/gongji", -1000, me);
        return 1;
}

mixed ask_skill6()
{
        object me;

        me = this_player();

        if( query("can_perform/mantian-xing/shan", me) )
                return "俺不是已經教過你了嗎？還多説什麼？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你又不是俺胡家的，還和我羅嗦什麼？";

        if (me->query_skill("mantian-xing", 1) < 1)
                return "你連滿天星都未曾學過，哪裏來絕招？";

        if( query("family/gongji", me)<200 )
                return "你在我胡家碌碌無為，這招我先不忙傳你。";

        if( query("shen", me)<3000 )
                return "你俠義正事做得不夠，這招我先不忙傳你。";

        if (me->query_skill("force") < 100)
                return "你的內功火候不足，學不成這招。";

        if (me->query_skill("mantian-xing", 1) < 100)
                return "你的滿天星火候未到，還得多練習練習。";

        message_vision(HIY "$n" HIY "哈哈一笑，將$N" HIY "招至跟前，輕"
                       "聲在耳旁細聲講解滿天星暗器手\n法的諸多要點。隨"
                       "後又伸出右手，十指箕張，一伸一縮，看樣子是\n一"
                       "種很特別的暗器法門。\n" NOR, me, this_object());

        command("nod");
        command("say 剛才俺説的你都記住了嗎？");
        tell_object(me, HIC "你學會了「星光閃爍」。\n" NOR);

        if (me->can_improve_skill("throwing"))
                me->improve_skill("throwing", 1500000);
        if (me->can_improve_skill("mantian-xing"))
                me->improve_skill("mantian-xing", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/mantian-xing/shan", 1, me);
        addn("family/gongji", -200, me);
        return 1;
}
mixed ask_skill7()
{
        object me;

        me = this_player();

        if( query("can_perform/chuangwang-dao/xiong", me) )
                return "俺不是已經教過你了嗎？還多説什麼？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你又不是俺胡家的，還和我羅嗦什麼？";

        if (me->query_skill("chuangwang-dao", 1) < 1)
                return "你連闖王刀法都未曾學過，哪裏來絕招？";

        if( query("gongxian", me)<50 )
                return "你在我胡家碌碌無為，這招我先不忙傳你。";

        if( query("shen", me)<500 )
                return "你俠義正事做得不夠，這招我先不忙傳你。";

        if (me->query_skill("force") < 60)
                return "你的內功火候不足，學不成這招。";

        if (me->query_skill("chuangwang-dao", 1) < 40)
                return "你的闖王刀法火候未到，還得多練習練習。";

        message_vision(HIY "$n" HIY "笑了笑，伸手將$N" HIY "招到身前"
                       "，低聲在$N" HIY "耳旁嘀咕了半天。然後\n又拔出"
                       "腰刀猛劈數下，似乎是一種頗為剛猛的刀訣。\n"
                       NOR, me, this_object());

        command("nod");
        command("say 這招是用於衝鋒陷陣的，高手對抗卻不多用。");
        tell_object(me, HIC "你學會了「雄霸羣山」。\n" NOR);

        if (me->can_improve_skill("blade"))
                me->improve_skill("blade", 1500000);
        if (me->can_improve_skill("chuangwang-dao"))
                me->improve_skill("chuangwang-dao", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/chuangwang-dao/xiong", 1, me);
        addn("gongxian", -50, me);
        return 1;
}
/*
mixed ask_skill8()
{
        object me;

        me = this_player();

        if( query("can_perform/liuhe-dao/shan", me) )
                return "俺不是已經教過你了嗎？還多説什麼？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你又不是俺胡家的，還和我羅嗦什麼？";

        if (me->query_skill("liuhe-dao", 1) < 1)
                return "你連六合刀法都未曾學過，哪裏來絕招？";

        if( query("family/gongji", me)<200 )
                return "你在我胡家碌碌無為，這招我先不忙傳你。";

        if( query("shen", me)<3500 )
                return "你俠義正事做得不夠，這招我先不忙傳你。";

        if (me->query_skill("force") < 100)
                return "你的內功火候不足，學不成這招。";

        if (me->query_skill("liuhe-dao", 1) < 80)
                return "你的六合刀法火候未到，還得多練習練習。";

        message_vision(HIY "$n" HIY "對$N" HIY "笑了笑，拔出腰間佩刀"
                       "握在手中，説道：“這六合刀法的\n要訣不過是展"
                       "、抹、鈎、剁、砍、劈六勢，看好了。”説完便只"
                       "見\n$n" HIY "手中鋼刀吞吐不定，形若游龍，勢如"
                       "猛虎。接連變換了數種方\n位，最後哧的一聲砍落"
                       "，刀身震得嗡嗡直響。\n" NOR, me, this_object());

        command("nod");
        command("say 只要掌握了四象六合的方位，這招便不難練習。");
        tell_object(me, HIC "你學會了「閃刀訣」。\n" NOR);

        if (me->can_improve_skill("blade"))
                me->improve_skill("blade", 1500000);
        if (me->can_improve_skill("liuhe-dao"))
                me->improve_skill("liuhe-dao", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/liuhe-dao/shan", 1, me);
        addn("family/gongji", -200, me);
        return 1;
}
*/
mixed ask_skill9()
{
        object me;

        me = this_player();

        if( query("can_perform/hujia-daofa/xian", me) )
                return "俺不是已經教過你了嗎？還多説什麼？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你又不是俺胡家的，還和我羅嗦什麼？";

        if (me->query_skill("hujia-daofa", 1) < 1)
                return "你連胡家刀法都未曾學過，哪裏來絕招？";

        if( query("family/gongji", me)<900 )
                return "你在我胡家碌碌無為，這招我先不忙傳你。";

        if (me->query_skill("force") < 160)
                return "你的內功火候不足，學不成這招。";

        if (me->query_skill("hujia-daofa", 1) < 120)
                return "你的胡家刀法火候未到，還得多練習練習。";

        message_vision(HIY "$n" HIY "拔出腰間佩刀，握在手中。對$N" HIY "笑"
                       "道：“我便用這招攻你，看\n你如何抵擋。”説完$n" HIY
                       "已橫過刀身，將刀鋒正對着$N" HIY "，雙手分握\n刀背和"
                       "刀把，緩緩向$N" HIY "推進。$N" HIY "見狀不禁啞然失"
                       "笑，心道：“這也\n稱得上是刀法？如此緩慢怎麼破敵。"
                       "”當下也不多言，衝上前攻出\n一招，可霎時只見$n" HIY
                       "刀勢一變，中攻直進向$N" HIY "劈來，竟然全無破\n綻。"
                       "$N" HIY "急忙左閃右避，可$n" HIY "的刀尖始終不離$N"
                       HIY "胸前半寸。\n" NOR, me, this_object());

        command("haha");
        command("say 這招乃是以慢制快的刀勢，後發制人便是要點。");
        command("say 當年我從苗人鳳處知曉了這個奧妙，終生收益不淺。");
        tell_object(me, HIC "你學會了「推天獻印勢」。\n" NOR);

        if (me->can_improve_skill("blade"))
                me->improve_skill("blade", 1500000);
        if (me->can_improve_skill("hujia-daofa"))
                me->improve_skill("hujia-daofa", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/hujia-daofa/xian", 1, me);
        addn("family/gongji", -900, me);
        return 1;
}

mixed ask_skill10()
{
        object me;

        me = this_player();

        if( query("can_perform/hujia-daofa/zhui", me) )
                return "俺不是已經教過你了嗎？還多説什麼？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你又不是俺胡家的，還和我羅嗦什麼？";

        if (me->query_skill("hujia-daofa", 1) < 1)
                return "你連胡家刀法都未曾學過，哪裏來絕招？";

        if( query("family/gongji", me)<600 )
                return "你在我胡家碌碌無為，這招我先不忙傳你。";

        if( query("shen", me)<22000 )
                return "你俠義正事做得不夠，這招我先不忙傳你。";

        if (me->query_skill("force") < 200)
                return "你的內功火候不足，學不成這招。";

        if (me->query_skill("hujia-daofa", 1) < 140)
                return "你的胡家刀法火候未到，還得多練習練習。";

        message_vision(HIY "$n" HIY "微微頷首，更不答話，當即伸出右掌"
                       "，以掌作刀，先使出胡家\n刀法中的一式「霸王卸甲"
                       "」，掌鋒斜斜劃出一道半圈，至下往上劈\n出。待掌"
                       "至中途卻猛然變成一招「穿心錐」，單掌急速旋轉，"
                       "復由\n上往中穿出。$N" HIY "看到這裏，雙目陡然"
                       "一亮，似乎明白了什麼。\n" NOR,
                       me, this_object());

        command("nod2");
        command("say 這招的精要便是先卸除敵人的防禦，再給他致命一擊。");
        command("say …嗯…這勢太過凌厲，可千萬不能用它為非作歹！");
        tell_object(me, HIC "你學會了「卸甲錐心勢」。\n" NOR);

        if (me->can_improve_skill("blade"))
                me->improve_skill("blade", 1500000);
        if (me->can_improve_skill("hujia-daofa"))
                me->improve_skill("hujia-daofa", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/hujia-daofa/zhui", 1, me);
        addn("family/gongji", -1300, me);
        return 1;
}

mixed ask_skill11()
{
        object me;

        me = this_player();

        if( query("can_perform/hujia-daofa/cang", me) )
                return "俺不是已經教過你了嗎？還多説什麼？";

        if( query("family/family_name", me) != query("family/family_name") )
                return "你又不是俺胡家的，還和我羅嗦什麼？";

        if( query("family/gongji", me)<2200 )
                return "你在我胡家碌碌無為，這招我先不忙傳你。";

        if( query("shen", me)<30000 )
                return "你俠義正事做得不夠，這招我先不忙傳你。";

        if (me->query_skill("force") < 250)
                return "你的內功火候不足，學不成這招。";

        if (me->query_skill("hujia-daofa", 1) < 180)
                return "你的胡家刀法火候未到，還得多練習練習。";

        message_vision(HIY "$n" HIY "凝視了$N" HIY "半天，緩緩地點了"
                        "點頭，頗為讚許道：“想不到今日\n你的刀法能有"
                        "如此造詣，假以時日，你必當超過為師。今日我就"
                        "傳\n你這套八方藏刀勢，希望日後你能夠有所作為"
                        "。”$n" HIY "頓了頓，又\n接着對$N" HIY "説道"
                        "：“我胡家刀法之所以厲害，不外乎刀勢凌厲。須"
                        "知\n以主欺客，不如以客犯主；嫩勝於老，遲勝於"
                        "急。胡家刀法常用到\n的纏、滑、絞、擦、抽、截"
                        "等刀勢就遠強於一般刀法中展、抹、鈎、\n剁、砍"
                        "、劈等刀勢。而這八方藏刀勢的變化卻又不止於此"
                        "，讓我慢\n慢給你説來……”如此這般，過了良久"
                        "……良久……\n" NOR, me, this_object());

        command("nod");
        command("say 剛才我所説的全是要點，需牢記在心。");
        command("say 你下來後一定要勤加練習，才能將這勢用得純熟。");
        tell_object(me, HIC "你學會了「八方藏刀勢」。\n" NOR);

        if (me->can_improve_skill("force"))
                me->improve_skill("force", 1500000);
        if (me->can_improve_skill("dodge"))
                me->improve_skill("dodge", 1500000);
        if (me->can_improve_skill("parry"))
                me->improve_skill("parry", 1500000);
        if (me->can_improve_skill("blade"))
                me->improve_skill("blade", 1500000);
        if (me->can_improve_skill("hujia-daofa"))
                me->improve_skill("hujia-daofa", 1500000);
        me->improve_skill("martial-cognize", 1500000);
        set("can_perform/hujia-daofa/cang", 1, me);
        addn("family/gongji", -2200, me);
        return 1;
}

mixed ask_baodao()
{
        object me;
        object ob;
        object owner;

        me = this_player();

        if( query("family/family_name", me) != "關外胡家" )
                return "你是哪裏來的？跑來跟我羅嗦什麼！";

        if( query("family/master_id", me) != query("id") )
                return "你又不是我的弟子，跟我羅嗦些什麼？";

        if( query("shen", me)<10000 )
                return "你不是我俠義中人，這寶刀我不能給你。";

        if (me->query_skill("hujia-daofa", 1) < 150)
                return "你還是先在我這裏把胡家刀法練好再説吧。";

        ob = find_object(LENGYUE);
        if (! ob) ob = load_object(LENGYUE);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "奶奶的，你這個渾人！俺的寶刀不是交給你了嗎？";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "…嗯…冷月寶刀現在不在我手裏。";

                if( query("family/family_name", owner) == "關外胡家" )
                        return "冷月寶刀現在暫時是你兄弟"+query("name", owner)+
                               "在用，你要用就去找他吧。";
                else
                        return "俺的冷月寶刀現在落在了"+query("name", owner)+
                               "手中，你去把它找回來吧！";
        }
        ob->move(this_object());

        ob = new("/clone/weapon/gangdao");
        ob->move(this_object());
        ob->wield();

        message_vision(CYN "$N" CYN "大笑數聲，道：好，我這柄寶刀你就拿去用吧。\n" NOR,
                       this_object(), me);
        command("give moon blade to "+query("id", me));
        return 1;
}

mixed ask_jundao()
{
        object me;
        object ob;
        object owner;

        me = this_player();

        if( query("family/family_name", me) != "關外胡家" )
                return "你是哪裏來的？跑來跟我羅嗦什麼！";

        if( query("family/master_id", me) != query("id") )
                return "你又不是我的弟子，跟我羅嗦些什麼？";

        if( query("shen", me)<10000 )
                return "你不是我俠義中人，這軍刀我不能給你。";

        if (me->query_skill("blade", 1) < 120)
                return "你連刀都不會使，怎麼配用闖王軍刀？";

        ob = find_object(JUNDAO);
        if (! ob) ob = load_object(JUNDAO);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "俺的那柄闖王軍刀不就是你拿着在用嗎？";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "…嗯…闖王軍刀現在不在我手裏。";

                if( query("family/family_name", owner) == "關外胡家" )
                        return "闖王軍刀現在暫時是你兄弟"+query("name", owner)+
                               "在用，你要用就去找他吧。";
                else
                        return "俺的闖王軍刀現在落在了"+query("name", owner)+
                               "手中，你去把它找回來吧！";
        }
        ob->move(this_object());

        ob = new("/clone/weapon/gangdao");
        ob->move(this_object());
        ob->wield();

        message_vision(CYN "$N" CYN "點了點頭，沉聲道：你小子有出息，闖王軍"
                       "刀你就拿去用吧。\n" NOR, this_object(), me);
        command("give chuangwang baodao to "+query("id", me));
        return 1;
}

mixed ask_quanjing()
{
        object me;
        object ob;
        object owner;

        me = this_player();

        if( query("family/family_name", me) != "關外胡家" )
                return "你是哪裏來的？跑來跟我羅嗦什麼！";

        if( query("family/master_id", me) != query("id") )
                return "你又不是我的弟子，跟我羅嗦些什麼？";

        if( query("shen", me)<10000 )
                return "你不是我俠義中人，這拳經我不能給你。";

        if( query("combat_exp", me)<10000 )
                return "你現在經驗太淺，不用忙着去閲讀拳經。";

        if (me->query_skill("hujia-quan", 1) > 119)
                return "你胡家拳法的造詣已經不淺了，那本拳經還是留給後輩們讀吧。";

        ob = find_object(QUANJING);
        if (! ob) ob = load_object(QUANJING);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "我胡家的家傳拳經不就是你拿着在看嗎？";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "…嗯…胡家拳經現在不在我手裏。";

                if( query("family/family_name", owner) == "關外胡家" )
                        return "胡家拳經現在暫時被你兄弟"+query("name", owner)+
                               "取去看了，你要看就去找他吧。";
                else
                        return "我們胡家的家傳拳經現在落在了"+query("name", owner)+
                               "手中，你去把它奪回來吧！";
        }
        ob->move(this_object());
        message_vision(CYN "$N" CYN "點頭道：…嗯…這本拳經你就拿去吧，可要認真研讀。\n" NOR,
                       this_object(), me);
        command("give hujia quanjing to "+query("id", me));
        return 1;
}

mixed ask_daopu()
{
        object me;
        object ob;
        object owner;

        me = this_player();

        if( query("family/family_name", me) != "關外胡家" )
                return "你是哪裏來的？跑來跟我羅嗦什麼！";

        if( query("family/master_id", me) != query("id") )
                return "你又不是我的弟子，跟我羅嗦些什麼？";

        if( query("shen", me)<15000 )
                return "你不是我俠義中人，這刀譜我不能給你。";

        if( query("combat_exp", me)<50000 )
                return "你現在經驗太淺，這本刀譜對你來説過於深奧了。";

        if (me->query_skill("blade", 1) > 179)
                return "你刀法的造詣已稱得上是登峯造極了，刀譜還是留給後輩們讀吧。";

        ob = find_object(DAOPU);
        if (! ob) ob = load_object(DAOPU);
        owner = environment(ob);
        while (owner)
        {
                if (owner->is_character() || ! environment(owner))
                        break;
                owner = environment(owner);
        }

        if (owner == me)
                return "我胡家的家刀譜經不就是你拿着在看嗎？";

        if (objectp(owner) && owner != this_object())
        {
                if (! owner->is_character())
                        return "…嗯…胡家刀譜現在不在我手裏。";

                if( query("family/family_name", owner) == "關外胡家" )
                        return "胡家刀譜現在暫時被你兄弟"+query("name", owner)+
                               "取去看了，你要看就去找他吧。";
                else
                        return "我們胡家的家傳刀譜現在落在了"+query("name", owner)+
                               "手中，你去把它奪回來吧！";
        }
        ob->move(this_object());
        message_vision(CYN "$N" CYN "點頭道：這本胡家刀譜你就拿去看吧，有不懂"
                       "之處可以來問我。\n" NOR, this_object(), me);
        command("give hujia daopu to "+query("id", me));
        return 1;
}

int accept_object(object me, object ob)
{
        int i;
        int r;
        if (r = ::accept_object(me, ob))
                return r;
        if( !me || environment(me) != environment() ) return 0;
        if ( !objectp(ob) ) return 0;
        if ( !present(ob, me) ) return notify_fail("你沒有這件東西。");
        if( query("id", ob) == "yanji" )
        {
                write(HIC "\n胡斐説道：這位" + RANK_D->query_respect(me)+"，如此大恩大德，在下實不知何以為報。\n");
                write(HIC "\n胡斐大喜道：狗賊！想不到你也有今天！！手起刀落，將閻基剁為兩段。\n");
                ob->die();
                set_temp("marks/hujiadaopu", 1, me);
        }
        return 1;
}

string ask_book()
{
        object ob, me;

        me = this_player();
        if( !query_temp("marks/hujiadaopu", me) )
                return "你説什麼? \n";
        if( (query("shen", me)<10000) )
                return "刀譜落入宵小之手，難免是閻基第二。\n";

        else
        if( (query("shen", me)>100000) )
        {
                if (query("book_count") > 0)
                {
                        write(HIC "胡斐説着轉身從閻基屍身上搜出一本破舊書本，遞了給你。\n");
                        call_out("waiting",0,me,ob);
                        addn("book_count", -1);
                        ob = new ("/clone/book/blade_book");
                        ob->move(this_player());
                        command("rumor "+query("name", me)+"拿到胡家刀譜啦。\n");
                        return "這本刀譜被這狗賊霸佔多時了，現在就贈與你吧。\n";
                }
                else return "你來晚了，現在刀譜已不在此處。\n";
        }

}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "歷練" :
        case "歷煉" :
        case "鍛鍊" :
                return QUEST_D->accept_ask(this_object(), me, topic);
                break;

        case "地老天荒" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/tianchang-zhang/huang",
                           "name"    : "地老天荒",
                           "sk1"     : "tianchang-zhang",
                           "lv1"     : 100,
                           "sk2"     : "force",
                           "lv2"     : 140,
                           "neili"   : 2000,
                           "gongxian": 1000,
                           "shen"    : 26000, ]));
                break;

        case "空手奪白刃" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/tianchang-zhang/duo",
                           "name"    : "空手奪白刃",
                           "sk1"     : "tianchang-zhang",
                           "lv1"     : 100,
                           "sk2"     : "force",
                           "lv2"     : 140,
                           "neili"   : 2000,
                           "gongxian": 1000,
                           "shen"    : 26000, ]));
                break;

        case "破字訣" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/hujia-daofa/po",
                           "name"    : "破字訣",
                           "sk1"     : "hujia-daofa",
                           "lv1"     : 120,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "gongxian": 600,
                           "neili"   : 1600,
                           "shen"    : 28000, ]));
                break;

         case "開天闢地" :
                 return MASTER_D->teach_pfm(me, this_object(),
                         ([ "perform" : "can_perform/hujia-daofa/pi",
                            "name"    : "開天闢地",
                            "sk1"     : "hujia-daofa",
                            "lv1"     : 120,
                            "sk2"     : "force",
                            "lv2"     : 120,
                            "gongxian": 600,
                            "neili"   : 1600,
                            "shen"    : 28000, ]));
                 break;
        case "穹外飛星" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/mantian-xing/xing",
                           "name"    : "穹外飛星",
                           "sk1"     : "mantian-xing",
                           "lv1"     : 60,
                           "force"   : 150,
                           "gongxian": 600,
                           "shen"    : 30000, ]));
                break;

       case "刀劍九重天" :
               return MASTER_D->teach_pfm(me, this_object(),
                       ([ "perform" : "can_perform/daojian-guizhen/jiu",
                          "name"    : "刀劍九重天",
                          "sk1"     : "daojian-guizhen",
                          "lv1"     : 1000,
                          "reborn"  : 1,
                          "force"   : 300,
                          "gongxian": 3000,
                          "shen"    : 30000, ]));
               break;

        default:
                return 0;
        }
}

/*
void unconcious()
{
        die();
}

*/
