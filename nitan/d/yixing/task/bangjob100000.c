//Cracked by Kafei
// /d/huanghe/bangjob/bangjob100000.c

// inherit SKILL;

inherit F_CLEAN_UP;

mapping *bangjobs = ({
        ([      "name"  :  "蕭半和",
                "file"  :  "/d/forest/npc/banhe",
                "area"  :  "揚州郊外",
                "type"  :  "殺",
                "bonus" :  50,
                "score" :  15,
        ]),

        ([      "name"  :  "侯通海",
                "file"  :  "/d/huanghe/npc/hou-tonghai",
                "area"  :  "黃河岸邊",
                "type"  :  "殺",
                "bonus" :  30,
                "score" :  10,
        ]),

        ([      "name"  :  "戚長髮",
                "file"  :  "/d/foshan/npc/changfa",
                "area"  :  "湘西",
                "type"  :  "殺",
                "bonus" :  30,
                "score" :  10,
        ]),

        ([      "name"  :  "黃鐘公",
                "file"  :  "/d/jiaxing/npc/huang",
                "area"  :  "杭州梅莊",
                "type"  :  "殺",
                "bonus" :  75,
                "score" :  25,
        ]),

        ([      "name"  :  "黑白子",
                "file"  :  "/d/jiaxing/npc/heibai",
                "area"  :  "杭州梅莊",
                "type"  :  "殺",
                "bonus" :  70,
                "score" :  20,
        ]),

        ([      "name"  :  "禿筆翁",
                "file"  :  "/d/jiaxing/npc/tubiweng",
                "area"  :  "杭州梅莊",
                "type"  :  "殺",
                "bonus" :  65,
                "score" :  20,
        ]),

        ([      "name"  :  "丹青生",
                "file"  :  "/d/jiaxing/npc/danqing",
                "area"  :  "杭州梅莊",
                "type"  :  "殺", 
                "bonus" :  60,
                "score" :  17,
        ]),

        ([      "name"  :  "丁堅",
                "file"  :  "/d/jiaxing/npc/dingjian",
                "area"  :  "杭州梅莊",
                "type"  :  "殺",
                "bonus" :  45,
                "score" :  10,
        ]),

        ([      "name"  :  "施令威",
                "file"  :  "/d/jiaxing/npc/shilingwei",
                "area"  :  "杭州梅莊",
                "type"  :  "殺",
                "bonus" :  40,
                "score" :  10,
        ]),

        ([      "name"  :  "陸冠英",
                "file"  :  "/d/taihu/npc/guanying",
                "area"  :  "歸雲莊",
                "type"  :  "殺",
                "bonus" :  60,
                "score" :  20,
        ]),

        ([      "type"  :  "截鏢",
        ]),

        ([      "type"  :  "截鏢",
        ]),

        ([      "type"  :  "截鏢",
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

        ([      "type"  :  "示威",
        ]),

        ([      "type"  :  "示威",
        ]),

        ([      "type"  :  "示威",
        ]),
});

void create() { seteuid(getuid()); }

mapping query_job()
{
        return bangjobs[random(sizeof(bangjobs))];
}
