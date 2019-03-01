//ROOM: /d/yanziwu/chuantang.c

inherit ROOM;

void create()
{
        set("short", "穿堂");
        set("long", @LONG
不知是什麼能工巧匠設計了這條穿堂，九曲回折，雕樑畫棟。再
望南就是後院了，向北則是一座大廳堂。
LONG );
        set("exits", ([
            "south" : __DIR__"lixiang",
            "north" : __DIR__"cuixia",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}