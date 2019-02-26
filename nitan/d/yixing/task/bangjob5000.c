//Cracked by Kafei
// /d/huanghe/changle/bangjob5000.c
// by aln 2 / 98

// inherit SKILL;

inherit F_CLEAN_UP;

mapping *bangjobs = ({
        ([      "name"  :  "回回",
                "file"  :  "/d/quanzhou/npc/huihui",
                "area"  :  "泉州",
                "type"  :  "殺",
                "bonus" :  18,
                "score" :  4,
        ]),

        ([      "name"  :  "塘工",
                "file"  :  "/d/hangzhou/npc/tbbz",
                "area"  :  "杭州灣海堤",
                "type"  :  "殺",
                "bonus" :  15,
                "score" :  3,
        ]),

        ([      "name"  :  "海沙派鹽梟",
                "file"  :  "/d/hangzhou/npc/hsbz",
                "area"  :  "杭州灣鹽田",
                "type"  :  "殺",
                "bonus" :  18,
                "score" :  5,
        ]),

        ([      "name"  :  "天鷹教眾",
                "file"  :  "/d/hangzhou/npc/tyjz",
                "area"  :  "杭州灣海神廟",
                "type"  :  "殺",
                "bonus" :  20,
                "score" :  5,
        ]),

        ([      "type"  :  "買賣",
        ]),

        ([      "type"  :  "買賣",
        ]),

        ([      "type"  :  "買賣",
        ]),

        ([      "type"  :  "買賣",
        ]),

        ([      "type"  :  "夥計",
        ]),

        ([      "type"  :  "夥計",
        ]),
});

void create() { seteuid(getuid()); }

mapping query_job()
{
        return bangjobs[random(sizeof(bangjobs))];
}

