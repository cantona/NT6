// Room: /heizhao/shanlu1.c
// Date: Dec. 8 1999 by Winder

inherit ROOM;

void create()
{
        set("short", "密林矮樹");
        set("long", @LONG
這裡荒無人煙，舉步踏到的盡是矮樹長草，哪裡有路可尋？每
走一步，荊棘都鉤刺到小腿，也不覺疼痛，走了一陣，四周林木漸
密，你一步一步走得很慢，只恐一個踏空，跌入山溝陷坑之中。
LONG );
        set("outdoors", "heizhao");
        set("no_clean_up", 0);

        set("exits", ([
                "east" : "/d/henshan/hsroad6",
                "west" : __DIR__"maze1",
        ]));
        set("coor/x", -3000);
        set("coor/y", -1500);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}