//RJQMIDAO.C

inherit ROOM;

void create()
{
        set("short", "密道");
        set("long", @LONG
這裏是一條祕道的盡頭，石牆之上嵌入兩盞油燈，火苗倏忽，向
前望去，黑暗中不知所往。
LONG );
        set("exits", ([
                "north" : __DIR__"rjqjiguan",
//                "down" : __DIR__"rjqmenlou1",
        ]));
        set("no_clean_up", 0);
//        set("outdoors", "mingjiao");
        setup();
        replace_program(ROOM);
}
