// Room: /qingcheng/zhuhezhuang.c
// Date: Frb.20 1998 by Java

inherit ROOM;
void create()
{
        set("short", "駐鶴莊");
        set("long", @LONG
駐鶴莊相傳為仙人休息賞玩之所。常有成羣丹頂鶴棲息、飛鳴
於林間。
LONG );
        set("outdoors", "qingcheng");
        set("exits", ([
                "south"    : __DIR__"tianran",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -8080);
        set("coor/y", -900);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}