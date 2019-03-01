inherit ROOM;

void create()
{
        set("short", "大觀園茶樓");
        set("long", @LONG
大觀園茶樓乃中州城內屈指可數的大茶樓，可是茶樓裡卻
沒幾個人。裡面好象有個樓梯往下，微微從下面透出的味道讓
人聞了頭有點發昏。
LONG);
        set("exits", ([
                  "east" : __DIR__"wendingnan2",
                  "down" : __DIR__"yanguan",
        ]));
        set("no_clean_up", 0);

        set("coor/x", -9050);
	set("coor/y", -1020);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}