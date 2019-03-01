// Room: /d/lingzhou/hut.c

inherit ROOM;

void create()
{
        set("short", "竹林小屋");
        set("long", @LONG
你面前是一間小屋。小屋亦是紫竹所制，一扇小門緊緊扣著，因為
竹屋與紫竹林渾然一色，不仔細看你很難發覺。竹蔭婆娑，竹葉沙沙，
你的心一緊，一股涼意直透脊背。
LONG
        );
        set("exits", ([ /* sizeof() == 2 */
                "east" : __DIR__"zhulin",
                "enter" : __DIR__"hut2",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "lingzhou");

        set("coor/x", -6295);
        set("coor/y", 2995);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}