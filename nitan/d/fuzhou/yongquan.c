// Room: /d/fuzhou/yongquan.c
// Date: May 12, 98  Java

inherit ROOM;

void create()
{
        set("short", "湧泉寺");
        set("long", @LONG
湧泉寺為閩中第一叢林。構築宏偉，氣勢磅礡，工藝精巧，冠絕一
時。寺東勝境靈源深處，懸崖峭壁，崢嶸奇巧，古樹參天，寧靜幽雅，
其中千載碑林，多朱熹、蔡襄遺墨。寺北絕頂峰，遠望東海煙波，近瞰
閩江流帶，福州平原一派田園風光盡收眼底。
LONG );
        set("exits", ([
                "south"    : __DIR__"gushan",
        ]));
        set("objects", ([
                "/d/hangzhou/npc/seng" : 1,
        ]));
        set("outdoors", "fuzhou");
        set("no_clean_up", 0);
	set("coor/x", -30);
	set("coor/y", -6170);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}