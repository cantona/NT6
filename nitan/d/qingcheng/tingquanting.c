// Room: /qingcheng/tingquanting.c
// Date: Frb.20 1998 by Java

inherit ROOM;
void create()
{
        set("short", "聽泉亭");
        set("long", @LONG
沿石梯向下，就是海棠溪。這裡是溪上的聽泉亭，四顧山環水
繞，古籐蔓蔓，飛泉濺落池中，如琴弦輕撥，如珠落玉盤，清絕幽
絕。
LONG );
        set("outdoors","qingcheng");
        set("exits", ([
                "westup"   : __DIR__"sandaoshi",
        ]));
        set("objects", ([
                __DIR__"npc/dizi" : 1,
        ]));
//        set("no_clean_up", 0);
        set("coor/x", -8080);
        set("coor/y", -910);
        set("coor/z", 20);
        setup();
        replace_program(ROOM);
}