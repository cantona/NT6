//Room: /d/dali/shilin2.c
//Date: June. 29 1998 by Java

inherit ROOM;
void create()
{
        set("short","和摩賽石林");
        set("long", @LONG
舊名石門峯或石門峭，石質黝黑古樸，氣勢磅礴，有如大海怒濤
沖天而起，境巧細緻的東西較少，當你身臨其境，踏石磴，入石門，
撥野草，探幽林，但覺山禽鳴崗，危石森森，其間原野開闊，山風陣
陣，花香悠悠，一股強烈的山野味迎面而來，不加修飾的粗獷的自然
美，令人耳目一新。
LONG );
        set("outdoors", "dalin");
        set("objects",([
            "/d/wudang/npc/tufei1": 2,
            "/d/wudang/npc/tufei2": 1,
        ]));
        set("exits",([ /* sizeof() == 1 */
            "southwest"    : "/d/dali/changhu",
        ]));
	set("coor/x", -19150);
	set("coor/y", -6790);
	set("coor/z", 30);
	setup();
        replace_program(ROOM);
}