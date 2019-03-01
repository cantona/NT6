// Room: /d/wuyi/liuxiangjian.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "流香澗");
        set("long", @LONG
流水潺潺，巖壑縱深。花香鳥語，意境幽雅。這裡就是天心巖北麓
的流香澗。是仙女沐浴時洒落的胭脂，還是澗邊花草染出的清香？走進
流香澗這條悠深的狹谷，崖壁聳立，青籐垂蔓，野花叢生。一路行去，
流水聲響與飛花相隨不舍，淡淡幽香，不盡飄來。
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "south"     : __DIR__"path10",
                "northeast" : __DIR__"path12",
                "southeast" : __DIR__"path11",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1380);
        set("coor/y", -4930);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
