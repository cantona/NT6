// Room: /d/wuyi/5qu.c
// Last modified by Winder on Mar.20.2002

inherit ROOM;

void create()
{
        set("short", "五曲");
        set("long", @LONG
五曲北岸就是雲窩了，在南岸更衣台光潔碩大的巖壁上，清晰可見
“玉皇大天尊”五字題刻。這裡就是道教小洞天中的第十六洞天。朱熹
《九曲棹歌》曰：“……五曲山高雲氣深，長時煙雨暗平林。林間有客
無人識，唉乃聲中萬古心。……”
LONG );
        set("outdoors", "wuyi");
        set("no_clean_up", 0);
        set("exits", ([
                "north"     : __DIR__"yunwo",
                "south"     : __DIR__"yuchayuan",
                "southwest" : __DIR__"gengyitai",
                "northeast" : __DIR__"4qu",
                "northwest" : __DIR__"6qu",
        ]));
        set("no_clean_up", 0);
        set("coor/x", 1360);
        set("coor/y", -5020);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}
