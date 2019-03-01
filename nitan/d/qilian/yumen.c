// Room: /d/qilian/yumen.c
// Winder 2000/09/05 

inherit ROOM;

void create()
{
        set("short", "玉門");
        set("long", @LONG
這裡是西北的一處調兵站，北對蒙古，西衛青海，尤其是在漢代，
玉門是中原和西域間的一大要塞。北方是哈拉湖，西方是玉門關。
LONG );
        set("outdoors", "qilian");
        set("no_clean_up", 0);
        set("exits", ([
                "southwest" : "/d/xingxiu/jiayuguan",
                "north"     : __DIR__"halahu",
        ]));
        set("coor/x", -17000);
        set("coor/y", 1000);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}