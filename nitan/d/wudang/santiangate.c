inherit ROOM;

void create()
{
        set("short", "三天門");
        set("long", @LONG
這裏是登山石階的盡頭三天門，再往上走就是武當絕頂了。
LONG );
        set("exits", ([
                "northdown": __DIR__"ertiangate",
                "southup"  : __DIR__"jinding",
        ]));
        set("outdoors", "wudang");
        set("no_clean_up", 0);
        set("coor/x", -350);
        set("coor/y", -410);
        set("coor/z", 170);
        setup();
        replace_program(ROOM);
}