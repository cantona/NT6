//Room: bingying2.c

inherit ROOM;

void create ()
{
        set ("short", "兵營");
        set("long", @LONG
這裏是一座臨街而建的兵營，距離長安的北城門只有幾步之遙。
兵營門口旌旗飄揚，偶爾可以看見兵士進出換崗，並且不動聲色地巡
視着四周。兵營裏面到處都有官兵來來回回地走動，有一名武將正在
指揮士兵列隊操練。
LONG );
         set("exits", ([ /* sizeof() == 1 */
                 "northeast" : "/d/changan/beian-daokou",
         ]));
         set("objects", ([ /* sizeof() == 5 */
                 "/d/changan/npc/fujiang" : 1,
                 "/d/changan/npc/guanbing" : 4,
         ]));

         set("outdoors", "changan");
        set("coor/x", -10730);
	set("coor/y", 1960);
	set("coor/z", 0);
	setup();
         replace_program(ROOM);
}