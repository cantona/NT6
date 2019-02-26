// Room: /d/kunlun/liangong.c 練功房
// Last Modified by Winder on Nov. 15 2000

inherit ROOM;

void create()
{
        set("short", "練功房");
        set("long", @LONG
這裏是練功房，地下凌亂地放着幾個蒲團，擺滿了大刀長劍、沙袋
綁腿等，是崑崙弟子日常練功的地方。
LONG
        );
        set("exits", ([
                "southwest" : __DIR__"jiuqulang4",
        ]));
        set("objects", ([
                "/d/shaolin/npc/mu-ren" : 5,
        ]));
        set("coor/x", -119970);
        set("coor/y", 40120);
        set("coor/z", 90);
        setup();
        replace_program(ROOM);
}