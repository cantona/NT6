//Cracked by Kafei
// /d/huanghe/bangjob/bangjob20000.c
// by aln 2 / 98

// inherit SKILL;

inherit F_CLEAN_UP;

mapping *bangjobs = ({
        ([      "name"  :  "王五",
                "file"  :  "/d/city/npc/guidao",
                "area"  :  "揚州醉仙樓",
                "type"  :  "殺",
                "bonus" :  20,
                "score" :  6,
        ]),

        ([      "name"  :  "空空兒",
                "file"  :  "/d/city/npc/qigai.c",
                "area"  :  "揚州城",
                "type"  :  "殺",
                "bonus" :  50,
                "score" :  20,
        ]),

        ([      "name"  :  "常長風",
                "file"  :  "/d/forest/npc/chang",
                "area"  :  "揚州郊外",
                "type"  :  "殺",
                "bonus" :  40,
                "score" :  15,
        ]),

        ([      "name"  :  "花劍影",
                "file"  :  "/d/forest/npc/hua",
                "area"  :  "揚州郊外",
                "type"  :  "殺",
                "bonus" :  40,
                "score" :  15,
        ]),

        ([      "name"  :  "逍遙子",
                "file"  :  "/d/forest/npc/xiaoyaozi",
                "area"  :  "揚州郊外",
                "type"  :  "殺",
                "bonus" :  40,
                "score" :  15,
        ]),

        ([      "name"  :  "刀客",
                "file"  :  "/d/taishan/npc/dao-ke",
                "area"  :  "泰山",
                "type"  :  "殺",
                "bonus" :  10,
                "score" :  3,
        ]),

        ([      "name"  :  "劍客",
                "file"  :  "/d/taishan/npc/jian-ke",
                "area"  :  "泰山",
                "type"  :  "殺",
                "bonus" :  12,
                "score" :  3,
        ]),

        ([      "name"  :  "土匪頭",
                "file"  :  "/d/wudang/npc/tufeitou",
                "area"  :  "武當山",
                "type"  :  "殺",
                "bonus" :  50,
                "score" :  17,
        ]),

        ([      "name"  :  "廣陵散",
                "file"  :  "  ",
                "type"  :  "尋",
                "bonus" :  10,
                "score" :  3,
        ]),

        ([      "name"  :  "率意帖",
                "file"  :  "  ",
                "type"  :  "尋",
                "bonus" :  10,
                "score" :  3,
        ]),

        ([      "name"  :  "棋譜",
                "file"  :  "  ",
                "type"  :  "尋",
                "bonus" :  10,
                "score" :  3,
        ]),

        ([      "name"  :  "行旅圖",
                "file"  :  "  ",
                "type"  :  "尋",
                "bonus" :  10,
                "score" :  3,
        ]),

        ([      "type"  :  "截鏢",
        ]),

        ([      "type"  :  "截鏢",
        ]),
});

void create() { seteuid(getuid()); }

mapping query_job()
{
        return bangjobs[random(sizeof(bangjobs))];
}