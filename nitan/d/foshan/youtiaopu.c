inherit ROOM;

void create()
{
        set("short", "油條鋪");
        set("long", @LONG
這家燒餅油條鋪是新開張的。鋪面不大，正中央擺了一個大炸鍋
和一個烤爐。
LONG );
        set("outdoors", "foshan");
        set("exits", ([
                "south" : __DIR__"street4",
        ]));
	set("coor/x", -6560);
	set("coor/y", -9740);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}