// Room: /d/yanziwu/ouxiang2.c
// Date: Jan.28 2000 by Winder

inherit ROOM;

void create()
{
        set("short", "藕香小居");
        set("long", @LONG
藕香小築建得小巧玲瓏。小築四周栽滿了湘妃竹，湖面和風催動，
頓時就嘩啦啦響成一片。小居四面臨窗，窗下一排排矮櫃，擺放着的都
是武功祕籍。案頭一支小兒臂粗的蠟燭已經燒了一半，長長的燭淚垂了
下來，把整支蠟燭固定在書案上。
LONG );
        set("exits", ([
                "down"  : __DIR__"ouxiang1",
        ]));
        set("objects", ([
                __DIR__"npc/wang" : 1,
        ]));
        set("coor/x", 1200);
        set("coor/y", -1230);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}