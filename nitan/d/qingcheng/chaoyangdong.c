// Room: /qingcheng/chaoyangdong.c
// Date: Frb.20 1998 by Java

inherit ROOM;
void create()
{
        set("short", "朝陽洞");
        set("long", @LONG
你來到朝陽洞。洞深廣數丈，相傳是寧封子棲息處。這裡也是
觀日好去處，“古洞常臨光照耀”，正是指旭日東升，霞光透過綠
蔭，射到洞口，一片璀燦絢麗的景色。
LONG );
        set("outdoors","qingcheng");
        set("exits", ([
                "westdown"  : __DIR__"zushidian",
                "northup"   : __DIR__"sanwanjiudao",
        ]));
        set("objects", ([
                __DIR__"npc/dizi" : 1,
        ]));
//        set("no_clean_up", 0);
        set("coor/x", -8090);
        set("coor/y", -890);
        set("coor/z", 60);
        setup();
        replace_program(ROOM);
}