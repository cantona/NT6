// Feb. 6, 1999 by Winder
inherit ROOM;
void create()
{
        set("short", "湖心小島");
        set("long", @LONG
你來到湖心的小島上。這裡鳥語花香，彩蝶紛飛，景色宜人，空
氣中仿佛有種玉蘭香的味道。
LONG
        );
        set("outdoors","shiliang");
        set("no_clean_up", 0);
        set("exits", ([ 
            "south" : __DIR__"xiaodao",
            "northeast" : __DIR__"xiaoyuan"
        ]));
        set("coor/x", 1610);
        set("coor/y", -1790);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}