// Room: /d/xingxiu/kezhan2.c
// Last Modified by winder on Apr. 25 2001

inherit ROOM;
void create()
{
        set("short", "客棧二樓");
        set("long", @LONG
這裡是伊犁城最大客棧的二樓，樓下人聲沸騰，不時飄上來一陣陣香噴
噴的烤羊肉味。你如果累了可以在床上舒舒服服地睡一覺。
LONG);
        set("sleep_room", 1);
        set("no_fight", 1);
        set("exits", ([ 
             "down" : __DIR__"kezhan",
        ]));
        set("objects", ([
                __DIR__"npc/yin": 1,
        ]));
        set("coor/x", -39000);
        set("coor/y", 13100);
        set("coor/z", 10);
        setup();
        replace_program(ROOM);
}