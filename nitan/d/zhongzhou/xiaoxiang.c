inherit ROOM;

void create()
{
        set("short", "小巷");
        set("long", @LONG
一條小巷不知通到何處，兩邊高牆院落，更顯的小巷的昏
暗。誰也不想在這種地方多呆，你只想往前走走，看看前面到
底通到哪裏。
LONG);

        set("outdoors", "zhongzhou");

        set("exits", ([
                "east" : __DIR__"wendingbei1",
                "west" : __DIR__"xiaoxiang1",
        ]));
        set("objects",([
                __DIR__"npc/dipi":1,
        ]));

        set("coor/x", -9050);
	set("coor/y", -990);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}