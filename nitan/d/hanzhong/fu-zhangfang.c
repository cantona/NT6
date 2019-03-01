// fu-zhangfang 帳房
// Winder Oct.10 1998

inherit ROOM;

void create()
{
        set("short", "帳房");
        set("long", @LONG
這裡是侯員外家的帳房。屋內青磚舖地，進門處橫擺著一張桌
子，一個管家正坐在桌後，小眼睛不住地跟著你轉，好象又在打什
麼壞主意。
LONG
        );
        set("exits", ([
                "east" : __DIR__"fu-datang",
        ]));
        set("objects", ([
                __DIR__"npc/guanjia" : 1,
        ]));

        set("coor/x", -12250);
	set("coor/y", 780);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}