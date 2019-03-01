// This program is a part of NT MudLIB
// xuan-ci.c 玄慈大師

#include <ansi.h>
inherit NPC;
inherit F_MASTER;
inherit F_QUESTER;

#define        IS_XUAN_CI        1

#include "xuan.h"

mixed ask_wldh();
void create()
{
        set_name("玄慈大師", ({
                "xuanci dashi",
                "xuanci",
                "dashi",
        }));
        set("long",
                "他是一位白須白眉的老僧，身穿一襲金絲繡紅袈裟。\n"
                "他身材略顯佝僂，但卻滿面紅光，目蘊慈笑，顯得神完氣足。\n"
        );

        set("nickname", "少林寺方丈");
        set("gender", "男性");
        set("attitude", "friendly");
        set("class", "bonze");

        set("age", 70);
        set("shen_type", 1);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("max_qi", 2800);
        set("max_jing", 1400);
        set("neili", 3800);
        set("max_neili", 3800);
        set("jiali", 50);
        set("level", 20);
        set("combat_exp", 1450000);
        set("score", 500000);

        set_skill("force", 170);
        set_skill("hunyuan-yiqi", 170);
        set_skill("dodge", 160);
        set_skill("shaolin-shenfa", 160);
        set_skill("finger", 170);
        set_skill("strike", 170);
        set_skill("hand", 160);
        set_skill("claw", 160);
        set_skill("parry", 160);
        set_skill("nianhua-zhi", 170);
        set_skill("sanhua-zhang", 170);
        set_skill("fengyun-shou", 160);
        set_skill("longzhua-gong", 160);
        set_skill("buddhism", 160);
        set_skill("literate", 160);
        set_skill("medical", 180);
        set_skill("shaolin-yishu", 180);
        set_skill("martial-cognize", 120);

        map_skill("force", "hunyuan-yiqi");
        map_skill("dodge", "shaolin-shenfa");
        map_skill("finger", "nianhua-zhi");
        map_skill("strike", "sanhua-zhang");
        map_skill("hand", "fengyun-shou");
        map_skill("claw", "longzhua-gong");
        map_skill("parry", "nianhua-zhi");

        prepare_skill("finger", "nianhua-zhi");
        prepare_skill("strike", "sanhua-zhang");

        create_family("少林派", 36, "弟子");

        set("master_ob",4);
        setup();

        carry_object("/d/shaolin/obj/xuan-cloth")->wear();
}

void init()
{
        object ob;

        ::init();
        if( interactive(ob = this_player()) && !is_fighting() &&
            query_temp("juxianzhuang_step", ob) == 4){
                set("inquiry/武林大會", (: ask_wldh :));
                set("inquiry/聚賢莊", (: ask_wldh :));
        }
}

mixed ask_wldh()
{
        object me = this_player();

        if( (int)query_temp("in_speech")
         || query_temp("juxianzhuang_step", me) != 4 )
                return notify_fail("玄慈大師很迷惑的看了看你。。。\n");

        set_temp("in_speech", 1);
        remove_call_out("say_msg");
        call_out("say_msg", 1, me, 1);
        return CYN"阿彌陀佛，施主來我少林的目的老衲已經猜到了。可惜老衲身在紅塵外，不問紅塵事了，阿彌陀佛……" NOR;
}

int say_msg(object me, int index)
{
        object ob;

        if( environment() != environment(me) )
                return 0;

        switch( index ) {
        case(1):
                message_vision(CYN"$N說道：阿彌陀佛，老衲當年犯下無數罪孽，終此一生，可能也難以補償，哪裡還能再去過問紅塵中的腥風血雨啊。\n"NOR, this_object(), me);
                break;
        case(2):
                message_vision(WHT"<$N一臉拒人千裡的模樣，于是$n開始發揮你舌粲蓮花、才辯無雙的本領。>\n"NOR, this_object(), me);
                break;
        case(3):
                message_vision(CYN"$N說道：唉，既然徐長老和施主誠心相邀，那好吧，到武林大會那日我會派玄難、玄寂兩位師弟前去聚賢莊，代表少林派參加大會。\n"NOR, this_object(), me);
                break;
        case(4):
                message_vision(CYN"$N說道：人緣常滿，歡喜無量，阿彌托佛，善哉善哉！施主若無其他事情，可以回洛陽將我的意思轉達(report)給徐長老了。\n"NOR, this_object(), me);
                break;
        case(5):
                message_vision(WHT"<$N說完後便閉目入定，獨自誦起佛經。>\n"NOR, this_object(), me);
                break;
        case(6):
                message_vision(CYN"$N念道：我獨經行時，見佛在大眾，名聞滿十方，廣饒益眾生。自惟失此利，我為自欺誑。\n"NOR, this_object(), me);
                break;
        case(7):
                message_vision(CYN"$N念道：我常于日夜，每思惟是事，欲以問世尊，為失為不失，我常見世尊，稱讚諸菩薩，以是于日夜，籌量此是事……。\n"NOR, this_object(), me);
                break;
        default:
                set_temp("juxianzhuang_step", 5, me);
                delete("inquiry/武林大會");
                delete("inquiry/聚賢莊");
                delete_temp("in_speech");
                return 1;
        }
        remove_call_out("say_msg");
        call_out("say_msg", 0, me,++index);
        return 1;
}

