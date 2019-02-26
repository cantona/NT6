inherit ROOM;

void create()
{
        set("short", "小村");
        set("long", @LONG
走在小村的石板路上，兩旁都是用青石砌成的房屋。東邊有一座
學堂，裏面傳來朗朗的讀書聲。 
LONG);
        set("outdoors", "wudujiao");

        set("exits", ([
                "northwest" : __DIR__"cun5",
                "southeast" : __DIR__"cun8",
                "southwest" : __DIR__"cun6",
                "east" : __DIR__"minju7",
        ]));

        setup();
}