//Room: /d/dali/cangshanlu1.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","蒼山山路");
        set("long",@LONG
此處正當河邊，兩側山壁幾乎是直上直下，面前是一條大河自北
滔滔而來，在此折向東咆哮而去，河水奔騰洶湧，拍擊河岸，發出一
陣陣駭人的轟響。這裡恰縫河灣，河床較窄，河谷上並無橋樑，只有
三根粗籐條橫跨兩岸，這端綁在一棵大樹上，似可攀援而過。
LONG);
        set("objects", ([
           __DIR__"npc/lieren": 1,
        ]));
        set("outdoors", "dalin");
        set("exits",([ /* sizeof() == 1 */
            "northeast"  : __DIR__"cangshanzhong",
            "west"       : __DIR__"heshang",
        ]));
	set("coor/x", -19190);
	set("coor/y", -6830);
	set("coor/z", 20);
	setup();
        replace_program(ROOM);
}