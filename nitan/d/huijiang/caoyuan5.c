// Room: /d/huijiang/caoyuan5.c
// Last Modified by winder on Sep. 12 2001

inherit ROOM;

void create()
{
        set("short", "草原");
        set("long", @LONG
這裏就是人跡罕至的大草原，一望無際的草地隨風波動，天地交接
處有幾個黑點，四周非常的安靜，只是不時有牧女清亮的歌聲不知從哪
兒飄渺的傳來.
LONG );
        set("outdoors", "huijiang");
        set("exits", ([
                "north" : __DIR__"caoyuan6",
                "south" : __DIR__"caoyuan4",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -50050);
        set("coor/y", 9110);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}