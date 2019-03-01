inherit ROOM;

void create()
{
        set("short", "私塾");
        set("long", @LONG
這裡是一家的私塾，窗明幾凈，一塵不染。一位莊重嚴肅的老先生坐
在太師椅上講學。在他的兩側坐滿了求學的學生。一張古意盎然的書案放
在老先生的前面，案上擺著幾本翻開了的線裝書籍。
LONG);
        set("no_clean_up", 0);
        set("exits", ([
                  "south" : __DIR__"eroad2",
                  "north" : __DIR__"mianbi",
        ]));
        set("objects", ([
                "/d/wudu/npc/xuetong" : 2,
                "/d/wudu/npc/xiansheng" : 1,
        ]));
	set("coor/x", -6970);
	set("coor/y", 2160);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}