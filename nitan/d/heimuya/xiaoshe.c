//ROOM: xiaoshe.c

inherit ROOM;

void create()
{
        set("short", "小舍");
        set("long", @LONG
這是一間用翠竹搭成的小舍。一進門，便聞到一陣濃烈的花香，
房中掛著一幅仕女圖，椅上舖了繡花錦墊，東邊有一扇門，掛著繡了
一叢牡丹的錦緞門幃。難道這是誰家姑娘的閨房？
LONG );
        set("exits", ([
            "east" : __DIR__"neishi",
            "out" :__DIR__"xiaohuayuan",
        ]));
        set("no_clean_up", 0);
        setup();
        replace_program(ROOM);
}