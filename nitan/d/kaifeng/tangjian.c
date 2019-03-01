inherit ROOM;

void create()
{
        set("short", "堂間");
        set("long", @LONG
一間四方的堂間，正中的供桌後還擺著尊殘缺的佛像，由于缺了
半個腦袋，加上半身被蜘蛛網罩住了，也看不出原來的模樣。一邊的
柱子旁打了個地舖，靠牆擺著幾個水罐。
LONG );
        set("objects", ([
                  __DIR__"npc/oldseng" : 1,
        ]));
        set("no_clean_up", 0);
        set("exits", ([
                  "west" : __DIR__"kongdi",
        ]));

	set("coor/x", -4970);
	set("coor/y", 2210);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}