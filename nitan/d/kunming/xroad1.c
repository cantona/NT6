inherit ROOM;

void create()
{
        set("short", "官道");
        set("long", @LONG
這是一條向南的黃土官道，兩旁是一片片綠油油的水田和
悠閒的牧童。大道上人流熙熙攘攘，過往的行人頂著炎炎烈日
滿頭大汗的匆匆趕路，似乎並無心欣賞這優美的田園風光。
LONG);
        set("outdoors", "kunming");
        set("exits", ([
                "west" : __DIR__"xroad2",
                "east" : __DIR__"xiaoximen",
        ]));
	set("coor/x", -16870);
	set("coor/y", -7210);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}