// Room: /d/ruzhou/yamen.c
// llm 1999/07/04

inherit ROOM;

void create()
{
        set("short", "汝州府衙門");
        set("long", @LONG
這裏便是汝州重鎮的衙門大門，朱木大柱，青瓦白牆，異常醒目。銅皮大門兩
邊擺動放着兩頭張牙舞爪的石獅子。前面照例都有一個大鼓，顯然是供小民鳴冤用
的。直看到去就可以看到知府做鎮的大堂。
LONG
        );
        set("exits", ([
           "south" : __DIR__"xidajie",
      "north" : __DIR__"yamen-datang",
        ]));
        set("objects", ([
        ]));

	set("coor/x", -6770);
	set("coor/y", 1870);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}