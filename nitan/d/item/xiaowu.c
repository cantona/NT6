// xiaoyuan.c

inherit ROOM;

#define GANJIANG        "/adm/npc/ganjiang"
#define MOYE            "/adm/npc/moye"

void create()
{
        object ob;

        set("short", "鑄劍室");
        set("long", @LONG
你一走進這個屋子，就感覺到有一股熱浪撲面而來。屋角有一個爐子，
裏面燃着熊熊火光，似乎無數的金蛇在你面前晃動。屋角堆放着一堆堆黑
乎乎的東西，不知道是什麼。
LONG );

        GANJIANG->come_here();
        MOYE->come_here();

        set("no_fight", 1);
        set("no_sleep_room", 1);

        set("exits", ([
                "out" : __DIR__"road5",
        ]));
        set("coor/x", 900);
        set("coor/y", -1060);
        set("coor/z", 0);
        setup();
}

void init()
{
        MYGIFT_D->check_mygift(this_player(), "newbie_mygift/ganjiang");
}


