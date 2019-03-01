// Room: /qingcheng/yuanyangjing.c
// Date: Frb.20 1998 by Java

inherit ROOM;
void create()
{
        set("short", "鴛鴦井");
        set("long", @LONG
上清殿左有鴛鴦井，一方一圓，泉流暗通。圓者水濁，方者水
清。井水一溫一涼，昔人題詩曰：“誰知上界神仙客，也與炎涼世
態同”。
LONG );
        set("outdoors","qingcheng");
        set("resource/water", 1);
        set("exits", ([
                "east"     : __DIR__"shangqing",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -8090);
        set("coor/y", -880);
        set("coor/z", 80);
        setup();
        replace_program(ROOM);
}