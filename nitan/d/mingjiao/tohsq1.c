//TOHSQ1.C

inherit ROOM;

void create()
{
        set("short", "山路");
        set("long", @LONG
這裏是一條很普通的山路，路邊的樹林密集，芳草流香，草叢中
星星點點地點綴着一些白色野花，一股清泉叮叮咚咚地向山下流淌，
遠處傳來陣陣水聲，為這山谷陡增了幾分氣勢。
LONG );
        set("exits", ([
                "southeast" : __DIR__"torjq3",
                "northwest" : __DIR__"tohsq2",
        ]));
        set("outdoors", "mingjiao");
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}