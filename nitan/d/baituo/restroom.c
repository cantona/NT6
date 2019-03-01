inherit ROOM;

void create()
{
        set("short", "休息室");
        set("long", @LONG
這是一家藥舖，一股濃濃的藥味讓你幾欲窒息，那是從藥櫃上的
幾百個小抽屜裡散發出來的。神醫平一指坐在茶幾旁獨自喝著茶，看
也不看你一眼。
LONG );
        set("exits",([
                "south" : __DIR__"changlang",
        ]));

        set("sleep_room", 1);
        set("no_fight", 1);
        set("no_steal", 1);

        set("coor/x", -49990);
        set("coor/y", 20030);
        set("coor/z", 30);
        setup();
        replace_program(ROOM);
}