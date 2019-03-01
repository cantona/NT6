inherit ROOM;

void create()
{
        set("short", "小花園");
        set("long", @LONG
這是縣太爺府前的小花園，花草樹木，鳥語花香。好一個
悠閒的地方。透過一簇牡丹花，北面就是縣太爺的府邸。西面
的廂房略微陳舊一點。可能是府內下人的屋子。
LONG);
        set("outdoors", "zhongzhou");

        set("exits", ([
                "west" : __DIR__"xiaren",
                "north" : __DIR__"taiyefu",
                "east" :__DIR__"zoulang", 
        ]));

        set("coor/x", -9070);
	set("coor/y", -970);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}