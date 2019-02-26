// Room: /d/mingjiao/mjdimen.c
// Date: Java 97/05/11

#include <room.h>
inherit ROOM;

void create()
{
    set("short", "草地");
        set("long", @LONG
這是一片芳草地，落英繽紛，蜂歌蝶舞，朝露夕光，沁人心脾。
幾個小姑娘鶯聲曼影，頑皮可人，宛如三月桃李，臘冬嫩梅，惹人憐
愛。任你是江湖豪傑，走到這裏，心中也平添幾寸温柔，少卻三分殺
意。
LONG );
    set("exits", ([
        "northeast" : __DIR__"mjdimen1",
        "southwest" : __DIR__"mjsimen1",
    ]));
    set("no_clean_up", 0);
    set("outdoors", "mingjiao");
    setup();
    replace_program(ROOM);
}
