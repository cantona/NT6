inherit ROOM;

void create()
{
        set("short", "小村");
        set("long", @LONG
走在小村的石板路上，兩旁都是用青石砌成的房屋。村子裏靜悄
悄的，看不到行人，偶爾傳來一兩聲狗叫。 
LONG);
        set("outdoors", "wudujiao");

        set("exits", ([
                "southwest" : __DIR__"cun4",
                "southeast" : __DIR__"cun7",
                "north" : __DIR__"minju4",
        ]));

        setup();
}