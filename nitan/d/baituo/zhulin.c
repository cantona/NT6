inherit ROOM;

void create()
{
        set("short", "竹林");
        set("long", @LONG
這裏是青竹林，常有蛇出沒。南邊是蒿草叢。北邊有一個大巖洞，
從裏面傳出一陣嘶嘶的聲音。
LONG );
        set("outdoors", "baituo");
        set("exits",([
                "northup" : __DIR__"cave",
                "south"   : __DIR__"cao2",
        ]));
        set("objects",([
                "/clone/beast/qingshe" : random(3),
                "/clone/beast/dushe" : random(2),
        ]));
        set("quarrys", ([
                "caihuashe"  : 100000,
                "dushe"      : 50000,
                "jinshe"     : 40000,
                "qingshe"    : 40000,
                "yanjingshe" : 5000,
                "mangshe"    : 3000,
        ]));
        set("coor/x", -50000);
        set("coor/y", 20040);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}