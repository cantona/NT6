// qianting.c 前廳
// Java Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "前廳");
        set("long", @LONG
這裏是古墓的前廳，黑黝黝的，你幾乎什麼也看不清。全靠大廳
正中間的樑上懸掛着一顆夜明珠，映射出淡淡的黃光。廳柱都是由碩
大的石柱砌成的，上面似乎還寫着一些什麼字(zi)，昏暗中似是重陽
手筆。可你不仔細看怎麼也看不清楚。
LONG        );
        set("item_desc", ([
                "zi": "秋水為神玉為骨    芙蓉如面柳如眉\n"
        ]));
        set("objects", ([
                CLASS_D("gumu") + "/first" : 1,
        ]));
        set("exits", ([
                "west"  : __DIR__"mudao02",
                "east"  : __DIR__"mudao05",
                "south" : __DIR__"mudao04",
                "north" : __DIR__"mudao01",
        ]));
        set("coor/x", -3220);
        set("coor/y", 10);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}
