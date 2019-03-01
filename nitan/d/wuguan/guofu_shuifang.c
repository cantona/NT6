inherit ROOM;

void create()
{
    set("short", "水房");
    set("long", @LONG
一進屋，你看見屋內放著幾口大缸，好象是裝水用的，不
過缸似乎都是空的，這裡沒有一個人，估計僕人都跑了。
LONG);
        set("no_fight", 1);
        set("exits", ([
             	"east" : __DIR__"guofu_houyuan",
        ]) );
        set("outdoors", "xiangyang");
        setup();
        replace_program(ROOM);
}