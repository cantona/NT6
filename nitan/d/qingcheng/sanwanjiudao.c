// Room: /qingcheng/sanwanjiudao.c
// Date: Frb.20 1998 by Java

inherit ROOM;
void create()
{
        set("short", "三彎九倒");
        set("long", @LONG
山勢越來越陡峭，石梯幾近壁立，拐過觀日亭，遠遠看到青城
山巔，高台山之陽的飛檐流瓦，上清宮到了。
LONG );
        set("outdoors","qingcheng");
        set("exits", ([
                "southdown"  : __DIR__"chaoyangdong",
                "eastup"    : __DIR__"shangqing",
        ]));
        set("coor/x", -8090);
        set("coor/y", -880);
        set("coor/z", 70);
        setup();
        replace_program(ROOM);
}