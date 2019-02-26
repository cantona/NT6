//Room: /d/dali/garments.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","薛記成衣鋪");
        set("long", @LONG
這是一家老字號的估衣莊，裏面擺滿了各式各樣的衣物。綢、絹、
絲、布、皮襖、大紅鬥蓬、葱黃綾子棉裙、水綠色棉襖，秋香色團花。。。
不一而足。
LONG );
        set("objects", ([
           "/d/dali/npc/xueboss": 1,
        ]));
        set("exits",([ /* sizeof() == 1 */
            "south" : "/d/dali/taiheeast",
        ]));
	set("coor/x", -19120);
	set("coor/y", -6870);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}