// /yubifeng/eastroom1.c
// Last modified by winder 2003.9.2

inherit ROOM;

void create()
{
        set("short", "劍房");
        set("long", @long
這裏原是杜莊主藏劍納寶之所。數十年來，他在這裏窮極山野，一
無所獲，這裏也就徒有四壁了。
long );
        set("exits", ([
                "west" : __DIR__"zoulang4",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 6140);
        set("coor/y", 5190);
        set("coor/z", 100);
        setup();
        replace_program(ROOM);
}