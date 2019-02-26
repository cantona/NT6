inherit ROOM;

void create()
{
        set("short", "西廂房");
        set("long", @LONG
這是縣太爺府裏供下人居住的地方。屋內沒什麼東西，只
有一張桌子和幾張竹凳。屋角的盆裏放着一大堆的衣服。有幾
個丫鬟沒事正在繡花。
LONG);
        set("exits", ([
                "east" : __DIR__"huayuan",
                                 
        ]));

        set("objects", ([
                __DIR__"npc/yahuan" : 2,
        ]));

        set("coor/x", -9080);
	set("coor/y", -970);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}