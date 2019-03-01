// Feb. 6, 1999 by Winder
inherit ROOM;
void create()
{
        set("short", "小院子");
        set("long", @LONG
這裡是個小院子，打掃得甚為整潔，旁邊有棵大樹，院子內
放了一些掃把等雜物。往北是個不大的客廳。
LONG
        );
        set("outdoors","shiliang");
        set("no_clean_up", 0);
        set("exits", ([ 
            "southwest" : __DIR__"xiaodao1",
            "north" : __DIR__"xiaoting",
        ]));
        set("coor/x", 1620);
        set("coor/y", -1780);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}