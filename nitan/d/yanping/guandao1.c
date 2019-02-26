// Room: /d/yanping/guandao1.c
// Date: Sep 28, 2002  Winder

inherit ROOM;

void create()
{
        set("short", "官道");
        set("long", @LONG
這裏密邇城郊，來往行人也漸漸多了起來。福州的官話聽起來刺耳
難懂，可是抑揚頓挫，別有一番風味。
    北面有股青煙冒起，似乎有家野店。
LONG );
        set("exits", ([
                "east"   : "/d/fuzhou/ximen",
                "north"  : __DIR__"jiusi",
                "westup" : __DIR__"guandao2",
        ]));
        set("no_clean_up", 0);
        set("outdoors", "yanping");
        set("coor/x", 1800);
        set("coor/y", -6300);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}