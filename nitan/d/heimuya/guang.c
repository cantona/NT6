//ROM

inherit ROOM;

void create()
{
        set("short", "山谷");
        set("long", @LONG
這裡是一處山谷，上面種植著草坪。南面是『日月神教』的青龍
堂。向西有一條上山的石道。
LONG );
        set("outdoors", "heimuya");
        set("exits", ([
            "east" : __DIR__"linjxd1",
            "southup" : __DIR__"dating3",
            "west" : __DIR__"shidao1",
        ]));
        set("objects",([
            __DIR__"npc/kid" : 2,
        ]));
//        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}