#include <ansi.h>

mapping *quest = ({
        ([
                "id":          "jian seng",
                "name":        "劍僧",
                "type":        "殺",
                "bonus":       72,
                "msg":        "",
                "object":      "/d/tulong/yitian/npc/18jingang-5jian.c",
        ]),
        ([
                "id":          "gongye qian",
                "name":        "公冶乾",
                "type":        "殺",
                "bonus":       87,
                "msg":        "",
                "object":      "/d/yanziwu/npc/gongye.c",
        ]),
        ([
                "id":          "dao seng",
                "name":        "刀僧",
                "type":        "殺",
                "bonus":       74,
                "msg":        "",
                "object":      "/d/tulong/yitian/npc/18jingang-5dao.c",
        ]),
        ([
                "id":          "yu canghai",
                "name":        "餘滄海",
                "type":        "殺",
                "bonus":       105,
                "msg":        "",
                "object":      "/kungfu/class/qingcheng/yu.c",
        ]),
        ([
                "id":          "feng boe",
                "name":        "風波惡",
                "type":        "殺",
                "bonus":       73,
                "msg":        "",
                "object":      "/d/yanziwu/npc/feng.c",
        ]),
        ([
                "id":          "zhao banshan",
                "name":        "趙半山",
                "type":        "殺",
                "bonus":       105,
                "msg":        "",
                "object":      "/d/hangzhou/honghua/zhao.c",
        ]),
        ([
                "id":          "deng baichuan",
                "name":        "鄧百川",
                "type":        "殺",
                "bonus":       100,
                "msg":        "",
                "object":      "/d/yanziwu/npc/deng.c",
        ]),
        ([
                "id":          "bai zhen",
                "name":        "白振",
                "type":        "殺",
                "bonus":       70,
                "msg":        "",
                "object":      "/d/hangzhou/npc/baizhen.c",
        ]),
        ([
                "id":          "yuzhen zi",
                "name":        "玉真子",
                "type":        "殺",
                "bonus":       85,
                "msg":        "",
                "object":      "/d/guanwai/npc/yuzhenzi.c",
        ]),
        ([
        "id":          "fei bin",
                "name":        "費彬",
                "type":        "殺",
                "bonus":       85,
                "msg":        "",
                "object":      "/kungfu/class/songshan/fei.c",
        ]),
        ([
                "id":          "bao butong",
                "name":        "包不同",
                "type":        "殺",
                "bonus":       80,
                "msg":        "",
                "object":      "/d/yanziwu/npc/bao.c",
        ]),
        ([
                "id":          "mu wanqing",
                "name":        "木婉清",
                "type":        "殺",
                "bonus":       80,
                "msg":        "",
                "object":      "/d/wanjiegu/npc/mu.c",
        ]),
        ([
                "id":          "nv lang",
                "name":        "蒙面女郎",
                "type":        "殺",
                "bonus":       75,
                "msg":        "",
                "object":      "/d/lingjiu/npc/nvlang.c",
        ]),
        ([
                "id":          "lazhang huofo",
                "name":        "拉章活佛",
                "type":        "殺",
                "bonus":       72,
                "msg":        "",
                "object":      "/kungfu/class/xueshan/lazhang.c",
        ]),
        ([
                "id":          "sheng di",
                "name":        "勝諦",
                "type":        "殺",
                "bonus":       89,
                "msg":        "",
                "object":      "/kungfu/class/xuedao/shengdi.c",
        ]),
        ([
                "id":          "zhang danyue",
                "name":        "張淡月",
                "type":        "殺",
                "bonus":       82,
                "msg":        "",
                "object":      "/kungfu/class/shenlong/zhang.c",
        ]),
        ([
                "id":          "wugen daozhang",
                "name":        "無根道長",
                "type":        "殺",
                "bonus":       97,
                "msg":        "",
                "object":      "/kungfu/class/shenlong/wugen.c",
        ]),
        ([
                "id":          "su quan",
                "name":        "蘇荃",
                "type":        "殺",
                "bonus":       87,
                "msg":        "",
                "object":      "/kungfu/class/shenlong/su.c",
        ]),
        ([
                "id":          "yu hongxing",
                "name":        "餘洪興",
                "type":        "殺",
                "bonus":       80,
                "msg":        "",
                "object":      "/kungfu/class/gaibang/yu-hx.c",
        ]),
        ([
                "id":          "quan guanqing",
                "name":        "全冠清",
                "type":        "殺",
                "bonus":       75,
                "msg":        "",
                "object":      "/kungfu/class/gaibang/quan-gq.c",
        ]),
        ([
                "id":          "li sheng",
                "name":        "黎生",
                "type":        "殺",
                "bonus":       73,
                "msg":        "",
                "object":      "/kungfu/class/gaibang/li-sh.c",
        ]),
});
mapping query_questdg()
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
