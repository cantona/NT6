// Room: /d/lingzhou/garden.c

inherit ROOM;

void create()
{
        set("short", "御花園");
        set("long", @LONG
這是皇宮裡的御花園，花團錦簇，百草飄香，雖不比江南水鄉般艷
麗，卻也別有一般風味。北面是佔園中一半面積的翠心湖，西面有條小
路通向一片紫竹林。
LONG
        );
        set("exits", ([ /* sizeof() == 3 */
                "south" : __DIR__"huilang2",
                "west" : __DIR__"zhulin",
                "east" : __DIR__"piandian",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "xixiagong");

        set("coor/x", -6275);
        set("coor/y", 2995);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}