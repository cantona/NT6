// Room:  /d/luoyang/dukang.c
// Last modified by winder 2002.11.11

inherit  ROOM;

void  create  ()
{
        set("short",  "杜康仙莊");
        set("long",  @LONG
杜康仙莊是酒祖造酒遺址，是酒文化發源地。“杜康仙莊”為周平
王封賜，位於洛陽東南一百里杜康村。山門是琉璃瓦的硃紅門樓，進入
莊內有杜康祠，爬山碑廊，雕欄池，櫻花圓和七賢台。
LONG);
        set("exits",  ([  /*  sizeof()  ==  2  */
                "north" : __DIR__"road7",
        ]));
        set("outdoors", "luoyang");
        set("no_clean_up", 0);
	set("coor/x", -6910);
	set("coor/y", 2130);
	set("coor/z", -10);
	setup();
        replace_program(ROOM);
}