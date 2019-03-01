// Room: /lingzhou/yipindayuan.c
// Java. Sep 21 1998

#include <room.h>

inherit ROOM;
void create()
{
        set("short", "一品堂大院");
        set("long", @LONG
這裡是西夏一品堂的大院，青石舖就的石板路，從大門直通正北面
那座構築巍峨的一品堂大廳。東面立著一個旗桿，桿上一面不知顏色的
錦旗挺精神地飄揚著，桿後是個低矮一些的回廊廳堂。西面一排平房看
那樣子也象是帳房。大院裡有幾棵老樹撐著幾片樹蔭，中央有一些武士
在練拳。
LONG );
        set("valid_startroom", 1);
        set("exits", ([
                "north"  : __DIR__"yipindating",
                "south"  : __DIR__"yipingate",
                "east"   : __DIR__"yipinjieyin",
                "west"   : __DIR__"yipinzhang",
        ]));
        set("objects", ([
                __DIR__"npc/yun" : 1,
                __DIR__"npc/yipinwushi" : 2,
        ]));
        set("coor/x", -6295);
        set("coor/y", 2955);
        set("coor/z", 0);
        setup();
        create_door("south" , "銅皮大門", "north" , DOOR_CLOSED);
        "/clone/board/yipin_b"->foo();
}
