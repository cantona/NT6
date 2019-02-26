// Room: /qingcheng/zoulang1.c
// Date: Aug. 10 1998 by Winder

inherit ROOM;
void create()
{
        set("short", "松風走廊");
        set("long", @LONG
這裏是松風觀中連貫前殿後院的走廊，松風觀高矗山頂，從走廊望
去，青山鳥寂，幽谷風生，漫天薄霧時時彌散在長林翠竹之間。自古號
稱：“青城天下幽”，不妨在此體味。
LONG );
        set("outdoors", "qingcheng");
        set("exits", ([
                "south" : __DIR__"zhongmen",
                "north" : __DIR__"caochang",
        ]));
        set("no_clean_up", 0);
        set("coor/x", -8080);
        set("coor/y", -850);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}