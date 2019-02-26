inherit ROOM;

void create()
{
        set("short", "明廊");
        set("long", @LONG
明廊的地板離地三尺，兩邊原來都是菜園子，自從東角門外住了
幫潑皮之後，這幾塊地裏再沒出過菜。東面還是走廊西面有個小門通
向素齋廚房，陣陣香味就從門中飄了出來。
LONG );
        set("no_clean_up", 0);
        set("exits", ([
                  "west" : __DIR__"chufang2",
                  "east" : __DIR__"zoulang2",
        ]));
        set("outdoors", "kaifeng");

	set("coor/x", -5020);
	set("coor/y", 2210);
	set("coor/z", 10);
	setup();
        replace_program(ROOM);
}