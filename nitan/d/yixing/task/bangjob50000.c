//Cracked by Kafei
// /d/huanghe/changle/bangjob50000.c

// inherit SKILL;

inherit F_CLEAN_UP;

mapping *bangjobs = ({
        ([      "name"  :  "哈薩克",
                "file"  :  "/d/xingxiu/npc/hasake",
                "area"  :  "天山腳下",
                "type"  :  "殺",
                "bonus" :  15,
                "score" :  4,
        ]), 

        ([      "name"  :  "袁冠男",
                "file"  :  "/d/forest/npc/guannan",
                "area"  :  "揚州郊外",
                "type"  :  "殺",
                "bonus" :  40,
                "score" :  12,
        ]), 

        ([      "name"  :  "林玉龍",
                "file"  :  "/d/forest/npc/lin",
                "area"  :  "揚州郊外",
                "type"  :  "殺",
                "bonus" :  40,
                "score" :  12,
        ]),

        ([      "name"  :  "任飛燕",
                "file"  :  "/d/forest/npc/ren",
                "area"  :  "揚州郊外",
                "type"  :  "殺",
                "bonus" :  40,
                "score" :  12,
        ]),

        ([      "name"  :  "祖千秋",
                "file"  :  "/d/huanghe/npc/qiu",
                "area"  :  "黃河岸邊",
                "type"  :  "殺",
                "bonus" :  25,
                "score" :  6,
        ]),

        ([      "name"  :  "蕭中慧",
                "file"  :  "/d/forest/npc/zhonghui",
                "area"  :  "揚州郊外",
                "type"  :  "殺",
                "bonus" :  40,
                "score" :  12,
        ]),

        ([      "name"  :  "向問天",
                "file"  :  "/d/jiaxing/npc/xiang",
                "area"  :  "揚州郊外",
                "type"  :  "殺",
                "bonus" :  60,
                "score" :  20,
        ]),

        ([      "name"  :  "賈人達",
                "file"  :  "/d/quanzhou/npc/jiarenda",
                "area"  :  "泉州山路",
                "type"  :  "殺",
                "bonus" :  30,
                "score" :  10,
        ]),

        ([      "type"  :  "截鏢",
        ]),

        ([      "type"  :  "截鏢",
        ]),

        ([      "type"  :  "截鏢",
        ]),

        ([      "type"  :  "截鏢",
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
