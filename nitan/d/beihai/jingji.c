// /d/beihai/jingji.c
// Last Modified by winder on May. 22 2002

inherit ROOM;

void create()
{
        set("short", "敬躋堂");
        set("long", @LONG
這裏是承光殿北的敬躋堂，闊十五間，緣城牆成環抱之勢。臨窗眺
望，可以一覽北海南面的風光。堂內整齊的放着幾把檀木椅子。中間是
一張八仙桌。雖然不經常有人來坐，卻仍然被打掃的一塵不染。
LONG
        );
        set("exits", ([
                "south" : __DIR__"chengguang",
        ]));
        set("outdoors", "beihai");
        set("no_clean_up", 0);

        set("coor/x", -180);
        set("coor/y", 4060);
        set("coor/z", 0);
        setup();
        replace_program(ROOM);
}
