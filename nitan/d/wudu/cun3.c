inherit ROOM;

void create()
{
        set("short", "小村");
        set("long", @LONG
走在小村的石板路上，兩旁都是用青石砌成的房屋。村子裏靜悄
悄的，看不到行人，偶爾傳來一兩聲狗叫。 
LONG );
        set("outdoors", "wudujiao");

        set("exits", ([
                "east" : __DIR__"cun4",
                "west" : __DIR__"cun2",
                "north" : __DIR__"minju2",
        ]));
        set("objects", ([
                "/clone/npc/walker" : 1,
        ]));

        setup();
}