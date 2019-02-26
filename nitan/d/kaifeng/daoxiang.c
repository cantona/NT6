inherit ROOM;

void create()
{
        set("short", "稻香居");
        set("long", @LONG
稻香居有三百年的歷史了。從這棟樓外面黑黑的招牌旗就能看出
來。不過裏面的食客還是挺多。桌子坐滿了人。樓上當然有雅座，不
過是要有一定身份地位的人才能上。
LONG );
        set("exits", ([
                "up" : __DIR__"daoxiang2",
                "west" : __DIR__"road2",
                "east" : __DIR__"majiu",
        ]));
        set("no_clean_up", 0);
        set("objects", ([
                __DIR__"npc/xiaoer" : 1,
        ]));

	set("coor/x", -5040);
	set("coor/y", 2250);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}