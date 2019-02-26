// Room: /qingcheng/yinxing.c
// Date: Frb.20 1998 by Java

inherit ROOM;
void create()
{
        set("short", "古銀杏樹");
        set("long", @LONG
觀前古銀杏樹相傳為張天師手植，高可十餘丈，腰圍七、八人
合抱，枝葉扶疏，蒼蓋如雲。
LONG );
        set("outdoors","qingcheng");
        set("exits", ([
                "east"     : __DIR__"tianshidong",
        ]));
        set("objects", ([
                "/clone/medicine/vegetable/danggui" : random(2),
        ]));
        set("coor/x", -8110);
        set("coor/y", -910);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}