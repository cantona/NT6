inherit ROOM;

void create()
{
        set("short", "小村");
        set("long", @LONG
走在小村的石板路上，兩旁都是用青石砌成的房屋。村子裡靜悄
悄的，看不到行人，偶爾傳來一兩聲狗叫。 
LONG);
        set("outdoors", "wudujiao");

        set("exits", ([
                "northwest" : __DIR__"cun4",
                "northeast" : __DIR__"cun7",
                "southwest" : __DIR__"minju5",
                "southeast" : __DIR__"minju6",
        ]));

        setup();
}