int accept_ask(object me, string topic)
{
        switch (topic)
        {
        case "歷練" :
        case "歷煉" :
        case "鍛煉" :
                return QUEST_D->accept_ask(this_object(), me, topic);
                break;

        case "一葦渡江" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/shaolin-shenfa/du",
                           "name"    : "一葦渡江",
                           "sk1"     : "shaolin-shenfa",
                           "lv1"     : 100,
                           "sk2"     : "dodge",
                           "lv2"     : 100,
                           "gongxian": 1000, ]));
                break;

        case "羅漢降魔" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/luohan-quan/xiangmo",
                           "name"    : "羅漢降魔",
                           "sk1"     : "luohan-quan",
                           "lv1"     : 100,
                           "sk2"     : "buddhism",
                           "lv2"     : 100,
                           "gongxian": 200, ]));
                break;

        case "大金剛神通" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/jingang-quan/jingang",
                           "name"    : "大金剛神通",
                           "sk1"     : "jingang-quan",
                           "lv1"     : 100,
                           "sk2"     : "buddhism",
                           "lv2"     : 100,
                           "gongxian": 600, ]));
                break;

        case "拈花拂穴" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/nianhua-zhi/fuxue",
                           "name"    : "拈花拂穴",
                           "sk1"     : "nianhua-zhi",
                           "lv1"     : 150,
                           "sk2"     : "force",
                           "lv2"     : 150,
                           "gongxian": 600, ]));
                break;

        case "驚魔一指" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/yizhi-chan/jingmo",
                           "name"    : "驚魔一指",
                           "sk1"     : "yizhi-chan",
                           "lv1"     : 150,
                           "sk2"     : "force",
                           "lv2"     : 150,
                           "gongxian": 600, ]));
                break;

        case "指點江山" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/yizhi-chan/dian",
                           "name"    : "指點江山",
                           "sk1"     : "yizhi-chan",
                           "lv1"     : 150,
                           "sk2"     : "force",
                           "lv2"     : 150,
                           "gongxian": 600, ]));
                break;

        case "無色無相" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/wuxiang-zhi/wuse",
                           "name"    : "無色無相",
                           "sk1"     : "wuxiang-zhi",
                           "lv1"     : 120,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "gongxian": 400, ]));
                break;

        case "修羅索命指" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/xiuluo-zhi/jueming",
                           "name"    : "修羅索命指",
                           "sk1"     : "xiuluo-zhi",
                           "lv1"     : 150,
                           "sk2"     : "force",
                           "lv2"     : 150,
                           "gongxian": 800, ]));
                break;

        case "金剛伏魔決" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/jingang-zhi/fumo",
                           "name"    : "金剛伏魔決",
                           "sk1"     : "jingang-zhi",
                           "lv1"     : 150,
                           "sk2"     : "buddhism",
                           "lv2"     : 200,
                           "gongxian": 600, ]));
                break;

        case "一指點三脈" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/jingang-zhi/san",
                           "name"    : "一指點三脈",
                           "sk1"     : "jingang-zhi",
                           "lv1"     : 200,
                           "sk2"     : "jingluo-xue",
                           "lv2"     : 200,
                           "gongxian": 1000, ]));
                break;

        case "菩提寂滅" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/duoluoye-zhi/jimie",
                           "name"    : "菩提寂滅",
                           "sk1"     : "duoluoye-zhi",
                           "lv1"     : 150,
                           "sk2"     : "buddhism",
                           "lv2"     : 200,
                           "gongxian": 1000, ]));
                break;

        case "封魔" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/banruo-zhang/feng",
                           "name"    : "封魔",
                           "sk1"     : "banruo-zhang",
                           "lv1"     : 100,
                           "sk2"     : "buddhism",
                           "lv2"     : 100,
                           "gongxian": 300, ]));
                break;

        case "天女散花" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/sanhua-zhang/san",
                           "name"    : "天女散花",
                           "sk1"     : "sanhua-zhang",
                           "lv1"     : 120,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "gongxian": 500, ]));
                break;

        case "群山疊影" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/xumishan-zhang/ying",
                           "name"    : "群山疊影",
                           "sk1"     : "xumishan-zhang",
                           "lv1"     : 120,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "gongxian": 500, ]));
                break;

        case "威震八方" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/shenzhang-bada/bafang",
                           "name"    : "威震八方",
                           "sk1"     : "shenzhang-bada",
                           "lv1"     : 120,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "gongxian": 500, ]));
                break;

        case "擒拿" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/fengyun-shou/qinna",
                           "name"    : "擒拿",
                           "sk1"     : "fengyun-shou",
                           "lv1"     : 120,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "gongxian": 400, ]));
                break;

        case "千葉佛手" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/qianye-shou/qianye",
                           "name"    : "千葉佛手",
                           "sk1"     : "qianye-shou",
                           "lv1"     : 120,
                           "sk2"     : "force",
                           "lv2"     : 120,
                           "gongxian": 400, ]));
                break;

        case "神龍抓" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/longzhua-gong/zhua",
                           "name"    : "神龍抓",
                           "sk1"     : "longzhua-gong",
                           "lv1"     : 150,
                           "sk2"     : "force",
                           "lv2"     : 150,
                           "gongxian": 1000, ]));
                break;

        case "盪妖除魔" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/yingzhua-gong/chumo",
                           "name"    : "盪妖除魔",
                           "sk1"     : "yingzhua-gong",
                           "lv1"     : 150,
                           "sk2"     : "force",
                           "lv2"     : 150,
                           "gongxian": 600, ]));
                break;

        case "佛心劍" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/fumo-jian/foxin",
                           "name"    : "佛心劍",
                           "sk1"     : "fumo-jian",
                           "lv1"     : 150,
                           "sk2"     : "force",
                           "lv2"     : 150,
                           "gongxian": 700, ]));
                break;

        case "修羅索命" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/xiuluo-dao/suoming",
                           "name"    : "修羅索命",
                           "sk1"     : "xiuluo-dao",
                           "lv1"     : 150,
                           "sk2"     : "force",
                           "lv2"     : 150,
                           "gongxian": 500, ]));
                break;

        case "舍身喂鷹" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/cibei-dao/sheshen",
                           "name"    : "舍身喂鷹",
                           "sk1"     : "cibei-dao",
                           "lv1"     : 150,
                           "sk2"     : "force",
                           "lv2"     : 150,
                           "gongxian": 400, ]));
                break;

        case "無常五化" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/wuchang-zhang/wuchang",
                           "name"    : "無常五化",
                           "sk1"     : "wuchang-zhang",
                           "lv1"     : 150,
                           "sk2"     : "force",
                           "lv2"     : 150,
                           "gongxian": 400, ]));
                break;

        case "佛光普照" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/pudu-zhang/zhao",
                           "name"    : "佛光普照",
                           "sk1"     : "pudu-zhang",
                           "lv1"     : 150,
                           "sk2"     : "force",
                           "lv2"     : 150,
                           "sk3"     : "buddhism",
                           "lv3"     : 200,
                           "gongxian": 400, ]));
                break;

        case "八仙醉打" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/zui-gun/zuida",
                           "name"    : "八仙醉打",
                           "sk1"     : "zui-gun",
                           "lv1"     : 150,
                           "sk2"     : "force",
                           "lv2"     : 150,
                           "gongxian": 400, ]));
                break;

        case "韋陀伏魔" :
                return MASTER_D->teach_pfm(me, this_object(),
                        ([ "perform" : "can_perform/weituo-gun/fumo",
                           "name"    : "韋陀伏魔",
                           "sk1"     : "weituo-gun",
                           "lv1"     : 150,
                           "sk2"     : "buddhism",
                           "lv2"     : 150,
                           "gongxian": 400, ]));
                break;

        default:
                return 0;
        }
}
