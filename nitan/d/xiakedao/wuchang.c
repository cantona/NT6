// ROOM: /xiakedao/wuchang.c

inherit ROOM;
void create()
{
        set("short", "武場");
        set("long", @LONG
這是一個寬大的石洞，足可以裝下幾百人，兩旁放著十八般兵器
。四周零散的放著許多椅子，中間一大塊舖著猩紅色的地毯，武士們
可以在這比試武功。
LONG );
        set("exits", ([
                "west" : __DIR__"shibi",
        ]));
        set("objects", ([
                "/d/shaolin/npc/mu-ren" : 4,
        ]));
//        set("no_clean_up", 0);
        set("coor/x", -3070);
        set("coor/y", -25000);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}