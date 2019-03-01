//Cracked by Kafei
// /d/huanghe/changle/bangjob3000.c
// by aln 2 / 98

// inherit SKILL;

inherit F_CLEAN_UP;

mapping *bangjobs = ({
        ([      "name"  :  "進香客",
                "file"  :  "/d/emei/npc/xiang-ke",
                "area"  :  "峨眉山",
                "type"  :  "殺",
                "bonus" :  8,
                "score" :  2,
        ]),

        ([      "name"  :  "皮貨商",
                "file"  :  "/d/changbai/npc/phshang",
                "area"  :  "長白山集市",
                "type"  :  "殺",
                "bonus" :  10,
                "score" :  3,
        ]),

        ([      "name"  :  "胖商人",
                "file"  :  "/d/foshan/npc/pang",
                "area"  :  "佛山鎮",
                "type"  :  "殺",
                "bonus" :  5,
                "score" :  1,
        ]),

        ([      "name"  :  "瘦商人",
                "file"  :  "/d/foshan/npc/shou",
                "area"  :  "佛山鎮",
                "type"  :  "殺",
                "bonus" :  5,
                "score" :  1,
        ]),

        ([      "name"  :  "小販",
                "file"  :  "/d/quanzhou/npc/mao-fan",
                "area"  :  "泉州中心廣場",
                "type"  :  "殺",
                "bonus" :  6,
                "score" :  2,
        ]),

        ([      "name"  :  "野菊花",
                "file"  :  "/d/city/obj/juhua",
                "type"  :  "尋",
                "bonus" :  3,
                "score" :  1,
        ]),

        ([      "name"  :  "狗皮",
                "file"  :  "/d/city/obj/goupi",
                "type"  :  "尋",
                "bonus" :  3,
                "score" :  1,
        ]),

        ([      "type"  :  "攤費",
        ]),

        ([      "type"  :  "攤費",
        ]),

        ([      "type"  :  "攤費",
        ]),

        ([      "type"  :  "攤費",
        ]),

        ([      "type"  :  "攤費",
        ]),

        ([      "type"  :  "攤費",
        ]),

        ([      "type"  :  "攤費",
        ]),

        ([      "type"  :  "攤費",
        ]),

        ([      "type"  :  "買賣",
        ]),

        ([      "type"  :  "買賣",
        ]),

        ([      "type"  :  "買賣",
        ]),

        ([      "type"  :  "買賣",
        ]),

        ([      "type"  :  "買賣",
        ]),

        ([      "type"  :  "買賣",
        ]),

        ([      "type"  :  "買賣",
        ]),

        ([      "type"  :  "買賣",
        ]),

        ([      "type"  :  "伙計",
        ]),

        ([      "type"  :  "伙計",
        ]),

        ([      "type"  :  "伙計",
        ]),

        ([      "type"  :  "伙計",
        ]),

        ([      "type"  :  "伙計",
        ]),

        ([      "type"  :  "伙計",
        ]),

        ([      "type"  :  "伙計",
        ]),

        ([      "type"  :  "伙計",
        ]),
});

void create() { seteuid(getuid()); }

mapping query_job()
{
        return bangjobs[random(sizeof(bangjobs))];
}


