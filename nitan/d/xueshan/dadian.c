inherit ROOM;

void create()
{
        set("short", "大殿");
        set("long", @LONG
 這裏是雪山寺的大殿，中央供奉着佛祖塑像。僧人們在念着經文，
所以這裏的香火很是旺盛。遠來的香客們在這裏虔誠地膜拜。大殿兩
側都是側殿。
LONG );
        set("exits", ([
                "east"  : __DIR__"cedian1",
                "west"  : __DIR__"cedian2",
                "south" : __DIR__"guangchang",
        ]));
        set("objects", ([
                CLASS_D("xueshan") + "/first" : 1,
                CLASS_D("xueshan") + "/lazhang" : 1,
                __DIR__"npc/xiang-ke" : 2,
        ]));
        set("valid_startroom", 1);
        setup();
        replace_program(ROOM);

        "/clone/board/xueshan_b"->foo();
}
