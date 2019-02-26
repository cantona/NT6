#include <ansi.h>

mapping *quest = ({
        ([
                "id":          "fuchen",
                "name":        "拂塵",
                "type":        "尋",
                "bonus":       62,
                "msg1":        "",
                "object":      "/d/dali/obj/fuchen.c",
        ]),
        ([
                "id":          "putuan",
                "name":        "小蒲團",
                "type":        "尋",
                "bonus":       50,
                "msg1":        "",
                "object":      "/d/xiaoyao/obj/putuan.c",
        ]),
        ([
                "id":          "dress",
                "name":        "[1;37m梨花飄雪裳[2;37;0m",
                "type":        "尋",
                "bonus":       75,
                "msg1":        "",
                "object":      "/d/wanjiegu/npc/obj/pink-dress.c",
        ]),
        ([
                "id":          "key",
                "name":        "鑰匙",
                "type":        "尋",
                "bonus":       68,
                "msg1":        "",
                "object":      "/d/lingjiu/obj/key.c",
        ]),
        ([
                "id":          "xuan tie",
                "name":        "[36m玄鐵石[2;37;0m",
                "type":        "尋",
                "bonus":       100,
                "msg1":        "",
                "object":      "/d/item/obj/xuantie.c",
        ]),
        ([
                "id":          "qing xin",
                "name":        "信",
                "type":        "尋",
                "bonus":       70,
                "msg1":        "",
                "object":      "/d/heimuya/npc/obj/letter.c",
        ]),
        ([
                "id":          "cloth",
                "name":        "布衣",
                "type":        "尋",
                "bonus":       70,
                "msg1":        "",
                "object":      "/d/heimuya/npc/obj/cloth.c",
        ]),
        ([
                "id":          "huang shan",
                "name":        "[1;33m黃衫[2;37;0m",
                "type":        "尋",
                "bonus":       80,
                "msg1":        "",
                "object":      "/d/hangzhou/honghua/obj/huangshan.c",
        ]),
        ([
                "id":          "qing yi",
                "name":        "青衣",
                "type":        "尋",
                "bonus":       75,
                "msg1":        "",
                "object":      "/d/lingjiu/obj/qingyi.c",
        ]),
        ([
                "id":          "dou peng",
                "name":        "斗篷",
                "type":        "尋",
                "bonus":       75,
                "msg1":        "",
                "object":      "/d/lingjiu/obj/doupeng.c",
        ]),
        ([
                "id":          "18 muou",
                "name":        "十八木偶",
                "type":        "尋",
                "bonus":       70,
                "msg1":        "",
                "object":      "/clone/book/18muou.c",
        ]),
        ([
                "id":          "18 niou",
                "name":        "十八泥偶",
                "type":        "尋",
                "bonus":       70,
                "msg1":        "",
                "object":      "/clone/book/18niou.c",
        ]),
        ([
                "id":          "jiuyin zhenjing1",
                "name":        "「九陰真經」上冊",
                "type":        "尋",
                "bonus":       90,
                "msg1":        "",
                "object":      "/clone/book/jiuyin1.c",
        ]),
        ([
                "id":          "jiuyin zhenjing2",
                "name":        "「九陰真經」下冊",
                "type":        "尋",
                "bonus":       90,
                "msg1":        "",
                "object":      "/clone/book/jiuyin2.c",
        ]),
        ([
                "id":          "jin",
                "name":        "金絲甲",
                "type":        "尋",
                "bonus":       70,
                "msg1":        "",
                "object":      "/d/heimuya/npc/obj/jin.c",
        ]),
        ([
                "id":          "silk",
                "name":        "薄絹",
                "type":        "尋",
                "bonus":       85,
                "msg1":        "",
                "object":      "/clone/book/book-silk.c",
        ]),
        ([
                "id":          "jian pu",
                "name":        "天羽奇劍劍譜",
                "type":        "尋",
                "bonus":       85,
                "msg1":        "",
                "object":      "/clone/book/qijianpu.c",
        ]),
        ([
                "id":          "short sword",
                "name":        "[1;36m短劍[2;37;0m",
                "type":        "尋",
                "bonus":       80,
                "msg1":        "",
                "object":      "/d/hangzhou/honghua/obj/shortsword.c",
        ]),
        ([
                "id":          "cui yu",
                "name":        "[1;32m翠羽[2;37;0m",
                "type":        "尋",
                "bonus":       80,
                "msg1":        "",
                "object":      "/d/hangzhou/honghua/obj/cuiyu.c",
        ]),
        ([
                "id":          "armor",
                "name":        "鐵甲",
                "type":        "尋",
                "bonus":       65,
                "msg1":        "",
                "object":      "/d/city/obj/tiejia.c",
        ]),
        ([
                "id":          "duanjian",
                "name":        "短劍",
                "type":        "尋",
                "bonus":       92,
                "msg1":        "",
                "object":      "/d/city/obj/duanjian.c",
        ]),
        ([
                "id":          "gang jian",
                "name":        "[1;37m鋼劍[2;37;0m",
                "type":        "尋",
                "bonus":       67,
                "msg1":        "",
                "object":      "/d/beijing/npc/obj/sword2.c",
        ]),
        ([
                "id":          "tie di",
                "name":        "[1;34m鐵笛[2;37;0m",
                "type":        "尋",
                "bonus":       92,
                "msg1":        "",
                "object":      "/kungfu/class/dali/obj/tiedi.c",
        ]),
        ([
                "id":          "zi pao",
                "name":        "[35m紫袍[2;37;0m",
                "type":        "尋",
                "bonus":       92,
                "msg1":        "",
                "object":      "/kungfu/class/dali/obj/magcloth.c",
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
