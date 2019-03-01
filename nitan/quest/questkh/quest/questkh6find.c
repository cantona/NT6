#include <ansi.h>

mapping *quest = ({
        ([
                "id":          "cloth",
                "name":        "淡黃衫",
                "type":        "尋",
                "bonus":       101,
                "msg1":        "",
                "object":      "/d/emei/obj/ycloth.c",
        ]),
        ([
                "id":          "leizhen dang",
                "name":        "雷震擋",
                "type":        "尋",
                "bonus":       101,
                "msg1":        "",
                "object":      "/d/heimuya/npc/obj/leizhendang.c",
        ]),
        ([
                "id":          "xuan tie",
                "name":        "[36m玄鐵石[2;37;0m",
                "type":        "尋",
                "bonus":       61,
                "msg1":        "",
                "object":      "/d/item/obj/xuantie.c",
        ]),
        ([
                "id":          "cloth",
                "name":        "熟羅長袍",
                "type":        "尋",
                "bonus":       72,
                "msg1":        "",
                "object":      "/d/henshan/npc/obj/luo_cloth.c",
        ]),
        ([
                "id":          "da fu",
                "name":        "大斧",
                "type":        "尋",
                "bonus":       101,
                "msg1":        "",
                "object":      "/d/heimuya/npc/obj/dafu.c",
        ]),
        ([
                "id":          "cloth",
                "name":        "白布長袍",
                "type":        "尋",
                "bonus":       72,
                "msg1":        "",
                "object":      "/d/mingjiao/obj/baipao.c",
        ]),
        ([
                "id":          "muyu",
                "name":        "木魚錘",
                "type":        "尋",
                "bonus":       72,
                "msg1":        "",
                "object":      "/d/wanjiegu/npc/obj/muyu.c",
        ]),
        ([
                "id":          "hong lian",
                "name":        HIR"小紅蓮"NOR,
                "type":        "尋",
                "bonus":       80,
                "msg1":        "",
                "object":      "/d/wudang/obj/honglian.c",
        ]),
        ([
                "id":          "ming zhu",
                "name":        "明珠",
                "type":        "尋",
                "bonus":       120,
                "msg1":        "",
                "object":      "/d/taohua/obj/mingzhu.c",
        ]),
        ([
                "id":          "buzhen xiang",
                "name":        "布陣箱",
                "type":        "尋",
                "bonus":       120,
                "msg1":        "",
                "object":      "/d/taohua/obj/xiang.c",
        ]),
        ([
                "id":          "zhuxiao",
                "name":        "竹簫",
                "type":        "尋",
                "bonus":       50,
                "msg1":        "",
                "object":      "/d/taohua/obj/zhuxiao.c",
        ]),
        ([
                "id":          "du jing1",
                "name":        "『星宿毒經□上冊□』",
                "type":        "尋",
                "bonus":       90,
                "msg1":        "",
                "object":      "/clone/book/dujing_1.c",
        ]),
        ([
                "id":          "qingxin san",
                "name":        "清心散",
                "type":        "尋",
                "bonus":       50,
                "msg1":        "",
                "object":      "/d/xingxiu/obj/xxqingxin-san.c",
        ]),
        ([
                "id":          "menghan yao",
                "name":        "蒙汗藥",
                "type":        "尋",
                "bonus":       50,
                "msg1":        "",
                "object":      "/d/xingxiu/obj/menghan_yao.c",
        ]),
        ([
                "id":          "mu ding",
                "name":        "木鼎",
                "type":        "尋",
                "bonus":       90,
                "msg1":        "",
                "object":      "/clone/misc/muding.c",
        ]),
        ([
                "id":          "lubo",
                "name":        BLU"顱砵"NOR,
                "type":        "尋",
                "bonus":       90,
                "msg1":        "",
                "object":      "/d/xueshan/obj/lubo.c",
        ]),
        ([
                "id":          "rentou lian",
                "name":        BLU"人頭鏈"NOR,
                "type":        "尋",
                "bonus":       90,
                "msg1":        "",
                "object":      "/d/xueshan/obj/rtlian.c",
        ]),
        ([
                "id":          "kulou guan",
                "name":        BLU"骷髏冠"NOR,
                "type":        "尋",
                "bonus":       90,
                "msg1":        "",
                "object":      "/d/xueshan/obj/klguan.c",
        ]),
        ([
                "id":          "qiankunbook",
                "name":        "羊皮",
                "type":        "尋",
                "bonus":       110,
                "msg1":        "",
                "object":      "/clone/book/qiankun_book.c",
        ]),
        ([
                "id":          "yi xin",
                "name":        "陽教主遺信",
                "type":        "尋",
                "bonus":       110,
                "msg1":        "",
                "object":      "/d/mingjiao/obj/yixin.c",
        ]),
        ([
                "id":          "baixiang hua",
                "name":        "[1;32m百香花[2;37;0m",
                "type":        "尋",
                "bonus":       90,
                "msg1":        "",
                "object":      "/d/shenlong/obj/hua.c",
        ]),
        ([
                "id":          "jinshe jian",
                "name":        "[33m金蛇劍[2;37;0m",
                "type":        "尋",
                "bonus":       120,
                "msg1":        "",
                "object":      "/clone/lonely/jinshejian.c",
        ]),
        ([
                "id":          "duanchang hua",
                "name":        "[1;31m斷腸花[2;37;0m",
                "type":        "尋",
                "bonus":       90,
                "msg1":        "",
                "object":      "/d/shenlong/obj/hua3.c",
        ]),
        ([
                "id":          "shenghuo ling",
                "name":        "[36m聖火令[2;37;0m",
                "type":        "尋",
                "bonus":       84,
                "msg1":        "",
                "object":      "/d/tulong/tulong/obj/ling1.c",
        ]),
        ([
                "id":          "jiasha",
                "name":        "[30m黑色袈裟[2;37;0m",
                "type":        "尋",
                "bonus":       86,
                "msg1":        "",
                "object":      "/d/xueshan/obj/b-jiasha.c",
        ]),
        ([
                "id":          "bosi cloth",
                "name":        "[35m波斯明教教服[2;37;0m",
                "type":        "尋",
                "bonus":       84,
                "msg1":        "",
                "object":      "/d/tulong/yitian/npc/obj/jiaofu.c",
        ]),
        ([
                "id":          "jia sha",
                "name":        "護法袈裟",
                "type":        "尋",
                "bonus":       72,
                "msg1":        "",
                "object":      "/d/shaolin/obj/xuan-cloth.c",
        ]),
        ([
                "id":          "cloth",
                "name":        "[1;33m一品侍衛裝[2;37;0m",
                "type":        "尋",
                "bonus":       72,
                "msg1":        "",
                "object":      "/d/beijing/npc/obj/guanfu2.c",
        ]),
        ([
                "id":          "huang magua",
                "name":        "[1;33m黃馬褂[2;37;0m",
                "type":        "尋",
                "bonus":       72,
                "msg1":        "",
                "object":      "/d/beijing/npc/obj/goldcloth1.c",
        ]),
        ([
                "id":          "cloth",
                "name":        "[1;34m青布長衫[2;37;0m",
                "type":        "尋",
                "bonus":       95,
                "msg1":        "",
                "object":      "/d/beijing/npc/obj/cloth1.c",
        ]),
});
mapping query_questkh()
{
        int i;
        mapping the_quest,random_quest;
        string *quest_key;

        random_quest = quest[random(sizeof(quest))];
        the_quest = ([]);

        quest_key = keys(random_quest);
        for (i = 0;i < sizeof(quest_key);i++)
                the_quest[quest_key[i]] = random_quest[quest_key[i]];

        return the_quest;
}
