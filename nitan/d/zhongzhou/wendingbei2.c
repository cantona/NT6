inherit ROOM;

void create()
{
        set("short", "文定北街");
        set("long", @LONG
這是中州城文定北街，寬敞的街道讓人不竟心情一暢。街
道的東面有一間藥鋪。走到這裏就可以聞見濃濃的藥味。西面
人聲鼎沸，原來是一座戲院子。
LONG);

        set("outdoors", "zhongzhou");
        set("exits", ([
                "east" : __DIR__"yaopu",
                "south" : __DIR__"wendingbei1",
                "west" : __DIR__"xiyuan",
                "north" : __DIR__"wendingbei3",
        ]));
        set("objects", ([
                __DIR__"npc/shusheng" : 1,
        ]));

        set("coor/x", -9040);
	set("coor/y", -980);
	set("coor/z", 0);
	setup();
        replace_program(ROOM);
}