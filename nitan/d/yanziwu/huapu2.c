// Room: /d/yanziwu/huapu2.c
// Date: Jan.28 2000 by Winder

inherit ROOM;

void create()
{
        set("short", "花圃");
        set("long", @LONG
這裡是蔓陀山莊中的花圃。花圃中擺了很多花盆和新泥，背蔭處花
盆裡多是新苗。四處散落著不少不知名的花兒，有繁有凋大凡茶花，皆
枝條窈窕，弱不勝風。
LONG );
        set("outdoors", "mantuo");
        set("exits", ([
                "north"  : __DIR__"path6",
                "west"   : __DIR__"huapu1",
        ]));
        set("objects", ([
                __DIR__"obj/mutong" : 1,
                "/d/dali/obj/chahua10" : 1,
        ]));
        set("coor/x", 1250);
        set("coor/y", -1280);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}