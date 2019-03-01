//Cracked by Kafei
// /d/huanghe/bangjob/bangjob300000.c
// by aln / 98

// inherit SKILL;

inherit F_CLEAN_UP;

mapping *bangjobs = ({
        ([      "name"  :  "寶樹",
                "file"  :  "/d/foshan/npc/baoshu",
                "area"  :  "少林寺",
                "type"  :  "殺",
                "bonus" :  40,
                "score" :  12,
        ]),

        ([      "name"  :  "樑子翁",
                "file"  :  "/d/huanghe/npc/liang-ziweng",
                "area"  :  "黃河幫",
                "type"  :  "殺",
                "bonus" :  70,
                "score" :  30,
        ]),

        ([      "name"  :  "日本浪人",
                "file"  :  "/d/quanzhou/npc/langren",
                "area"  :  "泉州",
                "type"  :  "殺",
                "bonus" :  30,
                "score" :  7,
        ]),

        ([      "name"  :  "楊鐵心",
                "file"  :  "/d/hangzhou/npc/yang",
                "area"  :  "牛家村",
                "type"  :  "殺",
                "bonus" :  30,
                "score" :  10,
        ]),

        ([      "name"  :  "郭嘯天",
                "file"  :  "/d/hangzhou/npc/guo",
                "area"  :  "牛家村",
                "type"  :  "殺",
                "bonus" :  30,
                "score" :  10,
        ]),

        ([      "name"  :  "虎骨",
                "file"  :  "  ",
                "type"  :  "尋",
                "bonus" :  30,
                "score" :  10,
        ]),

        ([      "name"  :  "熊膽",
                "file"  :  "  ",
                "type"  :  "尋",
                "bonus" :  40,
                "score" :  12,
        ]),

        ([      "name"  :  "指環",
                "file"  :  "  ",
                "type"  :  "尋",
                "bonus" :  25,
                "score" :  10,
        ]),

        ([      "type"  :  "示威",
        ]),

        ([      "type"  :  "示威",
        ]),

        ([      "type"  :  "示威",
        ]),

        ([      "type"  :  "示威",
        ]),

        ([      "type"  :  "示威",
        ]),

        ([      "type"  :  "送禮",
        ]),

        ([      "type"  :  "送禮",
        ]),

        ([      "type"  :  "送禮",
        ]),

        ([      "type"  :  "送禮",
        ]),

        ([      "type"  :  "送禮",
        ]),
});

void create() { seteuid(getuid()); }

mapping query_job()
{
        return bangjobs[random(sizeof(bangjobs))];
}